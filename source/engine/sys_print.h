/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SYS_PRINT_H
#define SYS_PRINT_H

#include "md5.h"

// Size of buffer for message prints
static constexpr UInt32 PRINT_MSG_BUFFER_SIZE = 16384;

/*
====================
CSysPrintInterface

====================
*/
class CSysPrintInterface
{
public:
	// Flags for a print msg
	enum printflags_t
	{
		PRINT_FL_NONE			= 0,
		PRINT_FL_ONLYONCE		= (1<<0),	// Only once per application instance
		PRINT_FL_ONLYONCE_GAME	= (1<<1)	// Only once per game instance
	};

public:
	CSysPrintInterface( void );
	~CSysPrintInterface( void );

public:
	// Clear class on cleanup
	void Clear( void );
	// Clear game specific stuff
	void ClearGame( void );

public:
	// Standard print to console
	void Printf( const char *pstring );
	// Print to debug
	void DPrintf( const char *pstring );
	// Print verbose
	void VPrintf( const char *pstring );
	// Print warning
	void WPrintf( const char *pstring );
	// Print error
	void EPrintf( const char *pstring );

private:
	// Processes any flags inside strings
	void CheckForFlags( CString& inputstring, Int32& outflags );
	// Tells if the message should be printed
	bool ShouldPrintMessage( const char* pstrMessage, Int32 flags );

private:
	// Set of only once an instance prints
	std::set<CString> m_applicationInstancePrintsSet;
	// Set of only once a game prints
	std::set<CString> m_gameInstancePrintsSet;
	// MD5 hasher
	CMD5 m_md5Hasher;
};
extern CSysPrintInterface gPrintInterface;

// Standard print to console
extern void Con_Printf( const char *fmt, ... );
// Print to debug
extern void Con_DPrintf( const char *fmt, ... );
// Print verbose
extern void Con_VPrintf( const char *fmt, ... );
// Print warning
extern void Con_WPrintf( const char *fmt, ... );
// Print error
extern void Con_EPrintf( const char *fmt, ... );
#endif //SYS_PRINT_H
