/******************************************************************************
SparkFunLSM6DS3.h
LSM6DS3 Arduino and Teensy Driver

Marshall Taylor @ SparkFun Electronics
May 20, 2015
https://github.com/sparkfun/LSM6DS3_Breakout
https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation
Either can be omitted if not used

Development environment specifics:
Arduino IDE 1.6.4
Teensy loader 1.23

This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef __LSM6DS3_H
#define __LSM6DS3_H

#ifdef __cplusplus
 extern "C" {
#endif
/*============================================================================
Include files
============================================================================*/
#include "config.h"
#include "utilities.h"

/*============================================================================
Macros
============================================================================*/
/************** Device Register  *******************/
//#define LSM6DS3_ADDRESS				0b11010111// 0xD4
#define LSM6DS3_DEVICE_ID			0x69

#define LSM6DS3_TEST_PAGE  			0X00
#define LSM6DS3_RAM_ACCESS  			0X01
#define LSM6DS3_SENSOR_SYNC_TIME  		0X04
#define LSM6DS3_SENSOR_SYNC_EN  		0X05
#define LSM6DS3_FIFO_CTRL1  			0X06
#define LSM6DS3_FIFO_CTRL2  			0X07
#define LSM6DS3_FIFO_CTRL3  			0X08
#define LSM6DS3_FIFO_CTRL4  			0X09
#define LSM6DS3_FIFO_CTRL5  			0X0A
#define LSM6DS3_ORIENT_CFG_G  			0X0B
#define LSM6DS3_REFERENCE_G  			0X0C
#define LSM6DS3_INT1_CTRL  			0X0D
#define LSM6DS3_INT2_CTRL  			0X0E
#define LSM6DS3_WHO_AM_I_REG  			0X0F
#define LSM6DS3_CTRL1_XL  			0X10
#define LSM6DS3_CTRL2_G  			0X11
#define LSM6DS3_CTRL3_C  			0X12
#define LSM6DS3_CTRL4_C  			0X13
#define LSM6DS3_CTRL5_C  			0X14
#define LSM6DS3_CTRL6_G  			0X15
#define LSM6DS3_CTRL7_G  			0X16
#define LSM6DS3_CTRL8_XL  			0X17
#define LSM6DS3_CTRL9_XL  			0X18
#define LSM6DS3_CTRL10_C  			0X19
#define LSM6DS3_MASTER_CONFIG  		0X1A
#define LSM6DS3_WAKE_UP_SRC  			0X1B
#define LSM6DS3_TAP_SRC  			0X1C
#define LSM6DS3_D6D_SRC  			0X1D
#define LSM6DS3_STATUS_REG  			0X1E
#define LSM6DS3_OUT_TEMP_L  			0X20
#define LSM6DS3_OUT_TEMP_H  			0X21
#define LSM6DS3_OUTX_L_G  			0X22
#define LSM6DS3_OUTX_H_G  			0X23
#define LSM6DS3_OUTY_L_G  			0X24
#define LSM6DS3_OUTY_H_G  			0X25
#define LSM6DS3_OUTZ_L_G  			0X26
#define LSM6DS3_OUTZ_H_G  			0X27
#define LSM6DS3_OUTX_L_XL  			0X28
#define LSM6DS3_OUTX_H_XL  			0X29
#define LSM6DS3_OUTY_L_XL  			0X2A
#define LSM6DS3_OUTY_H_XL  			0X2B
#define LSM6DS3_OUTZ_L_XL  			0X2C
#define LSM6DS3_OUTZ_H_XL  			0X2D
#define LSM6DS3_SENSORHUB1_REG  		0X2E
#define LSM6DS3_SENSORHUB2_REG  		0X2F
#define LSM6DS3_SENSORHUB3_REG  		0X30
#define LSM6DS3_SENSORHUB4_REG  		0X31
#define LSM6DS3_SENSORHUB5_REG  		0X32
#define LSM6DS3_SENSORHUB6_REG  		0X33
#define LSM6DS3_SENSORHUB7_REG  		0X34
#define LSM6DS3_SENSORHUB8_REG  		0X35
#define LSM6DS3_SENSORHUB9_REG  		0X36
#define LSM6DS3_SENSORHUB10_REG  		0X37
#define LSM6DS3_SENSORHUB11_REG  		0X38
#define LSM6DS3_SENSORHUB12_REG  		0X39
#define LSM6DS3_FIFO_STATUS1  			0X3A
#define LSM6DS3_FIFO_STATUS2  			0X3B
#define LSM6DS3_FIFO_STATUS3  			0X3C
#define LSM6DS3_FIFO_STATUS4  			0X3D
#define LSM6DS3_FIFO_DATA_OUT_L  		0X3E
#define LSM6DS3_FIFO_DATA_OUT_H  		0X3F
#define LSM6DS3_TIMESTAMP0_REG  		0X40
#define LSM6DS3_TIMESTAMP1_REG  		0X41
#define LSM6DS3_TIMESTAMP2_REG  		0X42
#define LSM6DS3_STEP_COUNTER_L  		0X4B
#define LSM6DS3_STEP_COUNTER_H  		0X4C
#define LSM6DS3_FUNC_SRC  			0X53
#define LSM6DS3_TAP_CFG1  			0X58
#define LSM6DS3_TAP_THS_6D  			0X59
#define LSM6DS3_INT_DUR2  			0X5A
#define LSM6DS3_WAKE_UP_THS  			0X5B
#define LSM6DS3_WAKE_UP_DUR  			0X5C
#define LSM6DS3_FREE_FALL  			0X5D
#define LSM6DS3_MD1_CFG  			0X5E
#define LSM6DS3_MD2_CFG  			0X5F

/************** Access Device RAM  *******************/
#define LSM6DS3_ADDR0_TO_RW_RAM         0x62
#define LSM6DS3_ADDR1_TO_RW_RAM         0x63
#define LSM6DS3_DATA_TO_WR_RAM          0x64
#define LSM6DS3_DATA_RD_FROM_RAM        0x65

#define LSM6DS3_RAM_SIZE                4096

