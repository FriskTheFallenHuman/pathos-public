/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

// Code by valina354
// Modified by Overfloater

#include "includes.h"
#include "bmp.h"
#include "bmpformat.h"
#include "file_interface.h"
#include "r_common.h"

//=============================================
// @brief Load a BMP file and extract the pure image data
// 
// @param pstrFilename File path
// @param pfile Pointer to file data
// @param pdata Output image data pointer parameter
// @param width Output width parameter
// @param height Output height parameter
// @param size Output size parameter
// @param compression Output compression parameter
// @param pfnPrintFn Pointer to print function to use
// @return true on success, false on failure
//=============================================
bool BMP_Load( const char* pstrFilename, const Byte* pfile, Byte*& pdata, UInt32& width, UInt32& height, UInt32& bpp, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn ) 
{
    const bmp_header_t* ptrBmpHeader = reinterpret_cast<const bmp_header_t*>(pfile);
    if (ptrBmpHeader->magic != BMP_MAGIC_NUMBER)
    {
        pfnPrintFn("%s Magic Header check failed.\n", pstrFilename);
        delete[] pdata;
        return false;
    }

    width = ptrBmpHeader->width;
    height = ptrBmpHeader->height;

    if (!Common::IsPowerOfTwo(width) || !Common::IsPowerOfTwo(height))
    {
        pfnPrintFn("%s is not a power of two texture.\n", pstrFilename);
        delete[] pdata;
        return false;
    }

    UInt32 pxsize = width * height;
    bpp = ptrBmpHeader->bits_per_pixel;
    pdata = new Byte[pxsize * 4]; // Always RGBA

    if (bpp == 24) 
    {
        for (UInt32 i = 0; i < pxsize; i++) 
        {
            const Byte* psrc = pfile + ptrBmpHeader->data_offset + i * 3;
            Byte *pdest = pdata + i * 4;

            pdest[0] = psrc[2];
            pdest[1] = psrc[1];
            pdest[2] = psrc[0];
            pdest[3] = 255;
        }
    }
    else if (bpp == 32) 
    {
        for (UInt32 i = 0; i < size; i++) 
        {
            const Byte* psrc = pfile + ptrBmpHeader->data_offset + i * 4;
            Byte *pdest = pdata + i * 4;

            pdest[0] = psrc[2];
            pdest[1] = psrc[1];
            pdest[2] = psrc[0];
            pdest[3] = psrc[3];
        }
    }
    else
    {
        pfnPrintFn("%s - File '%d' has an unsupported bits per pixel format %u\n", pstrFilename, bpp);
        delete[] pdata;
        return false;
    }

    // Texture needs to be flipped vertically
    Common::FlipTexture(width, height, 4, false, true, pdata);

    return true;
}

//=============================================
// @brief Load a paletted BMP file, while keeping the
// paletted color format.
//
// @param pstrFilename File path
// @param pfile Pointer to file data
// @param ppalette Output color palette data pointer parameter
// @param pdata Output color index data pointer parameter
// @param width Output width parameter
// @param height Output height parameter
// @param size Output size parameter
// @param compression Output compression parameter
// @param pfnPrintFn Pointer to print function to use
// @return true on success, false on failure
//=============================================
bool BMP_Load8Bit_Original(const char* pstrFilename, const Byte* pfile, Byte*& ppalette, Byte*& pdata, UInt32& width, UInt32& height, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn)
{
    const bmp_header_t* ptrBmpHeader = reinterpret_cast<const bmp_header_t*>(pfile);
    if (ptrBmpHeader->magic != BMP_MAGIC_NUMBER)
    {
        pfnPrintFn("%s Magic Header check failed.\n", pstrFilename);
        delete[] pdata;
        return false;
    }

    if(ptrBmpHeader->bits_per_pixel != 8)
    {
        pfnPrintFn("%s - File '%d' has an unsupported bits per pixel format %u, only 8-bit supported.\n", pstrFilename, ptrBmpHeader->bits_per_pixel);
        return false;
    }

    UInt32 nbColorsUsed;
    UInt64 paletteBytesCount;
    if(ptrBmpHeader->colors_used == 0)
    {
        nbColorsUsed = 256;
        paletteBytesCount = (1UL << ptrBmpHeader->bits_per_pixel) * sizeof(color32_t);
    }
    else
    {
        paletteBytesCount = ptrBmpHeader->colors_used * sizeof(color32_t);
        nbColorsUsed = ptrBmpHeader->colors_used;
    }

    // Copy over palette
    const Byte* psrc = pfile + sizeof(bmp_header_t);
    const Byte* psrcpalette = psrc;

    ppalette = new Byte[256*3];
    memset(ppalette, 0, sizeof(Byte)*256*3);

    for(UInt32 i = 0; i < nbColorsUsed; i++)
    {
        ppalette[i*3] = psrcpalette[i*4];
        ppalette[i*3+1] = psrcpalette[i*4+1];
        ppalette[i*3+2] = psrcpalette[i*4+2];
    }

    // Now load the actual pixel bytes
    const Byte* psrcpixels = psrc + paletteBytesCount;

    width = ptrBmpHeader->width;
    height = ptrBmpHeader->height;

    UInt32 fileOffset = psrcpixels - pfile;
    UInt32 pixelCount = ptrBmpHeader->file_size - fileOffset;

    // Data is actually stored rounded up to multiples of 4
    UInt32 trueWidth = (width % 4) != 0 ? ((width / 4) * 4 + 4) : width;

    pdata = new Byte[pixelCount];
    memcpy(pdata, psrcpixels, sizeof(Byte)*pixelCount);

    return true;
}