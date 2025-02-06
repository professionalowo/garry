#pragma once

#include "Arduino.h"

class TAudio
{
public:
    TAudio(int pin, const unsigned char *data, int length);
    void setup();
    void loop(bool start_audio);
    ~TAudio();

private:
    int m_pin;
    int m_length;
    const unsigned char *m_data;
    int m_index = 0;
    void step();
    void stop();
};