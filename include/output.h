#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <Arduino.h>
#include "serial.h"
#include "input.h"

/* mapeamento das saÃ­das */
//enum {OUT1=8, OUT2, OUT3, OUT4} OUTPUTS;
enum{OUTPUT_OFFSET = 1, LAM_D, LAM_R, EN1, EN2, OUT1, OUT2, OUT3, OUT4, SOLE, ARC, SIR};

/* mapeamento da saída analógica */
#define ANALOG_OUTPUT_OFFSET 10
#define OFFSET_SOLE 9

#define AR_SALA 15
#define HEAT 16
#define MAX_VENTO 50

void init_output();
int funcaoTeste(int value, int sensor, int vento);
void write_init_output(String msg);
void write_output(String msg);
void write_sol(String msg);
void analog_write_output(String msg);

#endif