// #define USING_TWI

// #define BACKWARDS_DIODES
// #define ROWS 6
// #define COLUMNS 14
#define ROWS 4
#define COLUMNS 12

#define MAX_TAP_DURATION 250


#define ROW_PINS { PIN(D, 0), PIN(D, 5), PIN(B, 5), PIN(B, 6) }
#define COLUMN_PINS { PIN(F, 1), PIN(F, 0), PIN(B, 0), PIN(C, 7), PIN(F, 4), PIN(F, 5), PIN(F, 6), PIN(F, 7), PIN(D, 4), PIN(D, 6), PIN(B, 4), PIN(D, 7)  }
#define UNUSED_PINS { }
#define BOOTLOADER_SEC_SIZE_BYTES 4096
// #define BOOTLOADER_SEC_SIZE_BYTES 512

#define VIRTUAL_SERIAL_ENABLE
