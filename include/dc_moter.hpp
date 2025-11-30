#pragma once

#include <Arduino.h>

struct DCMoterConfig {
    DCMoterConfig(int dir_pin, int pwm_pin, int pwm_channel, int pwm_res) :
    dir_pin     (dir_pin),
    pwm_pin     (pwm_pin),
    pwm_channel (pwm_channel),
    pwm_res     (pwm_res) {

    }
    const int dir_pin;
    const int pwm_pin;
    const int pwm_channel;
    const int pwm_res;
};

class DCMoter{
    public:
    DCMoter(DCMoterConfig config);
    ~DCMoter();
    
    void setup();
    void move(bool dir, double duty);
    
    private:
    const DCMoterConfig m_config;
};

DCMoter::DCMoter(DCMoterConfig config) :
    m_config(config) {}
DCMoter::~DCMoter() {}

void DCMoter::setup() {
    pinMode(m_config.dir_pin, OUTPUT);
    ledcAttachPin(m_config.pwm_pin, m_config.pwm_channel);
}
void DCMoter::move(bool dir, double duty) {
    if(dir) digitalWrite(m_config.dir_pin, HIGH);
    else digitalWrite(m_config.dir_pin, LOW);
    
    duty *= m_config.pwm_res;

    ledcWrite(m_config.pwm_channel, duty);
}
