#ifndef LAYERS_H
#define LAYERS_H

#include <stdint.h>
#include <string.h>

#include "matrix.h"
#include "actions.h"

uint8_t layers_get_source_layer(uint8_t keyswitch, bool new_keystroke);
uint8_t layers_get_active_layer(void);
void layers_set_primary_layer(uint8_t layer);
void layers_activate_secondary_layer(uint8_t layer);
void layers_deactivate_secondary_layer(uint8_t layer);

#endif
