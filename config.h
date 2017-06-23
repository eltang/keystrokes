// #define USE_TWI
// #define BACKWARDS_DIODES
#define ROWS 10
#define COLUMNS 8
#define MAX_TAP_DURATION 250
#define ROW_PINS { PIN(B, 2), PIN(C, 7), PIN(C, 6), PIN(B, 6), PIN(B, 5), PIN(B, 0), PIN(B, 3), PIN(D, 5), PIN(D, 3), PIN(D, 2) }
#define COLUMN_PINS { PIN(F, 0), PIN(F, 1), PIN(F, 4), PIN(F, 5), PIN(F, 6), PIN(F, 7), PIN(E, 6), PIN(B, 1) }
#define BOOTLOADER_SEC_SIZE_BYTES 4096
#define LED_CONFIG { { PIN(B, 4), SHOW_CAPS_LOCK_STATE } }
// #define USE_VIRTUAL_SERIAL
