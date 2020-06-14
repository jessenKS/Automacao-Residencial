#ifndef SERIAL_H_
#define SERIAL_H_

#include <Arduino.h>
#include "input.h"
#include "output.h"
#include "lm35.h"

/* Estrutura da mensagem */
#define READ_COIL    0X01
#define READ_INPUT   0X02
#define WRITE_COIL   0X05
#define READ_ANALOG  0x06
#define WRITE_ANALOG 0X07

/* lÃ³gica negada para saÃ­das */
#define ON  1
#define OFF 0

/* Parametros */
#define SLAVE_ADR       "03"
#define VAL tam/2  // tamanho de dado

extern void init_serial();
extern void msgHandler();
uint8_t lrc(uint8_t *dado, uint8_t t);

//extern void init_input();

#endif