/************** Embedded functions register mapping  *******************/
#define LSM6DS3_SLV0_ADD                     0x02
#define LSM6DS3_SLV0_SUBADD                  0x03
#define LSM6DS3_SLAVE0_CONFIG                0x04
#define LSM6DS3_SLV1_ADD                     0x05
#define LSM6DS3_SLV1_SUBADD                  0x06
#define LSM6DS3_SLAVE1_CONFIG                0x07
#define LSM6DS3_SLV2_ADD                     0x08
#define LSM6DS3_SLV2_SUBADD                  0x09
#define LSM6DS3_SLAVE2_CONFIG                0x0A
#define LSM6DS3_SLV3_ADD                     0x0B
#define LSM6DS3_SLV3_SUBADD                  0x0C
#define LSM6DS3_SLAVE3_CONFIG                0x0D
#define LSM6DS3_DATAWRITE_SRC_MODE_SUB_SLV0  0x0E
#define LSM6DS3_CONFIG_PEDO_THS_MIN          0x0F
#define LSM6DS3_CONFIG_TILT_IIR              0x10
#define LSM6DS3_CONFIG_TILT_ACOS             0x11
#define LSM6DS3_CONFIG_TILT_WTIME            0x12
#define LSM6DS3_SM_STEP_THS                  0x13
#define LSM6DS3_MAG_SI_XX                    0x24
#define LSM6DS3_MAG_SI_XY                    0x25
#define LSM6DS3_MAG_SI_XZ                    0x26
#define LSM6DS3_MAG_SI_YX                    0x27
#define LSM6DS3_MAG_SI_YY                    0x28
#define LSM6DS3_MAG_SI_YZ                    0x29
#define LSM6DS3_MAG_SI_ZX                    0x2A
#define LSM6DS3_MAG_SI_ZY                    0x2B
#define LSM6DS3_MAG_SI_ZZ                    0x2C
#define LSM6DS3_MAG_OFFX_L                   0x2D
#define LSM6DS3_MAG_OFFX_H                   0x2E
#define LSM6DS3_MAG_OFFY_L                   0x2F
#define LSM6DS3_MAG_OFFY_H                   0x30
#define LSM6DS3_MAG_OFFZ_L                   0x31
#define LSM6DS3_MAG_OFFZ_H                   0x32

/*******************************************************************************
* Register      : TEST_PAGE
* Address       : 0X00
* Bit Group Name: FLASH_PAGE
* Permission    : RW
*******************************************************************************/
#define FLASH_PAGE    0x40

/*============================================================================
Enums
============================================================================*/

// Return values 
typedef enum{
  IMU_SUCCESS = 1,
  IMU_ERROR = 0, 
} status_t;

