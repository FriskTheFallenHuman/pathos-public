/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef ENVSHAKE_H
#define ENVSHAKE_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvShake : public CPointEntity
{
public:
	enum
	{
		FL_SHAKE_EVERYWHERE	= (1<<0),
		FL_DISRUPT_CONTROLS	= (1<<1),
		FL_SHAKE_INAIR		= (1<<2)
	};

public:
	explicit CEnvShake( edict_t* pedict );
	virtual ~CEnvShake( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	
public:
	float GetAmplitude( void );
	float GetFrequency( void );
	float GetDuration( void );
	float GetRadius( void );

	void SetAmplitude( float amplitude );
	void SetFrequency( float frequency );
	void SetDuration( float duration );
	void SetRadius( float radius );

private:
	float m_amplitude;
	float m_frequency;
	float m_duration;
	float m_radius;
};
#endif //ENVSHAKE_H