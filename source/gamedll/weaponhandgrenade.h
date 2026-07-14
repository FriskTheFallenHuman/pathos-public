/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef WEAPONDEAGLE_H
#define WEAPONDEAGLE_H

#include "playerweapon.h"

//=============================================
//
//=============================================
class CWeaponHandGrenade : public CPlayerWeapon
{
public:
	enum weapon_anims_t
	{
		HANDGRENADE_IDLE = 0,
		HANDGRENADE_FIDGET,
		HANDGRENADE_PINPULL,
		HANDGRENADE_PINPULL_TOSS,
		HANDGRENADE_THROW1,
		HANDGRENADE_THROW2,
		HANDGRENADE_THROW3,
		HANDGRENADE_TOSS,
		HANDGRENADE_DRAW,
		HANDGRENADE_HOLSTER,

		// Must be last
		NUM_WEAPON_ANIMATIONS
	};

public:
	// Weapon view model
	static const char WEAPON_VIEWMODEL[];
	// Weapon weight
	static const Int32 WEAPON_WEIGHT;
	// Weapon slot
	static const Int32 WEAPON_SLOT;
	// Weapon slot position
	static const Int32 WEAPON_SLOT_POSITION;
	// Default ammo for weapon
	static const UInt32 WEAPON_DEFAULT_GIVE;
	// Grenade explosion delay
	static const float GRENADE_EXPLODE_DELAY;
	// Grenade cooking cut-off time
	static const float GRENADE_CUTOFF_TIME;

public:
	explicit CWeaponHandGrenade( edict_t* pedict );
	virtual ~CWeaponHandGrenade( void );

public:
	virtual void SetSpawnProperties( void ) override;
	virtual void Precache( void ) override;

	virtual bool GetWeaponInfo( weaponinfo_t* pWeapon ) override;

	virtual bool Deploy( void ) override;
	virtual bool CanHolster( void ) override;
	virtual void Holster( void ) override;

	virtual void PrimaryAttack( void ) override;
	virtual void SecondaryAttack( void ) override;
	virtual void Idle( void ) override;
	virtual void PostThink( void ) override;

public:
	void Begin( bool istossing );
	void SpawnPin( const Vector& origin, const Vector& angles, const Vector& velocity );

private:
	// Throw start time
	double m_throwStartTime;
	// Throw release time
	double m_throwReleaseTime;
	// true if we're tossing the grenade
	bool m_isTossing;

private:
	// Sequence names for weapon
	static const char* m_sequenceNames[NUM_WEAPON_ANIMATIONS];
};
#endif //WEAPONDEAGLE_H