#pragma once

#include "pico/time.h"
#include "hardware/gpio.h"

void ultrasonic_init(int pin_U_TRIG, int pin_U_ECHO);
float ultrasonic_get_distance(int pin_U_TRIG, int pin_U_ECHO);