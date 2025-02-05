#include "Arduino.h"

class TPressure
{
public:
    TPressure(int pin);
    bool loop();

private:
    int m_pin;
    int m_previous_time = 0;
    const int m_timeout = 1000;
};