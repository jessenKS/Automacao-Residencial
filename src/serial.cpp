#include "serial.h"
#include <string.h>

void init_serial()
{
	Serial.begin(9600);
    Serial.println("Sistema Iniciado");
}

void msgHandler()
{
	if (Serial.available() > 0)
	{
		while(Serial.available() > 0 )
		{
			// ler até encontrar LF
			int tam;
			String msg, usar;
			msg = Serial.readStringUntil('\n');
			usar = msg;

			//teste
			Serial.print("Msg recebida: ");
			Serial.println(msg);
			
			while(msg[tam] != '\0')
				++tam;

			if(tam == 13) tam-=1;
			else if(tam == 14) tam-=2;
			
			//início válido
			if(msg[0] == ':')
			{
				Serial.println("Caracter de inicio (:) encontrado");
				//Cálculo LRC
				
				int j = 0, i;
				uint8_t dado[VAL], t, valor = 0;
				
				for (i = 1; i <= tam; i+=2)  //conversao para decimal   
				{                                  
					if (msg[i] > '9' && msg[i+1] > '9')
						dado[j] = ((usar[i]-'7'))*16 + ((usar[i+1]-'7'));
					
					else if (msg[i] > '9')
						dado[j] = ((usar[i]-'7'))*16 + (usar[i+1]-'0');
					
					else if (msg[i+1] > '9')
						dado[j] = (usar[i]-'0')*16 + ((usar[i+1]-'7'));
					
					else
						dado[j] = (usar[i]-'0')*16 + (usar[i+1]-'0');
						
					j++;
				}
				
				t = (uint8_t)(sizeof(dado)) - 1;
				valor = lrc(dado, t); //cálculo do lrc
				
				Serial.print("Valor LRC ");
				Serial.println(valor);

				Serial.print("Valor dado ");
				Serial.println(dado[t]);
				/*
				//compara se o LRC da msg é igual ao calculado
				
				if (valor == dado[t])
					Serial.println("LRC correto");
				else
				{
					Serial.println("LRC incorreto");
					break;
				}*/

				//ve para qual escravo é a mensagem
				if(msg[1]==SLAVE_ADR[0] && msg[2]==SLAVE_ADR[1] )
				{
					Serial.println("Endereço do escravo correto");
					
					//processa a mensagem
					int cmd = (msg[3]-'0')*10 + (msg[4]-'0'), banda;

					switch (cmd)
					{
						case READ_COIL:
						{
							banda = write_init_output(msg);
							break;
						}
							
						case READ_INPUT:
						{
							read_input(msg);
							break;
						}

						case UPDATE_SCREEN:
						{
							update_screen(msg);
							break;
						}
							
						case WRITE_COIL:
						{  
							write_output(msg);
							break;
						}
						case READ_ANALOG:
						{ 
							write_sol(msg);
							break;
						}

						case WRITE_ANALOG:
						{
							analog_write_output(msg);
							break;
						}
					}
				}
				else
					Serial.println("Mensagem para outro escravo");
			}
			else
				Serial.println("Comando desconhecido");
		}
	}
}

uint8_t lrc(uint8_t *dado, uint8_t t)
{
	uint8_t val_lrc = 0;
	for(int i = 0; i < t; i++)
	{
		if((val_lrc + dado[i]) & 0xFF)
		val_lrc = val_lrc + dado[i];
	}
	val_lrc = ((val_lrc^0xFF) + 1) & 0xFF;

	return val_lrc;
}

void update_screen(String msg)
{
	/**
	*? msg = : 03 03 00 
	*? 54 - temperaturaBanheiro(00) 
	*? 55 - Anemômetro(000) 
	*? 56 - cortina1(000) 
	*? 57 - cortina2(000) 
	*? 12 - sirene(0) 
	*? 14 - porta(0) 
	*! 15 - temperaturaSala(00)
	* todo Valor range cortina1 
	* todo Valor range cortina2 
	*? LRC (00) 
	*/
	int atualiza[3];
	int passa, val, aux, temperatura, tempSala, d, u, vento, porta[3] = {WIND, DINE, ROOM};
	char buffer[4], envia[1], temp[2];
	int cortinaRoom = (msg[22]-'0')*100 + (msg[23]-'0')*10 +(msg[24]-'0');
	int cortinaDine = (msg[25]-'0')*100 + (msg[26]-'0')*10 +(msg[27]-'0');

	temperatura = Le_temperatura(); 
	sprintf(temp,"%02d", temperatura);
	msg[7]   = temp[0];
	msg[8]   = temp[1];

	aux = 9;

	for (int i = 0; i < 3; i++, aux+=3)
	{	
		atualiza[i] = analogRead(porta[i]);
		Serial.print("Leitura analogica: ");
		Serial.println(atualiza[i]);

		if(porta[i] == DINE && porta[i] == ROOM)
			atualiza[i] = map(atualiza[i], 0, 1023, 0, 100);

		if(porta[i] == WIND)
		{
			val = (5 * atualiza[i])/1023;
  			vento = atualiza[i] = int((val - PARAMETRO1)/PARAMETRO2);
		}
		
		else if (porta[i] == DINE)
			atualiza[i] = funcaoTeste(cortinaDine, porta[i], vento);
		else if(porta[i] == ROOM)
			atualiza[i] = funcaoTeste(cortinaRoom, porta[i], vento);

		sprintf(buffer,"%03d", atualiza[i]);

		// monta valor de retorno
		msg[aux]   = buffer[0];
		msg[aux+1] = buffer[1];
		msg[aux+2] = buffer[2];
	}
	/**
	*? PORTA*/
	passa = digitalRead(DOOR);
	Serial.print("Porta: ");
	Serial.println(passa);
	//sprintf(envia,"%01d", passa);
	msg[19]   = passa+'0';

	if(passa == 1)
		digitalWrite(SIR, OFF);
	
	/**
	*? SIRENE*/
	passa = digitalRead(SIR);
	Serial.print("Sirene: ");
	Serial.println(passa);
	sprintf(envia,"%01d", passa);
	msg[18]   = envia[0];
	
	
	tempSala = read_ds18b20();
	/*
	!sprintf(sala,"%02d", tempSala);
	*/
 	d = (tempSala/10); 
 	u = (tempSala-(d*10));
	msg[20] = d+'0';
	msg[21] = u+'0';
	

	// Responde para o mestre
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
    //default:
}
