/**
 * \file
 *
 * \brief Application to generate sample driver to AVRs TWI module
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel micro controller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI_Master.h"

#define TWI_GEN_CALL         0x00  // The General Call address is 0

// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

// Sample TWI transmission states, used in the main application.
#define SEND_DATA             0x01
#define REQUEST_DATA          0x02
#define READ_DATA_FROM_BUFFER 0x03

unsigned char TWI_Act_On_Failure_In_Last_Transmission ( unsigned char TWIerrorMsg )
{
                    // A failure has occurred, use TWIerrorMsg to determine the nature of the failure
                    // and take appropriate actions.
                    // Se header file for a list of possible failures messages.
                    
                    // Here is a simple sample, where if received a NACK on the slave address,
                    // then a retransmission will be initiated.
 
  if ( (TWIerrorMsg == TWI_MTX_ADR_NACK) | (TWIerrorMsg == TWI_MRX_ADR_NACK) )
    TWI_Start_Transceiver();
    
  return TWIerrorMsg; 
}


 int main( void )
{
 unsigned char messageBuf[4];
 unsigned char TWI_targetSlaveAddress, temp, TWI_operation=0,
 pressedButton, myCounter=0;

  //LED feedback port - connect port B to the ST600 LEDS
  DDRB  = 0xFF;
  PORTB = myCounter;
  
  //Switch port - connect portD to the STK600 switches
  DDRD  = 0x00;

  TWI_Master_Initialise();
  sei();//set global interrupt enable
  
  TWI_targetSlaveAddress   = 0x10;

  // This example is made to work together with the AVR311 TWI Slave application note and STK600.
  // In addition to connecting the TWI pins, also connect PORTB to the LEDS and PORTD to the switches.
  // The code reads the pins to trigger the action you request. There is an example sending a general call,
  // address call with Master Read and Master Write. The first byte in the transmission is used to send
  // commands to the TWI slave.
 for(;;)
  {  
    pressedButton = ~PIND;
    if (pressedButton)       // Check if any button is pressed
    {
      do{temp = ~PIND;}      // Wait until key released
      while (temp);
      
      switch ( pressedButton ) 
      {
        // Send a General Call
        case (1<<PD0):      
          messageBuf[0] = TWI_GEN_CALL;     // The first byte must always consists of General Call code or the TWI slave address.
          messageBuf[1] = 0xAA;             // The command or data to be included in the general call.
          TWI_Start_Transceiver_With_Data( messageBuf, 2 );
          break;
        // Send a Address Call, sending a request, followed by a receive          
        case (1<<PD1):      
        // Send the request-for-data command to the Slave
          messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consists of General Call code or the TWI slave address.
          messageBuf[1] = TWI_CMD_MASTER_READ;             // The first byte is used for commands.
          TWI_Start_Transceiver_With_Data( messageBuf, 2 );

          TWI_operation = REQUEST_DATA;         // To release resources to other operations while waiting for the TWI to complete,
                                                // we set a operation mode and continue this command sequence in a "follow up" 
                                                // section further down in the code.
              
        // Get status from Transceiver and put it on PORTB
        case (1<<PD2):
        PORTB = TWI_Get_State_Info();
        break;

        // Increment myCounter and put it on PORTB
        case (1<<PD5):
        PORTB = ++myCounter;
        break;
       // Send a Address Call, sending a command and data to the Slave
        case (1<<PD6):
        messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consists of General Call code or the TWI slave address.
        messageBuf[1] = TWI_CMD_MASTER_WRITE;             // The first byte is used for commands.
        messageBuf[2] = myCounter;                        // The second byte is used for the data.
        TWI_Start_Transceiver_With_Data( messageBuf, 3 );
        break;
        // Reset myCounter and put it on PORTB
        case (1<<PD7):      
          PORTB = myCounter = 0;        
          break;  
      }
    }    

    if ( ! TWI_Transceiver_Busy() )
    {
    // Check if the last operation was successful
      if ( TWI_statusReg.lastTransOK )
      {
        if ( TWI_operation ) // Section for follow-up operations.
        {
        // Determine what action to take now
          if (TWI_operation == REQUEST_DATA)
          { // Request/collect the data from the Slave
            messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT); // The first byte must always consists of General Call code or the TWI slave address.
            TWI_Start_Transceiver_With_Data( messageBuf, 2 );       
            TWI_operation = READ_DATA_FROM_BUFFER; // Set next operation        
          }
          else if (TWI_operation == READ_DATA_FROM_BUFFER)
          { // Get the received data from the transceiver buffer
            TWI_Get_Data_From_Transceiver( messageBuf, 2 );
            PORTB = messageBuf[1];        // Store data on PORTB.
            TWI_operation = FALSE;        // Set next operation        
          }
        }
      }
      else // Got an error during the last transmission
      {
        // Use TWI status information to determine cause of failure and take appropriate actions. 
        TWI_Act_On_Failure_In_Last_Transmission( TWI_Get_State_Info( ) );
      }
    }

    // Do something else while waiting for TWI operation to complete and/or a switch to be pressed
  asm("nop"); // Put own code here.

  }
}



 /* // This example code runs forever; sends a byte to the slave, then requests a byte
  // from the slave and stores it on PORTB, and starts over again. Since it is interrupt
  // driven one can do other operations while waiting for the transceiver to complete.
  
  // Send initial data to slave
  messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT);
  messageBuf[1] = 0x00;
  TWI_Start_Transceiver_With_Data( messageBuf, 2 );

  TWI_operation = REQUEST_DATA; // Set the next operation

  for (;;)
  {
	
	  
	  
    // Check if the TWI Transceiver has completed an operation.
	

    if ( ! TWI_Transceiver_Busy() )                              
    {
    // Check if the last operation was successful
      if ( TWI_statusReg.lastTransOK )
      {
      // Determine what action to take now
        if (TWI_operation == SEND_DATA)
        { // Send data to slave
          messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT);
          TWI_Start_Transceiver_With_Data( messageBuf, 2 );
          
          TWI_operation = REQUEST_DATA; // Set next operation
        }
        else if (TWI_operation == REQUEST_DATA)
        { // Request data from slave
          messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (TRUE<<TWI_READ_BIT);
          TWI_Start_Transceiver_With_Data( messageBuf, 2 );
          
          TWI_operation = READ_DATA_FROM_BUFFER; // Set next operation        
        }
        else if (TWI_operation == READ_DATA_FROM_BUFFER)
        { // Get the received data from the transceiver buffer
          TWI_Get_Data_From_Transceiver( messageBuf, 2 );
          PORTB = messageBuf[1];        // Store data on PORTB.
          
          TWI_operation = SEND_DATA;    // Set next operation        
        }
      }
      else // Got an error during the last transmission
      {
        // Use TWI status information to determine cause of failure and take appropriate actions. 
        TWI_Act_On_Failure_In_Last_Transmission( TWI_Get_State_Info( ) );
      }
    }
    // Do something else while waiting for the TWI Transceiver to complete the current operation
     asm("nop"); // Put own code here.
  }
}*/


