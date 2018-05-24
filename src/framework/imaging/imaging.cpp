#include <libtech/imaging.h>

void convert_argb_rgba(argb_pix * buf, size_t pixel_count, rgba_pix* out)
{
    for (size_t i = 0; i < pixel_count; i++)
    {
        out[i].a = buf[i].a;
        out[i].r = buf[i].r;
        out[i].g = buf[i].g;
        out[i].b = buf[i].b;
    }
}

void convert_rgba_argb(rgba_pix* buf, size_t pixel_count, argb_pix* out)
{
    for (size_t i = 0; i < pixel_count; i++)
    {
        out[i].r = buf[i].r;
        out[i].g = buf[i].g;
        out[i].b = buf[i].b;
        out[i].a = buf[i].a;
    }
}

void convert_bgra_rgba(bgra_pix* buf, size_t pixel_count, rgba_pix* out)
{
    for (size_t i = 0; i < pixel_count; i++)
    {
        out[i].b = buf[i].b;
        out[i].g = buf[i].g;
        out[i].r = buf[i].r;
        out[i].a = buf[i].a;
    }
}

void convert_rgba_bgra(rgba_pix* buf, size_t pixel_count, bgra_pix* out)
{
    for (size_t i = 0; i < pixel_count; i++)
    {
        out[i].r = buf[i].r;
        out[i].g = buf[i].g;
        out[i].b = buf[i].b;
        out[i].a = buf[i].a;
    }
}