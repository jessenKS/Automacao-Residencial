#include "output.h"

void init_output()
{
    for(int i = 2; i <= SIR; i++)
    {
        pinMode(i ,OUTPUT);
        digitalWrite(i, OFF);
    }
    pinMode(LAM_D ,OUTPUT);
    pinMode(LAM_R ,OUTPUT);
    pinMode(ARC   ,OUTPUT);
}

void read_init_output(String msg)
{
    int /*coil = ((msg[5]-'0')*10 + (msg[6]-'0')),*/ ar = ((msg[7]-'0')*10 + (msg[8]-'0')), banda = ((msg[9]-'0')*10 + (msg[10]-'0')); 						
    // debug
    Serial.print("Temp AR: ");
    Serial.println(ar);
    Serial.print("Banda morta:");
    Serial.println(banda);

    /*

    if(msg[7]=='F' && msg[8]=='F' && msg[9]=='0' && msg[10]=='0')
    {
        value = ON;
        Serial.println(" -> Mudar para Ligado");
    }*/
    
    // Resposta com o valor atual da entrada..
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}

void write_output(String msg)
{
    //Escrever em uma saída          
    // string para inteiro aplicando offset, saida 1 no Arduino está mapeada para o pino 8, saída 2 para o pino 9 ....
    int coil = ((msg[5]-'0')*10 + (msg[6]-'0')) + OUTPUT_OFFSET;

    // padrao é desligar
    int value = OFF;

    // debug
    Serial.print("Escrita na Saida ");
    Serial.println(coil-OUTPUT_OFFSET);

    // ligar ou desligar?
    if(msg[7]=='F' && msg[8]=='F' && msg[9]=='0' && msg[10]=='0')
    {
        value = ON;
        Serial.println(" -> Mudar para Ligado");
    }
    else if(msg[7]=='0' && msg[8]=='0' && msg[9]=='0' && msg[10]=='0')
    {
        value = OFF;
        Serial.println(" Mudar para Desligado");
    }
    // executao comando
    digitalWrite(coil, value);
    
    // Para esse caso, a resposta é um simples echo da mensagem original
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
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

    //escreve na saída
    analogWrite(aon, value);
    
    // Para esse caso, a resposta é um simples echo da mensagem original
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}