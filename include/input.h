#ifndef INPUT_H_
#define INPUT_H_

#include <Arduino.h>
#include "serial.h"
#include "lm35.h"

#define INPUT_OFFSET 11 // offset entradas 
#define DOOR 12 // sensor porta

#define ANALOG_INPUT_OFFSET 54
#define WIND 55 //Anemômetro - ler continuamente 

// sensores cortinas
#define DINE 56
#define ROOM 57

extern void init_input();
extern void read_input(String msg);
extern void analog_read_input(String msg);

#endif