/*
 * IncFile1.h
 *
 * Created: 24/05/2021 11:51:49
 *  Author: Overlord
 */ 


#ifndef I2C_H_
#define I2C_H_

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#define TWI_WRITE 0x00
#define TWI_READ 0x01

#define STATUS_MASK 0xF8

// Status master transmitter
#define TWI_STATUS_START 0x08
#define TWI_STATUS_REPEATED_START 0x10
#define TWI_STATUS_SLA_W_ACK 0x18
#define TWI_STATUS_SLA_W_NACK 0x20
#define TWI_STATUS_DATA_W_ACK 0x28
#define TWI_STATUS_DATA_W_NACK 0x30
#define TWI_STATUS_TRANSMISSION_LOST 0x38

// Status master receiver
#define TWI_STATUS_SLA_R_ACK 0x40
#define TWI_STATUS_SLA_R_NACK 0x48
#define TWI_STATUS_DATA_R_ACK 0x50
#define TWI_STATUS_DATA_R_NACK 0x58

#define BIT_RATE(a) (((F_CPU / a) - 16) >> 1)

#include <stdio.h>
#include <avr/io.h>

void TWI_init(unsigned long scl_speed);
uint8_t TWI_start(void);
void TWI_stop(void);
uint8_t TWI_write(uint8_t data);
uint8_t TWI_read(uint8_t *data);
uint8_t TWI_read_ACK(uint8_t *data);
uint8_t TWI_burst_read(uint8_t *buffer, uint8_t buffer_size);
uint8_t TWI_get_status(void);
uint8_t TWI_call(uint8_t address, uint8_t mode);

#endif /* I2C_H_ */