/*
*
* mokhwa_ICM20948.h
*
* writer : mokhwasomssi
* Chip : ICM-20948
* Breakout Board : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#include "mokhwa_ICM20948_REGISTER.h"
#include "mokhwa_ICM20948.h"

uint8_t TX_Buffer[6] = {0};
uint8_t RX_Buffer[6] = {0};

/* functions */
void CS_HIGH()		// Change The State of CS
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);
}

void CS_LOW()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}


void READ_REGISTER(uint8_t RegisterAddress, uint8_t Size)
{
	CS_LOW();

	TX_Buffer[0] = 0x80 | RegisterAddress;
	HAL_SPI_Transmit(SPI_ICM20948, TX_Buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, RX_Buffer, Size, 10);

	CS_HIGH();
}

void WRITE_REGISTER(uint8_t RegisterAddress, uint8_t WriteData)
{
	CS_LOW();

	TX_Buffer[0] = 0x00 | RegisterAddress;
	TX_Buffer[1] = WriteData;
	HAL_SPI_Transmit(SPI_ICM20948, TX_Buffer, 2, 10);

	CS_HIGH();
}

uint8_t WHOAMI()								// Check Connected Sensor is ICM-20948
{
	SELECT_USER_BANK(UsarBank_0);
	READ_REGISTER(B0_WHO_AM_I, 1);

	return RX_Buffer[0];
}

void SELECT_USER_BANK(UserBank UB)						// Select Bank Before Access the Register
{
	WRITE_REGISTER(B0_REG_BANK_SEL, UB);
}

/* Initialize ICM-20948(Gyroscope, accelerometer) */
void INIT_ICM20948()
{
	SELECT_USER_BANK(UsarBank_0);
	WRITE_REGISTER(B0_PWR_MGMT_1, WAKE | CLKSEL);						// Wake the chip and Recommended clock selection(CLKSEL = 1)

	// Set Gyroscope ODR and Scale
	SELECT_USER_BANK(UserBank_2);
	WRITE_REGISTER(B2_GYRO_SMPLRT_DIV, Gyro_ODR_1100Hz);				// Gyro ODR = 1.1kHz
	WRITE_REGISTER(B2_GYRO_CONFIG_1, GYRO_FS_SEL_250dps | GYRO_FCHOICE);	// Gyro scale ±250dps and Enable DLPF

	// Set Accelerometer ODR and Scale
	WRITE_REGISTER(B2_ACCEL_SMPLRT_DIV_2, Accel_ODR_1100Hz);			// Accel ODR = 1.1kHz
	WRITE_REGISTER(B2_ACCEL_CONFIG, ACCEL_FS_SEL_2g | ACCEL_FCHOICE);	// Accel scale ±2g and Enable DLPF
}

/* Initialize AK09916(Magnetometer) */
void INIT_AK09916()
{
	SELECT_USER_BANK(UsarBank_0);
	WRITE_REGISTER(B0_USER_CTRL, I2C_MST_EN);							// Enable I2C Master

	SELECT_USER_BANK(UserBank_3);



	WRITE_REGISTER(B3_I2C_MST_ODR_CONFIG, I2C_MST_ODR_CONFIG);			// ODR configuration when gyroscope and accelerometer are disabled.
	WRITE_REGISTER(B3_I2C_MST_CTRL, I2C_MST_CLK);						// Sets I2C master clock frequency
	WRITE_REGISTER(B3_I2C_MST_DELAY_CTRL, Reset_Value);					// Disabled
	WRITE_REGISTER(B3_I2C_SLV0_CTRL, I2C_SLV_EN | I2C_SLV_LENG_6bytes);	// Enable I2C Slave and Read 6 bytes data
}

void READ_GYRO(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UsarBank_0);
	READ_REGISTER(B0_GYRO_XOUT_H, 6);

	myData->Gyro_X_Data = (int16_t)(RX_Buffer[0] << 8 | RX_Buffer[1]);
	myData->Gyro_Y_Data = (int16_t)(RX_Buffer[2] << 8 | RX_Buffer[3]);
	myData->Gyro_Z_Data = (int16_t)(RX_Buffer[4] << 8 | RX_Buffer[5]);
}

void READ_ACCEL(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UsarBank_0);
	READ_REGISTER(B0_ACCEL_XOUT_H, 6);

	myData->Accel_X_Data = (int16_t)(RX_Buffer[0] << 8 | RX_Buffer[1]);
	myData->Accel_Y_Data = (int16_t)(RX_Buffer[2] << 8 | RX_Buffer[3]);
	myData->Accel_Z_Data = (int16_t)(RX_Buffer[4] << 8 | RX_Buffer[5]);
}

void READ_MAG(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UserBank_3);

	WRITE_REGISTER(B3_I2C_SLV0_ADDR, AK09916_Address);
	WRITE_REGISTER(B3_I2C_SLV0_REG, MAG_CNTL2);
	WRITE_REGISTER(B3_I2C_SLV0_DO, 0x02);

	WRITE_REGISTER(B3_I2C_SLV0_ADDR, AK09916_Address);
	WRITE_REGISTER(B3_I2C_SLV0_REG, MAG_HXL);
	READ_REGISTER(B0_EXT_SLV_SENS_DATA_00, 6);

	myData->Mag_X_Data = (int16_t)(RX_Buffer[0] << 8 | RX_Buffer[1]);
	myData->Mag_Y_Data = (int16_t)(RX_Buffer[2] << 8 | RX_Buffer[3]);
	myData->Mag_Z_Data = (int16_t)(RX_Buffer[4] << 8 | RX_Buffer[5]);
}
/* functions */













