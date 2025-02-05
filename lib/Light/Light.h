#pragma once

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Pressure.h"

class TLight
{

public:
    TLight(int pin, int length);
    void loop(bool on);
    void loop(TPressure& pressure);
    void setup();
    ~TLight();

private:
    int m_length;
    Adafruit_NeoPixel m_strip;
};