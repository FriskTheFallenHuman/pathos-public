/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CL_SND_H
#define CL_SND_H

#include <al/al.h>
#include <al/alc.h>
#include <al/alext.h>
#include <al/efx.h>
#include <al/efx-presets.h>

#include "cvar.h"
#include "ref_params.h"
#include "tempentity.h"
#include "snd_shared.h"
#include "sentencesfile.h"
#include "common.h"

struct stb_vorbis;

#ifndef ALC_SOFT_HRTF
#define ALC_SOFT_HRTF 1
#define ALC_HRTF_SOFT                            0x1992
#define ALC_DONT_CARE_SOFT                       0x0002
#define ALC_HRTF_STATUS_SOFT                     0x1993
#define ALC_HRTF_DISABLED_SOFT                   0x0000
#define ALC_HRTF_ENABLED_SOFT                    0x0001
#define ALC_HRTF_DENIED_SOFT                     0x0002
#define ALC_HRTF_REQUIRED_SOFT                   0x0003
#define ALC_HRTF_HEADPHONES_DETECTED_SOFT        0x0004
#define ALC_HRTF_UNSUPPORTED_FORMAT_SOFT         0x0005
#define ALC_NUM_HRTF_SPECIFIERS_SOFT             0x1994
#define ALC_HRTF_SPECIFIER_SOFT                  0x1995
#define ALC_HRTF_ID_SOFT                         0x1996
#endif

// Precache function for sentences file
Int32 Sentences_PrecacheSound( const char* pstrFilename );
// GetDuration function for sentences file
float Sentences_GetSoundDuration( const char* pstrFilename, UInt32 pitch );

struct snd_oggcache_t
{
	snd_oggcache_t():
		level(RS_LEVEL_UNDEFINED),
		pfileptr(nullptr),
		filesize(0)
		{}

	CString filepath;

	rs_level_t level;

	Byte* pfileptr;

	UInt32 filesize;
};

/*
=================================
CSoundEngine

=================================
*/
class CSoundEngine
{
public:
	struct snd_active_t;

	struct snd_cache_t
	{
		snd_cache_t():
			length(0),
			svindex(-1),
			index(0),
			samplerate(0),
			dataoffset(0),
			bitspersample(0),
			channels(0),
			loopbegin(0),
			pbuffers(nullptr),
			numbuffers(0),
			level(RS_LEVEL_UNDEFINED),
			ondemand(false),
			refcounter(0),
			pdata(nullptr)
		{
		}

		CString name;
		UInt64 length;
		Int32 svindex;
		Int32 index;

		Int32 samplerate;
		Int32 dataoffset;
		UInt16 bitspersample;
		UInt16 channels;
		Int32 loopbegin;

		ALuint *pbuffers;
		UInt32 numbuffers;

		rs_level_t level;

		bool ondemand;
		UInt32 refcounter;

		Byte* pdata;
	};

	struct snd_playing_t
	{
		snd_playing_t():
			psound(nullptr),
			sourceindex(0)
		{
		}

		snd_active_t* psound;
		ALuint sourceindex;
	};

	struct snd_active_t
	{
		snd_active_t():
			active(false),
			leafnum(0),
			timeoffs(0),
			pcache(nullptr),
			pentity(nullptr),
			entindex(0),
			datapos(0),
			curbuffer(0),
			channel(0),
			pitch(0),
			mainpitch(0),
			flags(0),
			volume(0),
			radius(0),
			time(0),
			delaytime(0),
			targetvolume(0),
			prevvolume(0),
			volchangetime(0),
			volchangeduration(0),
			targetpitch(0),
			prevpitch(0),
			pitchchangetime(0),
			pitchchangeduration(0),
			pplaying(nullptr),
			psentence(nullptr),
			pchunk(nullptr)
		{
		}

		bool active;
		UInt32 leafnum;
		double timeoffs;

		snd_cache_t* pcache;
		struct cl_entity_t* pentity;
		entindex_t entindex;

		// For debugging only
		CString cachename;

		Int32 datapos;
		UInt32 curbuffer;

		Byte channel;
		Byte pitch;
		Byte mainpitch;
		Int32 flags;

		float volume;
		float radius;
		double time;
		double delaytime;

		float targetvolume;
		float prevvolume;
		double volchangetime;
		float volchangeduration;

		Byte targetpitch;
		Byte prevpitch;
		double pitchchangetime;
		float pitchchangeduration;

		Vector origin;
		snd_playing_t* pplaying;

		const CSentencesFile::sentence_t *psentence;
		const CSentencesFile::sent_chunk_t *pchunk;
	};

