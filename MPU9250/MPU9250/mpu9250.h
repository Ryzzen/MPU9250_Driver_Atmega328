/*
 * mpu9250.h
 *
 * Created: 12/06/2021 18:14:39
 *  Author: Overlord
 */ 


#ifndef MPU9250_H_
	#define MPU9250_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define MPU9250_SCL_SPEED 400000UL

// Register addresses
#define MPU9250_AD 0x68
#define MAG_AD 0xC

#define MPU9250_PWR_MGMT_1_AD 0x6b
#define MPU9250_GYRO_CONFIG_AD 0x1b
#define MPU9250_ACCEL_CONFIG_1_AD 0x1c
#define MPU9250_ACCEL_CONFIG_2_AD 0x1d
#define MPU9250_CONFIG_AD 0x1a
#define MPU9250_USER_CTRL_AD 0x6A
#define MPU9250_INT_BYPASS_CONFIG_AD 0x37
#define MAG_CNTL1_AD 0x0A
#define MAG_ASAX_AD 0x10


// Output addresses
#define MPU9250_GYRO_X_H 0x43
#define MPU9250_GYRO_X_L 0x44
#define MPU9250_GYRO_Y_H 0x45
#define MPU9250_GYRO_Y_L 0x46
#define MPU9250_GYRO_Z_H 0x47
#define MPU9250_GYRO_Z_L 0x48

#define MPU9250_ACCEL_X_H 0x3b
#define MPU9250_ACCEL_X_L 0x3c
#define MPU9250_ACCEL_Y_H 0x3d
#define MPU9250_ACCEL_Y_L 0x3e
#define MPU9250_ACCEL_Z_H 0x3f
#define MPU9250_ACCEL_Z_L 0x40

#define MPU9250_MAG_X_H 0x03
#define MPU9250_MAG_X_L 0x04
#define MPU9250_MAG_Y_H 0x05
#define MPU9250_MAG_Y_L 0x06
#define MPU9250_MAG_Z_H 0x07
#define MPU9250_MAG_Z_L 0x08


uint8_t MAG_TWI_start(uint8_t r_address);
uint8_t MAG_TWI_write(uint8_t r_address, uint8_t data);
uint8_t MAG_TWI_read(uint8_t r_address, uint8_t *data);
uint8_t MPU9250_TWI_start(uint8_t r_address);
uint8_t MPU9250_TWI_write(uint8_t r_address, uint8_t data);
uint8_t MPU9250_TWI_read(uint8_t r_address, uint8_t *data);
void MAG_init(void);
void MPU9250_init(void);
uint8_t MPU9250_read_gyro_x(void);
uint8_t MPU9250_read_gyro_y(void);
uint8_t MPU9250_read_gyro_z(void);
uint8_t MPU9250_read_accel_x(void);
uint8_t MPU9250_read_accel_y(void);
uint8_t MPU9250_read_accel_z(void);
uint8_t MPU9250_read_mag_x(void);
uint8_t MPU9250_read_mag_y(void);
uint8_t MPU9250_read_mag_z(void);


// Exemple use

/*#include "mpu9250.h"
#include "uart0.h"

int main(void)
{
	UART0_init(9600, 1);
    TWI_init(MPU9250_SCL_SPEED);
	MPU9250_init();
	
    while (1) 
    {		
		printf("Gyro_x: %d Gyro_y: %d Gyro_z: %d\n",
				MPU9250_read_gyro_x(),
				MPU9250_read_gyro_y(),
				MPU9250_read_gyro_z());
		
		_delay_ms(50);
    }
}*/

#endif /* MPU9250_H_ */