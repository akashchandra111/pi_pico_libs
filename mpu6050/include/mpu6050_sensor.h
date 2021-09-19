#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#define MPU6050_ADDR 0x68

// Accelerometer data type
typedef struct mpu6050_accelerelometer	{
	union	{
		struct	{
			int16_t x;
			int16_t y;
			int16_t z;
		};
		int16_t vals[3];
	};
} mpu6050_accelerometer_t;

// Accelerometer data type
typedef struct mpu6050_gyrometer	{
	union	{
		struct	{
			int16_t x;
			int16_t y;
			int16_t z;
		};
		int16_t vals[3];
	};
} mpu6050_gryometer_t;

// Accelerometer, Gyrometer and temperature  data type for combined data
typedef struct mpu6050_sensor_data	{
	mpu6050_accelerometer_t accelerometer;
	mpu6050_gryometer_t gryometer;
	int16_t temp;
} mpu6050_sensor_data_t;

void mpu6050_sensor_reset(i2c_inst_t *i2c_instance);
void mpu6050_sensor_get_accelerometer_reading(i2c_inst_t *i2c_instance, mpu6050_accelerometer_t *accelerometer);
void mpu6050_sensor_get_gyrometer_reading(i2c_inst_t *i2c_instance, mpu6050_gryometer_t *gyrometer);
int16_t mpu6050_sensor_get_temperature_reading(i2c_inst_t *i2c_instance);
void mpu6050_sensor_get_all(i2c_inst_t *i2c_instance, mpu6050_sensor_data_t *mpu_data_t);