/*******************************************************************************
* Register      : RAM_ACCESS
* Address       : 0X01
* Bit Group Name: PROG_RAM1
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PROG_RAM1_DISABLED 		 = 0x00,
	LSM6DS3_PROG_RAM1_ENABLED 		 = 0x01,
} LSM6DS3_PROG_RAM1_t;

/*******************************************************************************
* Register      : RAM_ACCESS
* Address       : 0X01
* Bit Group Name: CUSTOMROM1
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_CUSTOMROM1_DISABLED 		 = 0x00,
	LSM6DS3_CUSTOMROM1_ENABLED 		 = 0x04,
} LSM6DS3_CUSTOMROM1_t;

/*******************************************************************************
* Register      : RAM_ACCESS
* Address       : 0X01
* Bit Group Name: RAM_PAGE
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_RAM_PAGE_DISABLED 		 = 0x00,
	LSM6DS3_RAM_PAGE_ENABLED 		 = 0x80,
} LSM6DS3_RAM_PAGE_t;

/*******************************************************************************
* Register      : SENSOR_SYNC_TIME
* Address       : 0X04
* Bit Group Name: TPH
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_TPH_MASK  	0xFF
#define  	LSM6DS3_TPH_POSITION  	0

/*******************************************************************************
* Register      : SENSOR_SYNC_EN
* Address       : 0X05
* Bit Group Name: SYNC_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SYNC_EN_DISABLED 		 = 0x00,
	LSM6DS3_SYNC_EN_ENABLED 		 = 0x01,
} LSM6DS3_SYNC_EN_t;

/*******************************************************************************
* Register      : SENSOR_SYNC_EN
* Address       : 0X05
* Bit Group Name: HP_RST
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_HP_RST_RST_OFF 		 = 0x00,
	LSM6DS3_HP_RST_RST_ON 		 = 0x02,
} LSM6DS3_HP_RST_t;

/*******************************************************************************
* Register      : FIFO_CTRL1
* Address       : 0X06
* Bit Group Name: WTM_FIFO
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_WTM_FIFO_CTRL1_MASK  	0xFF
#define  	LSM6DS3_WTM_FIFO_CTRL1_POSITION  	0
#define  	LSM6DS3_WTM_FIFO_CTRL2_MASK  	0x0F
#define  	LSM6DS3_WTM_FIFO_CTRL2_POSITION  	0

/*******************************************************************************
* Register      : FIFO_CTRL2
* Address       : 0X07
* Bit Group Name: TIM_PEDO_FIFO_DRDY
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TIM_PEDO_FIFO_DRDY_DISABLED 		 = 0x00,
	LSM6DS3_TIM_PEDO_FIFO_DRDY_ENABLED 		 = 0x40,
} LSM6DS3_TIM_PEDO_FIFO_DRDY_t;

/*******************************************************************************
* Register      : FIFO_CTRL2
* Address       : 0X07
* Bit Group Name: TIM_PEDO_FIFO_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TIM_PEDO_FIFO_EN_DISABLED 		 = 0x00,
	LSM6DS3_TIM_PEDO_FIFO_EN_ENABLED 		 = 0x80,
} LSM6DS3_TIM_PEDO_FIFO_EN_t;

/*******************************************************************************
* Register      : FIFO_CTRL3
* Address       : 0X08
* Bit Group Name: DEC_FIFO_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEC_FIFO_XL_DATA_NOT_IN_FIFO 		 = 0x00,
	LSM6DS3_DEC_FIFO_XL_NO_DECIMATION 		 = 0x01,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_2 		 = 0x02,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_3 		 = 0x03,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_4 		 = 0x04,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_8 		 = 0x05,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_16 		 = 0x06,
	LSM6DS3_DEC_FIFO_XL_DECIMATION_BY_32 		 = 0x07,
} LSM6DS3_DEC_FIFO_XL_t;

/*******************************************************************************
* Register      : FIFO_CTRL3
* Address       : 0X08
* Bit Group Name: DEC_FIFO_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEC_FIFO_G_DATA_NOT_IN_FIFO 		 = 0x00,
	LSM6DS3_DEC_FIFO_G_NO_DECIMATION 		 = 0x08,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_2 		 = 0x10,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_3 		 = 0x18,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_4 		 = 0x20,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_8 		 = 0x28,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_16 		 = 0x30,
	LSM6DS3_DEC_FIFO_G_DECIMATION_BY_32 		 = 0x38,
} LSM6DS3_DEC_FIFO_G_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: DEC_FIFO_SLV0
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEC_FIFO_SLV0_DATA_NOT_IN_FIFO 		 = 0x00,
	LSM6DS3_DEC_FIFO_SLV0_NO_DECIMATION 		 = 0x01,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_2 		 = 0x02,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_3 		 = 0x03,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_4 		 = 0x04,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_8 		 = 0x05,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_16 		 = 0x06,
	LSM6DS3_DEC_FIFO_SLV0_DECIMATION_BY_32 		 = 0x07,
} LSM6DS3_DEC_FIFO_SLV0_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: DEC_FIFO_SLV1
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEC_FIFO_SLV1_DATA_NOT_IN_FIFO 		 = 0x00,
	LSM6DS3_DEC_FIFO_SLV1_NO_DECIMATION 		 = 0x08,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_2 		 = 0x10,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_3 		 = 0x18,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_4 		 = 0x20,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_8 		 = 0x28,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_16 		 = 0x30,
	LSM6DS3_DEC_FIFO_SLV1_DECIMATION_BY_32 		 = 0x38,
} LSM6DS3_DEC_FIFO_SLV1_t;

/*******************************************************************************
* Register      : FIFO_CTRL4
* Address       : 0X09
* Bit Group Name: HI_DATA_ONLY
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_HI_DATA_ONLY_DISABLED 		 = 0x00,
	LSM6DS3_HI_DATA_ONLY_ENABLED 		 = 0x40,
} LSM6DS3_HI_DATA_ONLY_t;

/*******************************************************************************
* Register      : FIFO_CTRL5
* Address       : 0X0A
* Bit Group Name: FIFO_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FIFO_MODE_BYPASS 		 = 0x00,
	LSM6DS3_FIFO_MODE_FIFO 		 = 0x01,
	LSM6DS3_FIFO_MODE_STREAM 		 = 0x02,
	LSM6DS3_FIFO_MODE_STF 		 = 0x03,
	LSM6DS3_FIFO_MODE_BTS 		 = 0x04,
	LSM6DS3_FIFO_MODE_DYN_STREAM 		 = 0x05,
	LSM6DS3_FIFO_MODE_DYN_STREAM_2 		 = 0x06,
	LSM6DS3_FIFO_MODE_BTF 		 = 0x07,
} LSM6DS3_FIFO_MODE_t;

/*******************************************************************************
* Register      : FIFO_CTRL5
* Address       : 0X0A
* Bit Group Name: ODR_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ODR_FIFO_10Hz 		 = 0x08,
	LSM6DS3_ODR_FIFO_25Hz 		 = 0x10,
	LSM6DS3_ODR_FIFO_50Hz 		 = 0x18,
	LSM6DS3_ODR_FIFO_100Hz 		 = 0x20,
	LSM6DS3_ODR_FIFO_200Hz 		 = 0x28,
	LSM6DS3_ODR_FIFO_400Hz 		 = 0x30,
	LSM6DS3_ODR_FIFO_800Hz 		 = 0x38,
	LSM6DS3_ODR_FIFO_1600Hz 		 = 0x40,
	LSM6DS3_ODR_FIFO_3300Hz 		 = 0x48,
	LSM6DS3_ODR_FIFO_6600Hz 		 = 0x50,
	LSM6DS3_ODR_FIFO_13300Hz 		 = 0x58,
} LSM6DS3_ODR_FIFO_t;

/*******************************************************************************
* Register      : ORIENT_CFG_G
* Address       : 0X0B
* Bit Group Name: ORIENT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ORIENT_XYZ 		 = 0x00,
	LSM6DS3_ORIENT_XZY 		 = 0x01,
	LSM6DS3_ORIENT_YXZ 		 = 0x02,
	LSM6DS3_ORIENT_YZX 		 = 0x03,
	LSM6DS3_ORIENT_ZXY 		 = 0x04,
	LSM6DS3_ORIENT_ZYX 		 = 0x05,
} LSM6DS3_ORIENT_t;

/*******************************************************************************
* Register      : ORIENT_CFG_G
* Address       : 0X0B
* Bit Group Name: SIGN_Z_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIGN_Z_G_POSITIVE 		 = 0x00,
	LSM6DS3_SIGN_Z_G_NEGATIVE 		 = 0x08,
} LSM6DS3_SIGN_Z_G_t;

/*******************************************************************************
* Register      : ORIENT_CFG_G
* Address       : 0X0B
* Bit Group Name: SIGN_Y_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIGN_Y_G_POSITIVE 		 = 0x00,
	LSM6DS3_SIGN_Y_G_NEGATIVE 		 = 0x10,
} LSM6DS3_SIGN_Y_G_t;

/*******************************************************************************
* Register      : ORIENT_CFG_G
* Address       : 0X0B
* Bit Group Name: SIGN_X_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIGN_X_G_POSITIVE 		 = 0x00,
	LSM6DS3_SIGN_X_G_NEGATIVE 		 = 0x20,
} LSM6DS3_SIGN_X_G_t;

/*******************************************************************************
* Register      : REFERENCE_G
* Address       : 0X0C
* Bit Group Name: REF_G
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_REF_G_MASK  	0xFF
#define  	LSM6DS3_REF_G_POSITION  	0

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_DRDY_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_DRDY_XL_DISABLED 		 = 0x00,
	LSM6DS3_INT1_DRDY_XL_ENABLED 		 = 0x01,
} LSM6DS3_INT1_DRDY_XL_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_DRDY_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_DRDY_G_DISABLED 		 = 0x00,
	LSM6DS3_INT1_DRDY_G_ENABLED 		 = 0x02,
} LSM6DS3_INT1_DRDY_G_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_BOOT_DISABLED 		 = 0x00,
	LSM6DS3_INT1_BOOT_ENABLED 		 = 0x04,
} LSM6DS3_INT1_BOOT_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_FTH_DISABLED 		 = 0x00,
	LSM6DS3_INT1_FTH_ENABLED 		 = 0x08,
} LSM6DS3_INT1_FTH_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_OVR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_OVR_DISABLED 		 = 0x00,
	LSM6DS3_INT1_OVR_ENABLED 		 = 0x10,
} LSM6DS3_INT1_OVR_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_FSS5
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_FSS5_DISABLED 		 = 0x00,
	LSM6DS3_INT1_FSS5_ENABLED 		 = 0x20,
} LSM6DS3_INT1_FSS5_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_SIGN_MOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_SIGN_MOT_DISABLED 		 = 0x00,
	LSM6DS3_INT1_SIGN_MOT_ENABLED 		 = 0x40,
} LSM6DS3_INT1_SIGN_MOT_t;

/*******************************************************************************
* Register      : INT1_CTRL
* Address       : 0X0D
* Bit Group Name: INT1_PEDO
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_PEDO_DISABLED 		 = 0x00,
	LSM6DS3_INT1_PEDO_ENABLED 		 = 0x80,
} LSM6DS3_INT1_PEDO_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_DRDY_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_DRDY_XL_DISABLED 		 = 0x00,
	LSM6DS3_INT2_DRDY_XL_ENABLED 		 = 0x01,
} LSM6DS3_INT2_DRDY_XL_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_DRDY_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_DRDY_G_DISABLED 		 = 0x00,
	LSM6DS3_INT2_DRDY_G_ENABLED 		 = 0x02,
} LSM6DS3_INT2_DRDY_G_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_FTH_DISABLED 		 = 0x00,
	LSM6DS3_INT2_FTH_ENABLED 		 = 0x08,
} LSM6DS3_INT2_FTH_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_OVR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_OVR_DISABLED 		 = 0x00,
	LSM6DS3_INT2_OVR_ENABLED 		 = 0x10,
} LSM6DS3_INT2_OVR_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_FSS5
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_FSS5_DISABLED 		 = 0x00,
	LSM6DS3_INT2_FSS5_ENABLED 		 = 0x20,
} LSM6DS3_INT2_FSS5_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_SIGN_MOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_SIGN_MOT_DISABLED 		 = 0x00,
	LSM6DS3_INT2_SIGN_MOT_ENABLED 		 = 0x40,
} LSM6DS3_INT2_SIGN_MOT_t;

/*******************************************************************************
* Register      : INT2_CTRL
* Address       : 0X0E
* Bit Group Name: INT2_PEDO
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_PEDO_DISABLED 		 = 0x00,
	LSM6DS3_INT2_PEDO_ENABLED 		 = 0x80,
} LSM6DS3_INT2_PEDO_t;

/*******************************************************************************
* Register      : WHO_AM_I
* Address       : 0X0F
* Bit Group Name: WHO_AM_I_BIT
* Permission    : RO
*******************************************************************************/
#define  	LSM6DS3_WHO_AM_I_BIT_MASK  	0xFF
#define  	LSM6DS3_WHO_AM_I_BIT_POSITION  	0

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: BW_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_BW_XL_400Hz 		 = 0x00,
	LSM6DS3_BW_XL_200Hz 		 = 0x01,
	LSM6DS3_BW_XL_100Hz 		 = 0x02,
	LSM6DS3_BW_XL_50Hz 		 = 0x03,
} LSM6DS3_BW_XL_t;

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: FS_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FS_XL_2g 		 = 0b00,
	LSM6DS3_FS_XL_16g 		 = 0b01,
	LSM6DS3_FS_XL_4g 		 = 0b10,
	LSM6DS3_FS_XL_8g 		 = 0b11,
} LSM6DS3_FS_XL_t;

