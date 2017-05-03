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
 * @file    twi.c
 * @brief   I2C Driver code.
 *
 * @addtogroup I2C
 * @{
 */
#include "twi.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief I2C driver identifier.*/
I2CDriver I2CD1;

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/**
 * @brief   I2C event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(TWI_vect) {
  OSAL_IRQ_PROLOGUE();

  I2CDriver *i2cp = &I2CD1;

  switch (TWSR & 0xF8) {
  case TWI_START:
  case TWI_REPEAT_START:
    TWDR = (i2cp->addr << 1);
    if ((i2cp->txbuf == NULL) || (i2cp->txbytes == 0) || (i2cp->txidx == i2cp->txbytes)) {
      TWDR |= 0x01;
    }
    TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    break;
  case TWI_MASTER_TX_ADDR_ACK:
  case TWI_MASTER_TX_DATA_ACK:
    if (i2cp->txidx < i2cp->txbytes) {
      TWDR = i2cp->txbuf[i2cp->txidx++];
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      if (i2cp->rxbuf && i2cp->rxbytes) {
        TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
      }
      else {
        TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
        _i2c_wakeup_isr(i2cp);
      }
    }
    break;
  case TWI_MASTER_RX_ADDR_ACK:
    if (i2cp->rxidx == (i2cp->rxbytes - 1)) {
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      TWCR = ((1 << TWEA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    break;
  case TWI_MASTER_RX_DATA_ACK:
    i2cp->rxbuf[i2cp->rxidx++] = TWDR;
    if (i2cp->rxidx == (i2cp->rxbytes - 1)) {
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      TWCR = ((1 << TWEA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    break;
  case TWI_MASTER_RX_DATA_NACK:
    i2cp->rxbuf[i2cp->rxidx] = TWDR;
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
    _i2c_wakeup_isr(i2cp);
  case TWI_MASTER_TX_ADDR_NACK:
  case TWI_MASTER_TX_DATA_NACK:
  case TWI_MASTER_RX_ADDR_NACK:
    i2cp->errors |= I2C_ACK_FAILURE;
    break;
  case TWI_ARBITRATION_LOST:
    i2cp->errors |= I2C_ARBITRATION_LOST;
    break;
  case TWI_BUS_ERROR:
    i2cp->errors |= I2C_BUS_ERROR;
    break;
  default:
    /* FIXME: only gets here if there are other MASTERs in the bus */
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
    _i2c_wakeup_error_isr(i2cp);
  }

  if (i2cp->errors != I2C_NO_ERROR) {
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
    _i2c_wakeup_error_isr(i2cp);
  }

  OSAL_IRQ_EPILOGUE();
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level I2C driver initialization.
 *
 * @notapi
 */
void i2c_lld_init(void) {
  i2cObjectInit(&I2CD1);
  I2CD1.thread = NULL;
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp  pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_start(I2CDriver *i2cp) {
  uint32_t clock_speed = 100000;

  /* TODO: Test TWI without external pull-ups (use internal) */

  /* Configure prescaler to 1 */
  TWSR &= 0xF8;

  if (i2cp->config != NULL)
    clock_speed = i2cp->config->clock_speed;

  /* Configure baudrate */
  TWBR = ((F_CPU / clock_speed) - 16) / 2;
}

/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp  pointer to the @p I2CDriver object
 *
 * @notapi
 */
void i2c_lld_stop(I2CDriver *i2cp) {

  if (i2cp->state != I2C_STOP) {
    /* Disable TWI subsystem and stop all operations */
    TWCR &= ~(1 << TWEN);
  }
}

/**
 * @brief   Receives data via the I2C bus as master.
 *
 * @param[in]   i2cp      pointer to the @p I2CDriver object
 * @param[in]   addr      slave device address
 * @param[out]  rxbuf     pointer to the receive buffer
 * @param[in]   rxbytes   number of bytes to be received
 * @param[in]   timeout   the number of ticks before the operation timeouts,
 *                        the following special values are allowed:
 *                        - @a TIME_INFINITE no timeout.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                     uint8_t *rxbuf, size_t rxbytes,
                                     systime_t timeout) {
  i2cp->errors = I2C_NO_ERROR;
  i2cp->addr = addr;
  i2cp->txbuf = NULL;
  i2cp->txbytes = 0;
  i2cp->txidx = 0;
  i2cp->rxbuf = rxbuf;
  i2cp->rxbytes = rxbytes;
  i2cp->rxidx = 0;

  /* Send START */
  TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));

  return osalThreadSuspendTimeoutS(&i2cp->thread, TIME_INFINITE);
}

