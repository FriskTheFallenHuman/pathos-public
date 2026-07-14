/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CARRAY_H
#define CARRAY_H

/*
=======================
CArray

=======================
*/
template <typename T> class CArray
{
public:
	DO_INLINE CArray( void );
	DO_INLINE explicit CArray( Uint32 size );
	DO_INLINE CArray( const CArray& src );
	DO_INLINE CArray( const CArray* pArray );
	DO_INLINE ~CArray( void );

public:
	// Assignment operator
	DO_INLINE void operator=( const CArray& src );

	// Resizes the array
	DO_INLINE void resize( Uint32 size );
	// Resizes the array
	DO_INLINE void reserve( Uint32 size );
	// Deallocates the array
	DO_INLINE void clear( void );
	// Returns the size of the array
	DO_INLINE Uint32 size( void ) const;
	// Returns if the array is empty
	DO_INLINE bool empty( void ) const;
	// pushes an element back
	DO_INLINE void push_back( const T& element );
	// Erases an element from the array
	DO_INLINE void erase( Uint32 index );
	// Erases an element from the array
	DO_INLINE void erase_object( const T& element );

	// Indexing operator
	DO_INLINE T& operator[] ( Uint32 n ) const;

private:
	// Elements in array
	T* m_pArray;
	// Size of array
	Uint32 m_arraySize;
	// Actual size of the array
	Uint32 m_reservedSize;
};

#include "carray_inline.hpp"
#endif // CARRAY_H