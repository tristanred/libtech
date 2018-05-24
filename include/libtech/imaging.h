#pragma once

#include <cstdint>
#include "libtech.h"

enum PixType
{
    RGBA,
    ARGB,
    BGRA
};

struct rgba_pix
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct argb_pix
{
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct bgra_pix // Usually found in TGA files.
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

struct pixquad
{
    enum PixType type;

    union
    {
        rgba_pix* rgba;
        argb_pix* argb;
        bgra_pix* bgra;
    };

    size_t size;
};

LIBTECH_API void convert_argb_rgba(argb_pix* buf, size_t pixel_count, rgba_pix* out);
LIBTECH_API void convert_rgba_argb(rgba_pix* buf, size_t pixel_count, argb_pix* out);

LIBTECH_API void convert_bgra_rgba(bgra_pix* buf, size_t pixel_count, rgba_pix* out);
LIBTECH_API void convert_rgba_bgra(rgba_pix* buf, size_t pixel_count, bgra_pix* out);
