/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef FUNCPUSHABLE_H
#define FUNCPUSHABLE_H

#include "funcbreakable.h"

//=============================================
//
//=============================================
class CFuncPushable : public CFuncBreakable
{
public:
	enum
	{
		FL_BREAKABLE = (1<<7)
	};
public:
	// Default push sound pattern
	static const char PUSHABLE_DEFAULT_PUSH_SOUND[];
	// Maximum friction
	static const float MAX_FRICTION;
	// Minimum sound delay time
	static const float MIN_SOUND_DELAY;

public:
	explicit CFuncPushable( edict_t* pedict );
	virtual ~CFuncPushable( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual void CallTouch( CBaseEntity* pOther ) override;
	virtual bool TakeDamage( CBaseEntity* pInflictor, CBaseEntity* pAttacker, float amount, Int32 damageFlags ) override;
	virtual Int32 GetEntityFlags( void ) override { return (CDelayEntity::GetEntityFlags() & ~FL_ENTITY_TRANSITION) | FL_ENTITY_CONTINOUS_USE; }
	virtual bool CanBlackHolePull( void ) const override { return true; };
	virtual bool IsFuncPushableEntity( void ) const override { return true; }

public:
	float GetMaxSpeed( void ) const;
	void Move( CBaseEntity* pEntity, bool push );
	
private:
	// Push sounds pattern
	string_t m_pushSoundsPattern;
	// Number of push sounds
	UInt32 m_nbPushSounds;
	// Maximum speed
	float m_maxSpeed;
	// Next sound time
	double m_nextSoundTime;
};
#endif //FUNCPUSHABLE_H