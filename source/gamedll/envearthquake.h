/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENVBLUR
#define ENVBLUR

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvEarthQuake : public CPointEntity
{
public:
	explicit CEnvEarthQuake( edict_t* pedict );
	virtual ~CEnvEarthQuake( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;

public:
	EXPORTFN void QuakeThink( void );

protected:
	// Minimum delay
	float m_minDelay;
	// Maximum delay
	float m_maxDelay;

	// Minimum force
	float m_minForce;
	// Maximum force
	float m_maxForce;

	// Duration
	float m_duration;
	// Fade out time
	float m_fadeTime;

	// Shake end time
	double m_shakeBeginTime;
};
#endif //ENVBLUR