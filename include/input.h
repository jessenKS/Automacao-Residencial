#ifndef INPUT_H_
#define INPUT_H_

#include <Arduino.h>
#include "serial.h"
#include "lm35.h"

#define INPUT_OFFSET 11 // offset entradas 
#define DOOR 12 // sensor porta

/* mapeamento das entradas analógicas */
#define ANALOG_INPUT_OFFSET 1
#define WIND A0 //Anemômetro - ler continuamente 

// sensores cortinas
#define DINE A2
#define ROOM A3

extern void init_input();
extern void read_input(String msg);
extern void analog_read_input(String msg);

#endif