#pragma once

class Motor{

    public:
        Motor(int forward_pin, int backwards_pin);
        void forward();
        void backwards();
        void stop();
        ~Motor();

    private:
        int m_backwardsPin;
        int m_forward_pin;
};