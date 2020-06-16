#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <Arduino.h>
#include "serial.h"

/* mapeamento das saÃ­das */
//enum {OUT1=8, OUT2, OUT3, OUT4} OUTPUTS;
enum{OUTPUT_OFFSET = 1, OUT1, OUT2, OUT3, OUT4, EN1, EN2, SOLE, ARC, SIR, LAM_D, LAM_R};

/* mapeamento da saída analógica */
#define ANALOG_OUTPUT_OFFSET 8

extern void init_output();
extern void read_init_output(String msg);
extern void write_output(String msg);
extern void analog_write_output(String msg);

#endif