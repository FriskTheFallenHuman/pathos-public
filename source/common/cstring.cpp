/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"

// Empty string character
char CString::EMPTY_STRING[] = "\0";

// Work buffer
char* CString::g_pWorkBuffer = nullptr;
// Work buffer size
UInt32 CString::g_workBufferSize = 0;
// Work buffer mutex
std::mutex CString::g_workBufferMutex;

// Pointer to string pool
CStringPool* CString::g_pStringPool = CStringPool::Instance();

//=============================================
// @brief Default constructor
//
// @param pstr Pointer to string
//=============================================
CString::CString():
	m_pString(nullptr),
	m_stringLength(0),
	m_pPoolCacheEntry(nullptr),
	m_flags(fl_str_none)
{
	m_pString = EMPTY_STRING;
}

//=============================================
// @brief Default constructor
//
// @param pstr Pointer to string
//=============================================
CString::CString( const char* pstr ):
	m_pString(nullptr),
	m_stringLength(0),
	m_pPoolCacheEntry(nullptr),
	m_flags(fl_str_none)
{
	if(pstr && qstrlen(pstr) > 0)
		setdata(pstr);
	else
		m_pString = EMPTY_STRING;
}

//=============================================
// @brief Copy constructor
//
// @param str Reference to CString to copy
//=============================================
CString::CString( const CString& str ):
	m_pString(nullptr),
	m_stringLength(0),
	m_pPoolCacheEntry(nullptr),
	m_flags(fl_str_none)
{
	if(str.length())
		setdata( str.c_str());
	else
		m_pString = EMPTY_STRING;
}

//=============================================
// @brief Default constructor
//
// @param pstr Pointer to string
//=============================================
CString::CString( const char* pstr, UInt32 length ):
	m_pString(nullptr),
	m_stringLength(length),
	m_pPoolCacheEntry(nullptr),
	m_flags(fl_str_none)
{
	if(pstr && length)
	{
		g_workBufferMutex.lock();
		CheckBuffer(length);
		g_pWorkBuffer[0] = '\0';
		qstrncpy(g_pWorkBuffer, pstr, length);

		setdata(g_pWorkBuffer);
		g_workBufferMutex.unlock();
	}
	else
	{
		m_pString = EMPTY_STRING;
	}
}

//=============================================
// @brief Constructor with flags
//
//=============================================
CString::CString( Byte flags ):
	m_pString(nullptr),
	m_stringLength(0),
	m_pPoolCacheEntry(nullptr),
	m_flags(flags)
{
	m_pString = EMPTY_STRING;
}
//=============================================
// @brief Destructor
//
//=============================================
CString::~CString()
{
	if(m_pString && m_pString != EMPTY_STRING)
	{
		if(!(m_flags & fl_str_nopooling))
			g_pStringPool->RemoveString(m_pPoolCacheEntry);
		else
			delete[] m_pString;
	}
}


//=============================================
// @brief Appends a source string to the current string
//
// @param psrc Pointer to string
//=============================================
void CString::Append(const char* psrc)
{
	if(psrc)
	{
		const UInt32 srclength = qstrlen(psrc);
		const UInt32 newlength = srclength + m_stringLength;

		g_workBufferMutex.lock();
		CheckBuffer(newlength);
		g_pWorkBuffer[0] = '\0';

		if(m_pString && m_pString != EMPTY_STRING)
			ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%s%s", m_pString, psrc);
		else
			qstrcpy_s(g_pWorkBuffer, psrc, g_workBufferSize);

#ifdef _DEBUG
		assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

		setdata(g_pWorkBuffer);
		g_workBufferMutex.unlock();
	}
}

//=============================================
// @brief Appends a char to the current string
//
// @param c Character to append
//=============================================
void CString::Append(char c)
{
	const UInt32 newlength = m_stringLength+1;

	g_workBufferMutex.lock();
	CheckBuffer(newlength);
	g_pWorkBuffer[0] = '\0';

	if(m_pString && m_pString != EMPTY_STRING)
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%s%c", m_pString, c);
	else
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%c", c);

#ifdef _DEBUG
	assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

	setdata(g_pWorkBuffer);
	g_workBufferMutex.unlock();
}

//=============================================
// @brief Appends an integer to the current string
//
// @param i Integer value to append
//=============================================
void CString::Append(Int32 i)
{
	UInt32 absValue = SDL_abs(i);
	UInt32 logVal = SDL_log10(absValue);
	UInt32 digitCount = SDL_floor(logVal) + 1;
	if(i < 0)
		digitCount++;

	UInt32 newlength = m_stringLength + digitCount;

	g_workBufferMutex.lock();
	CheckBuffer(newlength);

	if(m_pString && m_pString != EMPTY_STRING)
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%s%d", m_pString, i);
	else
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%d", i);

#ifdef _DEBUG
	assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

	setdata(g_pWorkBuffer);
	g_workBufferMutex.unlock();
}

