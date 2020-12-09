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
#include "stm32f1xx_hal.h"
#include "main.h"
#include "spi.h"


/* User Configuration */
#define SPI_ICM20948 		(&hspi2)			// SPI Number
#define CS_PIN_PORT			GPIOB				// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_12
/* User Configuration */


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


/* typedef */
typedef enum _UserBank
{
	UsarBank_0,
	UserBank_1,
	UserBank_2,
	UserBank_3
} UserBank;

typedef enum _GyroOutDataRate
{
	Gyro_ODR_1100Hz = 0,
	Gyro_ODR_100Hz = 10,
	Gyro_ODR_10Hz = 109
} Gyro_ODR;

typedef enum _AccelOutDataRate
{
	Accel_ODR_1100Hz = 0,
	Accel_ODR_100Hz = 10,
	Accel_ODR_10Hz = 109
} Accel_ODR;

typedef enum _GyroFullScaleSellet
{
	Gyro_Scale_250dp = 1,
	Gyro_Scale_500dps = 3,
	Gyro_Scale_1000dps = 5,
	Gyro_Scale_2000dps = 7
} Gyro_Scale;

typedef enum _AccelFullScaleSellet
{
	Accel_Scale_2g = 1,
	Accel_Scale_4g = 3,
	Accel_Scale_8g = 5,
	Accel_Scale_16g = 7
} Accel_Scale;
/* typedef */


/* functions */
void CS_HIGH();
void CS_LOW();

void READ_REGISTER(uint8_t RegisterAddress, uint8_t Size);
void WRITE_REGISTER(uint8_t RegisterAddress, uint8_t WriteData);

uint8_t WHOAMI();
void SELECT_USER_BANK(UserBank UB);
void INIT_ICM20948(Gyro_ODR godr, Accel_ODR aodr, Gyro_Scale gs, Accel_Scale as);

void READ_GYRO(ICM20948_DATA* myData);
void READ_ACCEL(ICM20948_DATA* myData);
/* functions */


#endif	// __MOKHWA_ICM20948_H__
