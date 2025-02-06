#pragma once

#include "Arduino.h"
#include <vector>

class TAudio
{
public:
    TAudio(int pin, std::vector<unsigned char>&& data);
    void loop(bool start_audio);
    ~TAudio();

private:
    int m_pin;
    std::vector<unsigned char> m_data;
    int m_index = 0;
    void step();
    void stop();
};