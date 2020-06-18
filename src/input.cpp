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

void read_input(String msg)
{
    // numero da entrada
    int contact = ((msg[5]-'0')*10 + (msg[6]-'0')) + INPUT_OFFSET; 

    // debug
    Serial.print("Leitura na Entrada ");
    Serial.println(contact-INPUT_OFFSET);

    contact =  digitalRead(contact);

    // Ligada ou desligada?
    if(contact == 1)
    {
        msg[7]='F';
        msg[8]='F';
        msg[9]='0';
        msg[10]='0';
        digitalWrite(SIR, ON);
    }
    else
    {
        msg[7]='0';
        msg[8]='0';
        msg[9]='0';
        msg[10]='0';
        digitalWrite(SIR, OFF);
    }
    // Resposta com o valor atual da entrada..
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}

int analog_read_input(int porta)
{
    // executao comando
    uint16_t value = analogRead(porta);
    
    // int para string
    char buf[5];
    sprintf(buf,"%04d", value);

    // monta valor de retonro
    /*
    msg[7]=buf[0];
    msg[8]=buf[1];
    msg[9]=buf[2];
    msg[10]=buf[3];
    */
    return 0;
}