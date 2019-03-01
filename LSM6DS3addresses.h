/*
File containing addresses for some of the LSM6DS3 registers.
Written by Johanna Jansson

Last edited: 2019-03-01 by Alexander Carlsson
*/


// LSM6DS3 i2c address with read/write bit
#define SLAVEADDRESSREAD        0xD7   // R/!W as 1 indicates write.
#define SLAVEADDRESSWRITE       0xD6   // R/!W as 0 indicates read.


#define FUNC_CFG_ACCESS         0x01   //Embedded functions configuration register
#define SENSOR_SYNC_TIME_FRAME  0x04   //Sensor sync configuration register
#define ORIENT_CFG_G            0x0b
#define INT1_CTRL               0x0d   // INT1 pin control
#define INT2_CTRL               0x0e   // INT2 pin control
#define WHO_AM_I                0x0f   // who I am id


// Accelerometer and gyroscope control registers
#define CTRL1_XL                0x10
#define CTRL2_G                 0x11
#define CTRL3_C                 0x12
#define CTRL4_C                 0x13
#define CTRL5_C                 0x14
#define CTRL6_C                 0x15
#define CTRL7_G                 0x16
#define CTRL8_XL                0x17
#define CTRL9_XL                0x18
#define CTRL10_C                0x19

#define MASTER_CONFIG           0x1a  //I2C master configuration register

// Interrupts output registers
#define WAKE_UP_SRC             0x1b
#define TAP_SRC                 0x1C
#define D6D_SRC                 0x1d


#define STATUS_REG              0x1e  //Status data register



//Gyroscope output register
#define OUTX_L_G                0x22
#define OUTX_H_G                0x23
#define OUTY_L_G                0x24
#define OUTY_H_G                0x25
#define OUTZ_L_G                0x26
#define OUTZ_H_G                0x27

//Accelerometer output register
#define OUTX_L_XL                0x28
#define OUTX_H_XL                0x29
#define OUTY_L_XL                0x2a
#define OUTY_H_XL                0x2b
#define OUTZ_L_XL                0x2c
#define OUTZ_H_XL                0x2d

//Sensor hub output registers
//exstärna sensorer
#define SENSORHUB1_REG          0x2e
#define SENSORHUB2_REG          0x2f
#define SENSORHUB3_REG          0x30
#define SENSORHUB4_REG          0x31
#define SENSORHUB5_REG          0x32
#define SENSORHUB6_REG          0x33
#define SENSORHUB7_REG          0x34
#define SENSORHUB8_REG          0x35
#define SENSORHUB9_REG          0x36
#define SENSORHUB10_REG         0x37
#define SENSORHUB11_REG         0x38
#define SENSORHUB12_REG         0x39
#define SENSORHUB13_REG         0x4d
#define SENSORHUB14_REG         0x4e
#define SENSORHUB15_REG         0x4f
#define SENSORHUB16_REG         0x50
#define SENSORHUB17_REG         0x51
#define SENSORHUB18_REG         0x52


// Timestamp output output registers
#define TIMESTAMP0_REG          0x40
#define TIMESTAMP1_REG          0x41
#define TIMESTAMP2_REG          0x42


//Interrupt register
#define FUNC_SRC                0x53
#define TAP_CFG                 0x58
#define TAP_THS_6D              0x59
#define INT_DUR2                0x5a
#define WAKE_UP_THS             0x5b
#define WAKE_UP_DUR             0x5c
#define FREE_FALL               0x5d
#define MD1_CFG                 0x5e
#define MD2_CFG                 0x5f
