#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "Pressure.h"

class TLight
{

public:
    TLight(int length);
    void loop(bool on);
    void loop(TPressure &pressure);
    void setup();
    ~TLight();

private:
    int m_length;
    CRGB *m_leds;

    void set_color(CRGB color);
};