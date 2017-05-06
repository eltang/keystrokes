/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
   Concepts and parts of this file have been contributed by Uladzimir Pylinsky
   aka barthess.
 */

/**
 * @file    twi.h
 * @brief   I2C Driver macros and structures.
 *
 * @addtogroup I2C
 * @{
 */

#ifndef TWI_H
#define TWI_H

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stddef.h>

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/* TODO: To be reviewed, too STM32-centric.*/
/**
 * @name    I2C bus error conditions
 * @{
 */
#define I2C_NO_ERROR               0x00    /**< @brief No error.            */
#define I2C_BUS_ERROR              0x01    /**< @brief Bus Error.           */
#define I2C_ARBITRATION_LOST       0x02    /**< @brief Arbitration Lost.    */
#define I2C_ACK_FAILURE            0x04    /**< @brief Acknowledge Failure. */
#define I2C_OVERRUN                0x08    /**< @brief Overrun/Underrun.    */
#define I2C_PEC_ERROR              0x10    /**< @brief PEC Error in
                                                reception.                  */
#define I2C_TIMEOUT                0x20    /**< @brief Hardware timeout.    */
#define I2C_SMB_ALERT              0x40    /**< @brief SMBus Alert.         */
/** @} */

/** @brief   START transmitted.*/
#define TWI_START                  0x08
/** @brief   Repeated START transmitted.*/
#define TWI_REPEAT_START           0x10
/** @brief   Arbitration Lost.*/
#define TWI_ARBITRATION_LOST       0x38
/** @brief   Bus errors.*/
#define TWI_BUS_ERROR              0x00

/** @brief   SLA+W transmitted with ACK response.*/
#define TWI_MASTER_TX_ADDR_ACK     0x18
/** @brief   SLA+W transmitted with NACK response.*/
#define TWI_MASTER_TX_ADDR_NACK    0x20
/** @brief   DATA transmitted with ACK response.*/
#define TWI_MASTER_TX_DATA_ACK     0x28
/** @brief   DATA transmitted with NACK response.*/
#define TWI_MASTER_TX_DATA_NACK    0x30

/** @brief   SLA+R transmitted with ACK response.*/
#define TWI_MASTER_RX_ADDR_ACK     0x40
/** @brief   SLA+R transmitted with NACK response.*/
#define TWI_MASTER_RX_ADDR_NACK    0x48
/** @brief   DATA received with ACK response.*/
#define TWI_MASTER_RX_DATA_ACK     0x50
/** @brief   DATA received with NACK response.*/
#define TWI_MASTER_RX_DATA_NACK    0x58

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver configuration structure.
 * @note    Implementations may extend this structure to contain more,
 *          architecture dependent, fields.
 */
typedef struct {

  /**
   * @brief Specifies the I2C clock frequency.
   */
  uint32_t        clock_speed;

} I2CConfig;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void i2cInit(void);
  void i2cObjectInit(void);
  void i2cStart(const I2CConfig *config);
  void i2cStop(void);
  uint8_t i2cGetErrors(void);
  void i2cMasterTransmit(uint8_t addr,
                                 const uint8_t *txbuf, size_t txbytes,
                                 uint8_t *rxbuf, size_t rxbytes);
  void i2cMasterReceive(uint8_t addr,
                                uint8_t *rxbuf, size_t rxbytes);

#ifdef __cplusplus
}
#endif

#endif /* TWI_H */

/** @} */
