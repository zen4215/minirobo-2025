#pragma once

#include "dc_moter.hpp"

class TwoWheelRobo {
    public:
    TwoWheelRobo(DCMoterConfig right_moter_config, DCMoterConfig left_moter_config);
    
    void setup();
    void move(double run_v, double turn_V);
    
    private:
    DCMoter m_right_wheel;
    DCMoter m_left_wheel;
};

TwoWheelRobo::TwoWheelRobo(DCMoterConfig right_moter_config, DCMoterConfig left_moter_config) :
    m_right_wheel(DCMoter(right_moter_config)), 
    m_left_wheel(DCMoter(left_moter_config)) {}

void TwoWheelRobo::setup() {
    m_right_wheel.setup();
    m_left_wheel.setup();
}
void TwoWheelRobo::move(double run_v, double turn_v) { // -1~1
    float r_v, l_v;
    r_v = run_v - turn_v;
    l_v = run_v + turn_v;
    if(r_v > 1.0) r_v = 1.0;
    if(r_v < -1.0) r_v = -1.0;
    if(l_v > 1.0) l_v = 1.0;
    if(l_v < -1.0) l_v = -1.0;
    
    if(r_v > 0) m_right_wheel.move(1, r_v);
    else m_right_wheel.move(0, -r_v);
    if(l_v > 0) m_left_wheel.move(0, l_v);
    else m_left_wheel.move(1, -l_v);
}
