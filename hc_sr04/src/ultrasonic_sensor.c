#include "ultrasonic_sensor.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/time.h"
#include <stdint.h>

void ultrasonic_init(int pin_U_TRIG, int pin_U_ECHO)	{
	// Ultrasonic sensor
    gpio_init(pin_U_TRIG);
    gpio_init(pin_U_ECHO);
    gpio_set_dir(pin_U_TRIG, true);
    gpio_set_dir(pin_U_ECHO, false);
}

float ultrasonic_get_distance(int pin_U_TRIG, int pin_U_ECHO)	{
	// Send a beam
	gpio_put(pin_U_TRIG, true);
	sleep_ms(2);
	gpio_put(pin_U_TRIG, false);
	
	// Wait for the beam
	uint32_t start_time, end_time;
	while (gpio_get(pin_U_ECHO) == 0)	start_time = time_us_32();
	while (gpio_get(pin_U_ECHO) == 1)	end_time = time_us_32();
	
	// Calculate the distance and return the result
	return ((end_time - start_time) * 0.0343) / 2;
}