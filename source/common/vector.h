/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef VECTOR_H
#define VECTOR_H

/*
=======================
Vector

=======================
*/
class Vector
{
public:
	// Constructors
	DO_INLINE Vector( void );
	DO_INLINE Vector( float srcX, float srcY, float srcZ );
	DO_INLINE Vector( const Vector& src );
	DO_INLINE Vector( float coords[3] );
	DO_INLINE Vector( Int32 coords[3] );

	// Negation operator
	DO_INLINE Vector operator-( void ) const;
	// Equality operator
	DO_INLINE bool operator==( const Vector& rhv ) const;
	// Not equals operator
	DO_INLINE bool operator!=( const Vector& rhv ) const;
	// Addition operator
	DO_INLINE Vector operator+( const Vector& rhv ) const;
	// Plus equals operator
	DO_INLINE Vector& operator+=( const Vector& rhv );
	// Subtration operator
	DO_INLINE Vector operator-( const Vector& rhv ) const;
	// Minus equals operator
	DO_INLINE Vector& operator-=( const Vector& rhv );
	// Multiplication operator
	DO_INLINE Vector operator*( const Vector& rhv ) const;
	// Multiplication and assignment operator
	DO_INLINE Vector& operator*=( const Vector& rhv );
	// Division operator
	DO_INLINE Vector operator/( const Vector& rhv ) const;
	// Division and assignment operator
	DO_INLINE Vector& operator/=( const Vector& rhv );
	// Assignment operator
	DO_INLINE Vector& operator=( const Vector& rhv );
	// Indexing operator
	DO_INLINE float& operator[]( UInt32 n );
	// Indexing operator
	DO_INLINE float operator[]( UInt32 n ) const;
	// Indexing operator
	DO_INLINE float& operator[]( Int32 n );
	// Indexing operator
	DO_INLINE float operator[]( Int32 n ) const;
	// Multiplication operator
	DO_INLINE Vector operator*(float value) const;
	// Multiplication operator
	DO_INLINE Vector operator/(float value) const;

	// Operator to convert to float pointer
	operator float*( void );
	// Operator to convert to const float pointer
	operator const float*( void ) const;

	// Tells the length of the vector
	DO_INLINE float Length( void ) const;
	// Tells the 2d length of the vector
	DO_INLINE float Length2D( void ) const;
	// Returns the normalized vector
	DO_INLINE Vector& Normalize( void );
	// Clears the vector
	DO_INLINE void Clear( void );
	// Tells if the vector is null
	DO_INLINE bool IsZero( void ) const;
	// Tells if the vector value is NAN
	DO_INLINE bool IsNAN( Int32 index ) const;

public:
	// Elements of the vector
	float x;
	float y;
	float z;
};
// For multiplying Vector with float array
DO_INLINE Vector operator*( float lhv, const Vector& rhv );

#include "vector_inline.hpp"
#endif // VECTOR_H