	struct snd_missing_t
	{
		snd_missing_t():
			sv_index(0)
			{}

		CString filename;
		Int32 sv_index;
	};

	struct snd_music_t
	{
		snd_music_t():
			source(0),
			flags(0),
			channel(0),
			paused(false),
			pfile(nullptr),
			stream(nullptr),
			channels(0),
			samplerate(0),
			format(0),
			starttime(0),
			fadeinduration(0),
			fadeouttime(0),
			fadeoutduration(0),
			unpausefadetime(0),
			unpausefadebegin(0)
			{
				for(UInt32 i = 0; i < 2; i++)
					buffers[i] = 0;
			}

		ALuint source;
		Int32 flags;
		CString filename;
		Int32 channel;
		bool paused;

		ALuint buffers[2];
		snd_oggcache_t *pfile;

		stb_vorbis* stream;

		Int32 channels;
		Int32 samplerate;

		ALenum format;

		// Game time
		double starttime;
		// Fade in duration
		float fadeinduration;
		// Fade out begin time
		double fadeouttime;
		// Fade out duration
		float fadeoutduration;
		// Un-pause fade duration
		float unpausefadetime;
		// Un-pause fade begin
		double unpausefadebegin;
	};

	enum snd_cachetype_t
	{
		SND_CT_UNDEFINED = 0,
		SND_CT_PLAYENTITYSOUND,
		SND_CT_PLAYAMBIENTSOUND,
		SND_CT_APPLYEFFECT
	};

	struct s_msg_cache_t
	{
		s_msg_cache_t():
			type(SND_CT_UNDEFINED),
			cachetime(0),
			svindex(0),
			entindex(0),
			channel(0),
			flags(0),
			volume(0),
			pitch(0),
			atten(0),
			timeoffs(0),
			effect(SND_EF_UNDEFINED),
			effectduration(0),
			targetvalue(0),
			duration(0),
			looping(false)
			{}

		snd_cachetype_t type;

		Vector origin;

		double cachetime;
		Int32 svindex;
		entindex_t entindex;
		Int32 channel;
		Int32 flags;
		float volume;
		float pitch;
		float atten;
		float timeoffs;
		snd_effects_t effect;
		float effectduration;
		float targetvalue;
		float duration;
		bool looping;
	};

	enum stream_result_t
	{
		STREAM_ERROR = -1,
		STREAM_OK,
		STREAM_EOF
	};

private:
	// Max active sounds
	static const UInt32 MAX_ACTIVE_SOUNDS = 512;
	// Max playing sounds
	static const UInt32 MAX_PLAYING_SOUNDS = 256;
	// Number of reverbs
	static const UInt32 NUM_REVERBS = 29;

public:
	// Max active tempent sounds
	static const UInt32 MAX_ACTIVE_TEMP_SOUNDS;

	// Minimum sound distance
	static const float MIN_DISTANCE;
	// Maximum sound distance
	static const float MAX_DISTANCE;

	// Rever blend time
	static const float REVERB_BLEND_TIME;
	// Sound rolloff factor
	static const float SE_ROLLOFF_FACTOR;
	// Buffer size
	static const UInt32 BUFFER_SIZE;
	// Speed of sound ingame
	static const float SPEED_OF_SOUND;

	// Cached message max lifetime
	static const float CACHED_MSG_DELETE_TIME;

	// Average nb of samples for 8-bit sounds
	static const UInt32 AVERAGE_SAMPLES_8BIT;
	// Average nb of samples for 16-bit sounds
	static const UInt32 AVERAGE_SAMPLES_16BIT;

	// Default change time for SND_CHANGE_PITCH/SND_CHANGE_VOL flags
	static const float DEFAULT_SND_CHANGE_TIME;

	// On-demand sound file size limit
	static const UInt32 ONDEMAND_SOUND_SIZE_LIMIT;

	// Config group for sound engine
	static const char SOUNDENGINE_CONFIG_GRP_NAME[];
	// Config group for sound engine
	static const char SOUNDENGINE_HRTF_SETTING_NAME[];

public:
	CSoundEngine( void );
	~CSoundEngine( void );

public:
	// Initializes OpenAL
	bool Init( void );
	// Initialies engine for a game session
	void InitGame( void );
	// Shuts down the engine
	void Shutdown( void );

	// Resets the game state
	void ClearSounds( void );
	// Resets the engine
	void ResetEngine( bool clearall );
	// Updates the engine
	void Update( ref_params_t *pparams );
	// Resets the game souns
	void ResetGame( void );

