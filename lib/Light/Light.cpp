#include "Light.h"

TLight::TLight(int pin, int length) : m_length(length), m_strip(Adafruit_NeoPixel(pin, length, NEO_GRB + NEO_KHZ800)) {}

TLight::~TLight()
{
    m_strip.clear();
}



void TLight::loop(bool on)
{
    if (on)
    {
        m_strip.setPixelColor(m_length, m_strip.Color(0, 255, 0));
    }
    else
    {
        m_strip.clear();
    }
    m_strip.show();
}

void TLight::loop(TPressure &pressure)
{
    loop(pressure.loop());
}

void TLight::setup()
{
    m_strip.begin();
}