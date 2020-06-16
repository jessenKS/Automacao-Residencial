#ifndef DS18B20_H_
#define DS18B20_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20 12

extern void init_ds18b20();
extern void read_ds18b20();

#endif