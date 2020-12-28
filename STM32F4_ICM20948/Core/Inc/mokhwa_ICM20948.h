/*
*
* mokhwa_ICM20948.h
*
* writer : mokhwasomssi
* Chip : ICM-20948
* Breakout Board : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#ifndef __MOKHWA_ICM20948_H__
#define	__MOKHWA_ICM20948_H__

#include "mokhwa_ICM20948_REGISTER.h"			// Define Register List of ICM-20948
#include "stm32f4xx_hal.h"
#include "main.h"
#include "spi.h"


/* User Configuration */
#define SPI_ICM20948 		(&hspi1)			// SPI Number
#define CS_PIN_PORT			GPIOA				// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_4
/* User Configuration */


/* ICM20948 Status Enumeration */
typedef enum _ICM20948_STATUS
{
	ICM20948_STATUS_OK 		= 0,
	ICM20948_STATUS_ERROR 	= 1,
	ICM20948_WRONG_ID	 	= 2,
	ICM20948_NO_DATA		= 3
} ICM20948_STATUS;
/* ICM20948 Status Enumeration */


/* ICM20948 Data Structure */
typedef struct _ICM20948_DATA
{
	int16_t Accel_X_Data;		// Acceleromoter Output Data
	int16_t Accel_Y_Data;
	int16_t Accel_Z_Data;

	int16_t Gyro_X_Data;		// Gyroscope Output Data
	int16_t Gyro_Y_Data;
	int16_t Gyro_Z_Data;

	int16_t Mag_X_Data;			// Magnetometor Output Data
	int16_t Mag_Y_Data;
	int16_t Mag_Z_Data;
} ICM20948_DATA;
/* ICM20948 Data Structure */


/* UserBank */
typedef enum _UserBank
{
	UserBank_0		= 0 << 4,
	UserBank_1		= 1 << 4,
	UserBank_2		= 2 << 4,
	UserBank_3		= 3 << 4
} UserBank;
/* UserBank */


/* Enumeration ICM-20948 */
typedef enum _PWR_MGNT_1			// Reset Value : 0x41
{
	DEVICE_RESET 	= 1 << 7,		// Reset the internal registers and restores the default settings.
	SLEEP 			= 1 << 6,		// When set, the chip is set to sleep mode
	WAKE			= 0 << 6,		// Clearing the bit wakes the chip from sleep mode.
	LP_EN 			= 1 << 5,
	TEMP_DIS		= 1 << 3,
	CLKSEL 			= 1
} PWR_MGNT_1;

typedef enum _GYRO_SMPLRT_DIV
{
	Gyro_ODR_1100Hz = 0,			// Output Data Rate = 1.1kHz / (1 + GYRO_SMPLRT_DIV)
	Gyro_ODR_100Hz = 10,
	Gyro_ODR_10Hz = 109
} GYRO_SMPLRT_DIV;

typedef enum _GYRO_CONFIG_1			// Reset Value : 0x01
{
	GYRO_DLPFCFG = 0,				// Gyro low pass filter configuration (Table 16)
	GYRO_FS_SEL_250dps = 1,			// Gyro Full Scale Select
	GYRO_FS_SEL_500dps = 3,
	GYRO_FS_SEL_1000dps = 5,
	GYRO_FS_SEL_2000dps = 7,
	GYRO_FCHOICE = 1				// Enable gyro DLPF
} GYRO_CONFIG_1;

typedef enum _ACCEL_SMPLRT_DIV_2
{
	Accel_ODR_1100Hz = 0,			// Output Data Rate = 1.1kHz / (1 + ACCEL_SMPLRT_DIV)
	Accel_ODR_100Hz = 10,
	Accel_ODR_10Hz = 109
} ACCEL_SMPLRT_DIV_2;

typedef enum _ACCEL_CONFIG			// Reset Value : 0x01
{
	ACCEL_DLPFCFG = 0,				// accel low pass filter configuration (Table 18)
	ACCEL_FS_SEL_2g = 1,
	ACCEL_FS_SEL_4g = 3,
	ACCEL_FS_SEL_8g = 5,
	ACCEL_FS_SEL_16g = 7,
	ACCEL_FCHOICE = 1				// Enable accel DLPF
} ACCEL_CONFIG;

