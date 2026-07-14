/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef EFXAPI_H
#define EFXAPI_H

#include "beam_shared.h"
#include "tracer.h"

struct cl_dlight_t;
struct cl_entity_t;
struct decalgroupentry_t;
struct tempentity_t;
struct mlight_t;
struct beam_t;
struct tracer_t;

enum overlay_rendermode_t;
enum overlay_effect_t;

struct cl_efxapi_t
{
	// Miscellanous
	cl_entity_t*			(*pfnAllocStaticSpriteEntity)( void );
	cl_entity_t*			(*pfnAllocTempSpriteEntity)( Int32 key, float life );

	void					(*pfnCreateCableEntity)( const Vector& start, const Vector& end, UInt32 depth, UInt32 width, UInt32 numsegments );
	bool					(*pfnSetupEntityVertexLightVBO)( cl_entity_t* pentity, Int32 vlightoffset, UInt32 vertexcount, Byte* plightstyles );
	void					(*pfnSetFogParameters)( entindex_t entindex, const Vector& color, float start, float end, bool affectsky, float blendtime );
	void					(*pfnSetSkyboxParameters)( const Vector& worldorigin, float skysize, float fogend, float fogstart, const Vector& fogcolor, Int32 skytexturesetindex, bool affectskybox, bool isactive );
	mlight_t*				(*pfnAllocEntityLight)( Int32 key, float life, Int32 attachment );
	cl_dlight_t*			(*pfnAllocDynamicPointLight)( Int32 key, Int32 subkey, bool isstatic, bool noshadow, cl_entity_t *pentity );
	cl_dlight_t*			(*pfnAllocDynamicSpotLight)( Int32 key, Int32 subkey, bool isstatic, bool noshadow, cl_entity_t *pentity );
	void					(*pfnSetDayStage)( daystage_t daystage );
	void					(*pfnSetSpecialFog)( bool enablespecialfog );
	void					(*pfnFreeEntityData)( entindex_t entindex, Int32 flags );
	void					(*pfnSetLightStyle)( Int32 style, const char* pstrpattern, bool interpolate, float framerate );
	void					(*pfnAddCustomLightStyle)( Int32 style, const char* pstrpattern, bool interpolate, float framerate );

	// Decals
	CDecalList&				(*pfnGetDecalList)( void );
	void					(*pfnDecalVBMEntity)( const Vector& origin, const Vector& normal, decalgroupentry_t* pentry, cl_entity_t* pentity, Int32 flags );
	void					(*pfnCreateGenericDecal)( const char *pstrname, const Vector& origin, const Vector& normal, Int32 flags, entindex_t entindex, float life, float fadetime, float growthtime );

	// Particles
	void					(*pfnPrecacheParticleScript)( part_script_type_t type, const char* pstrFilepath );
	void					(*pfnRemoveParticleSystem)( UInt32 id, entindex_t entindex, bool keepcached );
	void					(*pfnSpawnParticleSystem)( const Vector& origin, const Vector& direction, part_script_type_t scripttype, const char* pstrFilepath, Int32 id, entindex_t entindex, Int32 attachment, Int32 boneindex, Int32 attachflags );
	void					(*pfnKillEntityParticleSystems)( Int32 entindex );

	// Post process
	void					(*pfnSetMotionBlur)( bool active, float blurfade, bool override );
	void					(*pfnSetVignette)(bool active, float strength, float radius);
	void					(*pfnSetFilmGrain)(bool active, float strength);
	void					(*pfnSetBlackAndWhite)(bool active, float strength);
	void					(*pfnSetChromatic)(bool active, float strength);
	void					(*pfnSetScreenOverlay)( Int32 layerindex, const char* pstrtexturename, overlay_rendermode_t rendermode, const Vector& rendercolor, float renderamt, overlay_effect_t effect, float effectspeed, float effectminalpha, float fadetime );
	void					(*pfnClearScreenOverlay)( Int32 layerindex, float fadetime );
	void					(*pfnSetFade)( UInt32 layerindex, float duration, float holdtime, Int32 flags, const color24_t& color, Byte alpha, float timeoffset );
	void					(*pfnSetGaussianBlur)( bool active, float alpha );

