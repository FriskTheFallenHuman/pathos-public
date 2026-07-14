/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

// Code by valina354
// Modified by Overfloater

#ifndef BMP_H
#define BMP_H

#include "includes.h"
#include "file_interface.h"
#include "texturemanager.h"

struct file_interface_t;

extern bool BMP_Load(const char* pstrFilename, const Byte* pfile, Byte*& pdata, UInt32& width, UInt32& height, UInt32& bpp, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn);
extern bool BMP_Load8Bit_Original(const char* pstrFilename, const Byte* pfile, Byte*& ppalette, Byte*& pdata, UInt32& width, UInt32& height, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn);

#endif // BMP_H