/*******************************************************************************
* Register      : CTRL1_XL
* Address       : 0X10
* Bit Group Name: ODR_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ODR_XL_POWER_DOWN 		 = 0x00,
	LSM6DS3_ODR_XL_13Hz 		         = 0x10,
	LSM6DS3_ODR_XL_26Hz 		         = 0x20,
	LSM6DS3_ODR_XL_52Hz 		         = 0x30,
	LSM6DS3_ODR_XL_104Hz 		 = 0x40,
	LSM6DS3_ODR_XL_208Hz 		 = 0x50,
	LSM6DS3_ODR_XL_416Hz 		 = 0x60,
	LSM6DS3_ODR_XL_833Hz 		 = 0x70,
	LSM6DS3_ODR_XL_1660Hz 		 = 0x80,
	LSM6DS3_ODR_XL_3330Hz 		 = 0x90,
	LSM6DS3_ODR_XL_6660Hz 		 = 0xA0,
	LSM6DS3_ODR_XL_13330Hz 		 = 0xB0,
} LSM6DS3_ODR_XL_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: FS_125
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FS_125_DISABLED          = 0x00,
	LSM6DS3_FS_125_ENABLED 		 = 0x02,
} LSM6DS3_FS_125_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: FS_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FS_G_245dps 		 = 0b00,
	LSM6DS3_FS_G_500dps 		 = 0b01,
	LSM6DS3_FS_G_1000dps 		 = 0b10,
	LSM6DS3_FS_G_2000dps 		 = 0b11,
} LSM6DS3_FS_G_t;

/*******************************************************************************
* Register      : CTRL2_G
* Address       : 0X11
* Bit Group Name: ODR_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ODR_G_POWER_DOWN 	 = 0x00,
	LSM6DS3_ODR_G_13Hz 		 = 0x10,
	LSM6DS3_ODR_G_26Hz 		 = 0x20,
	LSM6DS3_ODR_G_52Hz 		 = 0x30,
	LSM6DS3_ODR_G_104Hz 		 = 0x40,
	LSM6DS3_ODR_G_208Hz 		 = 0x50,
	LSM6DS3_ODR_G_416Hz 		 = 0x60,
	LSM6DS3_ODR_G_833Hz 		 = 0x70,
	LSM6DS3_ODR_G_1660Hz 		 = 0x80,
} LSM6DS3_ODR_G_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: SW_RESET
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SW_RESET_NORMAL_MODE 		 = 0x00,
	LSM6DS3_SW_RESET_RESET_DEVICE 		 = 0x01,
} LSM6DS3_SW_RESET_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BLE
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_BLE_LSB 		 = 0x00,
	LSM6DS3_BLE_MSB 		 = 0x02,
} LSM6DS3_BLE_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: IF_INC
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_IF_INC_DISABLED 		 = 0x00,
	LSM6DS3_IF_INC_ENABLED 		 = 0x04,
} LSM6DS3_IF_INC_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: SIM
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIM_4_WIRE 		 = 0x00,
	LSM6DS3_SIM_3_WIRE 		 = 0x08,
} LSM6DS3_SIM_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: PP_OD
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PP_OD_PUSH_PULL 		 = 0x00,
	LSM6DS3_PP_OD_OPEN_DRAIN 		 = 0x10,
} LSM6DS3_PP_OD_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: INT_ACT_LEVEL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT_ACT_LEVEL_ACTIVE_HI 		 = 0x00,
	LSM6DS3_INT_ACT_LEVEL_ACTIVE_LO 		 = 0x20,
} LSM6DS3_INT_ACT_LEVEL_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BDU
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_BDU_CONTINUOS 		 = 0x00,
	LSM6DS3_BDU_BLOCK_UPDATE 		 = 0x40,
} LSM6DS3_BDU_t;

/*******************************************************************************
* Register      : CTRL3_C
* Address       : 0X12
* Bit Group Name: BOOT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_BOOT_NORMAL_MODE 		 = 0x00,
	LSM6DS3_BOOT_REBOOT_MODE 		 = 0x80,
} LSM6DS3_BOOT_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: STOP_ON_FTH
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_STOP_ON_FTH_DISABLED 		 = 0x00,
	LSM6DS3_STOP_ON_FTH_ENABLED 		 = 0x01,
} LSM6DS3_STOP_ON_FTH_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: MODE3_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_MODE3_EN_DISABLED 		 = 0x00,
	LSM6DS3_MODE3_EN_ENABLED 		 = 0x02,
} LSM6DS3_MODE3_EN_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: I2C_DISABLE
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_I2C_DISABLE_I2C_AND_SPI 		 = 0x00,
	LSM6DS3_I2C_DISABLE_SPI_ONLY 		 = 0x04,
} LSM6DS3_I2C_DISABLE_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: DRDY_MSK
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DRDY_MSK_DISABLED 		 = 0x00,
	LSM6DS3_DRDY_MSK_ENABLED 		 = 0x08,
} LSM6DS3_DRDY_MSK_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: FIFO_TEMP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FIFO_TEMP_EN_DISABLED 		 = 0x00,
	LSM6DS3_FIFO_TEMP_EN_ENABLED 		 = 0x10,
} LSM6DS3_FIFO_TEMP_EN_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: INT2_ON_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_ON_INT1_DISABLED 		 = 0x00,
	LSM6DS3_INT2_ON_INT1_ENABLED 		 = 0x20,
} LSM6DS3_INT2_ON_INT1_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: SLEEP_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SLEEP_G_DISABLED 		 = 0x00,
	LSM6DS3_SLEEP_G_ENABLED 		 = 0x40,
} LSM6DS3_SLEEP_G_t;

/*******************************************************************************
* Register      : CTRL4_C
* Address       : 0X13
* Bit Group Name: BW_SCAL_ODR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_BW_SCAL_ODR_DISABLED 		 = 0x00,
	LSM6DS3_BW_SCAL_ODR_ENABLED 		 = 0x80,
} LSM6DS3_BW_SCAL_ODR_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: ST_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ST_XL_NORMAL_MODE 		 = 0x00,
	LSM6DS3_ST_XL_POS_SIGN_TEST 		 = 0x01,
	LSM6DS3_ST_XL_NEG_SIGN_TEST 		 = 0x02,
	LSM6DS3_ST_XL_NA 		 = 0x03,
} LSM6DS3_ST_XL_t;

/*******************************************************************************
* Register      : CTRL5_C
* Address       : 0X14
* Bit Group Name: ST_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ST_G_NORMAL_MODE 		 = 0x00,
	LSM6DS3_ST_G_POS_SIGN_TEST 		 = 0x04,
	LSM6DS3_ST_G_NA 		 = 0x08,
	LSM6DS3_ST_G_NEG_SIGN_TEST 		 = 0x0C,
} LSM6DS3_ST_G_t;

/*******************************************************************************
* Register      : CTRL6_G
* Address       : 0X15
* Bit Group Name: LP_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_LP_XL_DISABLED 		 = 0x00,
	LSM6DS3_LP_XL_ENABLED 		 = 0x10,
} LSM6DS3_LP_XL_t;

/*******************************************************************************
* Register      : CTRL6_G
* Address       : 0X15
* Bit Group Name: DEN_LVL2_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEN_LVL2_EN_DISABLED 		 = 0x00,
	LSM6DS3_DEN_LVL2_EN_ENABLED 		 = 0x20,
} LSM6DS3_DEN_LVL2_EN_t;

/*******************************************************************************
* Register      : CTRL6_G
* Address       : 0X15
* Bit Group Name: DEN_LVL_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEN_LVL_EN_DISABLED 		 = 0x00,
	LSM6DS3_DEN_LVL_EN_ENABLED 		 = 0x40,
} LSM6DS3_DEN_LVL_EN_t;

/*******************************************************************************
* Register      : CTRL6_G
* Address       : 0X15
* Bit Group Name: DEN_EDGE_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DEN_EDGE_EN_DISABLED 		 = 0x00,
	LSM6DS3_DEN_EDGE_EN_ENABLED 		 = 0x80,
} LSM6DS3_DEN_EDGE_EN_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: HPM_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_HPM_G_NORMAL_MODE 		 = 0x00,
	LSM6DS3_HPM_G_REF_SIGNAL 		 = 0x10,
	LSM6DS3_HPM_G_NORMAL_MODE_2 		 = 0x20,
	LSM6DS3_HPM_G_AUTO_RESET_ON_INT 		 = 0x30,
} LSM6DS3_HPM_G_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: HP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_HP_EN_DISABLED 		 = 0x00,
	LSM6DS3_HP_EN_ENABLED 		 = 0x40,
} LSM6DS3_HP_EN_t;

/*******************************************************************************
* Register      : CTRL7_G
* Address       : 0X16
* Bit Group Name: LP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_LP_EN_DISABLED 		 = 0x00,
	LSM6DS3_LP_EN_ENABLED 		 = 0x80,
} LSM6DS3_LP_EN_t;

/*******************************************************************************
* Register      : CTRL8_XL
* Address       : 0X17
* Bit Group Name: FDS
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FDS_FILTER_OFF 		 = 0x00,
	LSM6DS3_FDS_FILTER_ON 		 = 0x04,
} LSM6DS3_FDS_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: XEN_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_XEN_XL_DISABLED 		 = 0x00,
	LSM6DS3_XEN_XL_ENABLED 		 = 0x08,
} LSM6DS3_XEN_XL_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: YEN_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_YEN_XL_DISABLED 		 = 0x00,
	LSM6DS3_YEN_XL_ENABLED 		 = 0x10,
} LSM6DS3_YEN_XL_t;

/*******************************************************************************
* Register      : CTRL9_XL
* Address       : 0X18
* Bit Group Name: ZEN_XL
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ZEN_XL_DISABLED 		 = 0x00,
	LSM6DS3_ZEN_XL_ENABLED 		 = 0x20,
} LSM6DS3_ZEN_XL_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: SIGN_MOTION_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIGN_MOTION_EN_DISABLED 		 = 0x00,
	LSM6DS3_SIGN_MOTION_EN_ENABLED 		 = 0x01,
} LSM6DS3_SIGN_MOTION_EN_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: PEDO_RST_STEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PEDO_RST_STEP_DISABLED 		 = 0x00,
	LSM6DS3_PEDO_RST_STEP_ENABLED 		 = 0x02,
} LSM6DS3_PEDO_RST_STEP_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: XEN_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_XEN_G_DISABLED 		 = 0x00,
	LSM6DS3_XEN_G_ENABLED 		 = 0x08,
} LSM6DS3_XEN_G_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: YEN_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_YEN_G_DISABLED 		 = 0x00,
	LSM6DS3_YEN_G_ENABLED 		 = 0x10,
} LSM6DS3_YEN_G_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: ZEN_G
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_ZEN_G_DISABLED 		 = 0x00,
	LSM6DS3_ZEN_G_ENABLED 		 = 0x20,
} LSM6DS3_ZEN_G_t;

/*******************************************************************************
* Register      : CTRL10_C
* Address       : 0X19
* Bit Group Name: FUNC_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FUNC_EN_DISABLED 		 = 0x00,
	LSM6DS3_FUNC_EN_ENABLED 		 = 0x04,
} LSM6DS3_FUNC_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: MASTER_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_MASTER_ON_DISABLED 		 = 0x00,
	LSM6DS3_MASTER_ON_ENABLED 		 = 0x01,
} LSM6DS3_MASTER_ON_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: IRON_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_IRON_EN_DISABLED 		 = 0x00,
	LSM6DS3_IRON_EN_ENABLED 		 = 0x02,
} LSM6DS3_IRON_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: PASS_THRU_MODE
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PASS_THRU_MODE_DISABLED 		 = 0x00,
	LSM6DS3_PASS_THRU_MODE_ENABLED 		 = 0x04,
} LSM6DS3_PASS_THRU_MODE_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: PULL_UP_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PULL_UP_EN_DISABLED 		 = 0x00,
	LSM6DS3_PULL_UP_EN_ENABLED 		 = 0x08,
} LSM6DS3_PULL_UP_EN_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: START_CONFIG
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_START_CONFIG_XL_G_DRDY 		 = 0x00,
	LSM6DS3_START_CONFIG_EXT_INT2 		 = 0x10,
} LSM6DS3_START_CONFIG_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: DATA_VAL_SEL_FIFO
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DATA_VAL_SEL_FIFO_XL_G_DRDY 		 = 0x00,
	LSM6DS3_DATA_VAL_SEL_FIFO_SHUB_DRDY 		 = 0x40,
} LSM6DS3_DATA_VAL_SEL_FIFO_t;

/*******************************************************************************
* Register      : MASTER_CONFIG
* Address       : 0X1A
* Bit Group Name: DRDY_ON_INT1
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_DRDY_ON_INT1_DISABLED 		 = 0x00,
	LSM6DS3_DRDY_ON_INT1_ENABLED 		 = 0x80,
} LSM6DS3_DRDY_ON_INT1_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: Z_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_Z_WU_NOT_DETECTED 		 = 0x00,
	LSM6DS3_Z_WU_DETECTED 		 = 0x01,
} LSM6DS3_Z_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: Y_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_Y_WU_NOT_DETECTED 		 = 0x00,
	LSM6DS3_Y_WU_DETECTED 		 = 0x02,
} LSM6DS3_Y_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: X_WU
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_X_WU_NOT_DETECTED 		 = 0x00,
	LSM6DS3_X_WU_DETECTED 		 = 0x04,
} LSM6DS3_X_WU_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: WU_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_WU_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_WU_EV_STATUS_DETECTED 		 = 0x08,
} LSM6DS3_WU_EV_STATUS_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: SLEEP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_SLEEP_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_SLEEP_EV_STATUS_DETECTED 		 = 0x10,
} LSM6DS3_SLEEP_EV_STATUS_t;

/*******************************************************************************
* Register      : WAKE_UP_SRC
* Address       : 0X1B
* Bit Group Name: FF_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_FF_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_FF_EV_STATUS_DETECTED 		 = 0x20,
} LSM6DS3_FF_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: Z_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_Z_TAP_NOT_DETECTED 		 = 0x00,
	LSM6DS3_Z_TAP_DETECTED 		 = 0x01,
} LSM6DS3_Z_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: Y_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_Y_TAP_NOT_DETECTED 		 = 0x00,
	LSM6DS3_Y_TAP_DETECTED 		 = 0x02,
} LSM6DS3_Y_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: X_TAP
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_X_TAP_NOT_DETECTED 		 = 0x00,
	LSM6DS3_X_TAP_DETECTED 		 = 0x04,
} LSM6DS3_X_TAP_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: TAP_SIGN
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_TAP_SIGN_POS_SIGN 		 = 0x00,
	LSM6DS3_TAP_SIGN_NEG_SIGN 		 = 0x08,
} LSM6DS3_TAP_SIGN_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: DOUBLE_TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DOUBLE_TAP_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DOUBLE_TAP_EV_STATUS_DETECTED 		 = 0x10,
} LSM6DS3_DOUBLE_TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: SINGLE_TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_SINGLE_TAP_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_SINGLE_TAP_EV_STATUS_DETECTED 		 = 0x20,
} LSM6DS3_SINGLE_TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_SRC
* Address       : 0X1C
* Bit Group Name: TAP_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_TAP_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_TAP_EV_STATUS_DETECTED 		 = 0x40,
} LSM6DS3_TAP_EV_STATUS_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_XL
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_XL_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_XL_DETECTED 		 = 0x01,
} LSM6DS3_DSD_XL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_XH
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_XH_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_XH_DETECTED 		 = 0x02,
} LSM6DS3_DSD_XH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_YL
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_YL_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_YL_DETECTED 		 = 0x04,
} LSM6DS3_DSD_YL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_YH
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_YH_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_YH_DETECTED 		 = 0x08,
} LSM6DS3_DSD_YH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_ZL
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_ZL_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_ZL_DETECTED 		 = 0x10,
} LSM6DS3_DSD_ZL_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: DSD_ZH
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_DSD_ZH_NOT_DETECTED 		 = 0x00,
	LSM6DS3_DSD_ZH_DETECTED 		 = 0x20,
} LSM6DS3_DSD_ZH_t;

/*******************************************************************************
* Register      : D6D_SRC
* Address       : 0X1D
* Bit Group Name: D6D_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_D6D_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_D6D_EV_STATUS_DETECTED 		 = 0x40,
} LSM6DS3_D6D_EV_STATUS_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: XLDA
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_XLDA_NO_DATA_AVAIL 		 = 0x00,
	LSM6DS3_XLDA_DATA_AVAIL 		 = 0x01,
} LSM6DS3_XLDA_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: GDA
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_GDA_NO_DATA_AVAIL 		 = 0x00,
	LSM6DS3_GDA_DATA_AVAIL 		 = 0x02,
} LSM6DS3_GDA_t;

/*******************************************************************************
* Register      : STATUS_REG
* Address       : 0X1E
* Bit Group Name: EV_BOOT
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_EV_BOOT_NO_BOOT_RUNNING 		 = 0x00,
	LSM6DS3_EV_BOOT_BOOT_IS_RUNNING 		 = 0x08,
} LSM6DS3_EV_BOOT_t;

/*******************************************************************************
* Register      : FIFO_STATUS1
* Address       : 0X3A
* Bit Group Name: DIFF_FIFO
* Permission    : RO
*******************************************************************************/
#define  	LSM6DS3_DIFF_FIFO_STATUS1_MASK  	0xFF
#define  	LSM6DS3_DIFF_FIFO_STATUS1_POSITION  	0
#define  	LSM6DS3_DIFF_FIFO_STATUS2_MASK  0xF
#define  	LSM6DS3_DIFF_FIFO_STATUS2_POSITION  	0

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: FIFO_EMPTY
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_FIFO_EMPTY_FIFO_NOT_EMPTY 		 = 0x00,
	LSM6DS3_FIFO_EMPTY_FIFO_EMPTY 		 = 0x10,
} LSM6DS3_FIFO_EMPTY_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: FIFO_FULL
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_FIFO_FULL_FIFO_NOT_FULL 		 = 0x00,
	LSM6DS3_FIFO_FULL_FIFO_FULL 		 = 0x20,
} LSM6DS3_FIFO_FULL_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: OVERRUN
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_OVERRUN_NO_OVERRUN 		 = 0x00,
	LSM6DS3_OVERRUN_OVERRUN 		 = 0x40,
} LSM6DS3_OVERRUN_t;

