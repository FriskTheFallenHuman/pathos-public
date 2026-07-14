/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CL_EFX_H
#define CL_EFX_H

#include "beam_shared.h"
#include "tracer.h"

struct cl_efxapi_t;
struct cl_dlight_t;
struct cl_entity_t;
struct tempentity_t;
struct beam_t;
struct tracer_t;

enum beam_types_t;
enum overlay_rendermode_t;
enum overlay_effect_t;
enum tracer_type_t;

extern void CL_SetFade( UInt32 layerindex, float duration, float holdtime, Int32 flags, const color24_t& color, Byte alpha, float timeoffset );
extern void CL_SetMotionBlur( bool active, float blurfade, bool override );
extern void CL_SetVignette( bool active, float strength, float radius );
extern void CL_SetFilmGrain( bool active, float strength );
extern void CL_SetBlackAndWhite( bool active, float strength );
extern void CL_SetChromatic( bool active, float strength );
extern void CL_SetScreenOverlay( Int32 layerindex, const char* pstrtexturename, overlay_rendermode_t rendermode, const Vector& rendercolor, float renderamt, overlay_effect_t effect, float effectspeed, float effectminalpha, float fadetime );
extern void CL_ClearScreenOverlay( Int32 layerindex, float fadetime );
extern void CL_SpawnParticleSystem( const Vector& origin, const Vector& direction, part_script_type_t scripttype, const char* pstrFilepath, Int32 id, entindex_t entindex, Int32 attachment, Int32 boneindex, Int32 attachflags );
extern void CL_RemoveParticleSystem( UInt32 id, entindex_t entindex, bool keepcached );
extern void CL_KillEntityParticleSystems( Int32 entindex );
extern void CL_PrecacheParticleScript( part_script_type_t type, const char* pstrFilepath );
extern void CL_CreateGenericDecal( const char *pstrname, const Vector& origin, const Vector& normal, Int32 flags, entindex_t entindex, float life, float fadetime, float growthtime );
extern void CL_DecalVBMEntity( const Vector& origin, const Vector& normal, decalgroupentry_t* pentry, cl_entity_t* pentity, Int32 flags );
extern CDecalList& CL_GetDecalList( void );
extern void CL_SetLightStyle( Int32 style, const char* pstrpattern, bool interpolate, float framerate );
extern void CL_AddCustomLightStyle( Int32 style, const char* pstrpattern, bool interpolate, float framerate );
extern void CL_FreeEntityData( entindex_t entindex, Int32 flags );
extern void CL_SetDayStage( daystage_t daystage );
extern void CL_SetSpecialFog( bool enablespecialfog );
extern cl_dlight_t* CL_AllocDynamicSpotLight( Int32 key, Int32 subkey, bool isstatic, bool noshadow, cl_entity_t *pentity );
extern cl_dlight_t* CL_AllocDynamicPointLight( Int32 key, Int32 subkey, bool isstatic, bool noshadow, cl_entity_t *pentity );
extern void CL_SetSkyboxParameters( const Vector& worldorigin, float skysize, float fogend, float fogstart, const Vector& fogcolor, Int32 skytexturesetindex, bool affectskybox, bool isactive );
extern void CL_SetFogParameters( entindex_t entindex, const Vector& color, float start, float end, bool affectsky, float blendtime );
extern void CL_CreateCableEntity( const Vector& start, const Vector& end, UInt32 depth, UInt32 width, UInt32 numsegments );
extern bool CL_SetupEntityVertexLightVBO( cl_entity_t* pentity, Int32 vlightoffset, UInt32 vertexcount, Byte* plightstyles );
extern cl_entity_t* CL_AllocStaticSpriteEntity( void );
extern void CL_BreakModel( const Vector& origin, const Vector& size, bm_velocity_t velmode, const Vector& velvector, UInt32 randomvelmin, UInt32 randomvelmax, float life, UInt32 num, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
extern void CL_Bubbles( const Vector& mins, const Vector& maxs, float height, UInt32 modelindex, UInt32 num, float speed );
extern void CL_BubbleTrail( const Vector& start, const Vector& end, float height, UInt32 modelindex, UInt32 num, float speed );
extern void CL_FunnelSprite( const Vector& origin, const Vector& color, float alpha, UInt32 modelindex, bool reverse );
extern void CL_SphereModel( const Vector& origin, float speed, float life, UInt32 num, UInt32 modelindex, float buoyancy, float waterfriction, Int32 sound );
extern tempentity_t* CL_TempModel( const Vector& origin, const Vector& velocity, const Vector& angles, float life, UInt32 modelindex, Int32 sound, float buoyancy, float waterfriction, Int32 flags );
extern tempentity_t* CL_TempSprite( const Vector& origin, const Vector& velocity, float scale, UInt32 modelindex, Int32 rendermode, Int32 renderfx, float alpha, float life, Int32 sound, Int32 flags );
extern void CL_ParticleExplosion1( const Vector& origin );
extern void CL_ParticleExplosion2( const Vector& origin, UInt32 colorstart, UInt32 colorlength );
extern void CL_BlobExplosion( const Vector& origin );
extern void CL_RocketExplosion( const Vector& origin, UInt32 color );
extern void CL_ParticleEffect( const Vector& origin, const Vector& velocity, UInt32 color, UInt32 count );
extern void CL_LavaSplash( const Vector& origin );
extern void CL_TeleportSplash( const Vector& origin );
extern void CL_RocketTrail( const Vector& start, const Vector& end, UInt32 type );
extern void CL_CreateSparkStreak( const Vector& origin, UInt32 count, const Vector& color, float alpha, float width, float length, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );
extern void CL_CreateStreakSplash( const Vector& origin, const Vector& direction, const Vector& color, float alpha, float width, float length, UInt32 count, float speed, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );
extern void CL_CreateLargeFunnel( const Vector& origin, bool reverse );
extern void CL_CreateBloodStream( const Vector& origin, const Vector& direction, UInt32 color, float speed );
extern void CL_CreateBloodParticles( const Vector& origin, const Vector& direction, UInt32 color, float speed );
extern void CL_CreateTracerImplosion( const Vector& destination, float radius, UInt32 count, float life, const Vector& color, float alpha, float width, float length, bool reverse );
extern void CL_InitEffectsInterface( cl_efxapi_t &efxAPI );
extern void CL_SetGaussianBlur( bool active, float alpha );
extern cl_entity_t* CL_AllocTempSpriteEntity( Int32 key, float life );
extern mlight_t* CL_AllocEntityLight( Int32 key, float life, Int32 attachment );
extern beam_t* CL_BeamLightning( const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, Int32 flags );
extern beam_t* CL_BeamCirclePoints( beam_types_t type, const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
extern beam_t* CL_BeamEntityPoint( entindex_t startentity, Int32 attachment, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
extern beam_t* CL_BeamEntities( entindex_t startentity, entindex_t endentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
extern beam_t* CL_BeamFollow( entindex_t startentity, Int32 attachment, Int32 modelindex, float life, float width, float brightness, float r, float g, float b );
extern beam_t* CL_BeamPoints( const Vector& src, const Vector& end, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
extern beam_t* CL_BeamRing( entindex_t startentity, entindex_t endentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, float life, float width, float amplitude, float brightness, float speed, float noisespeed, UInt32 startframe, float framerate, float r, float g, float b, Int32 flags );
extern beam_t* CL_BeamVaporTrail( const Vector& src, const Vector& end, Int32 modelindex1, Int32 modelindex2, float colorfadedelay, float colorfadetime, float life, float width, float brightness, float r1, float g1, float b1, float r2, float g2, float b2, Int32 flags );
extern void CL_KillEntityBeams( entindex_t entityindex );
extern void CL_CreateBlackHole( Int32 key, const Vector& origin, float life, float scale, float strength, float rotation, float growthtime, float shrinktime );
extern void CL_KillBlackHole( Int32 key );
extern void CL_SetSunFlare( entindex_t entindex, bool active, float pitch, float roll, float scale, const Vector& color, bool portalSunFlare );
extern void CL_AddSkyTextureSet( const char* pstrSkyTextureName, Int32 skysetindex );
extern void CL_SetSkyTexture( Int32 skysetindex );
extern tracer_t* CL_CreateTracer( const Vector& origin, const Vector& velocity, const Vector& color, float alpha, float width, float length, float life, tracer_type_t type );
#endif //CL_EFX_H