#pragma once

#include "libtech.h"

class TgaFile;

/* Averaging functions */
LIBTECH_API int avg(int one, int two);
LIBTECH_API float favg(float one, float two);

/** Represent the pixels of a curve into an image.
 *  The image will have the height of 'amplitude*2' and a width of 'curveLength' */
LIBTECH_API TgaFile* PlotSequenceToImage(float* curve, int curveLength);