/*******************************************************************************
* Register      : FIFO_STATUS2
* Address       : 0X3B
* Bit Group Name: WTM
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_WTM_BELOW_WTM 		 = 0x00,
	LSM6DS3_WTM_ABOVE_OR_EQUAL_WTM 		 = 0x80,
} LSM6DS3_WTM_t;

/*******************************************************************************
* Register      : FIFO_STATUS3
* Address       : 0X3C
* Bit Group Name: FIFO_PATTERN
* Permission    : RO
*******************************************************************************/
#define  	LSM6DS3_FIFO_STATUS3_PATTERN_MASK  	0xFF
#define  	LSM6DS3_FIFO_STATUS3_PATTERN_POSITION  	0
#define  	LSM6DS3_FIFO_STATUS4_PATTERN_MASK  	0x03
#define  	LSM6DS3_FIFO_STATUS4_PATTERN_POSITION  	0

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X53
* Bit Group Name: SENS_HUB_END
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_SENS_HUB_END_STILL_ONGOING 		 = 0x00,
	LSM6DS3_SENS_HUB_END_OP_COMPLETED 		 = 0x01,
} LSM6DS3_SENS_HUB_END_t;

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X53
* Bit Group Name: SOFT_IRON_END
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_SOFT_IRON_END_NOT_COMPLETED 		 = 0x00,
	LSM6DS3_SOFT_IRON_END_COMPLETED 		 = 0x02,
} LSM6DS3_SOFT_IRON_END_t;

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X53
* Bit Group Name: PEDO_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_PEDO_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_PEDO_EV_STATUS_DETECTED 		 = 0x10,
} LSM6DS3_PEDO_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X53
* Bit Group Name: TILT_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_TILT_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_TILT_EV_STATUS_DETECTED 		 = 0x20,
} LSM6DS3_TILT_EV_STATUS_t;

