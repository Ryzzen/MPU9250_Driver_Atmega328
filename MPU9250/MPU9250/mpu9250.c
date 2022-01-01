/*
 * MPU9250.c
 *
 * Created: 12/06/2021 18:12:08
 * Author : Overlord
 */ 

#include "mpu9250.h"


uint8_t MAG_TWI_start(uint8_t r_address) {
	if (TWI_start() != TWI_STATUS_START)
	return 0;
	
	if (TWI_call(MAG_AD, TWI_WRITE) != TWI_STATUS_SLA_W_ACK)
	return 0;

	if (TWI_write(r_address) != TWI_STATUS_DATA_W_ACK)
	return 0;
	return 1;
}

uint8_t MAG_TWI_write(uint8_t r_address, uint8_t data) {
	if (!MAG_TWI_start(r_address))
	return 0;
	
	if (TWI_write(data) != TWI_STATUS_DATA_W_ACK)
	return 0;
	
	TWI_stop();
	
	return 1;
	
}

uint8_t MAG_TWI_read(uint8_t r_address, uint8_t *data) {
	if (!MAG_TWI_start(r_address))
	return 0;
	
	if (TWI_start() != TWI_STATUS_REPEATED_START)
	return 0;
	
	if (TWI_call(MAG_AD, TWI_READ) != TWI_STATUS_SLA_R_ACK)
	return 0;
	
	if (TWI_read(data) != TWI_STATUS_DATA_R_NACK)
	return 0;
	
	TWI_stop();
	
	return 1;
}

uint8_t MPU9250_TWI_start(uint8_t r_address) {
	if (TWI_start() != TWI_STATUS_START)
	return 0;
	
	if (TWI_call(MPU9250_AD, TWI_WRITE) != TWI_STATUS_SLA_W_ACK)
	return 0;

	if (TWI_write(r_address) != TWI_STATUS_DATA_W_ACK)
	return 0;
	return 1;
}

uint8_t MPU9250_TWI_write(uint8_t r_address, uint8_t data) {
	if (!MPU9250_TWI_start(r_address))
	return 0;
	
	if (TWI_write(data) != TWI_STATUS_DATA_W_ACK)
	return 0;
	
	TWI_stop();
	
	return 1;
	
}

uint8_t MPU9250_TWI_read(uint8_t r_address, uint8_t *data) {
	if (!MPU9250_TWI_start(r_address))
	return 0;
	
	if (TWI_start() != TWI_STATUS_REPEATED_START)
	return 0;
	
	if (TWI_call(MPU9250_AD, TWI_READ) != TWI_STATUS_SLA_R_ACK)
	return 0;
	
	if (TWI_read(data) != TWI_STATUS_DATA_R_NACK)
	return 0;
	
	TWI_stop();
	
	return 1;
}

void MAG_init(void) {
	MPU9250_TWI_write(MPU9250_INT_BYPASS_CONFIG_AD, 0x02); // set the bypass-multiplexer
	MAG_TWI_write(MAG_CNTL1_AD, 0x16); // set the Magnetometer to continuous mode 2?100Hz) and 16-bit output
	
	return;
}

void MPU9250_init(void) {
	MPU9250_TWI_write(MPU9250_PWR_MGMT_1_AD, 0x01); // Clock reference set to X axis gyro
	MPU9250_TWI_write(MPU9250_ACCEL_CONFIG_1_AD, 0x08); // Set accel to 4g
	MPU9250_TWI_write(MPU9250_ACCEL_CONFIG_2_AD, 0x05); // Set internal low pass filter of the accel to 10.2Hz bandwidth
	MPU9250_TWI_write(MPU9250_GYRO_CONFIG_AD, 0x18); // Set gyro's scale to 2000°/s + FCHOICE_B
	MPU9250_TWI_write(MPU9250_CONFIG_AD, 0x05); // set the internal low-pass filter of the gyroscope to 10Hz bandwidth
	MAG_init(); // Magnetometer initialization
	
	return;
}

uint8_t MPU9250_read_gyro_x(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_GYRO_X_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_GYRO_X_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_gyro_y(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_GYRO_Y_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_GYRO_Y_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_gyro_z(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_GYRO_Z_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_GYRO_Z_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_accel_x(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_X_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_X_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_accel_y(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_Y_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_Y_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_accel_z(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_Z_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_ACCEL_Z_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_mag_x(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_MAG_X_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_MAG_X_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_mag_y(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_MAG_Y_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_MAG_Y_L, &data_L);
	
	return ((data_H << 4) | data_L);
}

uint8_t MPU9250_read_mag_z(void) {
	uint8_t data_H = 0;
	MPU9250_TWI_read(MPU9250_MAG_Z_H, &data_H);
	uint8_t data_L = 0;
	MPU9250_TWI_read(MPU9250_MAG_Z_L, &data_L);
	
	return ((data_H << 4) | data_L);
}