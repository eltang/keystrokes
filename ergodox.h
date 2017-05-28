#ifndef ERGODOX_H
#define ERGODOX_H

#if 0
inline void ergodox_board_led_on(void)      { DDRD |=  (1<<6); PORTD |=  (1<<6); }
inline void ergodox_right_led_1_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void ergodox_right_led_2_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void ergodox_right_led_3_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }
inline void ergodox_left_led_1_on(void)     { ergodox_left_led_1 = 1; }
inline void ergodox_left_led_2_on(void)     { ergodox_left_led_2 = 1; }
inline void ergodox_left_led_3_on(void)     { ergodox_left_led_3 = 1; }

inline void ergodox_board_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }
inline void ergodox_right_led_1_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void ergodox_right_led_2_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void ergodox_right_led_3_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }
inline void ergodox_left_led_1_off(void)    { ergodox_left_led_1 = 0; }
inline void ergodox_left_led_2_off(void)    { ergodox_left_led_2 = 0; }
inline void ergodox_left_led_3_off(void)    { ergodox_left_led_3 = 0; }
#endif

#define LAYER( \
k00, k01, k02, k03, k04, k05, k06, \
k10, k11, k12, k13, k14, k15, k16, \
k20, k21, k22, k23, k24, k25, \
k30, k31, k32, k33, k34, k35, k36, \
k40, k41, k42, k43, k44, \
                         k55, k56, \
                              k54, \
                    k53, k52, k51, \
k07, k08, k09, k0A, k0B, k0C, k0D, \
k17, k18, k19, k1A, k1B, k1C, k1D, \
     k28, k29, k2A, k2B, k2C, k2D, \
k37, k38, k39, k3A, k3B, k3C, k3D, \
          k49, k4A, k4B, k4C, k4D, \
k57, k58, \
k59, \
k5C, k5B, k5A \
) \
{ \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
    k20, k21, k22, k23, k24, k25, NO_ACTION, NO_ACTION, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, \
    k40, k41, k42, k43, k44, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, k49, k4A, k4B, k4C, k4D, \
    NO_ACTION, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, NO_ACTION \
}

#endif
