/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENVBLACKHOLE_H
#define ENVBLACKHOLE_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvBlackHole : public CPointEntity
{
public:
	enum
	{
		FL_START_ON = (1<<0)
	};
public:
	explicit CEnvBlackHole( edict_t* pedict );
	virtual ~CEnvBlackHole( void );

public:
	virtual bool Spawn( void ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;

	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void SendInitMessage( const CBaseEntity* pPlayer ) override;

	void EXPORTFN SuckThink( void );
	void EXPORTFN DieThink( void );

protected:
	// true if black hole is active
	bool m_isActive;
	// Strength of the pull of the black hole
	float m_pullStrength;
	// Rotation speed
	float m_rotationSpeed;
	// Time it takes for the black hole to grow to full size
	float m_growthTime;
	// Time it takes for the black hole to shrink and disappear
	float m_shrinkTime;
	// Lifetime of the black hole
	float m_lifeTime;
	// Time when the black hole was spawned
	double m_spawnTime;
};

#endif //ENVBLACKHOLE_H