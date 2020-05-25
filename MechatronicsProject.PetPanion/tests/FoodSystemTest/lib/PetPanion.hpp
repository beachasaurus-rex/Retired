//dependencies
#ifndef DEPS_H
    #define DEPS_H
    #include "deps.hpp"
#endif

/*
Put all of the header files we want to use in here.
The reason for doing this is so we just need to include
this file in "src.ino".
*/
#ifndef COLOR_SENSOR_H
    #define COLOR_SENSOR_H
    #include "Hardware/Sensors/ColorSensor.hpp"
#endif
#ifndef COLOR_SENSOR_S
    #define COLOR_SENSOR_S
    #include "Hardware/Sensors/ColorSensor.cpp"
#endif

#ifndef SERVO_MOTOR_H
    #define SERVO_MOTOR_H
    #include "Hardware/ServoMotor.hpp"
#endif
#ifndef SERVO_MOTOR_S
    #define SERVO_MOTOR_S
    #include "Hardware/ServoMotor.cpp"
#endif

#ifndef I2C_EXP_H
    #define I2C_EXP_H
    #include "Hardware/I2CExpansion.hpp"
#endif
#ifndef I2C_EXP_S
    #define I2C_EXP_S
    #include "Hardware/I2CExpansion.cpp"
#endif

#ifndef RTC_H
    #define RTC_H
    #include "Hardware/Sensors/RTC.hpp"
#endif
#ifndef RTC_S
    #define RTC_S
    #include "Hardware/Sensors/RTC.cpp"
#endif

#ifndef COLOR_SENSOR_OPTS_H
    #define COLOR_SENSOR_OPTS_H
    #include "Hardware/Sensors/ColorSensorOptions.hpp"
#endif
#ifndef COLOR_SENSOR_OPTS_S
    #define COLOR_SENSOR_OPTS_S
    #include "Hardware/Sensors/ColorSensorOptions.cpp"
#endif

#ifndef COLOR_SENSOR_ARR_OPTS_H
    #define COLOR_SENSOR_ARR_OPTS_H
    #include "Hardware/Sensors/ColorSensorArrayOptions.hpp"
#endif
#ifndef COLOR_SENSOR_ARR_OPTS_S
    #define COLOR_SENSOR_ARR_OPTS_S
    #include "Hardware/Sensors/ColorSensorArrayOptions.cpp"
#endif

#ifndef COLOR_SENSOR_ARR_H
    #define COLOR_SENSOR_ARR_H
    #include "Hardware/Sensors/ColorSensorArray.hpp"
#endif
#ifndef COLOR_SENSOR_ARR_S
    #define COLOR_SENSOR_ARR_S
    #include "Hardware/Sensors/ColorSensorArray.cpp"
#endif

#ifndef SD_FILE_STREAM_H
    #define SD_FILE_STREAM_H
    #include "Hardware/SDFileStream.hpp"
#endif
#ifndef SD_FILE_STREAM_S
    #define SD_FILE_STREAM_S
    #include "Hardware/SDFileStream.cpp"
#endif

#ifndef LOAD_CELL_H
    #define LOAD_CELL_H
    #include "Hardware/Sensors/LoadCell.hpp"
#endif
#ifndef LOAD_CELL_S
    #define LOAD_CELL_S
    #include "Hardware/Sensors/LoadCell.cpp"
#endif

#ifndef LYNX_H
    #define LYNX_H
    #include "Hardware/Lynx.hpp"
#endif
#ifndef LYNX_S
    #define LYNX_S
    #include "Hardware/Lynx.cpp"
#endif

#ifndef LYNX_MOTOR_H
    #define LYNX_MOTOR_H
    #include "Hardware/LynxMotor.hpp"
#endif
#ifndef LYNX_MOTOR_S
    #define LYNX_MOTOR_S
    #include "Hardware/LynxMotor.cpp"
#endif

#ifndef IR_SENSOR_H
    #define IR_SENSOR_H
    #include "Hardware/Sensors/IRSensor.hpp"
#endif
#ifndef IR_SENSOR_S
    #define IR_SENSOR_S
    #include "Hardware/Sensors/IRSensor.cpp"
#endif

#ifndef MOTION_SYSTEM_H
    #define MOTION_SYSTEM_H
    #include "Systems/MotionSystem.hpp"
#endif
#ifndef MOTION_SYSTEM_S
    #define MOTION_SYSTEM_S
    #include "Systems/MotionSystem.cpp"
#endif

#ifndef MOTION_SYSTEM_OPTIONS_H
    #define MOTION_SYSTEM_OPTIONS_H
    #include "Systems/MotionSystemOptions.hpp"
#endif
#ifndef MOTION_SYSTEM_OPTIONS_S
    #define MOTION_SYSTEM_OPTIONS_S
    #include "Systems/MotionSystemOptions.cpp"
#endif

#ifndef LOAD_CELL_OPTIONS_H
    #define LOAD_CELL_OPTIONS_H
    #include "Systems/LoadCellOptions.hpp"
#endif
#ifndef LOAD_CELL_OPTIONS_S
    #define LOAD_CELL_OPTIONS_S
    #include "Systems/LoadCellOptions.cpp"
#endif

#ifndef SERVO_MOTOR_OPTIONS_H
    #define SERVO_MOTOR_OPTIONS_H
    #include "Systems/ServoMotorOptions.hpp"
#endif
#ifndef SERVO_MOTOR_OPTIONS_S
    #define SERVO_MOTOR_OPTIONS_S
    #include "Systems/ServoMotorOptions.cpp"
#endif

#ifndef FOOD_SYSTEM_H
    #define FOOD_SYSTEM_H
    #include "Systems/FoodSystem.hpp"
#endif
#ifndef FOOD_SYSTEM_S
    #define FOOD_SYSTEM_S
    #include "Systems/FoodSystem.cpp"
#endif
