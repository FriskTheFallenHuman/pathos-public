/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CBITSET_H
#define CBITSET_H

/*
=======================
CBitSet

=======================
*/
class CBitSet
{
public:
	// Number of bits in a byte
	static const Uint32 NB_BITS_IN_BYTE = 8*sizeof(Byte);

public:
	CBitSet( void );
	explicit CBitSet( Uint32 size );
	CBitSet( const CBitSet& src );
	CBitSet( const Byte* pdataarray, Uint32 numbits );
	CBitSet( Uint32 bitsetSize, const Uint32 inputBits[], Uint32 arraySize );
	~CBitSet( void );

public:
	// Sets a bit
	DO_INLINE void set( Uint32 index );
	// Resets a bit
	DO_INLINE void reset( Uint32 index );
	// Flips a bit's state
	DO_INLINE void flip( Uint32 index );
	// Returns a bit's state
	DO_INLINE bool test( Uint32 index ) const;
	// Checks if all bits are set
	DO_INLINE bool all( void ) const;
	// Checks if any of the bits are set
	DO_INLINE bool any( void ) const;
	// Resizes the bitset
	DO_INLINE void resize( Uint32 size );
	// Tells the count of set bits
	DO_INLINE Uint32 count( void ) const;
	// Sets all bits in the bitset
	DO_INLINE void setall( void );
	// Clears all bits in the bitset
	DO_INLINE void reset( void );
	// Clears the bitset
	DO_INLINE void clear( void );

public:
	// Implements assignment operator
	DO_INLINE CBitSet& operator = ( const CBitSet& other );
	// Implements the bitset OR operator
	DO_INLINE CBitSet operator | ( const CBitSet& other ) const;
	// Implements the bitset OR assignment operator
	DO_INLINE CBitSet& operator |= ( const CBitSet& other );
	// Implements the bitset AND operator
	DO_INLINE CBitSet operator & ( const CBitSet& other ) const;
	// Implements the bitset AND assignment operator
	DO_INLINE CBitSet& operator &= ( const CBitSet& other );

	// Implements the bitset inverse operator
	DO_INLINE CBitSet operator ~ ( void ) const;

	// Implements equality check operator
	DO_INLINE bool operator == ( const CBitSet& other );
	// Implements non-equality check operator
	DO_INLINE bool operator != ( const CBitSet& other );

public:
	// Get raw bitset data
	Byte* getData( void );
	// Get raw bitset data
	const Byte* getDataConst( void ) const;
	// Tells the size of the bitset
	DO_INLINE Uint32 size( void ) const;
	// Tells the number of bytes in the bitset
	DO_INLINE Uint32 numbytes( void ) const;

private:
	// Array of bits
	Byte* m_pDataArray;
	// Number of bits allocated for
	Uint32 m_numBits;
	// Number of bytes
	Uint32 m_numBytes;
};

#include "cbitset_inline.hpp"
#endif //CBITSET_H