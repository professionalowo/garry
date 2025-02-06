#include "Light.h"

TLight::TLight(int length)
    : m_length(length)
{
    m_leds = new CRGB[m_length];
}

TLight::~TLight()
{
    delete[] m_leds;
}

void TLight::loop(bool on)
{
    if (on)
    {
        set_color(CRGB::Green);
    }
    else
    {
        set_color(CRGB::Orange);
    }
    FastLED.show();
}

void TLight::loop(TPressure &pressure)
{
    loop(pressure.loop());
}

void TLight::setup()
{
    FastLED.addLeds<NEOPIXEL, 21>(m_leds, m_length);
    set_color(CRGB::Green);
    FastLED.show();
}

void TLight::set_color(CRGB color)
{
    for (int i = 0; i < m_length; i++)
    {
        m_leds[i] = color;
    }
}