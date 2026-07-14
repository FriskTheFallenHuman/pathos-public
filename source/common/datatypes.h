/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef DATATYPES_H
#define DATATYPES_H

typedef	uint8_t				Uchar;
typedef	uint8_t				Byte;
typedef	int32_t				Int32;
typedef uint32_t			UInt32;
typedef int16_t				Int16;
typedef	uint16_t			UInt16;
typedef int64_t				Int64;
typedef uint64_t			UInt64;
typedef UInt32				string_t;
typedef Int32				entindex_t;
typedef UInt32				Dword;

struct vec4_t
{
	DO_INLINE vec4_t()
	{
		for(UInt32 i = 0; i < 4; i++)
			v[i] = 0;
	}

	DO_INLINE vec4_t(const vec4_t& src)
	{
		for(UInt32 i = 0; i < 4; i++)
			v[i] = src.v[i];
	}

	DO_INLINE vec4_t( float coords[4] )
	{
		for(UInt32 i = 0; i < 4; i++)
			v[i] = coords[i];
	}

	DO_INLINE vec4_t& operator=( const vec4_t& src )
	{
		for(UInt32 i = 0; i < 4; i++)
			v[i] = src.v[i];

		return *this;
	}

	DO_INLINE float& operator[]( UInt32 n )
	{
		assert(n <= 4);
		return v[n];
	}

	DO_INLINE float operator[]( UInt32 n ) const
	{
		assert(n <= 4);
		return v[n];
	}

	DO_INLINE float& operator[]( Int32 n )
	{
		assert(n <= 4);
		return v[n];
	}

	DO_INLINE float operator[]( Int32 n ) const
	{
		assert(n <= 4);
		return v[n];
	}

	DO_INLINE operator float*( void )
	{
		return v;
	}

	DO_INLINE operator const float*( void ) const
	{
		return v;
	}

	float v[4];
};

struct color32_t
{
	color32_t():
		r(0),
		g(0),
		b(0),
		a(255)
	{}
	color32_t( Byte _r, Byte _g, Byte _b, Byte _a )
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	Byte& operator[]( UInt32 n )
	{
		assert(n <= 3);

		if(n == 0)
			return r;
		else if(n == 1)
			return g;
		else if(n == 2)
			return b;
		else
			return a;
	}

	Byte r;
	Byte g;
	Byte b;
	Byte a;
};

struct color24_t
{
	color24_t():
		r(0),
		g(0),
		b(0)
	{}
	color24_t( Byte _r, Byte _g, Byte _b )
	{
		r = _r;
		g = _g;
		b = _b;
	}
	Byte& operator[]( UInt32 n )
	{
		assert(n <= 2);

		if(n == 0)
			return r;
		else if(n == 1)
			return g;
		else
			return b;
	}

	Byte r;
	Byte g;
	Byte b;
};

struct pmatrix3x4_t
{
	pmatrix3x4_t()
	{
		memset(matrix, 0, sizeof(matrix));
	}

	float matrix[3][4];
};
#endif