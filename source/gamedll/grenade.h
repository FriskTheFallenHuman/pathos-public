/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef GRENADE_H
#define GRENADE_H

#include "animatingentity.h"

//=============================================
//
//=============================================
class CGrenade : public CAnimatingEntity
{
public:
	// Model file path
	static const char MODEL_FILENAME[];

public:
	explicit CGrenade( edict_t* pedict );
	virtual ~CGrenade( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;

public:
	void EXPORTFN BounceTouch( CBaseEntity* pOther );
	void EXPORTFN SlideTouch( CBaseEntity* pOther );
	void EXPORTFN ExplodeTouch( CBaseEntity* pOther );

	void EXPORTFN DangerSoundThink( void );
	void EXPORTFN TumbleThink( void );

public:
	void EXPORTFN Explode( void );
	void BounceSound( void );

public:
	void SetExplodeTime( float explodeTime );
	void SetExplodeDelay( float delay );
	void SetDamageAmount( float dmgAmount );
	void SetDamageRadius( float dmgRadius );
	void SetDamageTime( float dmgtime );
	void SetAttacker( CBaseEntity* pAttacker );
	void SetWeapon( CPlayerWeapon* pWeapon );

public:
	static CGrenade* CreateTimed( CBaseEntity* pOwner, const Vector& origin, const Vector& velocity, float time, float radius, float damage, bool contactDelayCountdown = false, CPlayerWeapon* pWeapon = nullptr );
	static CGrenade* CreateContact( CBaseEntity* pOwner, const Vector& origin, const Vector& velocity, float radius, float damage, CPlayerWeapon* pWeapon = nullptr );

private:
	double m_nextDmgTime;
	double m_explodeTime;
	float m_explodeDelay;
	bool m_emittedNPCSound;

	float m_damageAmount;
	float m_damageRadius;
	CEntityHandle m_attacker;
	CEntityHandle m_hitEntity;
	CPlayerWeapon* m_pWeapon;
};
#endif //GRENADE_H