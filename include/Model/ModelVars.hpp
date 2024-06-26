#pragma once

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256
#define RENDER_DISTANCE 10
#define CONTINENTAL_SCALE 15.f
#define TEMPERATURE_SCALE 8.f
#define EROSION_SCALE 10.f
#define PEAKS_VALLEYS_SCALE 5.f
#define CAVE_SCALE_Z 5.f
#define CAVE_SCALE 3.5f

#define BASE_LEVEL 40
#define SEA_LEVEL 87

typedef struct s_offsets
{
    int continental;
    int erosion;
    int peaks_and_valleys;
    int temperature;
    int cave;
} t_offsets;