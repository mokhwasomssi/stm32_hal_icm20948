/*
* icm20948.c
*
*  Created on: Dec 26, 2020
*      Author: mokhwasomssi
*/


#include "icm20948.h"


static void cs_high()
{
	HAL_GPIO_WritePin(ICM20948_SPI_CS_PIN_PORT, ICM20948_SPI_CS_PIN_NUMBER, SET);	
}

static void cs_low()
{
	HAL_GPIO_WritePin(ICM20948_SPI_CS_PIN_PORT, ICM20948_SPI_CS_PIN_NUMBER, RESET);
}

static void select_user_bank(userbank ub)
{
	uint8_t write_reg[2];

	write_reg[0] = WRITE | REG_BANK_SEL;
	write_reg[1] = ub;

	cs_low();
	HAL_SPI_Transmit(ICM20948_SPI, write_reg, 2, 10);
	cs_high();
}

static uint8_t read_single_register(userbank ub, uint8_t reg)
{
	uint8_t read_reg = READ | reg;
	uint8_t reg_val;

	select_user_bank(ub);

	cs_low();
	HAL_SPI_Transmit(ICM20948_SPI, &read_reg, 1, 1000);
	HAL_SPI_Receive(ICM20948_SPI, &reg_val, 1, 1000);
	cs_high();

	return reg_val;
}

static uint8_t* read_multiple_register(userbank ub, uint8_t reg, uint8_t len)
{
	uint8_t read_reg = READ | reg;
	static uint8_t reg_val[MAX_READ];

	select_user_bank(ub);

	cs_low();
	HAL_SPI_Transmit(ICM20948_SPI, &read_reg, 1, 1000);
	HAL_SPI_Receive(ICM20948_SPI, reg_val, len, 1000);
	cs_high();

	return reg_val;
}

static void write_single_register(userbank ub, uint8_t reg, uint8_t val)
{
	uint8_t write_reg[2];

	write_reg[0] = WRITE | reg;
	write_reg[1] = val;

	select_user_bank(ub);

	cs_low();
	HAL_SPI_Transmit(ICM20948_SPI, write_reg, 2, 1000);
	cs_high();

	//HAL_Delay(1);
}


/* ICM-20948 Main Functions */
void icm20948_init()
{
	icm20948_device_reset();
	icm20948_wakeup();

	icm20948_clock_source(1);
	icm20948_odr_align_enable();
	
	icm20948_spi_slave_enable();
	
	/*
	icm20948_i2c_master_reset();
	icm20948_i2c_master_enable();
	icm20948_i2c_master_clk_frq(7);
	*/

	icm20948_gyro_full_scale_select(_250dps);
	icm20948_accel_full_scale_select(_2g);

	icm20948_gyro_low_pass_filter(0);
	icm20948_accel_low_pass_filter(0);

	icm20948_gyro_sample_rate_divider(0);
	icm20948_accel_sample_rate_divider(0);
}

void icm20948_gyro_read(axises* data)
{
	uint8_t* temp = read_multiple_register(ub_0, B0_GYRO_XOUT_H, 6);

	data->x = (int16_t)(temp[0] << 8 | temp[1]);
	data->y = (int16_t)(temp[2] << 8 | temp[3]);
	data->z = (int16_t)(temp[4] << 8 | temp[5]);
}

void icm20948_accel_read(axises* data)
{
	uint8_t* temp = read_multiple_register(ub_0, B0_ACCEL_XOUT_H, 6);

	data->x = (int16_t)(temp[0] << 8 | temp[1]);
	data->y = (int16_t)(temp[2] << 8 | temp[3]);
	data->z = (int16_t)(temp[4] << 8 | temp[5]);	
}


/* ICM-20948 Sub Functions */
bool icm20948_who_am_i()
{
	uint8_t icm20948_id = read_single_register(ub_0, B0_WHO_AM_I);

	if(icm20948_id == 0xEA)
		return true;
	else
		return false;
}

void icm20948_device_reset()
{
	write_single_register(ub_0, B0_PWR_MGMT_1, 0x80 | 0x41);
	HAL_Delay(100);
}

void icm20948_wakeup()
{
	uint8_t new_val = read_single_register(ub_0, B0_PWR_MGMT_1);
	new_val &= 0xBF;

	write_single_register(ub_0, B0_PWR_MGMT_1, new_val);
	HAL_Delay(100);
}

