/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SENTENCESFILE_H
#define SENTENCESFILE_H

//=============================================
//
//=============================================
class CSentencesFile
{
public:
	typedef Int32 (*pfnPrecacheSoundFunctionPtr_t)( const char* pstrFilepath );
	typedef float (*pfnGetSoundDurationFunctionPtr_t)( const char* pstrfilename, UInt32 pitch );

public:
	// Comma delay amount
	static const float COMMA_DELAY;
	// Default folder for sentences
	static const char DEFAULT_FOLDER[];

public:
	struct sentencegroup_t
	{
		sentencegroup_t():
			numsentences(0),
			startindex(0),
			duration(-1)
			{
			}

		CString groupname;
		UInt32 numsentences;
		UInt32 startindex;
		float duration;
	};

	struct sent_chunk_t
	{
		sent_chunk_t():
			pitch(0),
			time(0),
			start(0),
			end(0),
			volume(0),
			delay(0),
			pnext(nullptr)
			{
			}

		CString soundname;
		UInt32 pitch;
		UInt32 time;
		UInt32 start;
		UInt32 end;
		UInt32 volume;
		float delay;

		sent_chunk_t* pnext;
	};

	struct sentence_t
	{
		sentence_t():
			index(0),
			duration(-1)
		{
		}
		~sentence_t()
		{
			for(UInt32 i = 0; i < chunks.size(); i++)
				delete chunks[i];
		}

		CString name;
		CString entryname;
		UInt32 index;
		float duration;

		CString folder;
		CArray<sent_chunk_t*> chunks;
	};

public:
	CSentencesFile( void );
	explicit CSentencesFile( pfnPrecacheSoundFunctionPtr_t pfnPrecacheSound, pfnGetSoundDurationFunctionPtr_t pfnGetSoundDuration );
	~CSentencesFile( void );

public:
	bool Init( const Byte* pfile );
	void Clear( void );

	const char* GetRandomSentence( const char* pstrGroupName, float* pDuration );
	const char* GetSentence( const char* pstrSentenceName, float* pDuration );

	const sentence_t* GetSentenceDefinition( const char* pstrSentenceName ) const;
	const sentence_t* GetSentenceDefinition( Int32 index ) const;
	float GetSentenceDuration( const char* pstrSentenceName );
	float GetSentenceDuration( Int32 index );

	void PrecacheGroup( const char* pstrGroupName );
	void PrecacheSentence( const char* pstrSentenceName );
	void PrecacheSentence( sentence_t* psentence );

public:
	bool HasWarnings( void ) const;
	const char* GetWarning( UInt32 index );
	UInt32 GetNbWarnings( void ) const;

	bool HasError( void ) const;
	const char* GetError( void ) const;

	sentence_t* GetSentenceDefinition(const char* pstrSentenceName);

private:
	bool ParseOptionToken( const char** ppoutstr, const char* pstroption, UInt32& pitch, UInt32& time, UInt32& start, UInt32& end, UInt32& volume );

private:
	// Array of sentence groups
	CArray<sentencegroup_t*> m_sentenceGroupsArray;
	// Array of sentences
	CArray<sentence_t*> m_sentencesArray;

	// Array of warning messages
	CArray<CString> m_warningMessagesArray;
	// Error message if any
	CString m_errorMessage;

private:
	// Precache sound function ptr
	pfnPrecacheSoundFunctionPtr_t m_pfnPrecacheSound;
	// Get sound duration function ptr
	pfnGetSoundDurationFunctionPtr_t m_pfnGetSoundDuration;
};
#endif //SENTENCESFILE_H