/*
 * I2C.c
 *
 * Created: 9/26/2019 09:08:14 ?
 *  Author: Mohamed Hafez
 */ 

#include "I2C.h"

#define I2C_BUSY (IS_BIT_CLEAR((ICBASE + CONTROL_OFFSET), TWINT))

static void (*ptr_func)(void);

void  i2c_init(uint8 myaddress)
{
	ACCESS_REG_8BIT((ICBASE + STATUS_OFFSET))   = 0x00;
	ACCESS_REG_8BIT((ICBASE + BITRATE_OFFSET))  = 0x02;
	ACCESS_REG_8BIT((ICBASE + ADDRESS_OFFSET))  = (0 << TWGCE) |(myaddress << TWA0);     //it's address if any master device want to call me & general call off
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) |= (SET << TWEN); //enable I2C
}

void  i2c_start(void)
{
	/* Clear the TWINT flag before sending the start bit TWINT=1 "MUST"
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT) | (SET << TWSTA);
	// Wait for TWINT flag set in TWCR Register (start bit is send successfully)
	while(I2C_BUSY);
}

void  i2c_stop(void)
{
	/* Clear the TWINT flag before sending the stop bit TWINT=1 
	 * send the stop bit by TWSTO=1 
	 * Enable TWI Module TWEN=1 
	 */
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT) | (SET << TWSTO);
}

void  i2c_writeAddress(uint8 adress, i2c_status status)
{
	ACCESS_REG_8BIT((ICBASE + DATA_OFFSET)) = (status << TWD0) | (adress << TWD1);
	// Put address On TWI Register
	//ACCESS_REG_8BIT((ICBASE + DATA_OFFSET))  = adress;
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT);
	// Wait for TWINT flag set in TWCR Register(data is send successfully)
	while(I2C_BUSY);
}

void  i2c_write(uint8 data)
{
	// Put data On TWI Register
	ACCESS_REG_8BIT((ICBASE + DATA_OFFSET))  = data;
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT);
	// Wait for TWINT flag set in TWCR Register(data is send successfully)
	while(I2C_BUSY);
}

void i2c_write_gcall(uint8 data)
{
	SET_BIT((ICBASE + ADDRESS_OFFSET),TWGCE);
	// Put address On TWI Register
    ACCESS_REG_8BIT((ICBASE + DATA_OFFSET)) |= (0b0000000 << TWD1);
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT);
	// Wait for TWINT flag set in TWCR Register(data is send successfully)
	while(I2C_BUSY);
	// Put data On TWI Register
	ACCESS_REG_8BIT((ICBASE + DATA_OFFSET))  = data;
	/* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT);
	// Wait for TWINT flag set in TWCR Register(data is send successfully)
	while(I2C_BUSY);
}

uint8 i2c_read(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT) | (SET << TWEA);
	// Wait for TWINT flag set in TWCR Register (data received successfully) 
	while(I2C_BUSY);
	return ACCESS_REG_8BIT((ICBASE + DATA_OFFSET));
}

uint8 i2c_readWithNAck(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
	ACCESS_REG_8BIT((ICBASE + CONTROL_OFFSET)) = (SET << TWEN) | (SET << TWINT);
	// Wait for TWINT flag set in TWCR Register (data received successfully)
	while(I2C_BUSY);
	return ACCESS_REG_8BIT((ICBASE + DATA_OFFSET));
}

uint8 i2c_getStatus(void)
{
	uint8 status;
	status = ACCESS_REG_8BIT((ICBASE + STATUS_OFFSET)) & 0xF8; //masking to eliminate first 3 bits 
	return status;
}

void i2c_int(void (*p_func)(void))
{
	SET_BIT((ICBASE + CONTROL_OFFSET),TWIE);
	ptr_func = p_func;
}
ISR(TWI_vect)
{
	sei();
	(*ptr_func)();
}