	// Releases resources
	void FreeResources( rs_level_t level, bool clearall );

public:
	// Plays a sound file
	void PlaySound( const char *sample, const Vector* pOrigin = nullptr, Int32 flags = SND_FL_NONE, Int32 channel = SND_CHAN_AUTO, float volume = VOL_NORM, Int32 pitch = PITCH_NORM, float attenuation = ATTN_NORM, cl_entity_t *entity = nullptr, entindex_t entindex = 0, Int32 svindex = -1, float timeoffs = 0 );
	// Updates a playing sound
	void UpdateSound( const char *sample, const Vector* pOrigin = nullptr, Int32 flags = SND_FL_NONE, Int32 channel = SND_CHAN_AUTO, float volume = VOL_NORM, Int32 pitch = PITCH_NORM, float attenuation = ATTN_NORM, cl_entity_t *entity = nullptr, entindex_t entindex = 0, Int32 svindex = -1, float timeoffs = 0 );
	// Stops a sound on an entity's given channel
	void StopSound( entindex_t entindex, Int32 channel );
	// Applies a sound effect
	void ApplySoundEffect( entindex_t entindex, const char *sample, Int32 channel, snd_effects_t effect, float duration, float targetvalue );
	// Applies a sound effect with a server index
	void ApplySoundEffect( entindex_t entindex, Int32 svindex, Int32 channel, snd_effects_t effect, float duration, float targetvalue );
	// Tells if a sound is available on a given entity with the given parameters
	bool IsSoundPlaying( entindex_t entindex, Int32 svindex, Int32 channel );
	// Tells if a sound is available on a given entity with the given parameters
	bool IsSoundPlaying( entindex_t entindex, const char *sample, Int32 channel );
	// Removes all sounds for an entity
	void FreeEntity( entindex_t entindex );
	// Draws debug info
	bool DrawNormal( void );

	// Stops all playing sounds
	void StopAllPlaying ( void );
	
	// Precaches a sound file
	snd_cache_t* PrecacheSound( const char *sample, Int32 serverindex, rs_level_t level, bool isforplayback = false );
	// Loads data for a sound cache entry
	bool LoadSoundData( const char *sample, snd_cache_t* pcache, Int32 serverindex, bool keepdata );

	// Precaches a server sound
	bool PrecacheServerSound( const char* sample, Int32 serverindex );
	// Caches a message
	void CacheMessage( const Vector* pOrigin, Int32 svindex, Int32 channel, Int32 flags, entindex_t entindex, Int32 pitch, float vol, float attn, bool isambient, float timeoffs );
	// Caches an effect
	void CacheEffect( entindex_t entindex, Int32 svindex, Int32 channel, snd_effects_t effect, float duration, float targetvalue );
	// Returns a sound file name for a server sound index
	const char* GetSoundFileForServerIndex( Int32 serverindex );

	// Plays and OGG file
	void PlayOgg( const char *sample, Int32 channel, float timeOffset, Int32 flags, float fadeInTime );
	// Stops and OGG file with fading
	void StopOggFade( const char *sample, Int32 channel, float fadeTime );
	// Stops an OGG file
	void StopOgg( Int32 channel = MUSIC_CHANNEL_ALL, bool menuAlso = false );

	// Pauses a music channel
	void PauseOggChannel( Int32 channel );
	// Un-pause ogg channel
	void UnPauseOggChannel( Int32 channel, float fadetime );

	// Sets the active reverb
	void SetActiveReverb( Int32 reverb );
	// Sets if all sounds should be killed
	void SetMuted( bool muted );
	// Tells if the sound engine is muted
	bool IsMuted( void ) const { return m_isMuted; }
	// Pauses all sounds that are currently playing
	void SetPauseAllSounds( bool paused ); 

	// Returns the duration of a sentence
	const CSentencesFile::sentence_t* GetSentence( Int32 index ) const;

	// Precaches an OGG file
	snd_oggcache_t* PrecacheOgg( const char *sample, rs_level_t level );

	// Set HRTF command
	void SetHRTFCommand( void );

private:
	// Kills a specific sound
	void KillSound( snd_active_t& sound );
	// Removes sound from the playing list
	static void RemovePlaying( snd_active_t& sound );
	// Tells if a sound should be playing
	bool ShouldPlay( snd_active_t *psound, const Vector& vieworg, double frametime, Int32 imsgnum, float gameVolume ) const;
	// Allocates a free sound slot
	snd_active_t* AllocSound( const char *sample, entindex_t entindex, Int32 flags, Int32 channel );
	// Retrieves sentence and/or cache data
	bool GetSoundCache( const char *sample, Int32 svindex, snd_cache_t*& psample, const CSentencesFile::sentence_t *& psentence, CString& filepath );

