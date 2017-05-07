/*
             LUFA Library
     Copyright (C) Dean Camera, 2016.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2016  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

    /* Includes: */
        #include <avr/pgmspace.h>

        #include <LUFA/Drivers/USB/USB.h>

    /* Macros: */
        /** Endpoint address of the Keyboard HID reporting IN endpoint. */
        #define KEYBOARD_EPADDR                (ENDPOINT_DIR_IN  | 1)

        /** Endpoint address of the Mouse HID reporting IN endpoint. */
        #define MOUSE_EPADDR                   (ENDPOINT_DIR_IN  | 2)

        /** Endpoint address of the Enhanced Keyboard HID reporting IN endpoint. */
        #define ENHANCEDKEYBOARD_EPADDR        (ENDPOINT_DIR_IN  | 3)

        /** Size in bytes of the HID reporting IN endpoint. */
        #define HID_EPSIZE                     8

        /** Endpoint address of the CDC device-to-host notification IN endpoint. */
        #define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 4)

        /** Endpoint address of the CDC device-to-host data IN endpoint. */
        #define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 5)

        /** Endpoint address of the CDC host-to-device data OUT endpoint. */
        #define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 6)

        /** Size in bytes of the CDC device-to-host notification IN endpoint. */
        #define CDC_NOTIFICATION_EPSIZE        8

        /** Size in bytes of the CDC data IN and OUT endpoints. */
        #define CDC_TXRX_EPSIZE                16

    /* Type Defines: */
        /** Type define for the device configuration descriptor structure. This must be defined in the
         *  application code, as the configuration descriptor contains several sub-descriptors which
         *  vary between devices, and which describe the device's usage to the host.
         */
        typedef struct
        {
            USB_Descriptor_Configuration_Header_t    Config;

            // Keyboard HID Interface
            USB_Descriptor_Interface_t               HID1_KeyboardInterface;
            USB_HID_Descriptor_HID_t                 HID1_KeyboardHID;
            USB_Descriptor_Endpoint_t                HID1_ReportINEndpoint;

            // Mouse HID Interface
            USB_Descriptor_Interface_t               HID2_MouseInterface;
            USB_HID_Descriptor_HID_t                 HID2_MouseHID;
            USB_Descriptor_Endpoint_t                HID2_ReportINEndpoint;

            // Enhanced Keyboard HID Interface
            USB_Descriptor_Interface_t               HID3_EnhancedKeyboardInterface;
            USB_HID_Descriptor_HID_t                 HID3_EnhancedKeyboardHID;
            USB_Descriptor_Endpoint_t                HID3_ReportINEndpoint;

#ifdef USE_VIRTUAL_SERIAL
            // CDC Control Interface
            USB_Descriptor_Interface_Association_t   CDC_IAD;
            USB_Descriptor_Interface_t               CDC_CCI_Interface;
            USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
            USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
            USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
            USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

            // CDC Data Interface
            USB_Descriptor_Interface_t               CDC_DCI_Interface;
            USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
            USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
#endif
        } USB_Descriptor_Configuration_t;

        typedef struct {
            uint16_t ConsumerControlCode;
            uint8_t SystemControlCode;
        } USB_EnhancedKeyboardReport_Data_t;

        /** Enum for the device interface descriptor IDs within the device. Each interface descriptor
         *  should have a unique ID index associated with it, which can be used to refer to the
         *  interface from other descriptors.
         */
        enum InterfaceDescriptors_t
        {
            INTERFACE_ID_Keyboard         = 0, /**< Keyboard interface descriptor ID */
            INTERFACE_ID_Mouse            = 1, /**< Mouse interface descriptor ID */
            INTERFACE_ID_EnhancedKeyboard = 2, /**< Enhanced Keyboard interface descriptor ID */
            INTERFACE_ID_CDC_CCI          = 3, /**< CDC CCI interface descriptor ID */
            INTERFACE_ID_CDC_DCI          = 4, /**< CDC DCI interface descriptor ID */
        };

        /** Enum for the device string descriptor IDs within the device. Each string descriptor should
         *  have a unique ID index associated with it, which can be used to refer to the string from
         *  other descriptors.
         */
        enum StringDescriptors_t
        {
            STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
            STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
            STRING_ID_Product      = 2, /**< Product string ID */
        };

    /* Function Prototypes: */
        uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                            const uint16_t wIndex,
                                            const void** const DescriptorAddress)
                                            ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
