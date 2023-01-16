/*
 * Library to communicate with DFRobot ENS160 Sensor via I2C/TWI
 * Author: Richard Karlson
 * Using base i2c functions by Steve Gunn
 */ 
 
#include "ens160.h"

void init_ens160(void)
{
	/* F_SCL = F_CPU/120 = 100kHz */
	TWBR = 0x34;
	TWSR = 0x00;
}

void com_start(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
}

void com_stop(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void tx(uint8_t b)
{
	TWDR = b;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
}

uint8_t rx_ack(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while(!(TWCR & _BV(TWINT)));
	return TWDR;
}

uint8_t rx_nack(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
	return TWDR;
}

void opmode(uint8_t mode)
{
	com_start();
	tx(W_ADDRESS);
	tx(A_OPMODE);
	tx(mode);
	com_stop();
}

void read_1byte(uint8_t* ptr_data, uint8_t regAdd)
{
	com_start();
	tx(W_ADDRESS);
	tx(regAdd);
	com_start();
	tx(R_ADDRESS);
	*ptr_data = rx_nack();
	com_stop();
}

void read_2byte(uint8_t* ptr_data1, uint8_t* ptr_data0, uint8_t regAdd)
{
	com_start();
	tx(W_ADDRESS);
	tx(regAdd);
	com_start();
	tx(R_ADDRESS);
	*ptr_data0 = rx_ack();
	*ptr_data1 = rx_nack();
	com_stop();
}

void write_1byte(uint8_t data, uint8_t regAdd)
{
	com_start();
	tx(W_ADDRESS);
	tx(regAdd);
	tx(data);
	com_stop();
}

void write_2byte(uint8_t data1, uint8_t data0, uint8_t regAdd)
{
	com_start();
	tx(W_ADDRESS);
	tx(regAdd);
	tx(data0);
	tx(data1);
	com_stop();
}

void read_TVOC(uint16_t* ptr_data0)
{
	uint8_t tvoc0 = 0;
	uint8_t tvoc1 = 0;
	read_2byte(&tvoc1, &tvoc0, A_DATA_TVOC);
	*ptr_data0 = (tvoc1 << 8) | tvoc0;
}

void read_ECO2(uint16_t* ptr_data0)
{
	uint8_t eco20 = 0;
	uint8_t eco21 = 0;
	read_2byte(&eco21, &eco20, A_DATA_ECO2);
	*ptr_data0 = (eco21 << 8) | eco20;
}

