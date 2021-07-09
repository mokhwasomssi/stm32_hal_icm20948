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


#include <icm_20948.h>


// temporary array
uint8_t tx_buffer[6] = {0};
uint8_t rx_buffer[6] = {0};


// constant for changing unit
float gyro_typ;
float accel_typ;
float mag_typ = 0.15;


// cs state
void cs_high()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, SET);	
}

void cs_low()
{
	HAL_GPIO_WritePin(CS_PIN_PORT, CS_PIN_NUMBER, RESET);
}

// user bank
void select_user_bank(userbank_e ub)
{
	cs_low();
	tx_buffer[0] = WRITE | B0_REG_BANK_SEL;
	tx_buffer[1] = ub;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	cs_high();
}

// spi
void read_icm20948(uint8_t regaddr, uint8_t len)
{
	cs_low();
	tx_buffer[0] = READ | regaddr;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 1, 10);
	HAL_SPI_Receive(SPI_ICM20948, rx_buffer, len, 10);
	cs_high();
}

void write_icm20948(uint8_t regaddr, uint8_t data)
{
	cs_low();
	tx_buffer[0] = WRITE | regaddr;
	tx_buffer[1] = data;
	HAL_SPI_Transmit(SPI_ICM20948, tx_buffer, 2, 10);
	cs_high();

	// necessary
	HAL_Delay(1);
}

// auxiliary i2c
void read_ak09916(uint8_t regaddr, uint8_t len)
{
	select_user_bank(userbank_3);

	write_icm20948(B3_I2C_SLV0_ADDR, READ | ADDRESS_AK09916);
	write_icm20948(B3_I2C_SLV0_REG, regaddr); 
	write_icm20948(B3_I2C_SLV0_CTRL, I2C_SLV_EN | len);

	select_user_bank(userbank_0);
	read_icm20948(B0_EXT_SLV_SENS_DATA_00, len);
}

void write_ak09916(uint8_t regaddr, uint8_t data)
{
	select_user_bank(userbank_3);

	write_icm20948(B3_I2C_SLV0_ADDR, WRITE | ADDRESS_AK09916);
	write_icm20948(B3_I2C_SLV0_REG, regaddr);
	write_icm20948(B3_I2C_SLV0_DO, data);
	write_icm20948(B3_I2C_SLV0_CTRL, 0x81);

}

// check sensor id
void whoami_icm20948()
{
	select_user_bank(userbank_0);
	read_icm20948(B0_WHO_AM_I, 1);
	while(rx_buffer[0] != DEVICE_ID_ICM20948)
		{
			printf("it isn't icm20948\n");
			HAL_Delay(1000);
		}
}

void whoami_ak09916()
{
	read_ak09916(MAG_WIA2, 1);
	while(rx_buffer[0] != DEVICE_ID_AK09916)
		{
			printf("it isn't ak09916\n");
			HAL_Delay(1000);
		}
}

// set full scale and ODR
void set_gyro_full_scale(gyro_fs_e gyro_fs)
{
	select_user_bank(userbank_2);
	write_icm20948(B2_GYRO_CONFIG_1, gyro_fs | GYRO_FCHOICE);

	switch(gyro_fs)
	{
		case gy_fs_250dps :
			gyro_typ = 131;
			break;
		
		case gy_fs_500dps :
			gyro_typ = 65.5;
			break;

		case gy_fs_1000dps :
			gyro_typ = 32.8;
			break;
		
		case gy_fs_2000dps :
			gyro_typ = 16.4;
			break;

		default : 
			gyro_typ = 0;
	}
}

void set_accel_full_scale(accel_fs_e accel_fs)
{
	select_user_bank(userbank_2);
	write_icm20948(B2_ACCEL_CONFIG, accel_fs | ACCEL_FCHOICE);

	switch(accel_fs)
	{
		case ac_fs_2g :
			accel_typ = 16384;
			break;
		
		case ac_fs_4g :
			accel_typ = 8192;
			break;

		case ac_fs_8g :
			accel_typ = 4096;
			break;
		
		case ac_fs_16g :
			accel_typ = 2048;
			break;

		default : 
			accel_typ = 0;
	}
}

void set_gyro_odr(odr_e odr)
{
	select_user_bank(userbank_2);

	uint8_t gy_div = odr;
	write_icm20948(B2_GYRO_SMPLRT_DIV, gy_div);
}

void set_accel_odr(odr_e odr)
{
	select_user_bank(userbank_2);

	uint8_t ac_div = odr;
	write_icm20948(B2_ACCEL_SMPLRT_DIV_2, ac_div);
}

