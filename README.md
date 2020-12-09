# SIMPLE_ICM20948_LIB
Very Simple ICM-20948 library (STM32 HAL)  
I'm still working on it...

### 0. Development environment
Tool : STM32Cubeide 1.5.0  
Target Board : NUCLEO-F103RB  
Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic) (https://www.sparkfun.com/products/15335)

### 1. User Configuration  
SPI - SPI2  
CS  - PB12
```
// in mokhwa_ICM20948.h

#define SPI_ICM20948 		(&hspi2)	  	  	// SPI Number
#define CS_PIN_PORT             GPIOB			      	// CS Pin
#define CS_PIN_NUMBER		GPIO_PIN_12
```  

```
// in CubeMX  

// SPI2
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

// PB12
GPIO output level : High
GPIO mode : Output Push Pull
GPIO Pull-up/Pull-down : No pull-up and no pull-down
Maximum output speed : Low
``` 

### 1. Sensor Default Value  
POWER MODE : Sleep Mode (Gyro Off, accel Off, Magetometer Off, DMP Off)  
Clock Source : Auto selects the best available clock source
DLPF


### 2. Communication
#### SPI with ICM-20948 (Gyroscope and Accelerometer)

##### 1. SPI Mode : MODE 3 
##### 2. Data Format   

- SPI Address format / Read (1), Write(0)

MSB| | | | | | |LSB| 
:----:|----|----|----|----|----|----|----|
R/W|A6|A5|A4|A3|A2|A1|A0|  

- SPI Data format

MSB| | | | | | |LSB| 
:----:|----|----|----|----|----|----|----|
D7|D6|D5|D4|D3|D2|D1|D0|

### I2C with AK09916 (Magnetometer)
