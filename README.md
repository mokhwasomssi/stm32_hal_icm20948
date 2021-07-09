# stm32_hal_icm20948

__ICM-20948, SPI, STM32 HAL__

## 0. Development environment  
* MCU : [STM32F411CEU6 (WeAct Black Pill V3.0)](https://github.com/WeActTC/MiniF4-STM32F4x1)
* IDE : STM32CubeIDE
* ICM-20948 module : [SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)](https://www.sparkfun.com/products/15335)

## 1. FEATURE   
* Check connected device is right
* Read raw data of 3-axis gyroscope and 3-aixs accelerometer (SPI) 
   * `MCU(master)` - `ICM 20948(slave)`
* Read raw data of 3-axis Magnetometer (Auxiliary I2C)  
    * `ICM 20948(master)` - `AK09916(slave)`

## 2. ICM-20948
* 9-axis MotionTracking device  
    * 3-axis gyroscope, 3-axis accelerometer, 3-axis compass

* [IMU Sensor list](https://invensense.tdk.com/smartmotion/)

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
    * Before access the register, select User Bank of the register


## 3. User Configuration   
* STM32F411
* SPI - SPI1  
* CS  - PA4

### `icm_20948.h`
```c
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
```c
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

