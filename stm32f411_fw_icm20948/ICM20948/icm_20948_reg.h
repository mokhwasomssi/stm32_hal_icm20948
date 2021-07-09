/*
*
* icm_20948_register.h
*
 *  Created on: Dec 26, 2020
 *      Author: mokhwasomssi
 *
*   Chip : ICM-20948
*   Breakout Board : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#ifndef _ICM_20948_REGISTER_H_
#define _ICM_20948_REGISTER_H_


#define DEVICE_ID_ICM20948				0xEA
#define DEVICE_ID_AK09916				0x09

#define ADDRESS_AK09916					0x0C		// The slave address of AK09916

#define RESET_VALUE				    	0x00
#define READ							0x80
#define WRITE							0x00


// Register Map for Magnetometer
// Magnetometer Name : AK09916
#define MAG_WIA2						0x01		// Device ID : 0x09
#define MAG_ST1							0x10		// Status 1

#define MAG_HXL							0x11		// Magnetometer X,Y,Z-axis Data
#define MAG_HXH							0x12
#define MAG_HYL							0x13
#define MAG_HYH							0x14
#define MAG_HZL							0x15
#define MAG_HZH							0x16

#define MAG_ST2							0x18		// Status 2

#define MAG_CNTL2						0x31		// Control
#define MAG_CNTL3						0x32

#define MAG_TS1							0x33		// TEST
#define MAG_TS2							0x34


// Register Map for Gyroscope and Accelerometer
// Divided into USER BANK 0, USER BANK 1, USER BANK 2, USER BANK 3 

/* USER BANK 0 */
#define B0_WHO_AM_I						0x00		//The value for ICM-20948 is 0xEA
#define B0_USER_CTRL					0x03
#define B0_LP_CONFIG					0x05
#define B0_PWR_MGMT_1					0x06
#define B0_PWR_MGMT_2					0x07


#define B0_INT_PIN_CFG					0x0F		// Interupt Configuration
#define B0_INT_ENABLE					0x10
#define B0_INT_ENABLE_1					0x11
#define B0_INT_ENABLE_2					0x12
#define B0_INT_ENABLE_3					0x13

#define B0_I2C_MST_STATUS				0x17		// I2C Status

#define B0_INT_STATUS					0x19		// Interupt Status
#define B0_INT_STATUS_1					0x1A
#define B0_INT_STATUS_2					0x1B
#define B0_INT_STATUS_3					0x1C

#define B0_DELAY_TIMEH					0x28
#define B0_DELAY_TIMEL					0x29


#define B0_ACCEL_XOUT_H					0x2D		// Accelerometer X,Y,Z-axis Data
#define B0_ACCEL_XOUT_L					0x2E		
#define B0_ACCEL_YOUT_H					0x2F		
#define B0_ACCEL_YOUT_L					0x30		
#define B0_ACCEL_ZOUT_H					0x31		
#define B0_ACCEL_ZOUT_L					0x32	

#define B0_GYRO_XOUT_H					0x33		// Gyroscope X,Y,Z-axis Data
#define B0_GYRP_XOUT_L					0x34
#define B0_GYRO_YOUT_H					0x35
#define B0_GYRP_YOUT_L					0x36
#define B0_GYRO_ZOUT_H					0x37
#define B0_GYRP_ZOUT_L					0x38

#define B0_TEMP_OUT_H					0x39		// Temp Sensor Data
#define B0_TEMP_OUT_L					0x3A

#define B0_EXT_SLV_SENS_DATA_00			0x3B		//Sensor Data read from external I2C devices via I2C master interface
#define B0_EXT_SLV_SENS_DATA_01			0x3C
#define B0_EXT_SLV_SENS_DATA_02			0x3D
#define B0_EXT_SLV_SENS_DATA_03			0x3E
#define B0_EXT_SLV_SENS_DATA_04			0x3F
#define B0_EXT_SLV_SENS_DATA_05			0x40

/*
#define B0_EXT_SLV_SENS_DATA_06			0x41
#define B0_EXT_SLV_SENS_DATA_07			0x42
#define B0_EXT_SLV_SENS_DATA_08			0x43
#define B0_EXT_SLV_SENS_DATA_09			0x44
#define B0_EXT_SLV_SENS_DATA_10			0x45
#define B0_EXT_SLV_SENS_DATA_11			0x46
#define B0_EXT_SLV_SENS_DATA_12			0x47
#define B0_EXT_SLV_SENS_DATA_13			0x48
#define B0_EXT_SLV_SENS_DATA_14			0x49
#define B0_EXT_SLV_SENS_DATA_15			0x4A
#define B0_EXT_SLV_SENS_DATA_16			0x4B
#define B0_EXT_SLV_SENS_DATA_17			0x4C
#define B0_EXT_SLV_SENS_DATA_18			0x4D
#define B0_EXT_SLV_SENS_DATA_19			0x4E
#define B0_EXT_SLV_SENS_DATA_20			0x4F
#define B0_EXT_SLV_SENS_DATA_21			0x50
#define B0_EXT_SLV_SENS_DATA_22			0x51
#define B0_EXT_SLV_SENS_DATA_23			0x52
*/

/*
#define B0_FIFO_EN_1					0x66		// FIFO
#define B0_FIFO_EN_2					0x67
#define B0_FIFO_RST						0x68
#define B0_FIFO_MODE					0x69
#define B0_FIFO_COUNTH					0X70
#define B0_FIFO_COUNTL					0X71
#define B0_FIFO_R_W						0x72

#define B0_DATA_RDY_STATUS				0x74
		
#define B0_FIFO_CFG						0x76	
*/

