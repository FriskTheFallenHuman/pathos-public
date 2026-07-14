/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FLEXMANAGER_H
#define FLEXMANAGER_H

#include "snd_shared.h"
#include "flex_shared.h"
#include "file_interface.h"

struct vbmheader_t;

enum flex_flags_t
{
	FLEX_FLAG_NONE		= 0,
	FLEX_FLAG_LOOP		= (1<<0),
	FLEX_FLAG_STAY		= (1<<1),
	FLEX_FLAG_NO_BLINK	= (1<<2)
};

struct sent_assoc_t
{
	CString sentence;
	CString flexfile;
};

/*
====================
CFlexManager

====================
*/
class CFlexManager
{
public:
	explicit CFlexManager( const file_interface_t& fileInterface );
	~CFlexManager( void );

public:
	// Resets the manager
	void Clear( void );

public:
	// Loads a flex script
	const flexscript_t* LoadScript( const char* pscriptname );

	// Sets a script for a VBM file
	void SetScript( const vbmheader_t* pvbm, flexstate_t* pstate, float time, const char* pscriptname );
	// Updates values for a flex script
	void UpdateValues( float cur_time, float health, Int32 mouthopen, flexstate_t* pstate, bool scripting );

	// Gets a controller index for a flex
	static Int32 GetControllerIndex( const flexscript_t* pscript, const char* name );
	// Gets a fixed flex's controller index
	static Int32 GetFixedFlexIndex( const char* pstrname );

	// Sets flex mapping based on VBM data
	static void SetFlexMappings( const vbmheader_t* pvbm, flexstate_t* pstate );
	// Sets a controller's name
	static bool SetControllerName( const flexscript_t* pscript, flexcontroller_t* pcontroller, const char* pstrname );

	// Gets the error message
	const char* GetError( void ) const { return m_errorString.c_str(); }

public:
	// Loads an association script
	bool LoadAssociationScript( flextypes_t npcType, const char* pscriptname );

	// Gets an AI script based on type and AI state
	const char* GetAIScript( flextypes_t npcType, flexaistates_t aiState );
	// Retreives a script for a sentence
	const char* GetSentenceScript( const char* pstrSentence );

private:
	// Sets mouth value
	void SetMouth( Int32 mouthopen, flexstate_t* pstate );
	// Calculates blinking
	void Blink( float cur_time, float health, flexstate_t* pstate );
	
	// Sets the error string
	void SetError( const char *fmt, ... );

private:
	// Array of flex scripts tied to npcs and AI states
	CArray<CString> m_flexAIStateScripts[NUM_FLEX_NPC_TYPES][NUM_FLEX_AISTATES];

	// Array of sentence-flex script associations
	CArray<sent_assoc_t> m_sentenceScriptArray;

private:
	// Cache of flex scripts
	CArray<flexscript_t*> m_scriptCache;
	// Current mouth value
	float m_mouthValue;

	// Error string if any
	CString m_errorString;

private:
	// File access interface
	file_interface_t m_fileInterface;
};
#endif