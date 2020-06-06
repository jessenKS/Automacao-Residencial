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

    // Ligada ou desligada?
    if(digitalRead(contact))
    {
        msg[7]='F';
        msg[8]='F';
        msg[9]='0';
        msg[10]='0';
    }
    else
    {
        msg[7]='0';
        msg[8]='0';
        msg[9]='0';
        msg[10]='0';
    }
    
    // Resposta com o valor atual da entrada..
    Serial.print("Resposta do Escravo: ");
    Serial.println(msg);
}

void analog_read_input(String msg)
{
    // decodifica entrada a ser lida
    int ain = ((msg[5]-'0')*10 + (msg[6]-'0')) + ANALOG_INPUT_OFFSET;

    // debug
    Serial.print("Leitura na Entrada Analogica ");
    Serial.println(ain-ANALOG_INPUT_OFFSET);

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
}