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

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

struct {
  /**
    * @brief   Current configuration data.
    */
  const I2CConfig           *config;
  /**
    * @brief   Error flags.
    */
  uint8_t                errors;
  /* End of the mandatory fields.*/
  /**
    * @brief   Address of slave device.
    */
  uint8_t                 addr;
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
} I2CDriver;

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
ISR(TWI_vect) {

  switch (TWSR & 0xF8) {
  case TWI_START:
  case TWI_REPEAT_START:
    TWDR = (I2CDriver.addr << 1);
    if ((I2CDriver.txbuf == NULL) || (I2CDriver.txbytes == 0) || (I2CDriver.txidx == I2CDriver.txbytes)) {
      TWDR |= 0x01;
    }
    TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    break;
  case TWI_MASTER_TX_ADDR_ACK:
  case TWI_MASTER_TX_DATA_ACK:
    if (I2CDriver.txidx < I2CDriver.txbytes) {
      TWDR = I2CDriver.txbuf[I2CDriver.txidx++];
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      if (I2CDriver.rxbuf && I2CDriver.rxbytes) {
        TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
      }
      else {
        TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
      }
    }
    break;
  case TWI_MASTER_RX_ADDR_ACK:
    if (I2CDriver.rxidx == (I2CDriver.rxbytes - 1)) {
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      TWCR = ((1 << TWEA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    break;
  case TWI_MASTER_RX_DATA_ACK:
    I2CDriver.rxbuf[I2CDriver.rxidx++] = TWDR;
    if (I2CDriver.rxidx == (I2CDriver.rxbytes - 1)) {
      TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    else {
      TWCR = ((1 << TWEA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
    }
    break;
  case TWI_MASTER_RX_DATA_NACK:
    I2CDriver.rxbuf[I2CDriver.rxidx] = TWDR;
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
  case TWI_MASTER_TX_ADDR_NACK:
  case TWI_MASTER_TX_DATA_NACK:
  case TWI_MASTER_RX_ADDR_NACK:
    I2CDriver.errors |= I2C_ACK_FAILURE;
    break;
  case TWI_ARBITRATION_LOST:
    I2CDriver.errors |= I2C_ARBITRATION_LOST;
    break;
  case TWI_BUS_ERROR:
    I2CDriver.errors |= I2C_BUS_ERROR;
    break;
  default:
    /* FIXME: only gets here if there are other MASTERs in the bus */
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
  }

  if (I2CDriver.errors != I2C_NO_ERROR) {
    TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
  }
}

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

  i2cObjectInit();
}

/**
 * @brief   Initializes the standard part of a @p I2CDriver structure.
 *
 * @param[out] i2cp     pointer to the @p I2CDriver object
 *
 * @init
 */
void i2cObjectInit(void) {

  I2CDriver.config = NULL;
}

/**
 * @brief   Configures and activates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @param[in] config    pointer to the @p I2CConfig object
 *
 * @api
 */
void i2cStart(const I2CConfig *config) {

  I2CDriver.config = config;

  uint32_t clock_speed = 100000;

  /* TODO: Test TWI without external pull-ups (use internal) */

  /* Configure prescaler to 1 */
  TWSR &= 0xF8;

  if (I2CDriver.config != NULL)
    clock_speed = I2CDriver.config->clock_speed;

  /* Configure baudrate */
  TWBR = ((F_CPU / clock_speed) - 16) / 2;
}

/**
 * @brief   Deactivates the I2C peripheral.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void i2cStop(void) {

  TWCR &= ~(1 << TWEN);
  I2CDriver.config = NULL;
}

/**
 * @brief   Returns the errors mask associated to the previous operation.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 * @return              The errors mask.
 *
 * @api
 */
uint8_t i2cGetErrors(void) {

  return I2CDriver.errors;
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
void i2cMasterTransmit(uint8_t addr,
                       const uint8_t *txbuf,
                       size_t txbytes,
                       uint8_t *rxbuf,
                       size_t rxbytes) {

  I2CDriver.errors = I2C_NO_ERROR;
  I2CDriver.addr = addr;
  I2CDriver.txbuf = txbuf;
  I2CDriver.txbytes = txbytes;
  I2CDriver.txidx = 0;
  I2CDriver.rxbuf = rxbuf;
  I2CDriver.rxbytes = rxbytes;
  I2CDriver.rxidx = 0;

  TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
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
void i2cMasterReceive(uint8_t addr, uint8_t *rxbuf, size_t rxbytes) {

  I2CDriver.errors = I2C_NO_ERROR;
  I2CDriver.addr = addr;
  I2CDriver.txbuf = NULL;
  I2CDriver.txbytes = 0;
  I2CDriver.txidx = 0;
  I2CDriver.rxbuf = rxbuf;
  I2CDriver.rxbytes = rxbytes;
  I2CDriver.rxidx = 0;

  /* Send START */
  TWCR = ((1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE));
}

/** @} */
