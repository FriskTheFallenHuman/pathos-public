/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENVBEAMFX_H
#define ENVBEAMFX_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvBeamFX : public CPointEntity
{
public:
	enum
	{
		FL_START_ON = (1<<0)
	};

	enum fxtype_t
	{
		FX_BEAMDISK = 0,
		FX_BEAMTORUS,
		FX_BEAMCYLINDER
	};

public:
	explicit CEnvBeamFX( edict_t* pedict );
	virtual ~CEnvBeamFX( void );

public:
	// Spawns the entity
	virtual bool Spawn( void ) override;
	// Performs precache functions
	virtual void Precache( void ) override;
	// Calls for classes and their children
	virtual void DeclareSaveFields( void ) override;
	// Manages keyvalues
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	// Calls use function
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;

public:
	// Repeat think function
	void EXPORTFN RepeatThink( void );
	// Spawns the effect
	void CreateEffect( void );

private:
	// Beam type
	Int32 m_beamType;
	// Sprite model name
	string_t m_spriteModelName;
	// Radius of beam
	float m_beamRadius;
	// Start frame
	UInt32 m_startFrame;
	// Lifetime of beam
	float m_life;
	// Beam width
	float m_width;
	// Beam noise
	float m_beamNoise;
	// Beam noise speed
	float m_noiseSpeed;
	// Beam speed
	float m_beamSpeed;
	// Min repeat delay
	float m_repeatMinDelay;
	// Max repeat delay
	float m_repeatMaxDelay;
	// true if active
	bool m_isActive;
};
#endif //ENVBEAMFX_H