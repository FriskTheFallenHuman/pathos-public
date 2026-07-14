/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef DDS_H
#define DDS_H

#include "constants.h"

#define DDS_MAGIC					0x20534444

#define DDSD_CAPS                   0x00000001
#define DDSD_PIXELFORMAT            0x00001000
#define DDPF_FOURCC                 0x00000004

#define DDS_DATA_OFFSET				128

#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
    ((UInt32)(unsigned char)(ch0) | ((UInt32)(unsigned char)(ch1) << 8) | \
    ((UInt32)(unsigned char)(ch2) << 16) | ((UInt32)(unsigned char)(ch3) << 24))

#define D3DFMT_DXT1 MAKEFOURCC('D','X','T','1')    //  DXT1 compression texture format 
#define D3DFMT_DXT5 MAKEFOURCC('D','X','T','5')    //  DXT5 compression texture format 

struct dds_header_t 
{
	Byte bMagic[4];
	Byte bSize[4];
	Byte bFlags[4];
	Byte bHeight[4];
	Byte bWidth[4];
	Byte bPitchOrLinearSize[4];

	Byte bPad1[52];

	Byte bPFSize[4];
	Byte bPFFlags[4];
	Byte bPFFourCC[4];
};

bool DDS_Load( const char* pstrFilename, const Byte* pfile, Byte*& pdata, UInt32& width, UInt32& height, UInt32& bpp, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn );
#endif // DDS_H