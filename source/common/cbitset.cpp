/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "cbitset.h"

//=============================================
// @brief
//
//=============================================
CBitSet::CBitSet():
	m_pDataArray(nullptr),
	m_numBits(0),
	m_numBytes(0)
{
}

//=============================================
// @brief
//
//=============================================
CBitSet::CBitSet( UInt32 size ):
	m_pDataArray(nullptr),
	m_numBits(size),
	m_numBytes(0)
{
	resize(size);
}

//=============================================
// @brief
//
//=============================================
CBitSet::CBitSet( const CBitSet& src ):
	m_pDataArray(nullptr),
	m_numBits(src.m_numBits),
	m_numBytes(src.m_numBytes)
{
	m_numBytes = src.m_numBytes;
	m_numBits = src.m_numBits;

	m_pDataArray = new Byte[m_numBytes];
	memcpy(m_pDataArray, src.m_pDataArray, sizeof(Byte)*m_numBytes);
}

//=============================================
// @brief
//
//=============================================
CBitSet::CBitSet( const Byte* pdataarray, UInt32 numbits ):
	m_pDataArray(nullptr),
	m_numBits(0),
	m_numBytes(0)
{
	UInt32 wholeBytesNumber = (numbits / NB_BITS_IN_BYTE);
	UInt32 fullByteCount = SDL_ceil(static_cast<float>(numbits) / static_cast<float>(NB_BITS_IN_BYTE));

	m_pDataArray = new Byte[fullByteCount];
	m_numBits = numbits;
	m_numBytes = fullByteCount;

	for(UInt32 i = 0; i < wholeBytesNumber; i++)
		m_pDataArray[i] = pdataarray[i];

	UInt32 i = wholeBytesNumber * NB_BITS_IN_BYTE;
	for(; i < numbits; i++)
	{
		if(pdataarray[i/NB_BITS_IN_BYTE] & (1U<<(i%NB_BITS_IN_BYTE)))
			set(i);
	}
}

//=============================================
// @brief
//
//=============================================
CBitSet::CBitSet( UInt32 bitsetSize, const UInt32 inputBits[], UInt32 arraySize ):
	m_pDataArray(nullptr),
	m_numBits(0),
	m_numBytes(0)
{
	resize(bitsetSize);
	for(UInt32 i = 0; i < arraySize; i++)
		set(inputBits[i]);
}

//=============================================
// @brief
//
//=============================================
CBitSet::~CBitSet()
{
	if(m_pDataArray)
		delete[] m_pDataArray;
}