/*******************************************************************************
* Register      : FUNC_SRC
* Address       : 0X53
* Bit Group Name: SIGN_MOT_EV_STATUS
* Permission    : RO
*******************************************************************************/
typedef enum {
	LSM6DS3_SIGN_MOT_EV_STATUS_NOT_DETECTED 		 = 0x00,
	LSM6DS3_SIGN_MOT_EV_STATUS_DETECTED 		 = 0x40,
} LSM6DS3_SIGN_MOT_EV_STATUS_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: LIR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_LIR_DISABLED 		 = 0x00,
	LSM6DS3_LIR_ENABLED 		 = 0x01,
} LSM6DS3_LIR_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_Z_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TAP_Z_EN_DISABLED 		 = 0x00,
	LSM6DS3_TAP_Z_EN_ENABLED 		 = 0x02,
} LSM6DS3_TAP_Z_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_Y_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TAP_Y_EN_DISABLED 		 = 0x00,
	LSM6DS3_TAP_Y_EN_ENABLED 		 = 0x04,
} LSM6DS3_TAP_Y_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TAP_X_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TAP_X_EN_DISABLED 		 = 0x00,
	LSM6DS3_TAP_X_EN_ENABLED 		 = 0x08,
} LSM6DS3_TAP_X_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TILT_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TILT_EN_DISABLED 		 = 0x00,
	LSM6DS3_TILT_EN_ENABLED 		 = 0x20,
} LSM6DS3_TILT_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: PEDO_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_PEDO_EN_DISABLED 		 = 0x00,
	LSM6DS3_PEDO_EN_ENABLED 		 = 0x40,
} LSM6DS3_PEDO_EN_t;

