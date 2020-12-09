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

/* FUNCTIONS */
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
	HAL_SPI_Transmit(&hspi2, TX_Buffer, 2, 10);

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

void INIT_ICM20948(Gyro_ODR godr, Accel_ODR aodr, Gyro_Scale gs, Accel_Scale as)
{
	// Wake the Chip from Sleep Mode
	SELECT_USER_BANK(UsarBank_0);
	WRITE_REGISTER(B0_PWR_MGMT_1, 0x01);					// 0x01 is CLKSEL = 1 (recommended clock selection)

	// Set Output Data Rate
	SELECT_USER_BANK(UserBank_2);
	uint8_t GYRO_SMPLRT_DIV_Value = 1100/godr - 1;		// Output Data Rate = 1.1kHz / (1 + GYRO_SMPLRT_DIV)
	uint8_t ACCEL_SMPLRT_DIV_2_Value = 1125/aodr - 1;	// Output Data Rate = 1.125kHz / (1 + ACCEL_SMPLRT_DIV)
	WRITE_REGISTER(B2_GYRO_SMPLRT_DIV, GYRO_SMPLRT_DIV_Value);
	WRITE_REGISTER(B2_ACCEL_SMPLRT_DIV_2, ACCEL_SMPLRT_DIV_2_Value);

	// Set Gyro and Accel Scale
	SELECT_USER_BANK(UserBank_2);
	WRITE_REGISTER(B2_GYRO_CONFIG_1, gs | 0x01);			// 0x01 is Enable Gyro and Accel DLPF (reset value)
	WRITE_REGISTER(B2_ACCEL_CONFIG, as | 0x01);
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














