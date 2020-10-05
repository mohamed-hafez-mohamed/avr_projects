/*
 * spi_cnfg.h
 *
 * Created: 9/17/2019 11:05:41 ?
 *  Author: mah_h
 */ 


#ifndef SPI_CNFG_H_
#define SPI_CNFG_H_


#define SET         1

#define SPIBASE     0x2D
#define SPCR_OFFSET 0x00
#define SPSR_OFFSET 0x01
#define SPDR_OFFSET 0x02

#define SPR0  0
#define SPR1  1
#define CPHA  2
#define CPOL  3
#define MSTR  4
#define DORD  5
#define SPE   6
#define SPIE  7
#define SPI2X 0
#define WCOL  6
#define SPIF  7
//////////////////////////////
#define SPI_SLAVE_1 A2

#endif /* SPI_CNFG_H_ */