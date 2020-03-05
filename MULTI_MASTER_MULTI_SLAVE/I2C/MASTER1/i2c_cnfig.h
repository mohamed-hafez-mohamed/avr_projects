/*
 * i2c_cnfg.h
 *
 * Created: 9/26/2019 02:06:49 ?
 *  Author: Mohamed Hafez
 */ 


#ifndef I2C_CNFG_H_
#define I2C_CNFG_H_

#define SET            1

#define	ICBASE         0x20
#define BITRATE_OFFSET 0x00
#define CONTROL_OFFSET 0x36
#define STATUS_OFFSET  0x01
#define ADDRESS_OFFSET 0x02
#define DATA_OFFSET    0x03

#define TWBR0          0
#define TWINT          7
#define TWEA           6
#define TWSTA          5
#define TWSTO          4
#define TWWCF          3
#define TWEN           2
#define TWIE           0
#define TWS3           3
#define TWPS0          0
#define TWGCE          0
#define TWA0           1
#define TWD0           0
#define TWD1           1


//if i use status table (Status Code (TWSR) Prescaler Bits are 0)
#define I2C_START                         0x08 // start has been sent
#define I2C_REP_START                     0x10 // repeated start
//master transmitter
#define I2C_MT_SLA_W_ACK                  0x18 // (slave address + Write have been sent ) + Ack received from slave
#define I2C_MT_SLA_W_NACK                 0x20 //SLA+W has been transmitted, NOT ACK has been received
#define I2C_MT_DATA_ACK                   0x28 // Data byte has been transmitted and ACK has been received from Slave.
#define I2C_MT_DATA_NACK                  0x30 // Data byte has been transmitted and NOT ACK has been received from Slave.
#define I2C_MT_ARBITRATION_LOST_SLA_W     0x38 //Arbitration lost in SLA+W or data bytes / Arbitration lost in SLA+R or NOT ACK bit
//master transmitter
#define I2C_MR_SLA_R_ACK                  0x40 // (slave address + Read have been sent ) + Ack received from slave
#define I2C_MR_SLA_R_NACK                 0x48 // (slave address + Read have been sent ) + NOT Ack received from slave
#define I2C_MR_DATA_ACK                   0x50 // Master received data and send ACK
#define I2C_MR_DATA_NACK                  0x58 // MAster received data but don't send ACK
#endif /* I2C_CNFG_H_ */