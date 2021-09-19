#include "mpu6050_sensor.h"
#include <stdint.h>

void mpu6050_init(i2c_inst_t *i2c_instance, int pin_SDA, int pin_SCL)   {
    i2c_init(i2c_instance, 1 * MHZ);
    gpio_set_function(pin_SCL, GPIO_FUNC_I2C);
    gpio_set_function(pin_SDA, GPIO_FUNC_I2C);

    // need to enable the pullups
    gpio_pull_up(pin_SCL);
    gpio_pull_up(pin_SDA);
}

void mpu6050_sensor_reset(i2c_inst_t *i2c_instance)	{
	uint8_t registers[] = {0x6B, 0x00};
	i2c_write_blocking(i2c_instance, MPU6050_ADDR, registers, sizeof(registers), false);
}

inline void mpu6050_sensor_get_accelerometer_reading(i2c_inst_t *i2c_instance, mpu6050_accelerometer_t *accelerometer)	{
	uint8_t buffer[6];

    uint8_t reg = 0x3B;	// Reading this register to fetch accelerometer data
    i2c_write_blocking(i2c_instance, MPU6050_ADDR, &reg, sizeof(reg), false);
    i2c_read_blocking(i2c_instance, MPU6050_ADDR, buffer, sizeof(buffer), false);

	// Assign the values to mpu_accelerometer_t for easy fetch
    accelerometer->vals[0] = (buffer[0] << 8) | buffer[1];
    accelerometer->vals[1] = (buffer[2] << 8) | buffer[3];
    accelerometer->vals[2] = (buffer[4] << 8) | buffer[5];
}

inline void mpu6050_sensor_get_gyrometer_reading(i2c_inst_t *i2c_instance, mpu6050_gryometer_t *gyrometer)	{
	uint8_t buffer[6];

    uint8_t reg = 0x43;	// Reading this register to fetch gryometer data
    i2c_write_blocking(i2c_instance, MPU6050_ADDR, &reg, sizeof(reg), false);
    i2c_read_blocking(i2c_instance, MPU6050_ADDR, buffer, sizeof(buffer), false);

	// Assign the values to mpu_gyrometer_t for easy fetch
    gyrometer->vals[0] = (buffer[0] << 8) | buffer[1];
    gyrometer->vals[1] = (buffer[2] << 8) | buffer[3];
    gyrometer->vals[2] = (buffer[4] << 8) | buffer[5];
}

inline int16_t mpu6050_sensor_get_temperature_reading(i2c_inst_t *i2c_instance)	{
	uint8_t buffer[2];

	uint8_t reg = 0x41;
    i2c_write_blocking(i2c_instance, MPU6050_ADDR, &reg, sizeof(reg), false);
    i2c_read_blocking(i2c_instance, MPU6050_ADDR, buffer, sizeof(buffer), false);
    
    int16_t raw_data = (buffer[0] << 8) | buffer[1];
    return (raw_data/340.0) + 36.53;
}

void mpu6050_sensor_get_all(i2c_inst_t *i2c_instance, mpu6050_sensor_data_t *mpu_data)	{
	mpu6050_sensor_get_accelerometer_reading(i2c_instance, &mpu_data->accelerometer);
	mpu6050_sensor_get_gyrometer_reading(i2c_instance, &mpu_data->gryometer);
	mpu_data->temp = mpu6050_sensor_get_temperature_reading(i2c_instance);
}