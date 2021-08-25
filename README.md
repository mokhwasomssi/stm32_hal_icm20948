# stm32_hal_icm20948

## Brief

__ICM-20948 is 9-axis IMU sensor.__  
__TAG - `ICM-20948` `AK09916` `SPI` `STM32 HAL`__

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
- ICM-20948 module ( [SparkFun 9Dof IMU Breakout - ICM-20948 (Qwiic)](https://www.sparkfun.com/products/15335) )

<img src = "https://user-images.githubusercontent.com/48342925/125441402-2af7d878-53d7-4d2f-83df-f304df4c330c.png" width = "25%">
<img src = "https://user-images.githubusercontent.com/48342925/125441479-3370f3fb-8485-4d11-ad3e-1eb6e697f8e0.png" width = "25%">

## STM32CubeMX

![image](https://user-images.githubusercontent.com/48342925/130714344-753f1b21-abe7-412c-b723-0826e43b9203.png)


### SPI
![image](https://user-images.githubusercontent.com/48342925/129033034-ef4d8818-7338-4d90-bcd9-9d66491074bd.png)

#### GPIO
![image](https://user-images.githubusercontent.com/48342925/129033151-7cf98ef2-22e9-44ef-8ddd-77b6ea9abf0b.png)


## Example

### icm20948.h
- SPI1, PA4 (CS Pin)

```c
/* User Configuration */
#define ICM20948_SPI					(&hspi1)

#define ICM20948_SPI_CS_PIN_PORT		GPIOA
#define ICM20948_SPI_CS_PIN_NUMBER		GPIO_PIN_4
```

### main.c
- only contain relative things

```c
#include "icm20948.h"

// variables to store sensor data
axises my_gyro;
axises my_accel;
axises my_mag;

int main(void)
{
    // initialize
    // Modify the inside of init function for personal setting.
    icm20948_init();
    ak09916_init();

    while (1)
    {
        // raw data
        icm20948_gyro_read(&my_gyro);
        icm20948_accel_read(&my_accel);
        ak09916_mag_read(&my_mag);

        // or unit conversion
        icm20948_gyro_read_dps(&my_gyro);
        icm20948_accel_read_g(&my_accel);
        ak09916_mag_read_uT(&my_mag);
    }
}
```