/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef FUNCBREAKABLE_H
#define FUNCBREAKABLE_H

#include "delayentity.h"
#include "weapons_shared.h"

//=============================================
//
//=============================================
class CFuncBreakable : public CDelayEntity
{
public:
	struct ammo_assocation_t
	{
		weaponid_t weaponId;
		const char* pstrAmmoName;
	};

public:
	// Spawn object types count
	static const UInt32 SPAWN_OBJECT_TYPES_COUNT = 6;
	// Object types spawned by breakable
	static const char* SPAWN_OBJECT_TYPES[SPAWN_OBJECT_TYPES_COUNT];
	// Wood gibs model file
	static const char GIB_MODEL_WOOD_FILENAME[];
	// Flesh gibs model file
	static const char GIB_MODEL_FLESH_FILENAME[];
	// Computer gibs model file
	static const char GIB_MODEL_COMPUTER_FILENAME[];
	// Glass gibs model file
	static const char GIB_MODEL_GLASS_FILENAME[];
	// Metal gibs model file
	static const char GIB_MODEL_METAL_FILENAME[];
	// Cinder block gibs model file
	static const char GIB_MODEL_CINDERBLOCKS_FILENAME[];
	// Rock gibs model file
	static const char GIB_MODEL_ROCK_FILENAME[];
	// Ceiling gibs model file
	static const char GIB_MODEL_CEILING_FILENAME[];

	// Wood damage sounds pattern
	static const char WOOD_DMG_SOUNDS_PATTERN[];
	// Wood break sounds pattern
	static const char WOOD_BREAK_SOUNDS_PATTERN[];
	// Flesh sounds pattern
	static const char FLESH_DMG_SOUNDS_PATTERN[];
	// Glass damage sounds pattern
	static const char GLASS_DMG_SOUNDS_PATTERN[];
	// Glass break sounds pattern
	static const char GLASS_BREAK_SOUNDS_PATTERN[];
	// Metal damage sounds pattern
	static const char METAL_DMG_SOUNDS_PATTERN[];
	// Metal break sounds pattern
	static const char METAL_BREAK_SOUNDS_PATTERN[];
	// Concrete damage sounds pattern
	static const char CONCRETE_DMG_SOUNDS_PATTERN[];
	// Concrete break sounds pattern
	static const char CONCRETE_BREAK_SOUNDS_PATTERN[];
	// Computer break sounds pattern
	static const char COMPUTER_DMG_SOUNDS_PATTERN[];

	// Gib model lifetime
	static const float GIB_MODEL_LIFETIME;

	// Weapon->ammo associations
	static const ammo_assocation_t WPN_AMMO_ASSOCIATIONS[NUM_WEAPONS];

public:
	enum
	{
		FL_BREAK_ON_TRIGGER_ONLY	= (1<<0),
		FL_BREAK_ON_TOUCH			= (1<<1),
		FL_BREAK_ON_PRESSURE		= (1<<2),
		FL_BREAK_CLUB				= (1<<8),
		FL_NO_GIBS					= (1<<9),
		FL_NO_PENETRATION_DAMAGE	= (1<<10),
		FL_SMART_AMMO_SPAWN			= (1<<11)
	};

	enum breakdirection_t
	{
		BREAKDIR_FROM_CENTER = 0,
		BREAKDIR_ATTACKDIR,
		BREAKDIR_RANDOM,
	};

public:
	explicit CFuncBreakable( edict_t* pedict );
	virtual ~CFuncBreakable( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual bool IsFuncBreakableEntity( void ) const override;
	virtual Int32 GetEntityFlags( void ) override { return CDelayEntity::GetEntityFlags() & ~FL_ENTITY_TRANSITION; }
	virtual void SetBoundingBox( void ) { }

	virtual bool TakeDamage( CBaseEntity* pInflictor, CBaseEntity* pAttacker, float amount, Int32 damageFlags ) override;
	virtual void TraceAttack( CBaseEntity* pAttacker, float damage, const Vector& direction, trace_t& tr, Int32 damageFlags ) override;

	virtual Vector GetEyePosition( bool addlean = false, bool usebone = false ) const override { return GetBrushModelCenter(); };
	virtual Vector GetNavigablePosition( void ) const override { return GetBrushModelCenter(); }

public:
	void EXPORTFN BreakTouch( CBaseEntity* pOther );
	void EXPORTFN DieThink( void );

	void PlayDamageSound( void );
	void SetPrecacheObjects( void );

	Int32 GetExplosionMagnitude( void ) const;
	void SetExplosionMagnitude( Int32 magnitude );

public:
	virtual void SetSpawnProperties( void );

protected:
	Int32 m_material;
	Int32 m_breakDirection;
	Int32 m_tempentSoundFlag;

	Int32 m_breakModelIndex;
	float m_angle;
	Int32 m_explodeMagnitude;

	string_t m_gibModelName;
	string_t m_spawnEntityName;

	string_t m_dmgSoundsPattern;
	UInt32 m_nbDmgSounds;

	string_t m_breakSoundsPattern;
	UInt32 m_nbBreakSounds;

	UInt32 m_spawnChance;

	CEntityHandle m_attacker;

	Vector m_breakVector;
	float m_breakDamage;
};
#endif //FUNCBREAKABLE_H