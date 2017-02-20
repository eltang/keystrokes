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
 *  Main source file for the KeyboardMouse demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "main.h"
#include "keys.h"
#include "modifiers.h"
#include "matrix.h"
#include "i2cmaster/i2cmaster.h"
#include "actions.h"
#include "layout.h"
#include "power.h"
#include "timer.h"
#include "layers.h"
#include "keystrokes.h"

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** Buffer to hold the previously generated Mouse HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevMouseHIDReportBuffer[sizeof(USB_MouseReport_Data_t)];

static uint8_t PrevExtendedKeyboardHIDReportBuffer[MAX(sizeof(USB_GenericDesktopReport_Data_t), sizeof(USB_ConsumerReport_Data_t))];

static uint8_t KeyboardReportCounter, MouseReportCounter, ExtendedKeyboardReportCounter;

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
						.Address              = KEYBOARD_IN_EPADDR,
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
						.Address              = MOUSE_IN_EPADDR,
						.Size                 = HID_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevMouseHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevMouseHIDReportBuffer),
			},
	};

USB_ClassInfo_HID_Device_t ExtendedKeyboard_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_ExtendedKeyboard,
				.ReportINEndpoint             =
					{
						.Address              = EXTENDEDKEYBOARD_IN_EPADDR,
						.Size                 = HID_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevExtendedKeyboardHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevExtendedKeyboardHIDReportBuffer),
			},
	};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	GlobalInterruptEnable();

	for (;;)
	{
        keystrokes_process(matrix_scan());
        keystrokes_task();
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

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
    timer_init();
#ifdef USING_TWI
    i2c_init();
#endif
    matrix_init();
	USB_Init();
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
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&ExtendedKeyboard_HID_Interface);

	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
	HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
	HID_Device_ProcessControlRequest(&ExtendedKeyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
	HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
	HID_Device_MillisecondElapsed(&ExtendedKeyboard_HID_Interface);
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

        KeyboardReport->Modifier = modifiers_get();
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
        switch (*ReportID = keys_get_extended_keyboard_report_id())
        {
            case HID_REPORTID_GenericDesktopReport:
                ((USB_GenericDesktopReport_Data_t*)ReportData)->Usage = keys_get_generic_desktop();
                *ReportSize = sizeof(USB_GenericDesktopReport_Data_t);
                break;
            case HID_REPORTID_ConsumerReport:
                ((USB_ConsumerReport_Data_t*)ReportData)->Usage = keys_get_consumer();
                *ReportSize = sizeof(USB_ConsumerReport_Data_t);
                break;
        }
        ++ExtendedKeyboardReportCounter;
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
	if (HIDInterfaceInfo == &Keyboard_HID_Interface)
	{
		uint8_t* LEDReport = (uint8_t*)ReportData;
	}
}

void SendKeyboardReport(void)
{
    uint8_t Temp = KeyboardReportCounter;

    do
        HID_Device_USBTask(&Keyboard_HID_Interface);
    while (Temp == KeyboardReportCounter);
}

void SendMouseReport(void)
{
    uint8_t Temp = MouseReportCounter;

    do
        HID_Device_USBTask(&Mouse_HID_Interface);
    while (Temp == MouseReportCounter);
}

void SendExtendedKeyboardReport(void)
{
    uint8_t Temp = ExtendedKeyboardReportCounter;

    do
        HID_Device_USBTask(&ExtendedKeyboard_HID_Interface);
    while (Temp == ExtendedKeyboardReportCounter);
}