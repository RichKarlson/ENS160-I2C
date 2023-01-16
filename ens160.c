/*
 * Version 1: Library to communicate with DFRobot ENS160 Sensor via I2C/TWI
 * Author: Richard Karlson
 * i2c.h library and functions by Steve Gunn
 */ 
 
#include "i2c.h"
#include "ens160.h"

void init_ens160(void)
{
	init_i2c_master();
}

void com_start(void)
{
	i2c_start();
}

void com_stop(void)
{
	i2c_stop();
}

void tx(uint8_t b)
{
	i2c_tx(b);
}

uint8_t rx_ack(void)
{
	return i2c_rx_ack();
}

uint8_t rx_nack(void)
{
	return i2c_rx_nack();
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

