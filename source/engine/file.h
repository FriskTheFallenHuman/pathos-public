/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FILE_H
#define FILE_H

/*
=================================
CFileCache

=================================
*/
class CFileCache
{
private:
	struct file_t
	{
		file_t():
			pfile(nullptr),
			filesize(0),
			refcount(0)
		{
		}
		~file_t()
		{
			if(pfile)
				delete[] pfile;
		}

		const Byte* pfile;
		UInt32 filesize;
		UInt32 refcount;
	};

	typedef std::map<CString, file_t*> FileCacheMap_t;
	typedef std::map<const Byte*, FileCacheMap_t::iterator> FilePtrCacheIteratorMap_t;

public:
	CFileCache( void );
	~CFileCache( void );

public:
	// Loads a file into memory
	const Byte* LoadFile( const char* pstrpath, UInt32* psize = nullptr );
	// Reduces refcount on a file, and removes it is refcount is zero
	bool FreeFile( const void* pfile );
	// Dumps open files list
	void Dump( void );

private:
	// Map containing files loaded currently
	FileCacheMap_t m_fileCacheMap;
	// Map of file pointer->cache map iterator mappings
	FilePtrCacheIteratorMap_t m_filePtrCacheIteratorMap;
};
extern CFileCache gFileCache;

extern const Byte* FL_LoadFile( const char* pstrpath, UInt32* psize = nullptr );
extern const Byte* FL_LoadFileFromRoot( const char* pstrpath, UInt32* psize = nullptr );
extern bool FL_WriteFile( const Byte* pdata, UInt32 size, const char* pstrpath, bool append = false );
extern bool FL_WriteLogFile( const Byte* pdata, UInt32 size, const char* pstrpath, bool append = false );
extern bool FL_WriteFileRoot( const Byte* pdata, UInt32 size, const char* pstrpath, bool append = false );
extern void FL_FreeFile( const void* pfile );
extern bool FL_FileExists( const char* pstrpath );
extern bool FL_DeleteFile( const char* pstrpath );
extern bool FL_DeleteFileRoot( const char* pstrpath );
extern bool FL_CreateDirectory( const char* pstrpath );
extern bool FL_GetFileDate( const char* pstrFile, file_dateinfo_t& dateinfo );
extern Int32 FL_CompareFileDates( const file_dateinfo_t& d1, const file_dateinfo_t& d2 );
extern const char* FL_GetGameDirectory( void );
extern struct file_interface_t& FL_GetInterface( void );
#endif //FILE_H