/*******************************************************************************
* Register      : TAP_CFG1
* Address       : 0X58
* Bit Group Name: TIMER_EN
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TIMER_EN_DISABLED 		 = 0x00,
	LSM6DS3_TIMER_EN_ENABLED 		 = 0x80,
} LSM6DS3_TIMER_EN_t;

/*******************************************************************************
* Register      : TAP_THS_6D
* Address       : 0X59
* Bit Group Name: TAP_THS
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_TAP_THS_MASK  	0x1F
#define  	LSM6DS3_TAP_THS_POSITION  	0

/*******************************************************************************
* Register      : TAP_THS_6D
* Address       : 0X59
* Bit Group Name: SIXD_THS
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SIXD_THS_80_degree 		 = 0x00,
	LSM6DS3_SIXD_THS_70_degree 		 = 0x20,
	LSM6DS3_SIXD_THS_60_degree 		 = 0x40,
	LSM6DS3_SIXD_THS_50_degree 		 = 0x60,
} LSM6DS3_SIXD_THS_t;

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: SHOCK
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_SHOCK_MASK  	0x03
#define  	LSM6DS3_SHOCK_POSITION  	0

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: QUIET
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_QUIET_MASK  	0x0C
#define  	LSM6DS3_QUIET_POSITION  	2

/*******************************************************************************
* Register      : INT_DUR2
* Address       : 0X5A
* Bit Group Name: DUR
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_DUR_MASK  	0xF0
#define  	LSM6DS3_DUR_POSITION  	4

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X5B
* Bit Group Name: WK_THS
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_WK_THS_MASK  	0x3F
#define  	LSM6DS3_WK_THS_POSITION  	0

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X5B
* Bit Group Name: INACTIVITY_ON
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INACTIVITY_ON_DISABLED 		 = 0x00,
	LSM6DS3_INACTIVITY_ON_ENABLED 		 = 0x40,
} LSM6DS3_INACTIVITY_ON_t;

/*******************************************************************************
* Register      : WAKE_UP_THS
* Address       : 0X5B
* Bit Group Name: SINGLE_DOUBLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_SINGLE_DOUBLE_TAP_DOUBLE_TAP 		 = 0x00,
	LSM6DS3_SINGLE_DOUBLE_TAP_SINGLE_TAP 		 = 0x80,
} LSM6DS3_SINGLE_DOUBLE_TAP_t;

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: SLEEP_DUR
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_SLEEP_DUR_MASK  	0x0F
#define  	LSM6DS3_SLEEP_DUR_POSITION  	0

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: TIMER_HR
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_TIMER_HR_6_4ms 		 = 0x00,
	LSM6DS3_TIMER_HR_25us 		 = 0x10,
} LSM6DS3_TIMER_HR_t;

/*******************************************************************************
* Register      : WAKE_UP_DUR
* Address       : 0X5C
* Bit Group Name: WAKE_DUR
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_WAKE_DUR_MASK  	0x60
#define  	LSM6DS3_WAKE_DUR_POSITION  	5

/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X5D
* Bit Group Name: FF_DUR
* Permission    : RW
*******************************************************************************/
#define  	LSM6DS3_FF_FREE_FALL_DUR_MASK  	0xF8
#define  	LSM6DS3_FF_FREE_FALL_DUR_POSITION  	3
#define  	LSM6DS3_FF_WAKE_UP_DUR_MASK  	0x80
#define  	LSM6DS3_FF_WAKE_UP_DUR_POSITION  	7


