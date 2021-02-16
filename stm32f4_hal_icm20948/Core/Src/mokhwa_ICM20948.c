/*
*
* mokhwa_ICM20948.c
*
* Updata Date : 2020-01-03
* writer : mokhwasomssi
* Chip : ICM-20948
* Breakout Board : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)
*
*/

#include "mokhwa_ICM20948_REGISTER.h"
#include "mokhwa_ICM20948.h"


/* Temporary Array */
uint8_t tx_buffer[6] = {0};
uint8_t rx_buffer[6] = {0};


/* Change The State of CS */
void CS_HIGH()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);
}

void CS_LOW()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}


/* Select Bank Before Access the Register */
void SELECT_USER_BANK(UserBank UB)
{
	ICM20948_WRITE(B0_REG_BANK_SEL, UB);
}


/* Read/Write ICM20948 */
void ICM20948_READ(uint8_t regaddr, uint8_t len)
{
	CS_LOW();
	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);
	CS_HIGH();

	HAL_Delay(1);
}

void ICM20948_WRITE(uint8_t regaddr, uint8_t data)
{
	CS_LOW();
	tx_buffer[0] = WRITE | regaddr;
	tx_buffer[1] = data;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	CS_HIGH();

	HAL_Delay(1);
}

/* Read/Write AK09916 */
void AK09916_READ(uint8_t regaddr, uint8_t len)
{
	SELECT_USER_BANK(UserBank_3);

	ICM20948_WRITE(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, regaddr); 
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, I2C_SLV_EN | len);

	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_EXT_SLV_SENS_DATA_00, len);

	HAL_Delay(1);
}

void AK09916_WRTIE(uint8_t regaddr, uint8_t data)
{
	SELECT_USER_BANK(UserBank_3);

	ICM20948_WRITE(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);
	ICM20948_WRITE(B3_I2C_SLV0_REG, regaddr);
	ICM20948_WRITE(B3_I2C_SLV0_DO, data);
	ICM20948_WRITE(B3_I2C_SLV0_CTRL, 0x81);

	HAL_Delay(1);
}


/* Who Am I */
uint8_t WHOAMI_ICM20948()
{
	SELECT_USER_BANK(UserBank_0);
	ICM20948_READ(B0_WHO_AM_I, 1);

	return rx_buffer[0];
}

uint8_t WHOAMI_AK09916()
{
	AK09916_READ(MAG_WIA2, 1);

	return rx_buffer[0];	// 0x09
}


/* Initialize ICM-20948(Gyroscope, accelerometer) */
void INIT_ICM20948()
{
	// ICM20948 Reset
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_PWR_MGMT_1, DEVICE_RESET | 0x41);

	// SPI mode only
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_USER_CTRL, I2C_IF_DIS);

	// Wake the chip and Recommended clock selection(CLKSEL = 1)
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_PWR_MGMT_1, WAKE | CLKSEL);

	// Set Gyroscope ODR and Scale
	SELECT_USER_BANK(UserBank_2);
	ICM20948_WRITE(B2_GYRO_SMPLRT_DIV, Gyro_ODR_1100Hz);				// Gyro ODR = 1.1kHz
	ICM20948_WRITE(B2_GYRO_CONFIG_1, GYRO_FS_SEL_250dps | GYRO_FCHOICE);	// Gyro scale ±250dps and Enable DLPF

	// Set Accelerometer ODR and Scale
	ICM20948_WRITE(B2_ACCEL_SMPLRT_DIV_2, Accel_ODR_1100Hz);			// Accel ODR = 1.1kHz
	ICM20948_WRITE(B2_ACCEL_CONFIG, ACCEL_FS_SEL_2g | ACCEL_FCHOICE);	// Accel scale ±2g and Enable DLPF
}


/* Initialize AK09916(Magnetometer) */
void INIT_AK09916()
{
	// I2C Master Reset
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_USER_CTRL, I2C_MST_RST);

	// I2C Master Enable
	SELECT_USER_BANK(UserBank_0);
	ICM20948_WRITE(B0_USER_CTRL, I2C_MST_EN);

	// I2C Master Clock Frequency
	SELECT_USER_BANK(UserBank_3);
	ICM20948_WRITE(B3_I2C_MST_CTRL, I2C_MST_CLK); // 345.6 kHz

	// I2C Slave Reset
	AK09916_WRTIE(MAG_CNTL3, 0x01);
	
	// I2C Slave Operation Mode
	AK09916_WRTIE(MAG_CNTL2, Continuous_measurement_mode_4);
}


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
	int16_t data[3] = {0};

	// Read status1(ST1) register
	AK09916_READ(MAG_ST1,1);

	// check data is ready
	if((rx_buffer[0] & 0x01) == 1)
	{ 
		// Read Measurement data register(HXL to HZH)
		AK09916_READ(MAG_HXL, 6);

		data[0] = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
		data[1] = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
		data[2] = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);

		// Read status2(ST2) register
		AK09916_READ(MAG_ST2, 1);

		if((rx_buffer[0] & 0x08) == 0x00) // not overflow
		{
			myData->Mag_X_Data = data[0];
			myData->Mag_Y_Data = data[1];
			myData->Mag_Z_Data = data[2];
		}
	}
}