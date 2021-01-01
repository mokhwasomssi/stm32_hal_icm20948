# Simple ICM20948 Library (Incomplete)
Very Simple ICM-20948 library (STM32 HAL)  
I'm still working on it...  


## 0. Development environment  
---
* IDE : STM32Cubeide 1.5.0 (STM32Cube HAL)  
https://www.st.com/en/development-tools/stm32cubeide  
* MCU : WeAct Black Pill V3.0 (STM32F411CEU6)  
https://github.com/WeActTC/MiniF4-STM32F4x1  
* Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)   
https://www.sparkfun.com/products/15335  

## 1. FEATURE   
---
* Check connected device is right
* Read raw data of 3-axis gyroscope and 3-aixs accelerometer (SPI) 
   * `MCU(master)` - `ICM 20948(slave)`
* Read raw data of 3-axis Magnetometer (Auxiliary I2C)  
    * `ICM 20948(master)` - `AK09916(slave)`
## 2. User Configuration   
---
* STM32F4xx
* SPI - SPI1  
* CS  - PA4

_mokhwa_ICM20948.h_
```
...

#include "stm32f4xx_hal.h"

...

#define SPI_ICM20948 		(&hspi1)	  	  	// SPI Number
#define CS_PIN_PORT         GPIOA			 	// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_4
```  
_STM32CubeMX_  
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
GPIO output level : High
GPIO mode : Output Push Pull
GPIO Pull-up/Pull-down : No pull-up and no pull-down
Maximum output speed : Low
``` 

## 3. Additional Description  
---
### (1) Product Overview

* IMU Sensor list  

|axis|Not Recommended for New Designs|Recommended for New Designs|
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

   
### (2) Read / Write ICM-20948

### (3) Read / Write AK09916 (external sensor)  

*This section is about how to access external sensor through ICM-20948*<br/>  

ICM-20948 supports an auxiliary I2C interface to external sensors.  
I'll take `AK09916(magnetometer)` in ICM-20948 for example.  
  
