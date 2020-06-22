#include "ds18b20.h"
#include "OneWire.h"
#include "DallasTemperature.h"

OneWire ourWire(DS18B20); 
DallasTemperature sensors(&ourWire); 
DeviceAddress sensor;
int tempC;
float aux;

void init_ds18b20()
{
    sensors.begin();
    sensors.getAddress(sensor, 0);
    delay(500);
}

int read_ds18b20()
{
    sensors.requestTemperatures();
    aux = sensors.getTempC(sensor);
    if (aux != -127.00 && aux != 85)
        tempC = int(aux);
    
    sensors.requestTemperatures();

    return tempC;
}