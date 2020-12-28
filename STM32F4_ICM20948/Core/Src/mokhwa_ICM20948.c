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


uint8_t tx_buffer[6] = {0};
uint8_t rx_buffer[7] = {0};


/* Change The State of CS */
void CS_HIGH()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);
}

void CS_LOW()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}
/* Change The State of CS */


/* Select Bank Before Access the Register */
void SELECT_USER_BANK(UserBank UB)
{
	ICM20948_WRITE(B0_REG_BANK_SEL, UB);
}
/* Select Bank Before Access the Register */


/* SPI */
void ICM20948_READ(uint8_t regaddr, uint8_t len)
{
	CS_LOW();

	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);

	CS_HIGH();
}

void ICM20948_WRITE(uint8_t regaddr, uint8_t data)
{
	CS_LOW();

	tx_buffer[0] = WRITE | regaddr;
	tx_buffer[1] = data;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);

	CS_HIGH();
}
/* SPI */


/* Auxiliary I2C */
void MAG_READ(uint8_t magregaddr, uint8_t len)
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);	// Read
	ICM20948_WRITE(B3_I2C_SLV0_REG, magregaddr);

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_EXT_SLV_SENS_DATA_00, len);

}

void MAG_READ_MOD(uint8_t magregaddr, uint8_t len)
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, magregaddr);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, len | I2C_SLV_EN);
}

void MAG_WRITE(uint8_t magregaddr, uint8_t data)
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);	// Write
	ICM20948_WRITE(B3_I2C_SLV0_REG, magregaddr);
	ICM20948_WRITE(B3_I2C_SLV0_DO, data);
}

void MAG_WRITE_MOD(uint8_t magregaddr, uint8_t data)
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);	// Write
	ICM20948_WRITE(B3_I2C_SLV0_REG, magregaddr);
	ICM20948_WRITE(B3_I2C_SLV0_DO, data);
}

/* Auxiliary I2C */


ICM20948_STATUS ICM20948_DATA_READY()
{
	uint8_t data_ready;

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_INT_STATUS_1, 1);

	data_ready = rx_buffer[0];

	if(data_ready)
		return ICM20948_STATUS_OK;
	else
		return ICM20948_NO_DATA;
}


/* Check Connected Sensor is Right */
uint8_t WHOAMI_ICM20948()
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_WHO_AM_I, 1);

	return rx_buffer[0];
}

uint8_t WHOAMI_AK09916()
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_USER_CTRL, I2C_MST_EN);

	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_MST_CTRL, I2C_MST_CLK);

	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, MAG_WIA2);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, I2C_SLV_EN | 1);
	HAL_Delay(10);

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_EXT_SLV_SENS_DATA_00, 1);

	return rx_buffer[0];	// 0x09
}
/* Check Connected Sensor is Right */


/* Initialize ICM-20948(Gyroscope, accelerometer) */
void INIT_ICM20948()
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_PWR_MGMT_1, WAKE | CLKSEL);						// Wake the chip and Recommended clock selection(CLKSEL = 1)

	// Set Gyroscope ODR and Scale
	SELECT_USER_BANK(UserBank_2);
	ICM20948_WRITE(B2_GYRO_SMPLRT_DIV, Gyro_ODR_1100Hz);				// Gyro ODR = 1.1kHz
	ICM20948_WRITE(B2_GYRO_CONFIG_1, GYRO_FS_SEL_250dps | GYRO_FCHOICE);	// Gyro scale ±250dps and Enable DLPF

	// Set Accelerometer ODR and Scale
	ICM20948_WRITE(B2_ACCEL_SMPLRT_DIV_2, Accel_ODR_1100Hz);			// Accel ODR = 1.1kHz
	ICM20948_WRITE(B2_ACCEL_CONFIG, ACCEL_FS_SEL_2g | ACCEL_FCHOICE);	// Accel scale ±2g and Enable DLPF
}
/* Initialize ICM-20948(Gyroscope, accelerometer) */


/* Initialize AK09916(Magnetometer) */
void INIT_AK09916()
{
	// Enable I2C Master
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_USER_CTRL, I2C_MST_EN);

	// Initialize I2C Master
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_MST_ODR_CONFIG, I2C_MST_ODR_CONFIG);			// ODR configuration when gyroscope and accelerometer are disabled.
	ICM20948_WRITE(B3_I2C_MST_CTRL, I2C_MST_CLK);						// Sets I2C master clock frequency
	//SPI_WRITE(B3_I2C_MST_DELAY_CTRL, Reset_Value);					// Disabled
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, I2C_SLV_EN | 1);	// Enable I2C Slave and Read 6 bytes data

	// Initialize I2C Slave
	MAG_WRITE(MAG_CNTL3, 0x01);	// reset
	MAG_WRITE(MAG_CNTL2, Continuous_measurement_mode_4);
}


void INIT_MAG()
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, MAG_CNTL2);
	ICM20948_WRITE(B3_I2C_SLV0_DO, Continuous_measurement_mode_4);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, 0x81);
	HAL_Delay(10);

	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, MAG_CNTL2);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, 0x81);
	HAL_Delay(10);

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_EXT_SLV_SENS_DATA_00, 1);
}

/* Initialize AK09916(Magnetometer) */


/* Read Sensor Data */
void READ_GYRO(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_GYRO_XOUT_H, 6);

	myData->Gyro_X_Data = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	myData->Gyro_Y_Data = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	myData->Gyro_Z_Data = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void READ_ACCEL(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_ACCEL_XOUT_H, 6);

	myData->Accel_X_Data = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	myData->Accel_Y_Data = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	myData->Accel_Z_Data = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);
}

void READ_MAG(ICM20948_DATA* myData)
{
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, MAG_HXL);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, 0x87);
	HAL_Delay(10);

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_EXT_SLV_SENS_DATA_00, 7);

	//MAG_READ(MAG_HXL, 6);
	//MAG_READ_MOD(MAG_HXL, 7);

	myData->Mag_X_Data = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
	myData->Mag_Y_Data = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
	myData->Mag_Z_Data = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);
}
/* Read Sensor Data */












