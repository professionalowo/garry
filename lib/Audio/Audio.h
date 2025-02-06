#pragma once

#include "Arduino.h"
#include <vector>
#include <memory>
#include "ToneESP32.h"

class TAudio
{
public:
    TAudio(int pin, std::vector<std::pair<int, int>> &&data);
    void loop(bool start_audio);
    ~TAudio() = default;

private:
    int m_pin;
    std::unique_ptr<ToneESP32> m_tone;
    std::vector<std::pair<int, int>> m_data;
    int m_index = 0;
    void step();
};

