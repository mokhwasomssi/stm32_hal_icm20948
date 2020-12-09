# SIMPLE_ICM20948_LIB
Very Simple ICM-20948 library (STM32 HAL)  
I'm still working on it...

### 0. Development environment
Tool : STM32Cubeide 1.5.0  
Target Board : NUCLEO-F103RB  
Sensor : SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic) (https://www.sparkfun.com/products/15335)

### Pin Setting

### 1. Sensor Default Value

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
