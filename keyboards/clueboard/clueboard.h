#ifndef CLUEBOARD_H
#define CLUEBOARD_H

#define LAYER( \
k00, k01, k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54, k55, k56, k57, \
k10, k11, k12, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65,      k67, \
k20, k21, k22, k23, k24, k25, k26, k27, k70, k71, k72, k73, k74, k75, \
k30, k31, k32, k33, k34, k35, k36, k37, k80, k81, k82, k83, k84, k85, k86, \
k40, k41, k42, k43,      k45, k46,      k90,      k92, k93, k94, k95, k96, k97 \
) \
{ \
    k00, k01, k02, k03, k04, k05, k06, k07, \
    k10, k11, k12, k13, k14, k15, k16, k17, \
    k20, k21, k22, k23, k24, k25, k26, k27, \
    k30, k31, k32, k33, k34, k35, k36, k37, \
    k40, k41, k42, k43, NO_ACTION, k45, k46, NO_ACTION, \
    k50, k51, k52, k53, k54, k55, k56, k57, \
    k60, k61, k62, k63, k64, k65, NO_ACTION, k67, \
    k70, k71, k72, k73, k74, k75, NO_ACTION, NO_ACTION, \
    k80, k81, k82, k83, k84, k85, k86, NO_ACTION, \
    k90, NO_ACTION, k92, k93, k94, k95, k96, k97  \
}

#endif
