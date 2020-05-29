/*#include "ds18b20.h"

void init_ds18b20()
{
  sensors.begin();
  sensors.getAddress(sensor, 0);
}

void read_ds18b20()
{
  tempC = sensors.getTempC(sensor);
  if (tempC == -127.00) 
    Serial.print(aux);
  else 
  {
    Serial.print(tempC);
    aux = tempC;
  }
  sensors.requestTemperatures();
  //delay(2000);
}*/