/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

#ifndef TGA_H
#define TGA_H

#include "texturemanager.h"
#include "tgaformat.h"
#include "constants.h"

#define TGA_FLIP_HORIZONTAL	8
#define TGA_FLIP_VERTICAL	16

struct file_interface_t;

extern bool TGA_Load( const char* pstrFilename, const Byte* pfile, Byte*& pdata, UInt32& width, UInt32& height, UInt32& bpp, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn );
extern bool TGA_Write( const Byte* pdata, UInt32 bpp, UInt32 width, UInt32 height, const char* pstrFilename, const file_interface_t& fileFuncs, pfnPrintf_t pfnPrintFn, UInt32* ptrCompressionRatio = nullptr, UInt32* ptrBytesWritten = nullptr, bool flipVertical = false );
extern void TGA_BuildFile( const Byte* pdata, UInt32 bpp, UInt32 width, UInt32 height, CBuffer& fileBuffer, UInt32* ptrCompressionRatio, bool flipVertical );
extern void TGA_BuildImageData( const Byte* pdata, UInt32 bpp, UInt32 width, UInt32 height, CBuffer& fileBuffer, tga_header_t*& pheader, UInt32& compressionPercentage, bool flipVertical );
#endif // TGA_H