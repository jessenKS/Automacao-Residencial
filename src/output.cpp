#include "output.h"

void init_output()
{
    for(int i = 2; i <= SIR; i++)
    {
        pinMode(i , OUTPUT);
        digitalWrite(i, OFF);
    }
    digitalWrite(EN1, ON);
    digitalWrite(EN2, ON);
}

int ajustaAr(int value)
{
    switch (value)
    {
        case 17:
            return value = 87;
            break;
        case 18:
            return value = 92;
            break;
        case 19:
            return value = 97;
            break;
        case 20:
            return value = 102;
            break;
        case 21:
            return value = 107;
            break;
        case 22:
            return value = 112;
            break;
        case 23:
            return value = 118;
            break;
        case 24:
            return value = 123;
            break;
        case 25:
            return value = 128;
            break;
    }
    return 0;
}

void write_init_output(String msg)
{
    int ar = ((msg[7]-'0')*10 + (msg[8]-'0')), banda = ((msg[9]-'0')*10 + (msg[10]-'0')); 						
    // debug
    Serial.print("Temp AR: ");
    Serial.println(ar);
    ar = ajustaAr(ar);
    analogWrite(ARC, ar);
    Serial.print("Banda morta:");
    Serial.println(banda);
    
    // Resposta com o valor atual da entrada..
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}

void write_output(String msg)
{
    //Escrever em uma saída          
    // string para inteiro aplicando offset, saida 1 no Arduino está mapeada para o pino 8, saída 2 para o pino 9 ....
    int coil = ((msg[5]-'0')*10 + (msg[6]-'0')) + OUTPUT_OFFSET;
    int value = (msg[7]-'0')*1000 + (msg[8]-'0')*100 + (msg[9]-'0')*10 +(msg[10]-'0');
    
    /** debug 
    *? MSG :03 // validacao e escravo
    *? 05 
    *! 00   // saida 
    *! 0255 // (DADO) recebe posicao da cortina ou brilho da lampada
    *? LRC
    *  TODO: cortina 1 = OUT1, OUT2, EN1
    *  TODO: cortina 2 = OUT3, OUT4, EN2
    */

    switch (coil)
    {
        case LAM_D:
        {
            analogWrite(coil, value);
            break;
        }
        case LAM_R:
        {
            analogWrite(coil, value);
            break;
        }/*
        case EN1:
        {
            funcaoTeste(value, DINE);
            break;
        }
            
        case EN2:
        {
            funcaoTeste(value, ROOM);
            break;
        }       */
    }

    value = map(value, 0, 255, 0, 100);
    // int para string
    char buf[5];
    sprintf(buf,"%04d", value);

    // monta valor de retonro
    msg[7]=buf[0];
    msg[8]=buf[1];
    msg[9]=buf[2];
    msg[10]=buf[3];

    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}

void funcaoTeste(int value, int sensor)
{
    int mot, hora[2] = {OUT1, OUT3}, anti[2] = {OUT2, OUT4};
    if (sensor == DINE)
        mot = 0;
    else 
        mot = 1;

    int lado = analogRead(sensor);
    lado = map(lado, 0, 1023, 0, 255);

    Serial.print("Lado: ");
    Serial.println(lado);
    Serial.print("Value: ");
    Serial.println(value);

    if (value > lado) 
    {
        digitalWrite(hora[mot],  ON);
        digitalWrite(anti[mot], OFF);
    }
        
    else if(value < lado)
    {
        digitalWrite(anti[mot],  ON);
        digitalWrite(hora[mot], OFF);
    }
    else
    {
        digitalWrite(hora[mot], OFF);
        digitalWrite(anti[mot], OFF);
    }
}

void analog_write_output(String msg)
{
    // decodifica entrada a ser lida
    int aon = ((msg[5]-'0')*10 + (msg[6]-'0')) + ANALOG_OUTPUT_OFFSET;
    // de string para inteito
    int value = (msg[7]-'0')*1000 + (msg[8]-'0')*100 + (msg[9]-'0')*10 +(msg[10]-'0');
    
    // debug
    Serial.print("Escrita na Saida Analogica ");
    Serial.println(aon-ANALOG_OUTPUT_OFFSET);
    Serial.print("Valor: ");
    Serial.println(value);

    value = ajustaAr(value);
    
    //escreve na saída
    analogWrite(aon, value);
    
    // Para esse caso, a resposta é um simples echo da mensagem original
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}