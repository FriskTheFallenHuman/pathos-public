/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CLOGFILE_H
#define CLOGFILE_H

#include "file_interface.h"

/*
=======================
CLogFile

=======================
*/
class CLogFile
{
public:
	typedef void (*pfnConPrintf_t)( const char *fmt, ... );

public:
	// Buffer size
	static const UInt32 LOG_BUFFER_SIZE;
	// Size of buffer for message prints
	static const UInt32 PRINT_MSG_BUFFER_SIZE;

public:
	explicit CLogFile( const char* pstrPath, pfnConPrintf_t pfnConPrintf, file_interface_t& fileInterface, bool deletePrevious = false, bool timeStamps = true );
	~CLogFile();

public:
	bool Init( void );
	bool Close( void );

	bool Write( const char* pstrString );
	bool Printf( const char *fmt, ... );

private:
	bool DumpBuffer( void );
	bool WriteInternal( const char* pstrString );

private:
	// Path to log file
	CString m_sLogPath;
	// Number of lines written
	UInt32 m_nbLinesWritten;
	// true if timestamps should be used
	bool m_useTimeStamps;
	// true if previous log should be deleted
	bool m_deletePreviousLog;

	// Log buffer
	char* m_pBuffer;
	// Log buffer load
	UInt32 m_logBufferLoad;
	// Protective semaphore
	bool m_writeSemaphore;

	// Pointer to Con_Printf function
	pfnConPrintf_t m_pfnConPrintf;
	// File interface fns
	file_interface_t m_fileInterface;

	// Temporary write buffer
	char* m_pTempWriteBuffer;
};
#endif //CLOGFILE_H