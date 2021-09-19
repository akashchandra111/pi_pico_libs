# Pi Pico libraries
Raspberry Pi Pico 2040 self-made libraries

## Directions to use this library
* Copy the required library inside your project include -> include and src -> src
* If project structure is simple then try to add these lines in your CMakeLists.txt

> add_executable( ${PROJECT_NAME}
>     src/main.c
>     src/mpu6050_sensor.c)
> 
> target_include_directories(${PROJECT_NAME} PUBLIC include/