typedef enum _USER_CTRL
{
	DMP_EN 			= 1 << 7,		// Enables DMP features
	FIFO_EN 		= 1 << 6,		// Enable FIFO operation mode
	I2C_MST_EN 		= 1 << 5,		// Enable the I2C Master I/F module
	I2C_IF_DIS		= 1 << 4,		// Reset I2C Slave module
	DMP_RST 		= 1 << 3,		// Reset DMP module
	SRAM_RST 		= 1 << 2,		// Reset SRAM module
	I2C_MST_RST		= 1 << 1		// Reset I2C Master module
} USER_CTRL;

typedef enum _I2C_MST_ODR_CONFIG
{
	I2C_MST_ODR_CONFIG = 0					// ODR configuration for external sensor when gyroscope and accelerometer are disabled.
											// ODR = 1.1kHz / ( 2 ^(odr_config[3:0]) )
} _I2C_MST_ODR_CONFIG;

typedef enum _I2C_MST_CTRL
{
	MULT_MST_EN				= 1 << 7,				// Enables multi-master capability
	I2C_MST_P_NSR			= 1 << 4,				// This bit controls the I2C Master's transition
	I2C_MST_CLK				= 7						// Sets I2C master clock frequency (Table 23)
} I2C_MST_CTRL;

typedef enum _I2C_MST_DELAY_CTRL
{
	DELAY_ES_SHADOW			= 1 << 7,				// Delays shadowing of external sensor data until all data is received
	I2C_SLV4_DELAY_EN 		= 1 << 4,				// When enabled, slave 0-4 will only be accessed 1/(1+I2C_SLC4_DLY) samples
	I2C_SLV3_DELAY_EN 		= 1 << 3,				// as determined by I2C_MST_ODR_CONFIG
	I2C_SLV2_DELAY_EN 		= 1 << 2,
	I2C_SLV1_DELAY_EN 		= 1 << 1,
	I2C_SLV0_DELAY_EN 		= 1 << 0
} I2C_MST_DELAY_CTRL;

typedef enum _I2C_SLV_CTRL
{
	I2C_SLV_EN				= 1 << 7,		// Enable reading data from this slave.
	I2C_SLV_BYTE_SW 		= 1 << 6,		// Swap bytes when reading both the low and high byte of a word.
	I2C_SLV_REG_DIS 		= 1 << 5,		// When set, transaction does not write a register value.
	I2C_SLV_GRP 			= 1 << 4,		// External sensor data typically comes in as groups of two bytes
	I2C_SLV_LENG_6bytes 	= 6				// Number of bytes to be read from I2C slave
} I2C_SLV_CTRL;
/* Enumeration ICM-20948 */


/* Enumeration AK09916 */
typedef enum _CNTL2
{
	Power_down_mode = 0b00000,
	Single_measurement_mode = 0b00001,			// Sensor is measured for one time
	Continuous_measurement_mode_1 = 0b00010,	// Sensor is measured periodically in 10Hz
	Continuous_measurement_mode_2 = 0b00100,	// ... 20Hz
	Continuous_measurement_mode_3 = 0b00110,	// ... 50Hz
	Continuous_measurement_mode_4 = 0b01000,	// ... 100Hz
	Self_test_mode = 0b10000
} CNTL2;
/* Enumeration AK09916 */


/* functions */
void CS_HIGH();
void CS_LOW();

void SELECT_USER_BANK(UserBank UB);

void ICM20948_READ(uint8_t RegisterAddress, uint8_t Size);
void ICM20948_WRITE(uint8_t RegisterAddress, uint8_t WriteData);

void MAG_READ(uint8_t RegisterAddress, uint8_t Size);
void MAG_WRITE(uint8_t RegisterAddress, uint8_t WriteData);

void MAG_READ_MOD(uint8_t magregaddr, uint8_t len);
void MAG_WRITE_MOD(uint8_t magregaddr, uint8_t data);

ICM20948_STATUS ICM20948_DATA_READY();

uint8_t WHOAMI_ICM20948();
uint8_t WHOAMI_AK09916();

void INIT_ICM20948();
void INIT_AK09916();
void INIT_MAG();

void READ_GYRO(ICM20948_DATA* myData);
void READ_ACCEL(ICM20948_DATA* myData);
void READ_MAG(ICM20948_DATA* myData);
/* functions */

#endif	// __MOKHWA_ICM20948_H__






























