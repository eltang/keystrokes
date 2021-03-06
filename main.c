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
 *  Main source file for Keystrokes. This file contains the main tasks of the
 *  application and is responsible for the initial application hardware configuration.
 */

#include "main.h"
#include "keys.h"
#include "modifiers.h"
#include "matrix.h"
#include "twi.h"
#include "timer.h"
#include "keystrokes.h"
#include "power.h"
#include "leds.h"
#include "avr/sleep.h"

bool HostReady;

#ifdef USE_VIRTUAL_SERIAL
/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
    {
        .Config =
            {
                .ControlInterfaceNumber         = INTERFACE_ID_CDC_CCI,
                .DataINEndpoint                 =
                    {
                        .Address                = CDC_TX_EPADDR,
                        .Size                   = CDC_TXRX_EPSIZE,
                        .Banks                  = 1,
                    },
                .DataOUTEndpoint                =
                    {
                        .Address                = CDC_RX_EPADDR,
                        .Size                   = CDC_TXRX_EPSIZE,
                        .Banks                  = 1,
                    },
                .NotificationEndpoint           =
                    {
                        .Address                = CDC_NOTIFICATION_EPADDR,
                        .Size                   = CDC_NOTIFICATION_EPSIZE,
                        .Banks                  = 1,
                    },
            },
    };
#endif

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** Buffer to hold the previously generated Mouse HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

static uint8_t PrevEnhancedKeyboardHIDReportBuffer[sizeof(USB_EnhancedKeyboardReport_Data_t)];

static uint8_t KeyboardReportCounter, MouseReportCounter, EnhancedKeyboardReportCounter;

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another. This is for the keyboard HID
 *  interface within the device.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
    {
        .Config =
            {
                .InterfaceNumber              = INTERFACE_ID_Keyboard,
                .ReportINEndpoint             =
                    {
                        .Address              = KEYBOARD_EPADDR,
                        .Size                 = HID_EPSIZE,
                        .Banks                = 1,
                    },
                .PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
                .PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
            },
    };

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another. This is for the mouse HID
 *  interface within the device.
 */
USB_ClassInfo_HID_Device_t Mouse_HID_Interface =
    {
        .Config =
            {
                .InterfaceNumber              = INTERFACE_ID_Mouse,
                .ReportINEndpoint             =
                    {
                        .Address              = MOUSE_EPADDR,
                        .Size                 = HID_EPSIZE,
                        .Banks                = 1,
                    },
                .PrevReportINBuffer           = PrevMouseHIDReportBuffer,
                .PrevReportINBufferSize       = sizeof(PrevMouseHIDReportBuffer),
            },
    };

USB_ClassInfo_HID_Device_t EnhancedKeyboard_HID_Interface =
    {
        .Config =
            {
                .InterfaceNumber              = INTERFACE_ID_EnhancedKeyboard,
                .ReportINEndpoint             =
                    {
                        .Address              = ENHANCEDKEYBOARD_EPADDR,
                        .Size                 = HID_EPSIZE,
                        .Banks                = 1,
                    },
                .PrevReportINBuffer           = PrevEnhancedKeyboardHIDReportBuffer,
                .PrevReportINBufferSize       = sizeof(PrevEnhancedKeyboardHIDReportBuffer),
            },
    };

#ifdef USE_VIRTUAL_SERIAL
/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
FILE USBSerialStream;
#endif

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    GlobalInterruptEnable();

    SetupHardware();

    USB_Device_EnableSOFEvents();

#ifdef USE_VIRTUAL_SERIAL
    /* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
#endif

    for (;;)
    {
        if (USB_DeviceState == DEVICE_STATE_Suspended) {
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            cli();
            sleep_enable();
            sei();
            sleep_cpu();
            sleep_disable();
            if (matrix_scan() && USB_Device_RemoteWakeupEnabled) {
                USB_Device_SendRemoteWakeup();
                while (USB_DeviceState == DEVICE_STATE_Suspended);
            }
            continue;
        }
#ifdef USE_VIRTUAL_SERIAL
        /* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
        CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
        CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
#endif

        HID_Device_USBTask(&Keyboard_HID_Interface);
        HID_Device_USBTask(&Mouse_HID_Interface);
        HID_Device_USBTask(&EnhancedKeyboard_HID_Interface);

        keystrokes_task();
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
#ifdef USE_TWI
    static const I2CConfig i2cconfig = { 400000 };
#endif
#if (ARCH == ARCH_AVR8)
    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    MCUCR |= 1 << JTD;
    MCUCR |= 1 << JTD;
#elif (ARCH == ARCH_XMEGA)
    /* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
    XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
    XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

    /* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
    XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
    XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

    PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif
    /* Hardware Initialization */
    USB_Init();
    power_init();
    leds_init();