// initialize
void icm20948_init(gyro_fs_e gy_fs, odr_e gy_odr, accel_fs_e ac_fs, odr_e ac_odr)
{
	// ICM20948 Reset
	select_user_bank(userbank_0);
	write_icm20948(B0_PWR_MGMT_1, DEVICE_RESET | 0x41);	// 0x41 is reset value

	// SPI mode only
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_IF_DIS);

	// Wake the chip and Recommended clock selection(CLKSEL = 1)
	select_user_bank(userbank_0);
	write_icm20948(B0_PWR_MGMT_1, WAKE | CLKSEL);

	// ODR start time alignment
	select_user_bank(userbank_2);
	write_icm20948(B2_ODR_ALIGN_EN, ODR_START_TIME_ALIGNMENT_ENABLE);

	// set full scale range
	set_gyro_full_scale(gy_fs);
	set_accel_full_scale(ac_fs);

	// set odr
	set_gyro_odr(gy_odr);
	set_accel_odr(ac_odr);


	printf("icm20948 initialized\n");
}

// i2c : master(icm-20948) / slave(ak09916)
void ak09916_init(mag_opmode_e op_mode)
{
	// I2C Master Reset
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_MST_RST);

	// I2C Master Enable
	select_user_bank(userbank_0);
	write_icm20948(B0_USER_CTRL, I2C_MST_EN);

	// I2C Master Clock Frequency
	select_user_bank(userbank_3);
	write_icm20948(B3_I2C_MST_CTRL, I2C_MST_CLK); // 345.6 kHz

	// I2C Slave Reset
	write_ak09916(MAG_CNTL3, 0x01);
	
	// I2C Slave Operation Mode
	write_ak09916(MAG_CNTL2, op_mode);


	printf("ak09916 initialized\n");
}

// read gyro
void read_gyro(gyro_data_t* gyro_data, unit_e unit)
{
	int16_t gyro_data_temp[3];

	select_user_bank(userbank_0);
	read_icm20948(B0_GYRO_XOUT_H, 6);

	gyro_data_temp[0] = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	gyro_data_temp[1] = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	gyro_data_temp[2] = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);

	switch(unit)
	{
		case unit_lsb :
			gyro_data->x = gyro_data_temp[0];
			gyro_data->y = gyro_data_temp[1];
			gyro_data->z = gyro_data_temp[2];
			break;
		
		case unit_dps : 
			gyro_data->x = (float)(gyro_data_temp[0] / gyro_typ);
			gyro_data->y = (float)(gyro_data_temp[1] / gyro_typ);
			gyro_data->z = (float)(gyro_data_temp[2] / gyro_typ);
			break;

		default : 
			gyro_data->x = 0;
			gyro_data->y = 0;
			gyro_data->z = 0;
	}
}


void read_accel(accel_data_t* accel_data, unit_e unit)
{
	int16_t accel_data_temp[3];

	select_user_bank(userbank_0);
	read_icm20948(B0_ACCEL_XOUT_H, 6);
	
	accel_data_temp[0] = (int16_t)(rx_buffer[0] << 8 | rx_buffer[1]);
	accel_data_temp[1] = (int16_t)(rx_buffer[2] << 8 | rx_buffer[3]);
	accel_data_temp[2] = (int16_t)(rx_buffer[4] << 8 | rx_buffer[5]);

	switch(unit)
	{
		case unit_lsb :
			accel_data->x = accel_data_temp[0];
			accel_data->y = accel_data_temp[1];
			accel_data->z = accel_data_temp[2];
			break;
		
		case unit_g : 
			accel_data->x = (float)(accel_data_temp[0] / accel_typ);
			accel_data->y = (float)(accel_data_temp[1] / accel_typ);
			accel_data->z = (float)(accel_data_temp[2] / accel_typ);
			break;

		default :
			accel_data->x = 0;
			accel_data->y = 0;
			accel_data->z = 0;
	}
}


// read mag
void read_mag(mag_data_t* mag_data, unit_e unit)
{
	int16_t mag_data_temp[3] = {0};

	// Read status1(ST1) register
	read_ak09916(MAG_ST1,1);

	// check data is ready
	if((rx_buffer[0] & 0x01) == 1)
	{ 
		// Read Measurement data register(HXL to HZH)
		read_ak09916(MAG_HXL, 6);
		mag_data_temp[0] = (int16_t)(rx_buffer[1] << 8 | rx_buffer[0]);
		mag_data_temp[1] = (int16_t)(rx_buffer[3] << 8 | rx_buffer[2]);
		mag_data_temp[2] = (int16_t)(rx_buffer[5] << 8 | rx_buffer[4]);

		// Read status2(ST2) register
		read_ak09916(MAG_ST2, 1);
		if((rx_buffer[0] & 0x08) == 0x00) // not overflow
		{
			switch(unit)
			{
				case unit_lsb :
					mag_data->x = mag_data_temp[0];
					mag_data->y = mag_data_temp[1];
					mag_data->z = mag_data_temp[2];
					break;
				
				case unit_uT : 
					mag_data->x = (float)(mag_data_temp[0] / mag_typ);
					mag_data->y = (float)(mag_data_temp[1] / mag_typ);
					mag_data->z = (float)(mag_data_temp[2] / mag_typ);
					break;

				default : 
					mag_data->x = 0;
					mag_data->y = 0;
					mag_data->z = 0;
			}

		}

	}

}
