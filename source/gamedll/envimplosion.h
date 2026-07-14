/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef ENVIMPLOSION_H
#define ENVIMPLOSION_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvImplosion : public CPointEntity
{
public:
	// Default tracer color
	static const Vector DEFAULT_COLOR;

public:
	enum
	{
		FL_REVERSE_DIRECTION	= (1<<0),
		FL_REVERSE_INTENSITY	= (1<<1)
	};

public:
	explicit CEnvImplosion( edict_t* pedict );
	virtual ~CEnvImplosion( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	
private:
	void EXPORTFN SpawnThink( void );

private:
	float m_radius;
	UInt32 m_tracerCount;
	float m_life;
	float m_duration;
	double m_lastSpawnTime;
	UInt32 m_spawnCount;
	double m_spawnBeginTime;
	float m_tracerLength;
	float m_tracerWidth;
};
#endif //ENVIMPLOSION_H