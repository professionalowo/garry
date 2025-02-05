#pragma once

class TMotor{

    public:
        TMotor(int forward_pin, int backwards_pin);
        void forward();
        void backward();
        void stop();
        ~TMotor();

    private:
        int m_backwardsPin;
        int m_forward_pin;
};