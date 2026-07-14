/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef TRIGGERCAMERA_H
#define TRIGGERCAMERA_H

#include "delayentity.h"

//=============================================
//
//=============================================
class CTriggerCamera : public CDelayEntity
{
public:
	// Default angular speed
	static const float DEFAULT_ANGULAR_SPEED;

public:
	enum
	{
		FL_PLAYER_POSITION		= (1<<0),
		FL_PLAYER_TARGET		= (1<<1),
		FL_PLAYER_TAKECONTROL	= (1<<2),
		FL_LOCKON				= (1<<3)
	};

public:
	explicit CTriggerCamera( edict_t* pedict );
	virtual ~CTriggerCamera( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual void SendInitMessage( const CBaseEntity* pPlayer ) override;

public:
	void Move( void );
	void EXPORTFN FollowTarget( void );

private:
	CBaseEntity* m_pPlayerEntity;
	CEntityHandle m_targetEntity;

	CBaseEntity* m_pPathEntity;

	string_t m_sPathEntityName;

	float m_waitTime;
	double m_returnTime;
	double m_stopTime;

	float m_moveDistance;
	float m_targetSpeed;
	float m_initialSpeed;
	float m_acceleration;
	float m_deceleration;
	float m_angularSpeed;

	bool m_isActive;
};
#endif //TRIGGERCAMERA_H