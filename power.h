#ifndef POWER_H
#define POWER_H

void power_init(void);

#ifdef USE_TWI
#define PRTWI_VALUE 0
#else
#define PRTWI_VALUE (1 << PRTWI)
#endif
#ifdef USE_BACKLIGHT
#define PRTIM1_VALUE 0
#else
#define PRTIM1_VALUE (1 << PRTIM1)
#endif
#define PRSPI_VALUE (1 << PRSPI)
#define PRADC_VALUE (1 << PRADC)
#define PRTIM4_VALUE (1 << 4)
#define PRTIM3_VALUE (1 << PRTIM3)
#define PRUSART1_VALUE (1 << PRUSART1)

#define PRR0_VALUE (PRTWI_VALUE | PRTIM1_VALUE | PRSPI_VALUE | PRADC_VALUE)
#define PRR1_VALUE (PRTIM4_VALUE | PRTIM3_VALUE | PRUSART1_VALUE)

#endif
