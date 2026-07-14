/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H

struct file_interface_t
{
	const Byte*		(*pfnLoadFile)( const char* pstrpath, UInt32* psize );
	bool			(*pfnWriteFile)( const Byte* pdata, UInt32 size, const char* pstrpath, bool append );
	bool			(*pfnWriteLogFile)( const Byte* pdata, UInt32 size, const char* pstrpath, bool append );
	void			(*pfnFreeFile)( const void* pfile );
	bool			(*pfnFileExists)( const char* pstrpath );
	bool			(*pfnDeleteFile)( const char* pstrpath );
	bool			(*pfnCreateDirectory)( const char* pstrpath );
	bool			(*pfnGetFileDate)( const char* pstrFile, file_dateinfo_t& dateinfo );
	Int32			(*pfnCompareFileDates)( const file_dateinfo_t& d1, const file_dateinfo_t& d2 );
	const char*		(*pfnGetGameDirectory)( void );
};

#endif //FILE_INTERFACE_H