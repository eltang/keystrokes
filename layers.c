#include "layers.h"

static uint8_t primary_layer, secondary_layer;
static uint8_t using_secondary_layer;

uint8_t layers_get_active_layer(void)
{
    return using_secondary_layer ? secondary_layer : primary_layer;
}

void layers_set_primary_layer(uint8_t layer)
{
    primary_layer = layer;
    using_secondary_layer = 0;
}

void layers_activate_secondary_layer(uint8_t layer)
{
    if (secondary_layer != layer) {
        using_secondary_layer = 0;
        secondary_layer = layer;
    }
    ++using_secondary_layer;
}

void layers_deactivate_secondary_layer(uint8_t layer)
{
    if (secondary_layer == layer && using_secondary_layer)
        --using_secondary_layer;
}
