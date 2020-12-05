# SIMPLE_ICM20948_LIB
Very Simple ICM-20948 library (STM32 HAL, STM32CUBEIDE)  
contents will be added...

## SPI with ICM-20948 (Gyroscope and Accelerometer)

### 1. SPI Mode : MODE 3 
### 2. Data Format   

- SPI Address format / Read (1), Write(0)

MSB| | | | | | |LSB| 
:----:|----|----|----|----|----|----|----|
R/W|A6|A5|A4|A3|A2|A1|A0|  

- SPI Data format

MSB| | | | | | |LSB| 
:----:|----|----|----|----|----|----|----|
D7|D6|D5|D4|D3|D2|D1|D0|

## I2C with AK09916 (Magnetometer)
