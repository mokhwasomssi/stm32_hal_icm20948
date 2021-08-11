# stm32_hal_icm20948

## Brief

__ICM-20948 is 9-axis IMU sensor.__  
__TAG - `ICM-20948` `SPI` `STM32 HAL`__

|Axis|Not Recommended for New Designs|Recommended for New Designs|
|:---:|:---:|:---:|
|6-axis|`MPU-6050`|`ICM-20602`|
|9-axis|`MPU-9250`|`ICM-20948`| 

## Library Feature
* Read sensor data
* Offset cancellation

## Dev Environment  
- STM32CubeIDE
- STM32 HAL driver
- STM32F411CEU6

## ICM-20948 module
[SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)](https://www.sparkfun.com/products/15335)

<img src = "https://user-images.githubusercontent.com/48342925/125441402-2af7d878-53d7-4d2f-83df-f304df4c330c.png" width = "40%"><img src = "https://user-images.githubusercontent.com/48342925/125441479-3370f3fb-8485-4d11-ad3e-1eb6e697f8e0.png" width = "40%">

## STM32CubeMX

### SPI

![image](https://user-images.githubusercontent.com/48342925/129033034-ef4d8818-7338-4d90-bcd9-9d66491074bd.png)

#### GPIO

![image](https://user-images.githubusercontent.com/48342925/129033151-7cf98ef2-22e9-44ef-8ddd-77b6ea9abf0b.png)
