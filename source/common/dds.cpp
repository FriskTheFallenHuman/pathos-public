/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "texturemanager.h"
#include "dds.h"

//=============================================
// @brief Loads a DDS file and returns it's data
//
// @param pfile Pointer to raw file data
// @param pdata Destination pointer for image data
// @param width Reference to texture width variable
// @param height Reference to texture height variable
// @param bpp Reference to texture bit depth variable
// @param size Reference to data size variable
// @param compression Reference to texture compression variable
// @return true if successfully loaded, false otherwise
//=============================================
bool DDS_Load( const char* pstrFilename, const Byte* pfile, Byte*& pdata, UInt32& width, UInt32& height, UInt32& bpp, UInt32& size, texture_compression_t& compression, pfnPrintf_t pfnPrintFn )
{
	const dds_header_t *pDDSHeader = reinterpret_cast<const dds_header_t*>(pfile);

	// Read information
	const UInt32 ddsFlags = Common::ByteToUint32(pDDSHeader->bFlags);
	const UInt32 ddsMagic = Common::ByteToUint32(pDDSHeader->bMagic);
	const UInt32 ddsFourCC = Common::ByteToUint32(pDDSHeader->bPFFourCC);
	const UInt32 ddsPFFlags = Common::ByteToUint32(pDDSHeader->bPFFlags);
	const UInt32 ddsLinSize = Common::ByteToUint32(pDDSHeader->bPitchOrLinearSize);
	const UInt32 ddsSize = Common::ByteToUint32(pDDSHeader->bSize);

	const UInt32 ddsWidth = Common::ByteToUint32(pDDSHeader->bWidth);
	const UInt32 ddsHeight = Common::ByteToUint32(pDDSHeader->bHeight);

	if(ddsMagic != DDS_MAGIC || ddsSize != 124 || !(ddsFlags & DDSD_PIXELFORMAT)
		|| !(ddsFlags & DDSD_CAPS) || !(ddsPFFlags & DDPF_FOURCC))
	{
		pfnPrintFn("Incorrect DDS format on %s.\n", pstrFilename);
		return false;
	}

	if(ddsFourCC == static_cast<UInt32>(D3DFMT_DXT1))
	{
		compression = TX_COMPRESSION_DXT1;
	}
	else if(ddsFourCC == static_cast<UInt32>(D3DFMT_DXT5))
	{
		compression = TX_COMPRESSION_DXT5;
	}
	else
	{
		pfnPrintFn("Incorrect compression on: %s. Only DXT1 and DXT5 DDS files are supported.\n", pstrFilename);
		return false;
	}

	// Set output data
	width = ddsWidth;
	height = ddsHeight;
	size = ddsLinSize;
	bpp = 4;

	// Copy data
	pdata = new Byte[ddsLinSize];
	memcpy(pdata, (pfile + DDS_DATA_OFFSET), ddsLinSize);

	return true;
}