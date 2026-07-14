/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENVLIGHTNING
#define ENVLIGHTNING

#include "beam.h"
#include "envsprite.h"

//=============================================
//
//=============================================
class CEnvLightning : public CBeam
{
public:
	// Number of random loops
	static const UInt32 NUM_RANDOM_LOOPS;

public:
	explicit CEnvLightning( edict_t* pedict );
	virtual ~CEnvLightning( void );

public:
	// Spawns the entity
	virtual bool Spawn( void ) override;
	// Performs precache functions
	virtual void Precache( void ) override;
	// Calls for classes and their children
	virtual void DeclareSaveFields( void ) override;
	// Manages keyvalues
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	// Called after save-restoring an entity
	virtual bool Restore( void ) override;
	// Initializes the entity after map has done loading
	virtual void InitEntity( void ) override;

public:
	// Use function for striking the beam
	void EXPORTFN StrikeUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value );
	// Use function for toggling the beam
	void EXPORTFN ToggleUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value );

	// Called when striking
	void EXPORTFN StrikeThink( void );
	// Called when doing damage
	void EXPORTFN DamageThink( void );

	// Random spot finding
	void RandomArea( void );
	// Random point finding
	void RandomPoint( const Vector& src );
	// Zaps between start and end
	void Zap( const Vector& src, const Vector& end );
	// Tells if beam is server side 
	bool IsServerSide( void );
	// Updates beam variables
	void UpdateBeamVars( void );

	// Tells if the entity is a point entity
	bool IsPointEntity( CBaseEntity* pEntity );

public:
	// true if active
	bool m_isActive;
	// Start entity name
	string_t m_startEntityName;
	// End entity name
	string_t m_endEntityName;
	// Lifetime of beam
	float m_life;
	// Beam width
	float m_beamWidth;
	// Noise amplitude
	float m_noiseAmplitude;
	// Brightness
	UInt32 m_brightness;
	// Speed of scroll
	float m_speed;
	// Spead of beam noise
	float m_noiseSpeed;
	// Max delay before next strikg
	float m_strikeMaxDelay;
	// Sprite texture index
	Int32 m_spriteModelIndex;
	// Sprite model name
	string_t m_spriteModelName;
	// Start frame
	UInt32 m_startFrame;
	// Radius
	float m_radius;
	// true if tesla beam
	bool m_isTeslaBeam;
};
#endif //ENVLIGHTNING