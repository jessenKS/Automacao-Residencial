#include <Arduino.h>
#include "lm35.h"
#include "input.h"
#include "output.h"
#include "serial.h"
#include "ds18b20.h"

void setup()
{   
    init_serial();
    init_output();
    init_input();
    init_ds18b20();
}

void loop()
{
    msgHandler();
}



