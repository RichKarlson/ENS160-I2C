/*
 * Version 1: Library to communicate with DFRobot ENS160 Sensor via I2C/TWI
 * Author: Richard Karlson
 * See https://www.sciosense.com
 */ 
 
/*
Address Name Size Access Description
0x00 PART_ID 2 Read Device Identity 0x01, 0x60
0x10 OPMODE 1 Read / Write Operating Mode
0x11 CONFIG 1 Read / Write Interrupt Pin Configuration
0x12 COMMAND 1 Read / Write Additional System Commands
0x13 TEMP_IN 2 Read / Write Host Ambient Temperature Information
0x15 RH_IN 2 Read / Write Host Relative Humidity Information
0x17 – 0x1F - 1 - Reserved
0x20 DEVICE_STATUS 1 Read Operating Mode
0x21 DATA_AQI 1 Read Air Quality Index
0x22 DATA_TVOC 2 Read TVOC Concentration (ppb)
0x24 DATA_ECO2 2 Read Equivalent CO2 Concentration (ppm)
0x26 - 2 - Reserved
0x28 - 2 - Reserved
0x2A - 2 Read Reserved
0x2C – 0x2F - 1 - Reserved
0x30 DATA_T 2 Read Temperature used in calculations
0x32 DATA_RH 2 Read Relative Humidity used in calculations
0x34 – 0x37 - 1 - Reserved
0x38 DATA_MISR 1 Read Data Integrity Field (optional)
0x40 GPR_WRITE[0:7] 8 Read/Write General Purpose Write Registers
0x48 GPR_READ[0:7] 8 Read General Purpose Read Registers
*/

#define W_ADDRESS 0xA6
#define R_ADDRESS 0xA7

#define A_PART_ID 0x00 //2
#define A_OPMODE 0x10
#define A_CONFIG 0x11
#define A_COMMAND 0x12
#define A_TEMP_IN 0x13 //2
#define A_RH_IN 0x15 //2
#define A_DEVICE_STATUS 0x20
#define A_DATA_AQI 0x21
#define A_DATA_TVOC 0x22 //2
#define A_DATA_ECO2 0x24 //2
#define A_DATA_T 0x30 //2
#define A_DATA_RH 0x32 //2
#define A_DATA_MISR 0x38
#define A_GPR_WRITE 0x40 //8
#define A_GPR_READ 0x48 //8

void init_ens160(void);
void com_start(void);
void com_stop(void);
void tx(uint8_t b);
uint8_t rx_ack(void);
uint8_t rx_nack(void);
void opmode(uint8_t mode);
void read_1byte(uint8_t* ptr_data, uint8_t regAdd);
void read_2byte(uint8_t* ptr_data1, uint8_t* ptr_data0, uint8_t regAdd);
void write_1byte(uint8_t data, uint8_t regAdd);
void write_2byte(uint8_t data1, uint8_t data0, uint8_t regAdd);
