## Simple ICM20948 Library (sorry, not working yet)
Very Simple ICM-20948 library (STM32 HAL)  
I'm still working on it...

### 0. Development environment
Tool : STM32Cubeide 1.5.0  
Target Board : NUCLEO-F103RB  
Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic) (https://www.sparkfun.com/products/15335)

### 1. User Configuration  
SPI - SPI2  
CS  - PB12  
#### ICM20948.h
```
#define SPI_ICM20948 		(&hspi2)	  	  	// SPI Number
#define CS_PIN_PORT             GPIOB			      	// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_12
```  
#### STM32CubeMX  
##### Setting  
```
Project Manager -> Code Generator -> Generated files 
-> Generate peripheral initialization as a pair of '.c/.h'files per peripheral
``` 
##### SPI2
```
Mode : Full-Duplex Master  

Frame Format : Motorola  
Data Size : 8 Bits  
First Bit : MSB First  

Prescaler : 4
Baud Rate : 8.0 MBits/s
Clock Polarity (CPOL) : High
Clock Phase (CPHA) : 2 Edge  

CRC Calculation : Disabled
NSS Signal Type : Software
``` 
##### PB12
```
GPIO output level : High
GPIO mode : Output Push Pull
GPIO Pull-up/Pull-down : No pull-up and no pull-down
Maximum output speed : Low
``` 