	// Temporary entities
	void					(*pfnBreakModel)( const Vector& origin, const Vector& size, bm_velocity_t velmode, const Vector& velvector, UInt32 randomvelmin, UInt32 randomvelmax, float life, UInt32 num, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
	void					(*pfnBubbles)( const Vector& mins, const Vector& maxs, float height, UInt32 modelindex, UInt32 num, float speed );
	void					(*pfnBubbleTrail)( const Vector& start, const Vector& end, float height, UInt32 modelindex, UInt32 num, float speed );
	void					(*pfnFunnelSprite)( const Vector& origin, const Vector& color, float alpha, UInt32 modelindex, bool reverse );
	void					(*pfnSphereModel)( const Vector& origin, float speed, float life, UInt32 num, UInt32 modelindex, float buoyancy, float waterfriction, Int32 sound );
	tempentity_t*			(*pfnTempModel)( const Vector& origin, const Vector& velocity, const Vector& angles, float life, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
	tempentity_t*			(*pfnTempSprite)( const Vector& origin, const Vector& velocity, float scale, UInt32 modelindex, Int32 rendermode, Int32 renderfx, float alpha, float life, Int32 sound, Int32 flags );
	tracer_t*				(*pfnCreateTracer)( const Vector& origin, const Vector& velocity, const Vector& color, float alpha, float width, float length, float life, tracer_type_t type );
	void					(*pfnCreateTracerImplosion)( const Vector& destination, float radius, UInt32 count, float life, const Vector& color, float alpha, float width, float length, bool reverse );
	void					(*pfnCreateSparkStreak)( const Vector& origin, UInt32 count, const Vector& color, float alpha, float width, float length, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );
	void					(*pfnCreateStreakSplash)( const Vector& origin, const Vector& direction, const Vector& color, float alpha, float width, float length, UInt32 count, float speed, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );

	// Legacy particle effects
	void					(*pfnParticleExplosion1)( const Vector& origin );
	void					(*pfnParticleExplosion2)( const Vector& origin, UInt32 colorstart, UInt32 colorlength );
	void					(*pfnBlobExplosion)( const Vector& origin );
	void					(*pfnRocketExplosion)( const Vector& origin, UInt32 color );
	void					(*pfnParticleEffect)( const Vector& origin, const Vector& velocity, UInt32 color, UInt32 count );
	void					(*pfnLavaSplash)( const Vector& origin );
	void					(*pfnTeleportSplash)( const Vector& origin );
	void					(*pfnRocketTrail)( const Vector& start, const Vector& end, UInt32 type );
	void					(*pfnCreateLargeFunnel)( const Vector& origin, bool reverse );
	void					(*pfnCreateBloodStream)( const Vector& origin, const Vector& direction, UInt32 color, float speed );
	void					(*pfnCreateBloodParticles)( const Vector& origin, const Vector& direction, UInt32 color, float speed );

	// Beam effects
	beam_t*					(*pfnBeamLightning)( const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, Int32 flags );
	beam_t*					(*pfnBeamCirclePoints)( beam_types_t type, const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
	beam_t*					(*pfnBeamEntityPoint)( entindex_t startentity, Int32 attachment, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
	beam_t*					(*pfnBeamEntities)( entindex_t startentity, entindex_t endentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
	beam_t*					(*pfnBeamFollow)( entindex_t startentity, Int32 attachment, Int32 modelindex, float life, float width, float brightness, float r, float g, float b );
	beam_t*					(*pfnBeamPoints)( const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
	beam_t*					(*pfnBeamRing)( entindex_t startentity, entindex_t endentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
	beam_t*					(*pfnBeamVaporTrail)( const Vector& src, const Vector& end, Int32 modelindex1, Int32 modelindex2, float colorfadedelay, float colorfadetime, float life, float width, float brightness, float r1, float g1, float b1, float r2, float g2, float b2, Int32 flags );
	void					(*pfnKillEntityBeams)( entindex_t entityindex );

	// Black holes
	void					(*pfnCreateBlackHole)( Int32 key, const Vector& origin, float life, float scale, float strength, float rotation, float growthtime, float shrinktime );
	void					(*pfnKillBlackHole)( Int32 key );

	// Sun flare
	void					(*pfnSetSunFlare)( entindex_t entindex, bool active, float pitch, float roll, float scale, const Vector& color, bool portalSunFlare );

	// Custom sky texture management
	void					(*pfnAddSkyTextureSet)( const char* pstrSkyTextureName, Int32 skysetindex );
	void					(*pfnSetSkyTexture)( Int32 skysetindex );
};
#endif //R_EFXAPI_H