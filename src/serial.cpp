#include "serial.h"

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

				/*/compara se o LRC da msg é igual ao calculado
				
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
					int cmd = (msg[3]-'0')*10 + (msg[4]-'0');

					switch (cmd)
					{
						case READ_COIL:
						{
							read_init_output(msg);
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
							//analog_read_input(msg);
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
	*?msg = : 03 03 00 
	*! 54 - temperaturaBanheiro(00) 
	*! 55 - Anemômetro(000) 
	*! 56 - cortina1(000) 
	*! 57 - cortina2(000)
	*! 58 - lampadaQuarto(000) 
	*! 59 - lampadaSala(000)
	*! 10 - sirene(0) 
	*! 11 - porta(0)
	*! 12 - temperaturaSala(00) 
	*! LRC (00)
	*/
	Serial.println("Atualizou a tela");
    //int ain = ((msg[5]-'0')*10 + (msg[6]-'0')) + ANALOG_INPUT_OFFSET; //FF00
	
	uint16_t atualiza[9];
	int merda, porta[9] = {54, 55, 56, 57, 58, 59, 10, 11, 12}, aux;
	char buf[4], envia[1], temp[2];

	Serial.print("Temperatura: ");
	Le_temperatura();
	Serial.println(temperatura);
	atualiza[0] = temperatura;
	sprintf(temp,"%02d", atualiza[0]);
	msg[7]   = temp[0];
	msg[8]   = temp[1];

	aux = 9;

	for (int i = 1; i < 6; i++, aux+=3)
	{
		atualiza[i] = analogRead(porta[i]);
		Serial.print("Leitura analogica: ");
		Serial.println(atualiza[i]);

		atualiza[i] = map(atualiza[i], 0, 1023, 0, 100);
		
		sprintf(buf,"%03d", atualiza[i]);

		// monta valor de retorno
		msg[aux]   = buf[0];
		msg[aux+1] = buf[1];
		msg[aux+2] = buf[2];
	}
	/**
	*? SIRENE*/
	digitalWrite(porta[6], ON);
	merda = digitalRead(porta[6]);
	Serial.print("Estado saida: ");
	Serial.println(merda);
	sprintf(envia,"%01d", merda);
	msg[24]   = envia[0];

	/**
	*? PORTA*/
	merda = digitalRead(porta[7]);
	Serial.print("Estado entrada: ");
	Serial.println(merda);
	sprintf(envia,"%01d", merda);
	msg[25]   = envia[0];
	
	/*
    // executao comando
    uint16_t value = analogRead(ain);
    
    // int para string
    char buf[5];
    sprintf(buf,"%04d", value);

    // monta valor de retonro
    msg[7]=buf[0];
    msg[8]=buf[1];
    msg[9]=buf[2];
    msg[10]=buf[3];
    
    // Responde para o mestre
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
    //default:
	*/
	// Responde para o mestre
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
    //default:
}