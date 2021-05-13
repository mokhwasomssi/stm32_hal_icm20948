# Simple icm_20948 lib for STM32 HAL

**Just reading raw data only**  
It doesn't include DMP, interrupt, FIFO...  

## 0. Development environment  
* IDE : STM32Cubeide 1.5.0 (STM32Cube HAL)  
https://www.st.com/en/development-tools/stm32cubeide  
* MCU : WeAct Black Pill V3.0 (STM32F411CEU6)  
https://github.com/WeActTC/MiniF4-STM32F4x1  
* Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)   
https://www.sparkfun.com/products/15335  

## 1. FEATURE   
* Check connected device is right
* Read raw data of 3-axis gyroscope and 3-aixs accelerometer (SPI) 
   * `MCU(master)` - `ICM 20948(slave)`
* Read raw data of 3-axis Magnetometer (Auxiliary I2C)  
    * `ICM 20948(master)` - `AK09916(slave)`
## 2. User Configuration   
* STM32F4xx
* SPI - SPI1  
* CS  - PA4

### in `icm_20948.h`
```
// User Configuration
#define SPI_ICM20948 		(&hspi1)	  	  	// SPI Number
#define CS_PIN_PORT         GPIOA			 	// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_4
```  
### STM32CubeMX  
* Setting  
```
Project Manager -> Code Generator -> Generated files 
-> Generate peripheral initialization as a pair of '.c/.h'files per peripheral
``` 
* SPI1
```
Mode : Full-Duplex Master  

Frame Format : Motorola  
Data Size : 8 Bits  
First Bit : MSB First  

Prescaler : 16
Baud Rate : 6.25 MBits/s
Clock Polarity (CPOL) : High
Clock Phase (CPHA) : 2 Edge  

CRC Calculation : Disabled
NSS Signal Type : Software
``` 
* CS (PA4)
```
GPIO_Output

GPIO output level : High
GPIO mode : Output Push Pull
GPIO Pull-up/Pull-down : No pull-up and no pull-down
Maximum output speed : Low
``` 

### in `main.c`
* Monitor sensor data using `live watch` in STM32CubeIDE
* Monitor status using `Serial Wire Viewer`
```
...

#include "icm_20948.h"

...

    /* USER CODE BEGIN 0 */

    int _write(int file, char *ptr, int len)
    {
        for(int i = 0; i < len; i++)
        {
            ITM_SendChar(*ptr++);
        }
        return len;
    }

    /* USER CODE END 0 */

...

int main(void)
{
    ...


    ...

    /* USER CODE BEGIN 2 */

    // initialize
    icm20948_init(gy_fs_2000dps, odr_1125_hz, ac_fs_2g, odr_1125_hz);
    ak09916_init(continuous_measure_100hz);

    // check sensor id
    whoami_icm20948();
    whoami_ak09916();

    /* USER CODE END 2 */

    ...

    while(1)
    {
        read_gyro(&gyro_data, unit_lsb);
        read_accel(&accel_data, unit_lsb);
        read_mag(&mag_data, unit_lsb);
    }

    ...

}

...
```

## 3. Additional Description  
### (1) Product Overview
* 9-axis MotionTracking device  
    * 3-axis gyroscope, 3-axis accelerometer, 3-axis compass


* IMU Sensor list  
https://invensense.tdk.com/smartmotion/

|Axis|Not Recommended for New Designs|Recommended for New Designs|
|:---:|:---:|:---:|
|6-axis|`MPU-6050`|`ICM-20602`|
|9-axis|`MPU-9250`|`ICM-20948`| 
 
* Serial Communications Interfaces
    * Primary I2C and SPI ( `ICM-20948` acts like a slave )
    * Auxiliary I2C ( `ICM-20948` acts like a master )  

* Measurement Range
    * Gyroscope with Programable full-scale range
        * ±250dps, ±500dps, ±1000dps, ±2000dps
    * Accelerometer with Programable full-scale range
        * ±2g, ±4g, ±8g, ±16g
    * Compass with a wide range
        * ±4900μT

* User Bank
    * It is different from `MPU-9250`
    * User Bank 0, 1, 2, 3 is a group of registers
    * Access the register, after select User Bank of the register

   
### (2) Read / Write ICM-20948 (SPI)
*the minimum necessary to read/write ICM-20948*  

* `ICM-20948` Registers to access

|User Bank|Address|Register Name|Features to use|
|:---:|:---:|:---:|:---:|
|0|0x00|WHO_AM_I|Device ID is 0xEA|
|0|0x03|USER_CTRL|SPI mode only|
|0|0x06|PWR_MGMT_1|device reset <br> sleep mode <br> select clock source|
|0|0x2D - 0x32|ACCEL_XOUT_H - ACCEL_ZOUT_L|accel data|
|0|0x33 - 0x38|GYRO_XOUT_H - GYRO_ZOUT_L|gyro data|
|2|0x00|GYRO_SMPLRT_DIV|gyro sample rate divider|
|2|0x01|GYRO_CONFIG_1|gyro full scale select|
|2|0x16|ACCEL_SMPLRT_DIV_1|MSB for accel sample rate divder|
|2|0x17|ACCEL_SMPLRT_DIV_2|LSB for accel sample rate divder|
|2|0x20|ACCEL_CONFIG|accel full scale select|



### (3) Read / Write AK09916 (Auxiliary I2C)  
*select `AK09916`(magnetometer) in `ICM-20948` as a external sensor*

* `ICM-20948` (master) Registers to access 

|User Bank|Address|Register Name|Features to use|
|:---:|:---:|:---:|:---:|
|0|0x03|USER_CTRL|reset I2C master module<br> enable I2C master module|
|0|0x3B - 0x40|EXT_SLV_SENS_DATA_00 - 05|data from external I2C device|
|3|0x01|I2C_MST_CTRL|set I2C master clock frequency|
|3|0x03|I2C_SLV0_ADDR|I2C slave 0 address|
|3|0x04|I2C_SLV0_REG|I2C slave 0 register address|
|3|0x05|I2C_SLV0_CTRL|enable reading data <br> length to be read|
|3|0x06|I2C_SLV0_DO|data to write|


* `AK09916` (slave) Registers to access  

|Address|Register Name|Features to use|
|:---:|:---:|:---:|
|0x01|WIA2|Device ID is 0x09|
|0x10|ST1|data ready <br> data overrun|
|0x11 - 0x16|HXL - HZH|mag data|
|0x18|ST2|mag overflow|
|0x31|CNTL2|operation mode setting|
|0x31|CNTL3| soft reset|
