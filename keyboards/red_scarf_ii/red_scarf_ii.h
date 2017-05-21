#define LAYER( \
    k5B, k5C, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, k0K, k0L, k0M, k0N, k0P, k0Q, k0R, k0S, \
    k5D, k5E, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1J, k1K, k1L, k1M, k1N, k1P, k1Q, k1R, k1S, \
    k5F, k5G, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2J, k2K, k2L, k2M, k2N, k2P, k2Q, k2R, k2S, \
    k5H, k5I, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3J, k3K, k3L, k3M, k3N, k3P, k3Q, k3R, k3S, \
    k5J, k5K, k4A, k4B, k4C,           k4J,                k4K, k4L, k4H, k4M, k4N, k4P, k4Q, k4R, k4S \
) \
{ \
    k0A,       k0B, k0C, k0D,       k0E,       k0F,       k0G,       k0H, k0I,       k0J, k0K, k0L, k0M, k0N, k0P, k0Q, k0R, k0S, \
    k1A,       k1B, k1C, k1D,       k1E,       k1F,       k1G,       k1H, k1I,       k1J, k1K, k1L, k1M, k1N, k1P, k1Q, k1R, k1S, \
    k2A,       k2B, k2C, k2D,       k2E,       k2F,       k2G,       k2H, k2I,       k2J, k2K, k2L, k2M, k2N, k2P, k2Q, k2R, k2S, \
    k3A,       k3B, k3C, k3D,       k3E,       k3F,       k3G,       k3H, k3I,       k3J, k3K, k3L, k3M, k3N, k3P, k3Q, k3R, k3S, \
    k4A,       k4B, k4C, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, k4H, NO_ACTION, k4J, k4K, k4L, k4M, k4N, k4P, k4Q, k4R, k4S, \
    NO_ACTION, k5B, k5C, k5D,       k5E,       k5F,       k5G,       k5H, k5I,       k5J, k5K \
}
