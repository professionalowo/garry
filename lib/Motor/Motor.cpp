#include "Motor.h"
#include "Arduino.h"

TMotor::TMotor(int forward_pin, int backwards_pin)
:m_backwardsPin(backwards_pin),m_forward_pin(forward_pin)
{
    pinMode(m_backwardsPin, OUTPUT);
    pinMode(m_forward_pin, OUTPUT);
}
TMotor::~TMotor()
{
    pinMode(m_backwardsPin, INPUT);
    pinMode(m_forward_pin, INPUT);
    stop();
}

void TMotor::backward(){
    digitalWrite(m_backwardsPin, HIGH);
    digitalWrite(m_forward_pin, LOW);
}

void TMotor::forward(){
    digitalWrite(m_backwardsPin, LOW);
    digitalWrite(m_forward_pin, HIGH);
}

void TMotor::stop(){
    digitalWrite(m_backwardsPin, LOW);
    digitalWrite(m_forward_pin, LOW);
}