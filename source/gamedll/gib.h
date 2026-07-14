/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef GIB_H
#define GIB_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CGib : public CBaseEntity
{
public:
	// Gib default lifetime
	static const float GIB_DEFAULT_LIFETIME;
	// Maximum gibs present ingame
	static const UInt32 MAX_ACTIVE_GIBS;
	// Max gib velocity
	static const float MAX_GIB_VELOCITY;
	// Maximum decals a gib can spawn
	static const UInt32 MAX_NB_DECALS;
	// Full Z velocity at full volume
	static const float FULL_VOLUME_VELOCITY;

public:
	enum gibbodyparts_t
	{
		GIB_RIBCAGE = 0,
		GIB_SKULL,
		GIB_HAND,
		GIB_HEART,
		GIB_BOWELS,
		GIB_THIGHBONE,
		GIB_KIDNEY,
		GIB_BONE,
		GIB_EYEBALL,
		GIB_MUSCLE,
		GIB_SPLEEN,
		GIB_RIBS,
		GIB_INTESTINES1,
		GIB_INTESTINES2,

		NB_GIBS
	};

public:
	static void ClearGibs( void );

public:
	explicit CGib( edict_t* pedict );
	virtual ~CGib( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual Int32 GetEntityFlags( void ) override;
	virtual void FreeEntity( edict_removed_t freeMode ) override;
	virtual bool CanBlackHolePull( void ) const override { return true; };

public:
	void EXPORTFN BounceTouch( CBaseEntity* pOther );
	void EXPORTFN WaitTillLand( void );

public:
	void LimitVelocity( void );

	void SetBloodColor( bloodcolor_t color );
	void SetLifeTime( float lifetime );
	void SetMaterial( Int32 material );

public:
	bool InitGib( const char* pstrModelname );

public:
	static void SpawnHeadGib( CBaseEntity* pVictim, const Vector* pflCenter, float minvel, float maxvel );
	static void SpawnChestGib( CBaseEntity* pVictim, const Vector* pflCenter, float minvel, float maxvel );
	static void SpawnRandomGibs( CBaseEntity* pVictim, UInt32 nbGibs, const Vector* pflCenter, float minvel, float maxvel );

private:
	Int32 m_bloodColor;
	Int32 m_numBloodDecals;
	Int32 m_material;
	float m_lifetime;

private:
	static UInt32 m_numGibs;
};
#endif //GIB_H