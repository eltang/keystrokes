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
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "descriptors.h"

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 *
 *  This descriptor describes the mouse HID interface's report structure.
 */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] =
{
    /* Use the HID class driver's standard Mouse report.
     *   Min X/Y Axis values: -1
     *   Max X/Y Axis values:  1
     *   Min physical X/Y Axis values (used to determine resolution): -1
     *   Max physical X/Y Axis values (used to determine resolution):  1
     *   Buttons: 3
     *   Absolute screen coordinates: false
     */
    HID_DESCRIPTOR_MOUSE(-1, 1, -1, 1, 3, false)
};

/** Same as the MouseReport structure, but defines the keyboard HID interface's report structure. */
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] =
{
    /* Use the HID class driver's standard Keyboard report.
     *   Max simultaneous keys: 6
     */
    HID_DESCRIPTOR_KEYBOARD(6)
};

const USB_Descriptor_HIDReport_Datatype_t PROGMEM EnhancedKeyboardReport[] =
{
    // Keyboard Collection
    0x05, 0x01,          // Usage Page (Generic Desktop),
    0x09, 0x06,          // Usage (Keyboard),
    0xA1, 0x01,          // Collection (Application) - Keyboard,

    // LED Report
    0x85, 0x01,          //   Report ID (1),
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x05,          //   Report Count (5),
    0x05, 0x08,          //   Usage Page (LEDs),
    0x19, 0x01,          //   Usage Minimum (1),
    0x29, 0x05,          //   Usage Maximum (5),
    0x91, 0x02,          //   Output (Data, Variable, Absolute),

    // LED Report Padding
    0x75, 0x03,          //   Report Size (3),
    0x95, 0x01,          //   Report Count (1),
    0x91, 0x03,          //   Output (Constant),

    // Normal Keys - Using an NKRO Bitmap
    //
    // NOTES:
    // Supports all keys defined by the spec, except 1-3 which define error events
    //  and 0 which is "no keys pressed"
    // See http://www.usb.org/developers/hidpage/Hut1_12v2.pdf Chapter 10
    // Or Macros/PartialMap/usb_hid.h
    //
    // 50 (ISO \ due to \ bug) and 156 (Clear due to Delete bug) must be excluded
    //  due to a Linux bug with bitmaps (not useful anyways)
    // 165-175 are reserved/unused as well as 222-223 and 232-65535
    //
    // Compatibility Notes:
    //  - Using a second endpoint for a boot mode device helps with compatibility
    //  - DO NOT use Padding in the descriptor for bitfields
    //    (Mac OSX silently fails... Windows/Linux work correctly)
    //  - DO NOT use Report IDs, Windows 8.1 will not update keyboard correctly (modifiers disappear)
    //    (all other OSs, including OSX work fine...)
    //    (you can use them *iff* you only have 1 per collection)
    //  - Mac OSX and Windows 8.1 are extremely picky about padding
    //
    // Packing of bitmaps are as follows:
    //   4-49  :  6 bytes (0x04-0x31) ( 46 bits + 2 padding bits for 6 bytes total)
    //  51-155 : 14 bytes (0x33-0x9B) (105 bits + 6 padding bits for 15 bytes total)
    // 157-164 :  1 byte  (0x9D-0xA4) (  8 bits)
    // 176-221 :  6 bytes (0xB0-0xDD) ( 46 bits + 2 padding bits for 6 bytes total)
    // 224-231 :  1 byte  (0xE0-0xE7) (  8 bits)

    // Modifier Byte
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x08,          //   Report Count (8),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0xE0,          //   Usage Minimum (224),
    0x29, 0xE7,          //   Usage Maximum (231),
    0x81, 0x02,          //   Input (Data, Variable, Absolute),

    // 4-49 (6 bytes/46 bits) - MainKeys
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x2E,          //   Report Count (46),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0x04,          //   Usage Minimum (4),
    0x29, 0x31,          //   Usage Maximum (49),
    0x81, 0x02,          //   Input (Data, Variable, Absolute, Bitfield),

    // Padding (2 bits)
    0x75, 0x02,          //   Report Size (2),
    0x95, 0x01,          //   Report Count (1),
    0x81, 0x03,          //   Input (Constant),

    // 51-155 (14 bytes/105 bits) - SecondaryKeys
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x69,          //   Report Count (105),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0x33,          //   Usage Minimum (51),
    0x29, 0x9B,          //   Usage Maximum (155),
    0x81, 0x02,          //   Input (Data, Variable, Absolute, Bitfield),

    // Padding (7 bits)
    0x75, 0x07,          //   Report Size (7),
    0x95, 0x01,          //   Report Count (1),
    0x81, 0x03,          //   Input (Constant),

    // 157-164 (1 byte/8 bits) - TertiaryKeys
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x08,          //   Report Count (8),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0x9D,          //   Usage Minimum (157),
    0x29, 0xA4,          //   Usage Maximum (164),
    0x81, 0x02,          //   Input (Data, Variable, Absolute, Bitfield),

    // 176-221 (6 bytes/46 bits) - QuartiaryKeys
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x2E,          //   Report Count (46),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0xB0,          //   Usage Minimum (176),
    0x29, 0xDD,          //   Usage Maximum (221),
    0x81, 0x02,          //   Input (Data, Variable, Absolute, Bitfield),

    // Padding (2 bits)
    0x75, 0x02,          //   Report Size (2),
    0x95, 0x01,          //   Report Count (1),
    0x81, 0x03,          //   Input (Constant),
    0xc0,                // End Collection - Keyboard

    0x05, 0x0C,             //  Usage Page (Consumer)
    0x09, 0x01,             //  Usage (Consumer Controls)
    0xA1, 0x01,             //  Collection (Application)
    0x85, 0x02,             //  Report ID (2)
    0x75, 0x10,             //  Report Size (16)
    0x95, 0x01,             //  Report Count (1)
    0x19, 0x00,             //  Usage Minimum (0)
    0x2A, 0x9C, 0x02,       //  Usage Maximum (0x29C)
    0x15, 0x00,             //  Logical Minimum (0)
    0x26, 0x9C, 0x02,       //  Logical Maximum (0x29C)
    0x81, 0x00,             //  Input (Data, Array)
    0x05, 0x01,             //  Usage Page (Generic Desktop)
    0x75, 0x08,             //  Report Size (8)
    0x95, 0x01,             //  Report Count (1)
    0x19, 0x00,             //  Usage Minimum (0)
    0x29, 0xB7,             //  Usage Maximum (0xB7)
    0x15, 0x00,             //  Logical Minimum (0)
    0x26, 0xB7, 0x00,       //  Logical Maximum (0xB7)
    0x81, 0x00,             //  Input (Data, Array)
    0xC0                    //  End Collection
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
    .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification       = VERSION_BCD(1,1,0),
#ifdef VIRTUAL_SERIAL_ENABLE
    .Class                  = USB_CSCP_IADDeviceClass,
    .SubClass               = USB_CSCP_IADDeviceSubclass,
    .Protocol               = USB_CSCP_IADDeviceProtocol,
#else
    .Class                  = USB_CSCP_NoDeviceClass,
    .SubClass               = USB_CSCP_NoDeviceSubclass,
    .Protocol               = USB_CSCP_NoDeviceProtocol,
#endif

    .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

    .VendorID               = 0x03EB,
    .ProductID              = 0x2062,
    .ReleaseNumber          = VERSION_BCD(0,0,1),

    .ManufacturerStrIndex   = STRING_ID_Manufacturer,
    .ProductStrIndex        = STRING_ID_Product,
#ifdef VIRTUAL_SERIAL_ENABLE
    .SerialNumStrIndex      = USE_INTERNAL_SERIAL,
#else
    .SerialNumStrIndex      = NO_DESCRIPTOR,
#endif

    .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
    .Config =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

            .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
#ifdef VIRTUAL_SERIAL_ENABLE
            .TotalInterfaces        = 5,
#else
            .TotalInterfaces        = 3,
#endif

            .ConfigurationNumber    = 1,
            .ConfigurationStrIndex  = NO_DESCRIPTOR,

            .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_REMOTEWAKEUP),

            .MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
        },

    .HID1_KeyboardInterface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_Keyboard,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_BootSubclass,
            .Protocol               = HID_CSCP_KeyboardBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .HID1_KeyboardHID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(KeyboardReport)
        },

    .HID1_ReportINEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = KEYBOARD_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = HID_EPSIZE,
            .PollingIntervalMS      = 0x01
        },

    .HID2_MouseInterface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_Mouse,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_BootSubclass,
            .Protocol               = HID_CSCP_MouseBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .HID2_MouseHID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(MouseReport)
        },

    .HID2_ReportINEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = MOUSE_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = HID_EPSIZE,
            .PollingIntervalMS      = 0x01
        },

    .HID3_EnhancedKeyboardInterface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_EnhancedKeyboard,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_NonBootSubclass,
            .Protocol               = HID_CSCP_NonBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .HID3_EnhancedKeyboardHID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(EnhancedKeyboardReport)
        },

    .HID3_ReportINEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = ENHANCEDKEYBOARD_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = HID_EPSIZE,
            .PollingIntervalMS      = 0x01
        },

