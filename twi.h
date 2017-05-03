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
 * @file    hal_i2c.h
 * @brief   I2C Driver macros and structures.
 *
 * @addtogroup I2C
 * @{
 */

#ifndef HAL_I2C_H
#define HAL_I2C_H

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
 * @brief   Driver state machine possible states.
 */
typedef enum {
  I2C_UNINIT = 0,                           /**< Not initialized.           */
  I2C_STOP = 1,                             /**< Stopped.                   */
  I2C_READY = 2,                            /**< Ready.                     */
  I2C_ACTIVE_TX = 3,                        /**< Transmitting.              */
  I2C_ACTIVE_RX = 4,                        /**< Receiving.                 */
  I2C_LOCKED = 5                            /**> Bus or driver locked.      */
} i2cstate_t;


/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

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
 * @brief   Type representing I2C address.
 */
typedef uint8_t i2caddr_t;

/**
 * @brief   I2C Driver condition flags type.
 */
typedef uint8_t i2cflags_t;

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

/**
 * @brief   Structure representing an I2C driver.
 */
struct I2CDriver {
  /**
   * @brief   Driver state.
   */
  i2cstate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const I2CConfig           *config;
  /**
   * @brief   Error flags.
   */
  i2cflags_t                errors;
  /* End of the mandatory fields.*/
  /**
   * @brief   Thread waiting for I/O completion.
   */
  thread_reference_t        thread;
  /**
   * @brief   Address of slave device.
   */
  i2caddr_t                 addr;
  /**
   * @brief   Pointer to the buffer with data to send.
   */
  const uint8_t             *txbuf;
  /**
   * @brief   Number of bytes of data to send.
   */
  size_t                    txbytes;
  /**
   * @brief   Current index in buffer when sending data.
   */
  size_t                    txidx;
  /**
   * @brief   Pointer to the buffer to put received data.
   */
  uint8_t                   *rxbuf;
  /**
   * @brief   Number of bytes of data to receive.
   */
  size_t                    rxbytes;
  /**
   * @brief   Current index in buffer when receiving data.
   */
  size_t                    rxidx;
};

/**
 * @brief   Type of a structure representing an I2C driver.
 */
typedef struct I2CDriver I2CDriver;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Get errors from I2C driver.
 *
 * @param[in] i2cp  pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_errors(i2cp) ((i2cp)->errors)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern I2CDriver I2CD1;

#ifdef __cplusplus
extern "C" {
#endif
  void i2c_lld_init(void);
  void i2c_lld_start(I2CDriver *i2cp);
  void i2c_lld_stop(I2CDriver *i2cp);
  msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                        const uint8_t *txbuf, size_t txbytes,
                                        uint8_t *rxbuf, size_t rxbytes,
                                        systime_t timeout);
  msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                       uint8_t *rxbuf, size_t rxbytes,
                                       systime_t timeout);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Wakes up the waiting thread notifying no errors.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define _i2c_wakeup_isr(i2cp) do {                                          \
  osalSysLockFromISR();                                                     \
  osalThreadResumeI(&(i2cp)->thread, MSG_OK);                               \
  osalSysUnlockFromISR();                                                   \
} while(0)

/**
 * @brief   Wakes up the waiting thread notifying errors.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define _i2c_wakeup_error_isr(i2cp) do {                                    \
  osalSysLockFromISR();                                                     \
  osalThreadResumeI(&(i2cp)->thread, MSG_RESET);                            \
  osalSysUnlockFromISR();                                                   \
} while(0)

/**
 * @brief   Wrap i2cMasterTransmitTimeout function with TIME_INFINITE timeout.
 * @api
 */
#define i2cMasterTransmit(i2cp, addr, txbuf, txbytes, rxbuf, rxbytes)       \
  (i2cMasterTransmitTimeout(i2cp, addr, txbuf, txbytes, rxbuf, rxbytes,     \
                            TIME_INFINITE))

/**
 * @brief   Wrap i2cMasterReceiveTimeout function with TIME_INFINITE timeout.
 * @api
 */
#define i2cMasterReceive(i2cp, addr, rxbuf, rxbytes)                        \
  (i2cMasterReceiveTimeout(i2cp, addr, rxbuf, rxbytes, TIME_INFINITE))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void i2cInit(void);
  void i2cObjectInit(I2CDriver *i2cp);
  void i2cStart(I2CDriver *i2cp, const I2CConfig *config);
  void i2cStop(I2CDriver *i2cp);
  i2cflags_t i2cGetErrors(I2CDriver *i2cp);
  msg_t i2cMasterTransmitTimeout(I2CDriver *i2cp,
                                 i2caddr_t addr,
                                 const uint8_t *txbuf, size_t txbytes,
                                 uint8_t *rxbuf, size_t rxbytes,
                                 systime_t timeout);
  msg_t i2cMasterReceiveTimeout(I2CDriver *i2cp,
                                i2caddr_t addr,
                                uint8_t *rxbuf, size_t rxbytes,
                                systime_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_H */

/** @} */
