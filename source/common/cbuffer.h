/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CBUFFER_H
#define CBUFFER_H

/*
=======================
CBuffer

=======================
*/
class CBuffer
{
public:
	CBuffer( void );
	explicit CBuffer( Uint32 allocsize );
	CBuffer( const void* pdata, Uint32 datasize );
	CBuffer( Uint32 allocsize, const void* pdata, Uint32 datasize );
	~CBuffer( void );

public:
	// Appends data to the buffer
	DO_INLINE bool append( const void* pdata, Uint32 datasize );
	// Returns the buffer pointer
	DO_INLINE void*& getbufferdata( void );
	// Retreives the writing offset into the buffer data
	DO_INLINE Uint32 getdatasize( void ) const;
	// Retreives the buffer array size
	DO_INLINE Uint32 getbuffersize( void ) const;
	// Resets the writing position to zero
	DO_INLINE void reset( void );

	// Adds a pointer to the list
	DO_INLINE void addpointer( void** ptr );
	// Removes a pointer from the list
	DO_INLINE void removepointer( void** ptr );
	// Removes a pointer from the list
	DO_INLINE void removepointer( const void** ptr );

private:
	// initializes the buffer
	DO_INLINE void initbuffer( void );

public:
	// Pointer to buffer
	void* m_pBufferData;
	// Size of buffer
	Uint32 m_bufferSize;
	// Buffer usage
	Uint32 m_bufferDataPosition;
	// Buffer allocation unit size
	Uint32 m_bufferAllocSize;

	// List of pointers
	CArray<void**> m_pointersArray;
};
#include "cbuffer_inline.hpp"
#endif