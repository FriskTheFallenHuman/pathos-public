/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CL_TEMPENTITIES_H
#define CL_TEMPENTITIES_H

#include "tempentity.h"

class CCVar;

/*
=================================
-Class: CTempEntityManager
-Description:

=================================
*/
class CTempEntityManager
{
public:
	// Tempentity allocation size
	static const UInt32 TEMPENT_ALLOC_SIZE;
	// One shard every n^3 units
	static const float SHARD_VOLUME;

public:
	CTempEntityManager( void );
	~CTempEntityManager( void );

public:
	// Initializes the class
	bool Init( void );
	// Shuts down the class
	void Shutdown( void );

	// Inits game objects
	bool InitGame( void );
	// Clears game objects
	void ClearGame( void );

public:
	// Allocates a tempentity
	tempentity_t* AllocTempEntity( const Vector& origin, const cache_model_t* pmodel );
	// Updates temporary entities
	void UpdateTempEntities( void );

	// Creates a sprite funnel effect
	void CreateFunnel( const Vector& origin, const Vector& color, float alpha, UInt32 modelindex, bool reverse );
	// Creates a box of gib models
	void CreateBreakModel( const Vector& origin, const Vector& size, bm_velocity_t velmode, const Vector& velvector, UInt32 randomvelmin, UInt32 randomvelmax, float life, UInt32 num, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
	// Creates a box of bubbles
	void CreateBubbles( const Vector& mins, const Vector& maxs, float height, UInt32 modelindex, UInt32 num, float speed );
	// Creates a trail of bubbles
	void CreateBubbleTrail( const Vector& start, const Vector& end, float height, UInt32 modelindex, UInt32 num, float speed );
	// Creates a spherical shower of models
	void CreateSphereModel( const Vector& origin, float speed, float life, UInt32 num, UInt32 modelindex, float buoyancy, float waterfriction, Int32 sound );
	// Creates a temporary model
	tempentity_t* CreateTempModel( const Vector& origin, const Vector& velocity, const Vector& angles, float life, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
	// Creates a temporary sprite
	tempentity_t* CreateTempSprite( const Vector& origin, const Vector& velocity, float scale, UInt32 modelindex, Int32 rendermode, Int32 renderfx, float alpha, float life, Int32 sound, Int32 flags );

private:
	// Allocates new tempentity block
	void AllocateTempEntities( void );
	// Frees all active tempentities
	void FreeActiveTempEntities( void );
	// Frees a single tempentity
	void FreeTempEntity( tempentity_t* pfree );
	// Deletes all tempentities allocated
	void DeleteAllTempEntities( void );
	
	// Updates a single tempentity
	bool UpdateTempEntity( tempentity_t* ptemp ) const;

	// Plays a tempentity sound
	static void PlayTempEntitySound( tempentity_t *ptempentity, float volume );

private:
	// Linked list of free tempentities
	tempentity_t* m_pFreeTempEntityHeader;
	// Linked list of acitve tempentities
	tempentity_t* m_pActiveTempEntityHeader;

	// Tempentity allocation blocks
	CArray<tempentity_t*> m_pTempEntityAllocationBlocksArray;

	// Gravity CVar
	CCVar* m_pCvarGravity;
};
extern CTempEntityManager gTempEntities;
#endif //CL_TEMPENTITY_H