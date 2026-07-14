/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SAVERESTORE_H
#define SAVERESTORE_H

#include "savefile.h"
#include "globalstate_shared.h"

class CCVar;

struct edict_t;

extern void Save_WriteBool( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteByte( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteBitset( const char* fieldname, const Byte* pdata, UInt32 numberofbits, entfieldtype_t fieldtype );
extern void Save_WriteChar( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteInt16( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteUint16( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteInt32( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteUint32( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteInt64( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteUint64( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteFloat( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteDouble( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteTime( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteString( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteRawString( const char* fieldname, const Byte* pdata, entfieldtype_t fieldtype );
extern void Save_WriteVector( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteCoord( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteEntindex( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
extern void Save_WriteGlobalState( UInt32 index, const char* pstrglobalname, const char* pstrlevelname, globalstate_state_t state );

/*
=======================
CSaveRestore

=======================
*/
class CSaveRestore
{
public:
	// Optimized string array alloc size
	static const UInt32 STRING_ARRAY_ALLOC_SIZE;
	// Allocation size for buffers
	static const UInt32 BUFFER_ALLOC_SIZE;
	// Save directory path
	static const char SAVE_DIR_PATH[];
	// Save file version
	static const UInt32 SAVE_FILE_VERSION;

public:
	struct saved_string_t
	{
		saved_string_t():
			offset(-1),
			length(0)
			{
			}

		Int32 offset;
		UInt32 length;
	};

	struct saved_cvar_t
	{
		saved_cvar_t():
			type(CVAR_FLOAT)
		{}

		CString name;
		CString value;
		cvar_type_t type;
	};

	typedef std::map<CString, Int32> StringPositionMap_t;

public:
	CSaveRestore();
	~CSaveRestore();

public:
	// Creates a save file
	bool CreateSaveFile( const char* baseName, savefile_type_t type, const Vector* plandmarkorigin, CString* poutname, bool keepOld = false );
	// Loads a save file
	const Byte *LoadSaveFile( const char* savePath, UInt32* psize = nullptr );
	// Frees a save file
	void FreeSaveFile( const Byte* pfile );
	// Loads a save file
	bool LoadSaveData( const save_header_t* pheader, const Vector* plandmarkoffset = nullptr );
	// Loads globals from a save file
	void LoadGlobalsFromSaveFile( const save_header_t* pheader );
	// Loads connections from a save file
	void LoadConnectionsFromSaveFile( const save_header_t* pheader );
	// Returns the save file type
	savefile_type_t GetSaveFileType( const char* pstrSaveFile );

public:
	// Finds the most recent save file
	bool GetMostRecentSave( CString* pOutput );

private:
	// Saves an entity's data
	void SaveEntity( edict_t* pedict, save_edict_info_t& saveinfo );

	// Writes a field entry into the list
	save_field_t* SaveField( const char* fieldname, entfieldtype_t fieldtype, const UInt32& blocksize );
	// Saves a string to the buffer
	save_block_t& SaveToStringBuffer( const char* pstrstring );
	// Saves a buffer to the entity data buffer
	save_block_t& SaveToDataBuffer( const Byte* pdata, Int32 size );

	// Add a cvar to be saved
	bool AddSavedCVar( CCVar* pcvar );

	// Cleans save files
	void CleanSaveFiles( const char* pstrLastSave );

public:
	// Writes a integer values to the output
	void WriteBool( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteByte( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes bitset bytes to the output
	void WriteBitset( const char* fieldname, const Byte* pdata, UInt32 numberofbits, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteChar( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteInt16( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteUint16( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteInt32( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteUint32( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteInt64( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteUint64( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a float values to the output
	void WriteFloat( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes time values to the output
	void WriteDouble( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes time values to the output
	void WriteTime( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes strings to the output
	void WriteString( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a raw string to the output
	void WriteRawString( const char* fieldname, const Byte* pdata, entfieldtype_t fieldtype );
	// Writes vectors to the output
	void WriteVector( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes coordinate vectors to the output
	void WriteCoord( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	// Writes a integer values to the output
	void WriteEntindex( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );

public:
	// Writes a global state to the save file
	void WriteGlobalState( UInt32 index, const char* pstrglobalname, const char* pstrlevelname, globalstate_state_t state );

private:
	// Buffer of entities to save
	CArray<save_edict_info_t> m_saveEdictsBuffer;
	// Number of edicts in array
	UInt32 m_numSaveEdicts;

	// Buffer of fields saved for entities
	CArray<save_field_t> m_edictFieldsBuffer;
	// Number of entity fields
	UInt32 m_numEdictFields;

	// Linked list of data blocks saved
	CArray<save_block_t> m_saveDataBlocksBuffer;
	// Number of saved data blocks
	UInt32 m_numSaveDataBlocks;

	// Linked list of string blocks
	CArray<save_block_t> m_saveStringBlocksBuffer;
	// Number of saved string blocks
	UInt32 m_numSaveStringBlocks;

	// Raw data buffer for entity fields
	Byte* m_pEntityDataBuffer;
	// Entity data buffer size
	UInt32 m_entityDataBufferSize;
	// Entity data buffer usage
	UInt32 m_entityDataBufferUsage;

	// Raw data buffer for strings
	Byte* m_pStringBuffer;
	// String buffer size
	UInt32 m_stringBufferSize;
	// String buffer usage
	UInt32 m_stringBufferUsage;

	// Buffer of global states to save
	save_global_t* m_pGlobalStatesBuffer;
	// Number of globals expected
	UInt32 m_nbGlobalStates;

	// Server string index into string buffer map
	CArray<Int32> m_serverStringIndexArray;

	// Array of saved string
	CArray<saved_string_t> m_savedStringsArray;
	// String->position map
	StringPositionMap_t m_savedStringPositionMap;
	// Number of elements in array
	UInt32 m_numSavedStrings;

	// Saved cvar ptrs
	CArray<saved_cvar_t> m_savedCVarsArray;

private:
	// Save buffer size
	UInt32 m_saveBufferSize;

	// true if using a landmark
	bool m_isTransitionSave;
	// Landmark origin
	Vector m_landmarkOrigin;

	// Time base we need to get delta from
	double m_timeBase;
};
extern CSaveRestore gSaveRestore;
#endif // SAVERESTORE_H