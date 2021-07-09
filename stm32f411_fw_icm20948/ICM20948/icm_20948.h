/*
*
* 	icm_20948.h
*
*  	Created on: Dec 26, 2020
*      Author: mokhwasomssi
*
*   gyro and accel 		: icm-20948
*	magnatometer 		: ak09916
*   Breakout Board		: SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/


#ifndef _ICM_20948_H_
#define	_ICM_20948_H_


#include <icm_20948_reg.h>
#include "spi.h"

#include <stdio.h>


// User Configuration
#define SPI_ICM20948 		(&hspi1)	  	  	// SPI Number
#define CS_PIN_PORT         GPIOA			 	// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_4


typedef enum unit_e
{
	unit_lsb,
	unit_dps,
	unit_g,
	unit_deg,
	unit_uT

} unit_e;

typedef enum
{
	userbank_0		= 0 << 4,
	userbank_1		= 1 << 4,
	userbank_2		= 2 << 4,
	userbank_3		= 3 << 4
} userbank_e;

typedef enum
{
	gy_fs_250dps = 0,
	gy_fs_500dps = 2,
	gy_fs_1000dps = 4,
	gy_fs_2000dps = 6

} gyro_fs_e;	// full scale

typedef enum
{
	ac_fs_2g = 1,
	ac_fs_4g = 3,
	ac_fs_8g = 5,
	ac_fs_16g = 7

} accel_fs_e;

typedef enum
{
	odr_1125_hz = 0,
	odr_563_hz = 1,
	odr_375_hz = 2,
	odr_225_hz = 4,
	odr_125_hz = 8

} odr_e; // output data rate

typedef enum
{
	power_down 				 = 0,
	single_measure 			 = 1,
	continuous_measure_10hz  = 2,
	continuous_measure_20hz  = 4,
	continuous_measure_50hz  = 6,
	continuous_measure_100hz = 8,
	self_test 				 = 16

} mag_opmode_e;	// operation mode

typedef struct
{
	float x;
	float y;
	float z;

} gyro_data_t;

typedef struct
{
	float x;
	float y;
	float z;

} accel_data_t;

typedef struct
{
	float x;
	float y;
	float z;

} mag_data_t;


// sensor data structure
gyro_data_t gyro_data;
accel_data_t accel_data;
mag_data_t mag_data;


// cs state
void cs_high();
void cs_low();

// user bank
void select_user_bank(userbank_e ub);

// read / write
void read_icm20948(uint8_t regaddr, uint8_t len);
void write_icm20948(uint8_t regaddr, uint8_t data);

// auxiliary i2c
void read_ak09916(uint8_t regaddr, uint8_t len);
void write_ak09916(uint8_t regaddr, uint8_t data);

// check sensor id
void whoami_icm20948();	// 0xEA
void whoami_ak09916();	// 0x09

// initialize
void icm20948_init(gyro_fs_e gy_fs, odr_e gy_odr, accel_fs_e ac_fs, odr_e ac_odr);
void ak09916_init(mag_opmode_e op_mode);

// read sensor data
void read_gyro(gyro_data_t* gyro_data, unit_e unit);
void read_accel(accel_data_t* accel_data, unit_e unit);
void read_mag(mag_data_t* mag_data, unit_e unit);


#endif	/* _ICM_20948_H_ */




