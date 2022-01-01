/*
 * i2c.c
 *
 * Created: 23/05/2021 16:28:27
 * Author : Overlord
 */ 

#include "i2c.h"

uint8_t TWI_get_status(void) { return TWSR & STATUS_MASK; } // Returns 5 status bits

void TWI_init(unsigned long scl_speed) {
	TWSR = 0x0; // Reset TWI Status Register
	TWBR = BIT_RATE(scl_speed); //BIT_RATE(scl_speed); // Setting the bit rate value
	// Atmel documentation recommends not using the prescaler
	TWCR = (1 << TWEN); // Enabling TWI
		
	return;
}

uint8_t TWI_start(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Clearing the interrupt flag and sending the start signal
	
	while (!(TWCR & (1 << TWINT))); // Waiting for TWI to be available
	
	return TWI_get_status();
}

void TWI_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // Clearing the interrupt flag and sending the stop signal
	
	return;
}

uint8_t TWI_write(uint8_t data) {
	TWDR = data; // Writing the data into the SDA line
	TWCR = (1 << TWINT) | (1 << TWEN); // Sending the data
	
	while (!(TWCR & (1 << TWINT))); // Waiting for the bus to send the data
	
	return TWI_get_status();
}

uint8_t TWI_read(uint8_t *data) {
	TWCR = (1 << TWINT) | (1 << TWEN); // Read from a device
	
	while (!(TWCR & (1 << TWINT))); // Waiting for TWI to be available
	
	*data = TWDR;
	
	return TWI_get_status();
}

uint8_t TWI_read_ACK(uint8_t *data) {	
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN); // Read from a device using the Acknowledge bit
	
	while (!(TWCR & (1 << TWINT))); // Waiting for TWI to be available
	
	*data = TWDR;
	
	return TWI_get_status();
}

uint8_t TWI_call(uint8_t address, uint8_t mode) { return TWI_write((address << 1) | mode); }

uint8_t TWI_burst_read(uint8_t *buffer, uint8_t buffer_size) {
	for (uint8_t i = 0 ; i < buffer_size - 1 ; i++) {
		if (TWI_read_ACK(&buffer[i]) != TWI_STATUS_DATA_R_ACK)
			return TWI_get_status();
	}
	
	if (TWI_read(&buffer[buffer_size - 1]) != TWI_STATUS_DATA_R_NACK)
		return TWI_get_status();
	
	TWI_stop();
	
	return TWI_get_status();
}