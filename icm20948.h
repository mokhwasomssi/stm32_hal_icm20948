/*
* icm20948.h
*
*  Created on: Dec 26, 2020
*      Author: mokhwasomssi
*/


#ifndef __ICM20948_H__
#define	__ICM20948_H__


#include "icm20948_reg.h"
#include "spi.h"			// header from stm32cubemx code generate
#include <stdbool.h>


/* User Configuration */

// ICM-20948 SPI Interface
#define ICM20948_SPI					(&hspi1)

// ICM-20948 CS Pin
#define ICM20948_SPI_CS_PIN_PORT		GPIOA
#define ICM20948_SPI_CS_PIN_NUMBER		GPIO_PIN_4


/* ICM-20948 Defines */
#define READ							0x80
#define WRITE							0x00

#define MAX_READ						6


/* ICM-20948 Typedefs */
typedef enum
{
	ub_0 = 0 << 4,
	ub_1 = 1 << 4,
	ub_2 = 2 << 4,
	ub_3 = 3 << 4
} userbank;

typedef enum
{
	_250dps,
	_500dps,
	_1000dps,
	_2000dps
} gyro_full_scale;

typedef enum
{
	_2g,
	_4g,
	_8g,
	_16g
} accel_full_scale;

typedef struct
{
	float x;
	float y;
	float z;
} axises;


/* ICM-20948 Main Functions */
void icm20948_init();

void icm20948_gyro_read(axises* data);	// 16bits ADC value
void icm20948_accel_read(axises* data);	// 16bits ADC value

void icm20948_gyro_read_dps(axises* data);
void icm20948_accel_read_g(axises* data);


/* ICM-20948 Sub Functions */
bool icm20948_who_am_i();

void icm20948_device_reset();

void icm20948_wakeup();
void icm20948_sleep();

void icm20948_spi_slave_enable();

void icm20948_i2c_master_reset();
void icm20948_i2c_master_enable();
void icm20948_i2c_master_clk_frq(uint8_t config); // 0 - 15

void icm20948_clock_source(uint8_t source);
void icm20948_odr_align_enable();

void icm20948_gyro_low_pass_filter(uint8_t config); // 0 - 7
void icm20948_accel_low_pass_filter(uint8_t config); // 0 - 7

// Output Data Rate = 1.125kHz / (1 + divider)
void icm20948_gyro_sample_rate_divider(uint8_t divider);
void icm20948_accel_sample_rate_divider(uint16_t divider);

void icm20948_gyro_calibration();
void icm20948_accel_calibration();

void icm20948_gyro_full_scale_select(gyro_full_scale full_scale);
void icm20948_accel_full_scale_select(accel_full_scale full_scale);


#endif	/* __ICM20948_H__ */




