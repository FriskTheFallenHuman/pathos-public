/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CSTRING_H
#define CSTRING_H

#include "cstringpool.h"

/*
=======================
CString

=======================
*/
class CString
{
public:
	// flags for string object
	enum stringflags_t
	{
		fl_str_none = 0,
		fl_str_nopooling = (1<<0)
	};
	// No position value
	static const Int32 CSTRING_NO_POSITION = -1;

private:
	// Empty string character
	static char EMPTY_STRING[];

public:
	CString();
	CString( const char* pstr );
	CString( const CString& str );
	CString( const char* pstr, Uint32 length );
	CString( Byte flags );
	~CString();
	
public:
	// Assignment operator
	CString& operator=(const CString& str);
	// Comparison operator
	DO_INLINE bool operator==(const char* pstr) const;
	// Comparison operator
	DO_INLINE bool operator==(const CString& str) const;

	// Comparison operator
	DO_INLINE bool operator<(const char* pstr) const;
	// Comparison operator
	DO_INLINE bool operator<(const CString& str) const;

	// Comparison operator
	DO_INLINE bool operator>(const char* pstr) const;
	// Comparison operator
	DO_INLINE bool operator>(const CString& str) const;

	// Byte shift operator
	DO_INLINE CString& operator<<(const char* pstr);
	// Byte shift operator
	DO_INLINE CString& operator<<(const CString& str);
	// Byte shift operator
	DO_INLINE CString& operator<<(char c);
	// Byte shift operator
	DO_INLINE CString& operator<<(Int32 i);
	// Byte shift operator
	DO_INLINE CString& operator<<(Uint32 i);
	// Byte shift operator
	DO_INLINE CString& operator<<(float f);
	// Byte shift operator
	DO_INLINE CString& operator<<(double d);
	// Plus equal operator
	DO_INLINE CString& operator+=(const char* pstr);
	// Plus equal operator
	DO_INLINE CString& operator+=(const CString& str);
	// Plus equal operator
	DO_INLINE CString& operator+=(char c);
	// Plus equal operator
	DO_INLINE CString& operator+=(Int32 i);
	// Plus equal operator
	DO_INLINE CString& operator+=(Uint32 i);
	// Plus equal operator
	DO_INLINE CString& operator+=(float f);
	// Plus equal operator
	DO_INLINE CString& operator+=(double d);
	// Plus operator
	DO_INLINE CString operator+(const char* pstr);
	// Plus operator
	DO_INLINE CString operator+(const CString& str);
	// Plus operator
	DO_INLINE CString operator+(char c);
	// Plus operator
	DO_INLINE CString operator+(Int32 i);
	// Plus operator
	DO_INLINE CString operator+(Uint32 i);
	// Plus operator
	DO_INLINE CString operator+(float f);
	// Plus operator
	DO_INLINE CString operator+(double d);
	// Indexing operator
	DO_INLINE char operator[] (Uint32 n) const;

public:
	// Returns the raw string
	DO_INLINE const char* c_str( void ) const;
	// Returns the string length
	DO_INLINE Uint32 length( void ) const;
	// Returns if the string is empty
	DO_INLINE bool empty( void ) const;
	// Returns if the string is empty
	DO_INLINE void clear( void );
	// Assigns a string to use
	DO_INLINE void assign( const char* pstr, Uint32 num );
	// Finds the first occurrence of a string in the string
	DO_INLINE Int32 find( Uint32 offset, const char* psubstr, bool caseinsensitive = false );
	// Erases part of the string
	DO_INLINE void erase( Uint32 begin, Uint32 numremove );
	// Converts characters to lowercase
	DO_INLINE void tolower( void );
	// Inserts a substrinct into the string
	DO_INLINE void insert( Uint32 begin, const char* pstrsubstr );
	// Replaces slashes with PATH_SLASH_CHAR
	DO_INLINE void replaceslashes( void );

public:
	// Appends a string to the current one
	void Append( const char* psrc );
	// Appends a string to the current one
	void Append( char c );
	// Appends a string to the current one
	void Append( Int32 i );
	// Appends a string to the current one
	void Append( Uint32 i );
	// Appends a string to the current one
	void Append( float f );
	// Appends a string to the current one
	void Append( double d );

public:
	// Sets data for the string
	virtual void setdata( const char* pString );

private:
	// Ensures work buffer is of adequate size
	static void CheckBuffer( Uint32 length );

private:
	// Pointer to string
	const char* m_pString;
	// Length of the string
	Uint32 m_stringLength;
	// Link to current string link in pool
	CStringPool::cachestring_t* m_pPoolCacheEntry;
	// Flags for string
	Byte m_flags;

private:
	// Work buffer
	static char* g_pWorkBuffer;
	// Work buffer size
	static Uint32 g_workBufferSize;
	// Work buffer mutex
	static std::mutex g_workBufferMutex;

private:
	// Pointer to string pool
	static CStringPool* g_pStringPool;
};

// Hash structure for CString
template <>
struct std::hash<CString>
{
	std::size_t operator()( const CString& k ) const
	{
		return std::hash<const char*>()(k.c_str());
	}
};

// For adding strings together
extern DO_INLINE CString operator + ( const CString& lhs, const CString& rhs );

#include "cstring_inline.hpp"
#endif // CSTRING_H