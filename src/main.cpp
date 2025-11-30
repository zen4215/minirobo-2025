#include <Arduino.h>
#include <PS4Controller.h>
#include "two_wheel_robo.hpp"

namespace config{
    const     char* PS4_BLE_ADDRESS {"test_str"};
    constexpr int   DIR1            {15};
    constexpr int   DIR2            {2};
    constexpr int   PWM1            {0};
    constexpr int   PWM2            {4};
    constexpr int   PWM_CHANNEL1    {0};
    constexpr int   PWM_CHANNEL2    {1};
    constexpr int   PWM_FREQ        {1000};
    constexpr int   PWM_RES         {8};
}

DCMoterConfig right_wheel(config::DIR1, config::PWM1, config::PWM_CHANNEL1, config::PWM_RES);
DCMoterConfig left_Wheel (config::DIR2, config::PWM2, config::PWM_CHANNEL2, config::PWM_RES);
TwoWheelRobo robo(right_wheel, left_Wheel);

void setup() {
    PS4.begin(config::PS4_BLE_ADDRESS);
    ledcSetup(config::PWM_CHANNEL1, config::PWM_FREQ, config::PWM_RES);
    ledcSetup(config::PWM_CHANNEL2, config::PWM_FREQ, config::PWM_RES);
    robo.setup();
}

void loop() {
    double run_x_v, run_y_v;
    run_x_v = PS4.LStickX();
    // deadzone
    if(run_x_v < 10 && run_x_v > -10) run_x_v = 0;
    run_y_v = PS4.LStickY();
    if(run_y_v < 10 && run_y_v > -10) run_y_v = 0;
    
    robo.move(run_y_v / 255.0, run_x_v / 255.0);
}