/**
 * @brief   Transmits data via the I2C bus as master.
 *
 * @param[in]   i2cp      pointer to the @p I2CDriver object
 * @param[in]   addr      slave device address
 * @param[in]   txbuf     pointer to the transmit buffer
 * @param[in]   txbytes   number of bytes to be transmitted
 * @param[out]  rxbuf     pointer to the receive buffer
 * @param[in]   rxbytes   number of bytes to be received
 * @param[in]   timeout   the number of ticks before the operation timeouts,
 *                        the following special values are allowed:
 *                        - @a TIME_INFINITE no timeout.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end. <b>After a
 *                      timeout the driver must be stopped and restarted
 *                      because the bus is in an uncertain state</b>.
 *
 * @notapi
 */
msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                      const uint8_t *txbuf, size_t txbytes,
                                      uint8_t *rxbuf, size_t rxbytes,
                                      systime_t timeout) {
  i2cp->errors = I2C_NO_ERROR;
  i2cp->addr = addr;
  i2cp->txbuf = txbuf;
  i2cp->txbytes = txbytes;
  i2cp->txidx = 0;
  i2cp->rxbuf = rxbuf;
  i2cp->rxbytes = rxbytes;
  i2cp->rxidx = 0;

  TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));

  return osalThreadSuspendTimeoutS(&i2cp->thread, TIME_INFINITE);
}

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   I2C Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void i2cInit(void) {

  i2c_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p I2CDriver structure.
 *
 * @param[out] i2cp     pointer to the @p I2CDriver object
 *
 * @init
 */
void i2cObjectInit(I2CDriver *i2cp) {

  i2cp->state  = I2C_STOP;
  i2cp->config = NULL;
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] config    pointer to the @p I2CConfig object
 *
 * @api
 */
void i2cStart(I2CDriver *i2cp, const I2CConfig *config) {

  osalSysLock();
  i2cp->config = config;
  i2c_lld_start(i2cp);
  i2cp->state = I2C_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void i2cStop(I2CDriver *i2cp) {

  osalSysLock();

  i2c_lld_stop(i2cp);
  i2cp->config = NULL;
  i2cp->state  = I2C_STOP;

  osalSysUnlock();
}

/**
 * @brief   Returns the errors mask associated to the previous operation.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @return              The errors mask.
 *
 * @api
 */
i2cflags_t i2cGetErrors(I2CDriver *i2cp) {

  return i2c_lld_get_errors(i2cp);
}

/**
 * @brief   Sends data via the I2C bus.
 * @details Function designed to realize "read-through-write" transfer
 *          paradigm. If you want transmit data without any further read,
 *          than set @b rxbytes field to 0.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address (7 bits) without R/W bit
 * @param[in] txbuf     pointer to transmit buffer
 * @param[in] txbytes   number of bytes to be transmitted
 * @param[out] rxbuf    pointer to receive buffer
 * @param[in] rxbytes   number of bytes to be received, set it to 0 if
 *                      you want transmit only
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 *
 * @api
 */
msg_t i2cMasterTransmitTimeout(I2CDriver *i2cp,
                               i2caddr_t addr,
                               const uint8_t *txbuf,
                               size_t txbytes,
                               uint8_t *rxbuf,
                               size_t rxbytes,
                               systime_t timeout) {
  msg_t rdymsg;

  osalSysLock();
  i2cp->errors = I2C_NO_ERROR;
  i2cp->state = I2C_ACTIVE_TX;
  rdymsg = i2c_lld_master_transmit_timeout(i2cp, addr, txbuf, txbytes,
                                           rxbuf, rxbytes, timeout);
  if (rdymsg == MSG_TIMEOUT) {
    i2cp->state = I2C_LOCKED;
  }
  else {
    i2cp->state = I2C_READY;
  }
  osalSysUnlock();
  return rdymsg;
}

/**
 * @brief   Receives data from the I2C bus.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] addr      slave device address (7 bits) without R/W bit
 * @param[out] rxbuf    pointer to receive buffer
 * @param[in] rxbytes   number of bytes to be received
 * @param[in] timeout   the number of ticks before the operation timeouts,
 *                      the following special values are allowed:
 *                      - @a TIME_INFINITE no timeout.
 *                      .
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 *
 * @api
 */
msg_t i2cMasterReceiveTimeout(I2CDriver *i2cp,
                              i2caddr_t addr,
                              uint8_t *rxbuf,
                              size_t rxbytes,
                              systime_t timeout){

  msg_t rdymsg;

  osalSysLock();
  i2cp->errors = I2C_NO_ERROR;
  i2cp->state = I2C_ACTIVE_RX;
  rdymsg = i2c_lld_master_receive_timeout(i2cp, addr, rxbuf, rxbytes, timeout);
  if (rdymsg == MSG_TIMEOUT) {
    i2cp->state = I2C_LOCKED;
  }
  else {
    i2cp->state = I2C_READY;
  }
  osalSysUnlock();
  return rdymsg;
}

/** @} */
