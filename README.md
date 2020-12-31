## Simple ICM20948 Library (Incomplete)
Very Simple ICM-20948 library (STM32 HAL)  
I'm still working on it...  

### To-do List  
- [ ] Troubleshooting problem that mag doesn't update measured value  
- [ ] Unit conversion  
- [ ] Calculate communication speed  
- [ ] Calibration 

### 0. Development environment
* IDE : STM32Cubeide 1.5.0 (STM32Cube HAL)  
https://www.st.com/en/development-tools/stm32cubeide  
* MCU : WeAct Black Pill V3.0 (STM32F411CEU6)  
https://github.com/WeActTC/MiniF4-STM32F4x1  
* Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)   
https://www.sparkfun.com/products/15335  

### 1. FEATURE   

* Read 3-axis gyroscope and 3-aixs accelerometer (SPI) 
* Read 3-axis Magnetometer (Auxiliary I2C)  

### 2. User Configuration (example)
* STM32F4xx
* SPI - SPI1  
* CS  - PA4

_mokhwa_ICM20948.h_
```
#include "stm32f4xx_hal.h"

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
* SPI2
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
* PA4 (CS)
```
GPIO output level : High
GPIO mode : Output Push Pull
GPIO Pull-up/Pull-down : No pull-up and no pull-down
Maximum output speed : Low
``` 
