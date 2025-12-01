#include <Arduino.h>
#include <PS4Controller.h>
#include "two_wheel_robo.hpp"

const     char*     PS4_BLE_ADDRESS {"test_str"};
constexpr uint8_t   DIR1            {15};
constexpr uint8_t   DIR2            {2};
constexpr uint8_t   PWM1            {0};
constexpr uint8_t   PWM2            {4};
constexpr uint8_t   PWM_CHANNEL1    {0};
constexpr uint8_t   PWM_CHANNEL2    {1};
constexpr uint16_t  PWM_FREQ        {1000};
constexpr uint8_t   PWM_RES         {8};

DCMoterConfig right_wheel(DIR1, PWM1, PWM_CHANNEL1, PWM_RES);
DCMoterConfig left_Wheel (DIR2, PWM2, PWM_CHANNEL2, PWM_RES);
TwoWheelRobo robo(right_wheel, left_Wheel);

void setup() {
    PS4.begin(PS4_BLE_ADDRESS);
    ledcSetup(PWM_CHANNEL1, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_CHANNEL2, PWM_FREQ, PWM_RES);
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