#ifdef VIRTUAL_SERIAL_ENABLE
    .CDC_IAD =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_Association_t), .Type = DTYPE_InterfaceAssociation},

            .FirstInterfaceIndex    = INTERFACE_ID_CDC_CCI,
            .TotalInterfaces        = 2,

            .Class                  = CDC_CSCP_CDCClass,
            .SubClass               = CDC_CSCP_ACMSubclass,
            .Protocol               = CDC_CSCP_ATCommandProtocol,

            .IADStrIndex            = NO_DESCRIPTOR
        },

    .CDC_CCI_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_CDC_CCI,
            .AlternateSetting       = 0,

            .TotalEndpoints         = 1,

            .Class                  = CDC_CSCP_CDCClass,
            .SubClass               = CDC_CSCP_ACMSubclass,
            .Protocol               = CDC_CSCP_ATCommandProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .CDC_Functional_Header =
        {
            .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = DTYPE_CSInterface},
            .Subtype                = CDC_DSUBTYPE_CSInterface_Header,

            .CDCSpecification       = VERSION_BCD(1,1,0),
        },

    .CDC_Functional_ACM =
        {
            .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = DTYPE_CSInterface},
            .Subtype                = CDC_DSUBTYPE_CSInterface_ACM,

            .Capabilities           = 0x06,
        },

    .CDC_Functional_Union =
        {
            .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = DTYPE_CSInterface},
            .Subtype                = CDC_DSUBTYPE_CSInterface_Union,

            .MasterInterfaceNumber  = INTERFACE_ID_CDC_CCI,
            .SlaveInterfaceNumber   = INTERFACE_ID_CDC_DCI,
        },

    .CDC_NotificationEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = CDC_NOTIFICATION_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = CDC_NOTIFICATION_EPSIZE,
            .PollingIntervalMS      = 0xFF
        },

    .CDC_DCI_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_CDC_DCI,
            .AlternateSetting       = 0,

            .TotalEndpoints         = 2,

            .Class                  = CDC_CSCP_CDCDataClass,
            .SubClass               = CDC_CSCP_NoDataSubclass,
            .Protocol               = CDC_CSCP_NoDataProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .CDC_DataOutEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = CDC_RX_EPADDR,
            .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = CDC_TXRX_EPSIZE,
            .PollingIntervalMS      = 0x05
        },

    .CDC_DataInEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = CDC_TX_EPADDR,
            .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = CDC_TXRX_EPSIZE,
            .PollingIntervalMS      = 0x05
        }
