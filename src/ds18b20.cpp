#include "ds18b20.h"

OneWire ourWire(DS18B20); 
DallasTemperature sensors(&ourWire); 
DeviceAddress sensor;
float tempC, aux;

void init_ds18b20()
{
  sensors.begin();
  sensors.getAddress(sensor, 0);
}

void read_ds18b20()
{
  tempC = sensors.getTempC(sensor);
  if (tempC == -127.00) 
    Serial.println(aux);
  else 
  {
    Serial.println(tempC);
    aux = tempC;
  }
  sensors.requestTemperatures();
  delay(2000);
}