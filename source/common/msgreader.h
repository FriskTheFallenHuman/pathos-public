/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef MSGREADER_H
#define MSGREADER_H

/*
====================
CMSGReader

====================
*/
class CMSGReader
{
public:
	CMSGReader():
		m_pMessageData(nullptr),
		m_messageSize(0),
		m_readOffset(0)
	{
	}
	CMSGReader( const Byte* pdata, Uint32 msgsize ):
		m_pMessageData(nullptr),
		m_messageSize(0),
		m_readOffset(0)
	{
		BeginRead(pdata, msgsize);
	}
	~CMSGReader()
	{
	}

public:
	// Begins reading a message
	DO_INLINE void BeginRead( const Byte* pdata, Uint32 msgsize );
	// Returns the error code if any
	DO_INLINE const char* GetError( void ) const;
	// Returns if we have an error
	DO_INLINE bool HasError( void );

public:
	// Reads a single byte
	DO_INLINE Byte ReadByte( void );
	// Reads a single char
	DO_INLINE char ReadChar( void );
	// Reats an short
	DO_INLINE Int16 ReadInt16( void );
	// Reads a unsigned short
	DO_INLINE Uint16 ReadUint16( void );
	// Reads a 32-bit integer
	DO_INLINE Int32 ReadInt32( void );
	// Reads a 32-bit unsigned integer
	DO_INLINE Uint32 ReadUint32( void );
	// Reads a 64-bit integer
	DO_INLINE Int64 ReadInt64( void );
	// Reads a 64-bit unsigned integer
	DO_INLINE Uint64 ReadUint64( void );
	// Reads a 2-byte small float
	DO_INLINE float ReadSmallFloat( void );
	// Reads a float
	DO_INLINE float ReadFloat( void );
	// Reads a double
	DO_INLINE double ReadDouble( void );
	// Reads a string
	DO_INLINE const char* ReadString( void );
	// Reads a buffer
	DO_INLINE const Byte* ReadBuffer( Uint32 size );
	// Reads a bitset
	DO_INLINE CBitSet ReadBitSet( void );

private:
	// Message data pointer
	const Byte* m_pMessageData;
	// Message size
	Uint32 m_messageSize;
	// Message read offset
	Uint32 m_readOffset;

	// Error string
	CString m_errorString;
};
#include "msgreader_inline.hpp"
#endif //MSGREADER_H