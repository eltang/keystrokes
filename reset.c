#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "reset.h"
#include <LUFA/Common/Common.h>
#include <LUFA/Drivers/USB/USB.h>

uint32_t Boot_Key ATTR_NO_INIT;

#define MAGIC_BOOT_KEY            0xDC42ACCA
#define FLASH_SIZE_BYTES (FLASHEND + (uint32_t)1)
#define BOOTLOADER_START_ADDRESS  ((FLASH_SIZE_BYTES - BOOTLOADER_SEC_SIZE_BYTES) >> 1)

void Bootloader_Jump_Check(void) ATTR_INIT_SECTION(3);
void Bootloader_Jump_Check(void)
{
    // If the reset source was the bootloader and the key is correct, clear it and jump to the bootloader
    bool watchdog_reset = MCUSR & (1 << WDRF);

    MCUSR = 0;
    wdt_disable();
    if (watchdog_reset && (Boot_Key == MAGIC_BOOT_KEY))
    {
        Boot_Key = 0;
        ((void (*)(void))BOOTLOADER_START_ADDRESS)();
    }
}

void Jump_To_Bootloader(void)
{
    // If USB is used, detach from the bus and reset it
    USB_Disable();

    // Disable all interrupts
    cli();

    // Wait two seconds for the USB detachment to register on the host
    Delay_MS(2000);

    // Set the bootloader key to the magic value and force a reset
    Boot_Key = MAGIC_BOOT_KEY;
    wdt_enable(WDTO_250MS);
    for (;;);
}
