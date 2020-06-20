#include "input.h"

void init_input()
{
    // configura entradas
    pinMode(DOOR, INPUT);
    pinMode(LM35, INPUT);
    pinMode(WIND, INPUT);
    pinMode(DINE, INPUT);
    pinMode(ROOM, INPUT);
}

void read_input(String msg) // funcao para ligar sirene se 
{
    // numero da entrada
    int contact = ((msg[5]-'0')*10 + (msg[6]-'0')) + INPUT_OFFSET; 

    // debug
    Serial.print("Leitura na Entrada ");
    Serial.println(contact-INPUT_OFFSET);

    contact =  digitalRead(contact); // testa estado da porta

    // Ligada ou desligada?
    if(contact == 1)
    {
        msg[7]='0';
        msg[8]='0';
        msg[9]='0';
        msg[10]='0';
        digitalWrite(SIR, OFF);
    }
    else
    {
        msg[7]='F';
        msg[8]='F';
        msg[9]='F';
        msg[10]='F';
        digitalWrite(SIR, ON);
    }
    // Resposta com o valor atual da entrada..
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}