void icm20948_sleep()
{
	uint8_t new_val = read_single_register(ub_0, B0_PWR_MGMT_1);
	new_val |= 0x40;

	write_single_register(ub_0, B0_PWR_MGMT_1, new_val);
	HAL_Delay(100);
}

void icm20948_spi_slave_enable()
{
	uint8_t new_val = read_single_register(ub_0, B0_USER_CTRL);
	new_val |= 0x10;

	write_single_register(ub_0, B0_USER_CTRL, new_val);
}

void icm20948_i2c_master_reset()
{
	uint8_t new_val = read_single_register(ub_0, B0_USER_CTRL);
	new_val |= 0x02;

	write_single_register(ub_0, B0_USER_CTRL, new_val);
}

void icm20948_i2c_master_enable()
{
	uint8_t new_val = read_single_register(ub_0, B0_USER_CTRL);
	new_val |= 0x20;

	write_single_register(ub_0, B0_USER_CTRL, new_val);
}

void icm20948_i2c_master_clk_frq(uint8_t config)
{
	uint8_t new_val = read_single_register(ub_3, B3_I2C_MST_CTRL);
	new_val |= config;

	write_single_register(ub_3, B3_I2C_MST_CTRL, new_val);	
}

void icm20948_clock_source(uint8_t source)
{
	uint8_t new_val = read_single_register(ub_0, B0_PWR_MGMT_1);
	new_val |= source;

	write_single_register(ub_0, B0_PWR_MGMT_1, new_val);
}

void icm20948_odr_align_enable()
{
	write_single_register(ub_2, B2_ODR_ALIGN_EN, 0x01);
}

void icm20948_gyro_full_scale_select(gyro_full_scale full_scale)
{
	uint8_t new_val = read_single_register(ub_2, B2_GYRO_CONFIG_1);
	
	switch(full_scale)
	{
		case _250dps :
			new_val |= 0x00;
			break;
		case _500dps :
			new_val |= 0x02;
			break;
		case _1000dps :
			new_val |= 0x04;
			break;
		case _2000dps :
			new_val |= 0x06;
			break;
	}

	write_single_register(ub_2, B2_GYRO_CONFIG_1, new_val);
}

void icm20948_accel_full_scale_select(accel_full_scale full_scale)
{
	uint8_t new_val = read_single_register(ub_2, B2_ACCEL_CONFIG);
	
	switch(full_scale)
	{
		case _2g :
			new_val |= 0x00;
			break;
		case _4g :
			new_val |= 0x02;
			break;
		case _8g :
			new_val |= 0x04;
			break;
		case _16g :
			new_val |= 0x06;
			break;
	}

	write_single_register(ub_2, B2_ACCEL_CONFIG, new_val);
}

void icm20948_gyro_low_pass_filter(uint8_t config)
{
	uint8_t new_val = read_single_register(ub_2, B2_GYRO_CONFIG_1);
	new_val |= config << 3;

	write_single_register(ub_2, B2_GYRO_CONFIG_1, new_val);
}

void icm20948_accel_low_pass_filter(uint8_t config)
{
	uint8_t new_val = read_single_register(ub_2, B2_ACCEL_CONFIG);
	new_val |= config << 3;

	write_single_register(ub_2, B2_GYRO_CONFIG_1, new_val);
}

void icm20948_gyro_sample_rate_divider(uint8_t divider)
{
	write_single_register(ub_2, B2_GYRO_SMPLRT_DIV, divider);
}

void icm20948_accel_sample_rate_divider(uint16_t divider)
{
	uint8_t divider_1 = (uint8_t)(divider >> 8);
	uint8_t divider_2 = (uint8_t)(0x0F & divider);

	write_single_register(ub_2, B2_ACCEL_SMPLRT_DIV_1, divider_1);
	write_single_register(ub_2, B2_ACCEL_SMPLRT_DIV_2, divider_2);
}

void icm20948_gyro_calibration()
{
	uint8_t* temp;
	uint16_t gyro_offset[6];
	
	for(int i = 0; i < 100; i++)
	{
		temp = read_multiple_register(ub_0, B0_GYRO_XOUT_H, 6);

		gyro_offset[0] += temp[0];
		gyro_offset[1] += temp[1];
		gyro_offset[2] += temp[2];
		gyro_offset[3] += temp[3];
		gyro_offset[4] += temp[4];
		gyro_offset[5] += temp[5];
	}



}