#define B0_REG_BANK_SEL					0x7F		// Select a USER BANK


/* USER BANK 1 */

/*
#define B1_SELF_TEST_X_GYRO				0x02		// Self Test for Gyroscope
#define B1_SELF_TEST_Y_GYRO				0x03
#define B1_SELF_TEST_Z_GYRO				0x04

#define B1_SELF_TEST_X_ACCEL			0x0E		// Self Test for Accelerometer
#define B1_SELF_TEST_Y_ACCEL			0x0F
#define B1_SELF_TEST_Z_ACCEL			0x10
*/

#define B1_XA_OFFS_H					0x14		// Accelerometer Offset Cancellation
#define B1_XA_OFFS_L					0x15
#define B1_YA_OFFS_H					0x17
#define B1_YA_OFFS_L					0x18
#define B1_ZA_OFFS_H					0x1A
#define B1_ZA_OFFS_L					0x1B

/*
#define B1_TIMEBASE_CORRECTION_PLL		0x28		// System PLL Clock Period Error
*/

#define B1_REG_BANK_SEL					0x7F		// Select a USER BANK


/* USER BANK 2 */
#define B2_GYRO_SMPLRT_DIV				0x00		// Gyro Sample Rate Divider

#define B2_GYRO_CONFIG_1				0x01		// Gyro Configuration
#define B2_GYRO_CONFIG_2				0x02

#define B2_XG_OFFS_USRH					0x03		// Gyro Offset cancellation
#define B2_XG_OFFS_USRL 				0x04
#define B2_YG_OFFS_USRH					0x05
#define B2_YG_OFFS_USRL					0x06
#define B2_ZG_OFFS_USRH					0x07
#define B2_ZG_OFFS_USRL					0x08


#define B2_ODR_ALIGN_EN					0x09		// ODR Start-Time Alignment


#define B2_ACCEL_SMPLRT_DIV_1			0x10		// ACCEL Sample Rate Divider
#define B2_ACCEL_SMPLRT_DIV_2			0x11		

/*
#define B2_ACCEL_INTEL_CTRL				0x12		
#define B2_ACCEL_WOM_THR				0x13
*/

#define B2_ACCEL_CONFIG					0x14		// ACCEL Configuration
#define B2_ACCEL_CONFIG_2				0x15

/*
#define B2_FSYNC_CONFIG					0x52

#define B2_TEMP_CONFIG					0x53

#define B2_MOD_CTRL_USR					0X54
*/

#define B2_REG_BANK_SEL					0x7F		// Select a USER BANK


/* USER BANK 3 */
#define B3_I2C_MST_ODR_CONFIG			0x00		// I2C Master Configuration
#define B3_I2C_MST_CTRL					0x01
#define B3_I2C_MST_DELAY_CTRL			0x02	

#define B3_I2C_SLV0_ADDR				0x03		// I2C Slave Configuration
#define B3_I2C_SLV0_REG					0x04		
#define B3_I2C_SLV0_CTRL				0x05
#define B3_I2C_SLV0_DO					0x06

/*
#define B3_I2C_SLV1_ADDR				0x07		
#define B3_I2C_SLV1_REG					0x08		
#define B3_I2C_SLV1_CTRL				0x09
#define B3_I2C_SLV1_DO					0x0A

#define B3_I2C_SLV2_ADDR				0x0B		
#define B3_I2C_SLV2_REG					0x0C		
#define B3_I2C_SLV2_CTRL				0x0D
#define B3_I2C_SLV2_DO					0x0E

#define B3_I2C_SLV3_ADDR				0x0F		
#define B3_I2C_SLV3_REG					0x10		
#define B3_I2C_SLV3_CTRL				0x11
#define B3_I2C_SLV3_DO					0x12

#define B3_I2C_SLV4_ADDR				0x13	
#define B3_I2C_SLV4_REG					0x14		
#define B3_I2C_SLV4_CTRL				0x15
#define B3_I2C_SLV4_DO					0x16
#define B3_I2C_SLV4_DI					0x17
*/
	
#define B3_REG_BANK_SEL					0x7F		// Select a USER BANK




// registers
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
	Gyro_ODR_1125Hz = 0,			// Output Data Rate = 1.1kHz / (1 + GYRO_SMPLRT_DIV)
	Gyro_ODR_100Hz = 10,
	Gyro_ODR_10Hz = 109
} GYRO_SMPLRT_DIV;

typedef enum _GYRO_CONFIG_1			// Reset Value : 0x01
{
	GYRO_DLPFCFG = 0,				// Gyro low pass filter configuration (Table 16)
	GYRO_FS_SEL_250dps = 0,			// Gyro Full Scale Select
	GYRO_FS_SEL_500dps = 2,
	GYRO_FS_SEL_1000dps = 4,
	GYRO_FS_SEL_2000dps = 6,
	GYRO_FCHOICE = 1				// Enable gyro DLPF
} GYRO_CONFIG_1;



typedef enum _ODR_ALING_EN
{
	ODR_START_TIME_ALIGNMENT_DISABLE = 0,
	ODR_START_TIME_ALIGNMENT_ENABLE = 1

} ODR_ALING_EN;

typedef enum _ACCEL_SMPLRT_DIV_2
{
	Accel_ODR_1125Hz = 0,			// Output Data Rate = 1.1kHz / (1 + ACCEL_SMPLRT_DIV)
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




#endif	/* _ICM_20948_REGISTER_H_ */