#endif
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"Eric Tang");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"Keystrokes");

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
    const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorNumber = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

    switch (DescriptorType)
    {
        case DTYPE_Device:
            Address = &DeviceDescriptor;
            Size    = sizeof(USB_Descriptor_Device_t);
            break;
        case DTYPE_Configuration:
            Address = &ConfigurationDescriptor;
            Size    = sizeof(USB_Descriptor_Configuration_t);
            break;
        case DTYPE_String:
            switch (DescriptorNumber)
            {
                case STRING_ID_Language:
                    Address = &LanguageString;
                    Size    = pgm_read_byte(&LanguageString.Header.Size);
                    break;
                case STRING_ID_Manufacturer:
                    Address = &ManufacturerString;
                    Size    = pgm_read_byte(&ManufacturerString.Header.Size);
                    break;
                case STRING_ID_Product:
                    Address = &ProductString;
                    Size    = pgm_read_byte(&ProductString.Header.Size);
                    break;
            }

            break;
        case HID_DTYPE_HID:
            switch (wIndex)
            {
                case INTERFACE_ID_Keyboard:
                    Address = &ConfigurationDescriptor.HID1_KeyboardHID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = &ConfigurationDescriptor.HID2_MouseHID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);
                    break;
                case INTERFACE_ID_EnhancedKeyboard:
                    Address = &ConfigurationDescriptor.HID3_EnhancedKeyboardHID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);
                    break;
            }

            break;
        case HID_DTYPE_Report:
            switch (wIndex)
            {
                case INTERFACE_ID_Keyboard:
                    Address = &KeyboardReport;
                    Size    = sizeof(KeyboardReport);
                    break;
                case INTERFACE_ID_Mouse:
                    Address = &MouseReport;
                    Size    = sizeof(MouseReport);
                    break;
                case INTERFACE_ID_EnhancedKeyboard:
                    Address = &EnhancedKeyboardReport;
                    Size    = sizeof(EnhancedKeyboardReport);
                    break;
            }

            break;
    }

    *DescriptorAddress = Address;
    return Size;
}