	// Prints engine states
	void PrintStats( void );

	// Calculates mouth movement from an 8-bit WAV
	static void CalcMouth8( snd_active_t& sound );
	// Calculates mouth movement from a 16-bit WAV
	static void CalcMouth16( snd_active_t& sound );
	// Calculates gain for a sound
	float CalcGain( const Vector& vieworg, snd_active_t *psound, float multval, float gameVolume ) const;

	// Updates music playback
	void UpdateMusicPlayback( const ref_params_t* pparams, float flmultval );
	// Updates music playback for a track
	bool UpdateMusicTrackPlayback( snd_music_t& track, const ref_params_t* pparams, float flmultval );
	// Updates reverb effects
	void UpdateReverb( ref_params_t *pparams );
	// Clears the sound cache
	void ClearCache( void );

	// Retreives the sync offset for a sound
	Int32 GetSyncOffset( const snd_cache_t *pcache, UInt32 index );
	// Streams an OGG file
	stream_result_t Stream( ALuint buffer, snd_music_t& track );

	// Loads sentences
	bool LoadSentences( void );

private:
	// Volume CVAR
	CCVar* m_pCVarVolume;
	// Game volume CVAR
	CCVar* m_pCVarGameVolume;
	// Music volume CVAR
	CCVar* m_pCVarMusicVolume;
	// Occlusion CVAR
	CCVar* m_pCVarOcclusion;
	// Debug CVAR
	CCVar* m_pCvarDebug;
	// On-demand load cvar
	CCVar* m_pCvarOnDemandLoad;

	// Device pointer
	ALCdevice* m_pDevice;
	// Context pointer
	ALCcontext* m_pContext;

	// OpenAL module
	void* m_hOpenALDLL;

	// Cache of precached sounds
	CLinkedList<snd_cache_t*> m_cachedSoundsList;
	// Cache of ogg files
	CLinkedList<snd_oggcache_t*> m_cachedOggFilesList;

	// Array of playing sounds
	CArray<snd_playing_t> m_playingSoundsArray;
	// Array of active sounds
	CArray<snd_active_t> m_activeSoundsArray;

	// List of missing sounds
	CArray<snd_missing_t> m_missingSoundsArray;

	// Active music track
	CLinkedList<snd_music_t*> m_musicTracksList;

	// Message cache
	CLinkedList<s_msg_cache_t*> m_msgCacheList;
	// Update message cache
	CLinkedList<s_msg_cache_t*> m_updateMsgCacheList;

	// true if we the sound engine is muted
	bool			m_isMuted;
	// true if all sounds are paused
	bool			m_allSoundsPaused;
	// true if HRTF is enabled
	bool			m_isHRTFEnabled;

private:
	LPALGENEFFECTS					alGenEffects;
	LPALDELETEEFFECTS				alDeleteEffects;
	LPALEFFECTI						alEffecti;
	LPALEFFECTF						alEffectf;
	LPALEFFECTFV					alEffectfv;

	LPALGENAUXILIARYEFFECTSLOTS		alGenAuxiliaryEffectSlots;
	LPALDELETEAUXILIARYEFFECTSLOTS	alDeleteAuxiliaryEffectSlots;
	LPALAUXILIARYEFFECTSLOTI		alAuxiliaryEffectSloti;
	LPALAUXILIARYEFFECTSLOTF		alAuxiliaryEffectSlotf;

private:
	// Flag for initialization status
	bool					m_bInitialized;

	// PAS data
	const Byte*				m_pPAS;
	// PAS buffer
	Byte*					m_pPASBuffer;

	// Reverb effect id
	ALuint					m_reverbEffect;
	// Reverb effect slot
	ALuint					m_effectSlot;
	// Current active reverb effect index
	Int32					m_activeReverb;
	// Last ideal reverb effect index
	Int32					m_lastActiveReverb;
	// Ideal reverb effect index
	Int32					m_idealReverb;

	// Missing sounds array
	CArray<snd_missing_t>	m_missingArray;

	// Sentences file manager
	CSentencesFile*			m_pSentencesFile;

private:
	// Reverb effects
	static const EFXEAXREVERBPROPERTIES g_pEAXEffects[NUM_REVERBS];
	// Multipliers for EAX effects
	static const float g_pEAXMultipliers[NUM_REVERBS];
};
extern CSoundEngine gSoundEngine;
#endif