//=============================================
// @brief Appends an integer to the current string
//
// @param i Unsigned integer value to append
//=============================================
void CString::Append(UInt32 i)
{
	UInt32 logValue = SDL_log10(i);
	UInt32 digitCount = SDL_floor(logValue) + 1;
	UInt32 newlength = m_stringLength + digitCount;

	g_workBufferMutex.lock();
	CheckBuffer(newlength);
	g_pWorkBuffer[0] = '\0';

	if(m_pString && m_pString != EMPTY_STRING)
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%s%u", m_pString, i);
	else
		ENGINE_SPRINTF_S(g_pWorkBuffer, g_workBufferSize, "%u", i);

#ifdef _DEBUG
	assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

	setdata(g_pWorkBuffer);
	g_workBufferMutex.unlock();
}

//=============================================
// @brief Appends a float value to the current string
//
// @param f Floating point value to append
//=============================================
void CString::Append(float f)
{
	// Accounts for negative zero
	float baseValue = (f == 0) ? 0 : f; 
	// Turn to abs so it works with log
	float absValue = SDL_fabs(baseValue);
	// Turn into integer value by flooring it, removing fraction part
	float floorValue = SDL_floor(absValue);
	// Get 10 logarythmic value(nb of digits past first digit)
	UInt32 logarithmicValue = SDL_log10(floorValue);
	// Get nb of digits past 1 in integer portion + 1
	UInt32 integerDigits = logarithmicValue + 1; 
	// Digit count is (int digits) + dot + (six fractional digits)
	UInt32 digitCount = integerDigits + 1 + 6; 
	// Account for negative signage
	if(baseValue < 0) 
		digitCount++; 

	UInt32 newlength = m_stringLength + digitCount;

	g_workBufferMutex.lock();
	CheckBuffer(newlength);
	g_pWorkBuffer[0] = '\0';

	// WARNING: If you change the floating point digit count here,
	// change it at the end of digitCount too!
	if(m_pString && m_pString != EMPTY_STRING)
		sprintf(g_pWorkBuffer, "%s%.6f", m_pString, baseValue);
	else
		sprintf(g_pWorkBuffer, "%.6f", baseValue);

#ifdef _DEBUG
	assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

	setdata(g_pWorkBuffer);
	g_workBufferMutex.unlock();
}

//=============================================
// @brief Appends a double float value to the current string
//
// @param d double value to append
//=============================================
void CString::Append(double d)
{
	// Accounts for negative zero
	double baseValue = (d == 0) ? 0 : d; 
	// Turn to abs so it works with log
	double absValue = SDL_fabs(baseValue);
	// Turn into integer value by flooring it, removing fraction part
	double floorValue = SDL_floor(absValue);
	// Get 10 logarythmic value(nb of digits past first digit)
	UInt32 logarithmicValue = SDL_log10(floorValue);
	// Get nb of digits past 1 in integer portion + 1
	UInt32 integerDigits = logarithmicValue + 1; 
	// Digit count is (int digits) + dot + (six fractional digits)
	UInt32 digitCount = integerDigits + 1 + 6; 
	// Account for negative signage
	if(baseValue < 0) 
		digitCount++; 

	UInt32 newlength = m_stringLength + digitCount;

	g_workBufferMutex.lock();
	CheckBuffer(newlength);
	g_pWorkBuffer[0] = '\0';

	// WARNING: If you change the floating point digit count here,
	// change it at the end of digitCount too!
	if(m_pString && m_pString != EMPTY_STRING)
		sprintf(g_pWorkBuffer, "%s%.6lf", m_pString, baseValue);
	else
		sprintf(g_pWorkBuffer, "%.6lf", baseValue);

#ifdef _DEBUG
	assert(qstrlen(g_pWorkBuffer) == newlength);
#endif

	setdata(g_pWorkBuffer);
	g_workBufferMutex.unlock();
}

//=============================================
// @brief Sets data for the string
//
//=============================================
void CString::setdata( const char* pString )
{
	m_stringLength = qstrlen(pString);
	if(!(m_flags & fl_str_nopooling))
	{
		// If we have a new entry, then remove that one
		if(m_pString && m_pString != EMPTY_STRING)
			g_pStringPool->RemoveString(m_pPoolCacheEntry);

		// First seek out an existing string entry, and if not found,
		// only then add a new one
		m_pPoolCacheEntry = g_pStringPool->GetExistingString(pString);
		if(!m_pPoolCacheEntry)
			m_pPoolCacheEntry = g_pStringPool->AddString(pString);

		// Set our string ptr as the cache
		m_pString = m_pPoolCacheEntry->iterator->first.c_str();
	}
	else
	{
		// Delete previous string object if it wasn't pointing to EMPTY_STRING
		if(m_pString && m_pString != EMPTY_STRING)
			delete[] m_pString;

		// Set new one
		if(pString && m_stringLength > 0)
		{
			char* pstrNew = new char[m_stringLength+1];
			qstrcpy(pstrNew, pString);
			m_pString = pstrNew;
		}
		else
		{
			m_pString = EMPTY_STRING;
		}
	}
}

//=============================================
// @brief Ensures work buffer is of adequate size
//
//=============================================
void CString::CheckBuffer( UInt32 length )
{
	UInt32 fullLength = length+1;
	if(g_workBufferSize >= fullLength)
		return;

	g_pWorkBuffer = new char[fullLength];
	memset(g_pWorkBuffer, 0, sizeof(char)*fullLength);
	g_workBufferSize = fullLength;
}