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

//if i use status table(Status Code (TWSR) Prescaler Bits are 0)
//slave transmitter
#define I2C_ST_SLA_R_ACK                 0xA8 // (own slave address + READ has been received ) + Ack returned
#define I2C_ST_ARBITRATION_LOST_SLA_R_W  0xB0 //Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
#define I2C_ST_DATA_ACK                  0xB8 // Data byte has been transmitted and ACK has been received from master.
#define I2C_ST_DATA_NACK                 0xC0 // Data byte has been transmitted and NOT ACK has been received from master.
#define I2C_ST_LAST_DATA_ACK             0xC8 //Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
//slave receiver
#define I2C_SR_SLA_W_ACK                 0x60 // (own slave address + Write has been received ) + Ack returned
#define I2C_SR_ARBITRATION_LOST_SLA_R_W  0x68 //Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
#define I2C_SRGCALL_ACK                  0x70 //General call address has been received; ACK has been returned
#define I2C_SR_ARBITRATION_LOST_SLA_R_W  0x78 //Arbitration lost in SLA+R/W as master; General call address has been received; ACK has been returned
#define I2C_SR_DATA_ACK                  0x80 //Previously addressed with own SLA+W; data has been received; ACK has been returned
#define I2C_SR_DATA_NACK                 0x88 // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
#define I2C_SR_GCALL_DATA_ACK            0x90 //Previously addressed with general call; data has been received; ACK has been returned
#define I2C_SR_GCALL_DATA_NACK           0x98 // Previously addressed with general call; data has been received; NOT ACK has been returned
#define I2C_SR_STOP_RSTART               0xA0 //A STOP condition or repeated START condition has been received while still addressed as slave
#endif /* I2C_CNFG_H_ */