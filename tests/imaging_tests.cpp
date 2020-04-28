#include <libtech/imaging.h>

#include "gtest/gtest.h"

// Buffer len of 16
#define BLEN 16

// Buffer than we will transform.
const uint8_t test_buffer[BLEN] =
{
    0x00, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB,
    0xCC, 0xDD, 0xEE, 0xFF
};

TEST(ImagingTests, ARGBTORGBA)
{
    rgba_pix out[BLEN];

    /**
     * When converting, the `out` parameter will be queried in terms of *pix
     * values. Those structures store the same color data in different orders.
     *
     * The first test is to make sure that color data is not changed.
     * The second test is to ensure that the bytes are actually changing to the
     * correct order.
     *
     * TODO : Currently not testing all pixels of the structure.
     */

    convert_argb_rgba((argb_pix*)test_buffer, 4, out);

    EXPECT_EQ(out[0].a, 0x00);
    EXPECT_EQ(out[0].r, 0x11);
    EXPECT_EQ(out[0].g, 0x22);
    EXPECT_EQ(out[0].b, 0x33);

    uint8_t* out_raw = (uint8_t*)out;
    EXPECT_EQ(out_raw[0], 0x11);
    EXPECT_EQ(out_raw[1], 0x22);
    EXPECT_EQ(out_raw[2], 0x33);
    EXPECT_EQ(out_raw[3], 0x00);
}
