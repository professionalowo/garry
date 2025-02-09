#pragma once
#include "Arduino.h"

class TPressure
{
public:
    TPressure(int pin);
    bool loop();

private:
    int m_pin;
    int m_previous_time;
    const int m_timeout = 300;
};