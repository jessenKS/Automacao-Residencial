#ifndef DS18B20_H_
#define DS18B20_H_

#include <Arduino.h>

#define DS18B20 13

void init_ds18b20();
int read_ds18b20();

#endif