#ifdef USE_TWI
    i2cStart(&i2cconfig);
#endif
    matrix_init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);
    ConfigSuccess &= HID_Device_ConfigureEndpoints(&EnhancedKeyboard_HID_Interface);
#ifdef USE_VIRTUAL_SERIAL
    ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
#endif
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
#ifdef USE_VIRTUAL_SERIAL
    CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
#endif
    HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
    HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
    HID_Device_ProcessControlRequest(&EnhancedKeyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
    HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
    HID_Device_MillisecondElapsed(&EnhancedKeyboard_HID_Interface);
    timer_increment();
}

void EVENT_USB_Device_Suspend(void)
{
    WDTCSR |= 1 << WDCE | 1 << WDE;
    WDTCSR = 1 << WDIE;
}

ISR(WDT_vect)
{
}

void EVENT_USB_Device_WakeUp(void)
{
    wdt_disable();
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{

    /* Determine which interface must have its report generated */
    if (HIDInterfaceInfo == &Keyboard_HID_Interface)
    {
        USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

        KeyboardReport->Modifier = modifiers_get_disguised_modifiers();
        memcpy(KeyboardReport->KeyCode, keys_get_scancode(), 6);

        *ReportSize = sizeof(USB_KeyboardReport_Data_t);
        ++KeyboardReportCounter;
    }
    else if (HIDInterfaceInfo == &Mouse_HID_Interface)
    {
        USB_MouseReport_Data_t* MouseReport = (USB_MouseReport_Data_t*)ReportData;


        *ReportSize = sizeof(USB_MouseReport_Data_t);
        ++MouseReportCounter;
    }
    else
    {
        USB_EnhancedKeyboardReport_Data_t* EnhancedKeyboardReport = (USB_EnhancedKeyboardReport_Data_t*)ReportData;

        EnhancedKeyboardReport->ConsumerControlCode = keys_get_multimedia();
        EnhancedKeyboardReport->SystemControlCode = keys_get_power_management();

        *ReportSize = sizeof(USB_EnhancedKeyboardReport_Data_t);
        ++EnhancedKeyboardReportCounter;
    }
    return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    static uint8_t PrevLEDReport;
    uint8_t LEDReport;

    if (HIDInterfaceInfo == &Keyboard_HID_Interface)
    {
        LEDReport = *(uint8_t*)ReportData;
        if (LEDReport == PrevLEDReport)
            return;
        leds_process_led_report_change(PrevLEDReport = LEDReport);
    }
}

/** CDC class driver callback function the processing of changes to the virtual
 *  control lines sent from the host..
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
    /* You can get changes to the virtual CDC lines in this callback; a common
       use-case is to use the Data Terminal Ready (DTR) flag to enable and
       disable CDC communications in your application when set to avoid the
       application blocking while waiting for a host to become ready and read
       in the pending data from the USB endpoints.
    */
    HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;
}

void SendKeyboardReport(void)
{
    uint8_t Temp = KeyboardReportCounter;

    while (1) {
        HID_Device_USBTask(&Keyboard_HID_Interface);
        if (Temp != KeyboardReportCounter)
            break;
        set_sleep_mode(SLEEP_MODE_IDLE);
        cli();
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
    }
}

void SendMouseReport(void)
{
    uint8_t Temp = MouseReportCounter;

    while (1) {
        HID_Device_USBTask(&Mouse_HID_Interface);
        if (Temp != MouseReportCounter)
            break;
        set_sleep_mode(SLEEP_MODE_IDLE);
        cli();
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
    }
}

void SendEnhancedKeyboardReport(void)
{
    uint8_t Temp = EnhancedKeyboardReportCounter;

    while (1) {
        HID_Device_USBTask(&EnhancedKeyboard_HID_Interface);
        if (Temp != EnhancedKeyboardReportCounter)
            break;
        set_sleep_mode(SLEEP_MODE_IDLE);
        cli();
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
    }
}
