/*
 * (c) 2015 flabberast <s3+flabbergast@sdfeu.org>
 *
 * Based on the following work:
 *  - Guillaume Duc's raw hid example (MIT License)
 *    https://github.com/guiduc/usb-hid-chibios-example
 *  - PJRC Teensy examples (MIT License)
 *    https://www.pjrc.com/teensy/usb_keyboard.html
 *  - hasu's TMK keyboard code (GPL v2 and some code Modified BSD)
 *    https://github.com/tmk/tmk_keyboard/
 *  - ChibiOS demo code (Apache 2.0 License)
 *    http://www.chibios.org
 *
 * Since some GPL'd code is used, this work is licensed under
 * GPL v2 or later.
 */

#include "ch.h"
#include "hal.h"

#include "usb_main.h"

__attribute__((weak))
void hook_usb_suspend_loop(void) {
  /* Do this in the suspended state */
  suspend_power_down(); // on AVR this deep sleeps for 15ms
  /* Remote wakeup */
  if((USB_DRIVER.status & 2) && suspend_wakeup_condition()) {
    send_remote_wakeup(&USB_DRIVER);
  }
}

/* Main thread
 */
int main(void) {
  /* ChibiOS/RT init */
  halInit();
  chSysInit();

  /* Init USB */
  init_usb_driver(&USB_DRIVER);

  /* Wait until the USB is active */
  while(USB_DRIVER.state != USB_ACTIVE)
    chThdSleepMilliseconds(50);

  /* init TMK modules */
  keyboard_init();
  host_set_driver(&chibios_driver);

  hook_late_init();

  /* Main loop */
  while(true) {

    if(USB_DRIVER.state == USB_SUSPENDED) {
      while(USB_DRIVER.state == USB_SUSPENDED) {
        hook_usb_suspend_loop();
      }
      /* Woken up */
      // variables have been already cleared
      send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
      mousekey_send();
#endif /* MOUSEKEY_ENABLE */
    }

    keyboard_task();
  }
}
