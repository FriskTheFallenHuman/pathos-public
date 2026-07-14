/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef NPCSECURITYDEAD_H
#define NPCSECURITYDEAD_H

#include "ai_basenpc.h"

//=============================================
//
//=============================================
class CNPCSecurityDead : public CBaseNPC
{
public:
	// Model name for the npc
	static const char NPC_MODEL_NAME[];
	// Bodygroup name for guns
	static const char NPC_BODYGROUP_WEAPONS_NAME[];
	// Submodel name for blank weapon
	static const char NPC_SUBMODEL_WEAPON_BLANK_NAME[];

public:
	// Number of poses available
	static const UInt32 NPC_NB_CORPSE_POSES = 4;
	// Pose sequence names for corpse
	static const char* NPC_CORPSE_POSES[NPC_NB_CORPSE_POSES];

public:
	explicit CNPCSecurityDead( edict_t* pedict );
	virtual ~CNPCSecurityDead( void );

public:
	// Spawns the entity
	virtual bool Spawn( void ) override;
	// Manages a keyvalue
	virtual bool KeyValue( const keyvalue_t& kv ) override;

public:
	// Sets the ideal yaw speed
	virtual void SetYawSpeed( void ) override { };
	// Returns the sound mask for the NPC
	virtual UInt64 GetSoundMask( void ) override;
	// Returns the gun position
	virtual Vector GetGunPosition( stance_t stance = STANCE_ACTUAL ) override { return m_pState->origin; }

private:
	// Pose used by corpse
	UInt32 m_corpsePose;
};
#endif //NPCSECURITYDEAD_H