/*******************************************************************************
* Register      : FREE_FALL
* Address       : 0X5D
* Bit Group Name: FF_THS
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_FF_THS_5 		 = 0x00,
	LSM6DS3_FF_THS_7 		 = 0x01,
	LSM6DS3_FF_THS_8 		 = 0x02,
	LSM6DS3_FF_THS_10 		 = 0x03,
	LSM6DS3_FF_THS_11 		 = 0x04,
	LSM6DS3_FF_THS_13 		 = 0x05,
	LSM6DS3_FF_THS_15 		 = 0x06,
	LSM6DS3_FF_THS_16 		 = 0x07,
} LSM6DS3_FF_THS_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TIMER
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_TIMER_DISABLED 		 = 0x00,
	LSM6DS3_INT1_TIMER_ENABLED 		 = 0x01,
} LSM6DS3_INT1_TIMER_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_TILT_DISABLED 		 = 0x00,
	LSM6DS3_INT1_TILT_ENABLED 		 = 0x02,
} LSM6DS3_INT1_TILT_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_6D_DISABLED 		 = 0x00,
	LSM6DS3_INT1_6D_ENABLED 		 = 0x04,
} LSM6DS3_INT1_6D_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_TAP_DISABLED 		 = 0x00,
	LSM6DS3_INT1_TAP_ENABLED 		 = 0x08,
} LSM6DS3_INT1_TAP_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_FF
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_FF_DISABLED 		 = 0x00,
	LSM6DS3_INT1_FF_ENABLED 		 = 0x10,
} LSM6DS3_INT1_FF_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_WU
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_WU_DISABLED 		 = 0x00,
	LSM6DS3_INT1_WU_ENABLED 		 = 0x20,
} LSM6DS3_INT1_WU_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_SINGLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_SINGLE_TAP_DISABLED 		 = 0x00,
	LSM6DS3_INT1_SINGLE_TAP_ENABLED 		 = 0x40,
} LSM6DS3_INT1_SINGLE_TAP_t;

/*******************************************************************************
* Register      : MD1_CFG
* Address       : 0X5E
* Bit Group Name: INT1_SLEEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT1_SLEEP_DISABLED 		 = 0x00,
	LSM6DS3_INT1_SLEEP_ENABLED 		 = 0x80,
} LSM6DS3_INT1_SLEEP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_TIMER
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_TIMER_DISABLED 		 = 0x00,
	LSM6DS3_INT2_TIMER_ENABLED 		 = 0x01,
} LSM6DS3_INT2_TIMER_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_TILT
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_TILT_DISABLED 		 = 0x00,
	LSM6DS3_INT2_TILT_ENABLED 		 = 0x02,
} LSM6DS3_INT2_TILT_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_6D
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_6D_DISABLED 		 = 0x00,
	LSM6DS3_INT2_6D_ENABLED 		 = 0x04,
} LSM6DS3_INT2_6D_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_TAP_DISABLED 		 = 0x00,
	LSM6DS3_INT2_TAP_ENABLED 		 = 0x08,
} LSM6DS3_INT2_TAP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_FF
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_FF_DISABLED 		 = 0x00,
	LSM6DS3_INT2_FF_ENABLED 		 = 0x10,
} LSM6DS3_INT2_FF_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_WU
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_WU_DISABLED 		 = 0x00,
	LSM6DS3_INT2_WU_ENABLED 		 = 0x20,
} LSM6DS3_INT2_WU_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_SINGLE_TAP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_SINGLE_TAP_DISABLED 		 = 0x00,
	LSM6DS3_INT2_SINGLE_TAP_ENABLED 		 = 0x40,
} LSM6DS3_INT2_SINGLE_TAP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_SLEEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT2_SLEEP_DISABLED 		 = 0x00,
	LSM6DS3_INT2_SLEEP_ENABLED 		 = 0x80,
} LSM6DS3_INT2_SLEEP_t;

/*******************************************************************************
* Register      : MD2_CFG
* Address       : 0X5F
* Bit Group Name: INT2_SLEEP
* Permission    : RW
*******************************************************************************/
typedef enum {
	LSM6DS3_INT_FLAG_FF_IA                         = 0b100000,
	LSM6DS3_INT_FLAG_SLEEP_STATE_IA                = 0b10000,
        LSM6DS3_INT_FLAG_WU_IA                         = 0b1000,
        LSM6DS3_INT_FLAG_X_WU                          = 0b100,
        LSM6DS3_INT_FLAG_Y_WU                          = 0b10,
        LSM6DS3_INT_FLAG_Z_WU                          = 0b1,
} LSM6DS3_INT_WAKE_UP_SRC_t;

typedef enum {
        LSM6DS3_INT_FLAG_TAP_IA                        = 0b1000000,
        LSM6DS3_INT_FLAG_SINGLE_TAP                    = 0b100000,
        LSM6DS3_INT_FLAG_DOUBLE_TAP                    = 0b10000,
        LSM6DS3_INT_FLAG_TAP_SIGN                      = 0b1000,
        LSM6DS3_INT_FLAG_X_TAP                         = 0b100,
        LSM6DS3_INT_FLAG_Y_TAP                         = 0b10,
        LSM6DS3_INT_FLAG_Z_TAP                         = 0b1,
} LSM6DS3_INT_TAP_SRC_t;

typedef enum {        
        LSM6DS3_INT_FLAG_D6D_IA                        = 0b1000000,
        LSM6DS3_INT_FLAG_ZH                            = 0b100000,
        LSM6DS3_INT_FLAG_ZL                            = 0b10000,
        LSM6DS3_INT_FLAG_YH                            = 0b1000,
        LSM6DS3_INT_FLAG_YL                            = 0b100,
        LSM6DS3_INT_FLAG_XH                            = 0b10,
        LSM6DS3_INT_FLAG_XL                            = 0b1,
} LSM6DS3_INT_D6D_SRC_t;

typedef enum {
        LSM6DS3_INT_FUNC_STEP_COUNT_DELTA_IA           = 0b10000000,
        LSM6DS3_INT_FUNC_SIGN_MOTION_IA                = 0b1000000,
        LSM6DS3_INT_FUNC_TILT_IA                       = 0b100000,
        LSM6DS3_INT_FUNC_STEP_DETECTED                 = 0b10000,
        LSM6DS3_INT_FUNC_STEP_OVERFLOW                 = 0b1000,
        LSM6DS3_INT_FUNC_SI_END_OP                     = 0b10,
        LSM6DS3_INT_FUNC_SENSORHUB_END_OP              = 0b1,
} LSM6DS3_INT_FUNC_SRC_t;

/*============================================================================
Prototypes
============================================================================*/
status_t getIMUDeviceID(uint8_t* id);
status_t resetIMU();
status_t initIMU();
status_t calibrateLSM6DS3();

status_t initGyro();
status_t initAccel();
status_t initInterrupts();
void getIMUInterruptSource(uint8_t* interruptSrc);

status_t setAccelBW(LSM6DS3_BW_XL_t bw);
status_t setAccelODR(LSM6DS3_ODR_XL_t rate);
status_t setGyroODR(LSM6DS3_ODR_G_t rate);
status_t setAccelRange(LSM6DS3_FS_XL_t range);
status_t setGyroRange(LSM6DS3_FS_G_t range);

status_t getMotionT(MotionData* motionData);

float calculateTemperature(int16_t rawInput);
float calculateAcceleration(int16_t rawInput);
float calculateRotation(int16_t rawInput);

status_t getRawMotionT(ImuRawData* imu);

status_t getRawAcceleration(int16_t* ax, int16_t* ay, int16_t* az);
status_t getRawRotation(int16_t* gx, int16_t* gy, int16_t* gz);

status_t getRawTemperature(int16_t *t);
status_t getRawAccelerationX(int16_t *ax);
status_t getRawAccelerationY(int16_t *ay);
status_t getRawAccelerationZ(int16_t *az);
status_t getRawRotationX(int16_t *gx);
status_t getRawRotationY(int16_t *gy);
status_t getRawRotationZ(int16_t *gz);

#ifdef __cplusplus
}
#endif

#endif  // End of __LSM6DS3_H__ definition check