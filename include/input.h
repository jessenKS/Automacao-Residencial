#ifndef INPUT_H_
#define INPUT_H_

#include <Arduino.h>
#include "serial.h"
#include "lm35.h"

#define INPUT_OFFSET 13 // offset entradas 
#define DOOR 14 

#define ANALOG_INPUT_OFFSET 54
#define WIND 55 //Anemômetro - ler continuamente 

// sensores cortinas
#define DINE 56
#define ROOM 57

void init_input();
void read_input(String msg);

#endif