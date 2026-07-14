/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef BEAM_H
#define BEAM_H

#include "delayentity.h"
#include "beam_shared.h"

//=============================================
//
//=============================================
class CBeam : public CBaseEntity
{
public:
	enum
	{
		FL_START_ON			= (1<<0),
		FL_TOGGLE			= (1<<1),
		FL_RANDOM			= (1<<2),
		FL_RING				= (1<<3),
		FL_START_SPARKS		= (1<<4),
		FL_END_SPARKS		= (1<<5),
		FL_DECAL_END		= (1<<6),
		FL_SHADE_START		= (1<<7),
		FL_SHADE_END		= (1<<8),
		FL_TEMPORARY		= (1<<9),
		FL_NO_FADING		= (1<<10)
	};
public:
	explicit CBeam( edict_t* pedict );
	virtual ~CBeam( void );

public:
	// Spawns the entity
	virtual bool Spawn( void ) override;
	// Called after save-restoring an entity
	virtual bool Restore( void ) override;
	// Performs precache functions
	virtual void Precache( void ) override;
	// Calls for classes and their children
	virtual void DeclareSaveFields( void ) override;
	// Returns entity's flags
	virtual Int32 GetEntityFlags( void ) override;
	// Returns the entity's center
	virtual Vector GetCenter( void ) override;
	// Tells if entity should set bounds on restore
	virtual bool ShouldSetBoundsOnRestore( void ) override { return false; }

public:
	// Called when touched
	void EXPORTFN TriggerTouch( CBaseEntity* pOther );
	// Relinks the beam to the world
	void RelinkBeam( void );

	// Creates random sparks
	void BeamSparks( const Vector& start, const Vector& end );
	// Picks a random entity with the targetname
	CBaseEntity* GetRandomTargetName( const char* pstrName );
	// Deals beam damage
	void BeamDamage( trace_t& tr );
	// Initializes a beam
	bool BeamInit( const char* pstrSpriteName, float width );
	// Initializes a points beam
	void BeamInitPoints( const Vector& start, const Vector& end );
	// Initializes a beam connecting two entities
	void BeamInitEntities( CBaseEntity* pStartEntity, CBaseEntity* pEndEntity );
	// Initializes a beam connecting an entity and a point
	void BeamInitPointEntity( CBaseEntity* pStartEntity, const Vector& end );

public:
	// Sets the beam type
	DO_INLINE void SetBeamType( beam_msgtype_t type );
	// Returns the beam type
	DO_INLINE beam_msgtype_t GetBeamType( void ) const;
	// Sets a beam flag
	DO_INLINE void SetBeamFlags( Int32 flags );
	// Returns the beam flags
	DO_INLINE Int32 GetBeamFlags( void ) const;
	// Sets the start position
	DO_INLINE void SetBeamStartPosition( const Vector& position );
	// Returns the beam's starting position
	DO_INLINE const Vector& GetBeamStartPosition( void ) const;
	// Sets the end position
	DO_INLINE void SetBeamEndPosition( const Vector& position );
	// Returns the beam's starting position
	DO_INLINE const Vector& GetBeamEndPosition( void ) const;

	// Sets the start entity attachment
	DO_INLINE void SetBeamStartEntityAttachment( Int32 attachmentindex );
	// Returns the start entity attachment
	DO_INLINE Int32 GetBeamStartEntityAttachment( void );
	// Sets the end entity attachment
	DO_INLINE void SetBeamEndEntityAttachment( Int32 attachmentindex );
	// Returns the end entity attachment
	DO_INLINE Int32 GetBeamEndEntityAttachment( void );

	// Sets the start entity
	DO_INLINE void SetBeamStartEntity( CBaseEntity* pEntity );
	// Returns the start entity index
	DO_INLINE CBaseEntity* GetBeamStartEntity( void );
	// Sets the end entity
	DO_INLINE void SetBeamEndEntity( CBaseEntity* pEntity );
	// Returns the start entity index
	DO_INLINE CBaseEntity* GetBeamEndEntity( void );

	// Sets the texture of the beam
	DO_INLINE bool SetBeamTexture( Int32 spriteindex );
	// Sets the texture of the beam
	DO_INLINE bool SetBeamTexture( const char* pstrSpriteName );
	// Returns the sprite index
	DO_INLINE Int32 GetBeamTexture( void ) const;
	// Sets the width of the beam
	DO_INLINE void SetBeamWidth( float width );
	// Returns the beam width
	DO_INLINE float GetBeamWidth( void ) const;
	// Sets the amplitude of the beam
	DO_INLINE void SetBeamAmplitude( float amplitude );
	// Returns the beam amplitude
	DO_INLINE float GetBeamAmplitude( void ) const;
	// Sets the color of the beam
	DO_INLINE void SetBeamColor( Int32 r, Int32 g, Int32 b );
	// Returns the beam color
	DO_INLINE const Vector& GetBeamColor( void ) const;
	// Sets the brightness of the beam
	DO_INLINE void SetBeamBrightness( float brightness );
	// Returns the beam brightness
	DO_INLINE float GetBeamBrightness( void ) const;
	// Sets the current frame
	DO_INLINE void SetBeamFrame( float frame );
	// Returns the beam frame
	DO_INLINE float GetBeamFrame( void ) const;
	// Sets the scroll rate
	DO_INLINE void SetBeamScrollRate( float speed );
	// Returns the scroll rate
	DO_INLINE float GetBeamScrollRate( void ) const;
	// Sets the noise speed
	DO_INLINE void SetBeamNoiseSpeed( float speed );
	// Returns the noise speed
	DO_INLINE float GetBeamNoiseSpeed( void ) const;

	// Sets the beam to die after the given amount of time
	DO_INLINE void LiveForTime( float time );
	// Deal instant damage
	DO_INLINE void BeamDamageInstant( trace_t& tr, float damage );

public:
	// Creates a beam object
	static CBeam* CreateBeam( const char* pstrSpriteName, float width );

protected:
	// Last time we were animated
	double m_lastTime;
	// Max frame count
	float m_maxFrame;
	// Damage dealt
	float m_beamDamage;
	// Last damage time
	double m_dmgTime;
	// Start entity
	CEntityHandle m_startEntity;
	// End entity
	CEntityHandle m_endEntity;
	// Beam end position
	Vector m_endPosition;
	// Start entity attachment index
	Int32 m_attachment1Index;
	// Start entity attachment index
	Int32 m_attachment2Index;
};
#include "beam_inline.hpp"
#endif //BEAM_H