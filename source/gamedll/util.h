/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef UTIL_H
#define UTIL_H

#include "constants.h"
#include "snd_shared.h"
#include "beam_shared.h"
#include "trace.h"
#include "tracer.h"
#include "flex_shared.h"

enum part_script_type_t;
enum flextypes_t;
enum usemode_t;
enum beam_types_t;

namespace Util
{
	extern void RemoveEntity( CBaseEntity* pEntity );
	extern void RemoveEntity( edict_t* pEdict );
	extern edict_t* FindEntityByString( edict_t* pStartEntity, const char* pstrFieldName, const char* pstrValue );
	extern edict_t* FindEntityByClassname( edict_t* pStartEntity, const char* pstrValue );
	extern edict_t* FindEntityByTargetName( edict_t* pStartEntity, const char* pstrValue );
	extern edict_t* FindEntityByTarget( edict_t* pStartEntity, const char* pstrValue );
	extern edict_t* FindEntityInBBox( edict_t* pStartEntity, const Vector& mins, const Vector& maxs );
	extern void SetMoveDirection( entity_state_t& state );
	extern void SetAxisDirection( entity_state_t& state, Int32 flags, Int32 flagz, Int32 flagx );
	extern float GetAxisValue( Int32 flags, const Vector& angles, Int32 flagz, Int32 flagx );
	extern float GetAxisDelta( Int32 flags, const Vector& angle1, const Vector& angle2, Int32 flagz, Int32 flagx );
	extern void TraceLine( const Vector& start, const Vector& end, bool ignorenpcs, bool usehitboxes, bool ignoreglass, bool hitcorpses, const edict_t* pignoreent, trace_t& tr );
	extern void TraceLine( const Vector& start, const Vector& end, bool ignorenpcs, bool usehitboxes, bool ignoreglass, const edict_t* pignoreent, trace_t& tr );
	extern void TraceLine( const Vector& start, const Vector& end, bool ignorenpcs, bool usehitboxes, const edict_t* pignoreent, trace_t& tr );
	extern void TraceHull( const Vector& start, const Vector& end, bool ignorenpcs, bool usehitboxes, bool ignoreglass, hull_types_t hulltype, const edict_t* pignoreent, trace_t& tr );
	extern void TraceHull( const Vector& start, const Vector& end, bool ignorenpcs, bool usehitboxes, hull_types_t hulltype, const edict_t* pignoreent, trace_t& tr );
	extern void TraceModel( const CBaseEntity* pEntity, const Vector& start, const Vector& end, bool usehitboxes, hull_types_t hulltype, trace_t& tr );
	extern const char* TraceTexture( entindex_t hitentity, const Vector& position, const Vector& planeNormal );
	extern void FireTargets( const char* pstrtargetname, CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value );
	extern bool IsMasterTriggered( const char* pstrtargetname, const CBaseEntity* pentity, const CBaseEntity* pslave );
	extern bool IsNullEntity( const edict_t* pentity );
	extern bool IsNullEntity( const entindex_t entindex );
	extern bool IsVBMEntity( const edict_t* pentity );
	extern bool IsVBMEntity( const entindex_t entindex );
	extern class CBaseEntity* GetHostPlayer( void );
	extern class CBaseEntity* GetPlayerByIndex( UInt32 index );
	extern void WarnEmptyEntity( const edict_t* pentity );
	extern void EntityConPrintf( const edict_t* pentity, const char *fmt, ... );
	extern void EntityConDPrintf( const edict_t* pentity, const char *fmt, ... );
	extern void CreateParticles( const char* pstrscriptname, const Vector& origin, const Vector& direction, part_script_type_t type );
	extern void CreateParticles( const char* pstrscriptname, const Vector& origin, const Vector& direction, part_script_type_t type, const edict_t* pentity, UInt32 attachment, Int32 id, Int32 boneindex = NO_POSITION, Int32 attachflags = PARTICLE_ATTACH_NONE );
	extern void CreateTracer( const Vector& origin, const Vector& velocity, const Vector& color, float alpha, float width, float length, float life, tracer_type_t type );
	extern void PrecacheEntity( const char* pstrClassname );
	extern void ShowMessage( const char* pmsgname, CBaseEntity* pPlayer );
	extern void ShowMessageAllPlayers( const char* pmsgname );
	extern void EmitEntitySound( const CBaseEntity* pEntity, const char* pstrfilename, snd_channels_t channel, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE, const CBaseEntity* pPlayer = nullptr, float timeoffset = 0 );
	extern void EmitEntitySound( const CBaseEntity* pEntity, string_t filename, snd_channels_t channel, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE, const CBaseEntity* pPlayer = nullptr, float timeoffset = 0 );
	extern void EmitAmbientSound( const Vector& origin, const char* pstrfilename, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE, const CBaseEntity* pEntity = nullptr, const CBaseEntity* pPlayer = nullptr, float timeoffset = 0 );
	extern void EmitAmbientSound( const Vector& origin, string_t filename, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE, const CBaseEntity* pEntity = nullptr, const CBaseEntity* pPlayer = nullptr, float timeoffset = 0 );
	extern void StopEntitySounds( CBaseEntity* pEntity, snd_channels_t channel, const CBaseEntity* pPlayer = nullptr );
	extern void SpawnBloodParticles( const trace_t& tr, bloodcolor_t color, bool isplayer );
	extern void SpawnBloodParticles( const Vector& origin, const Vector& direction, bloodcolor_t color, bool isplayer );
	extern void SpawnBloodDecal( const trace_t& tr, bloodcolor_t color, bool decalvbm );
	extern void CreateGenericDecal( const Vector& origin, const Vector* pnormal, const char* pstrname, Int32 decalflags, entindex_t entindex = NO_ENTITY_INDEX, float life = 0, float fadetime = 0, float growthtime = 0, const edict_t* pplayer = nullptr );
	extern void CreateVBMDecal( const Vector& origin, const Vector& normal, const char* pstrname, const edict_t* pentity, Int32 decalflags );
	extern float GetDamageForce( const edict_t& entity, float damage );
	extern void ScreenFadePlayer( const edict_t* pplayer, const Vector& color, float fadetime, float fadeholdtime, Int32 alpha, Int32 flags, Int32 layer = 0, float timeoffset = 0 );
	extern void ScreenFadePlayer( const edict_t* pplayer, const color24_t& color, float fadetime, float fadeholdtime, Int32 alpha, Int32 flags, Int32 layer = 0, float timeoffset = 0 );
	extern void ScreenFadeAllPlayers( const Vector& color, float fadetime, float fadeholdtime, Int32 alpha, Int32 flags, Int32 layer = 0, float timeoffset = 0 );
	extern void ScreenFadeAllPlayers( const color24_t& color, float fadetime, float fadeholdtime, Int32 alpha, Int32 flags, Int32 layer = 0, float timeoffset = 0 );
	extern void Ricochet( const Vector &position, const Vector &direction, bool metalsound = false );
	extern Vector ClampVectorToBox( const Vector& vectoadj, const Vector& boxsize );
	extern CBaseEntity* FindEntityAtDirection( const Vector& origin, const Vector& angles, const edict_t* pedict );
	extern Int32 CalculateLightIllumination( const Vector& origin, const Vector& lightorigin, const Vector& lightcolor, float lightradius );
	extern Int32 GetIllumination( const Vector& position );
	extern void CreateImpactEffects( const trace_t& tr, const Vector& traceBegin, bool createDecal, bool vbmDecal = false, bool playSounds = true, const char* pstrDecalGroupName = nullptr );
	extern void MakeEntityDormant( edict_t* pedict );
	extern void CreateTempModel( const Vector& origin, const Vector& angles, const Vector& velocity, float life, UInt32 num, const char* pstrModelname, Int32 sound, float bouyancy, float waterfriction, Int32 flags, Int32 body );
	extern void CreateTempModel( const Vector& origin, const Vector& angles, const Vector& velocity, float life, UInt32 num, Int32 modelindex, Int32 sound, float bouyancy, float waterfriction, Int32 flags, Int32 body );
	extern void CreateBreakModel( const Vector& origin, const Vector& size, bm_velocity_t velocitymode, const Vector& velvector, UInt32 randomvelmin, UInt32 randomvelmax, float life, UInt32 num, const char* pstrModelname, Int32 sound, float bouyancy, float waterfriction, Int32 flags );
	extern void CreateBreakModel( const Vector& origin, const Vector& size, bm_velocity_t velocitymode, const Vector& velvector, UInt32 randomvelmin, UInt32 randomvelmax, float life, UInt32 num, Int32 modelindex, Int32 sound, float bouyancy, float waterfriction, Int32 flags );
	extern void CreateBubbles( const Vector& mins, const Vector& maxs, const float height, const char* pstrSpritename, UInt32 num, float speed );
	extern void CreateBubbles( const Vector& mins, const Vector& maxs, const float height, Int32 modelindex, UInt32 num, float speed );
	extern void CreateBubbleTrail( const Vector& start, const Vector& end, const float height, const char* pstrSpritename, UInt32 num, float speed );
	extern void CreateBubbleTrail( const Vector& start, const Vector& end, const float height, Int32 modelindex, UInt32 num, float speed );
	extern void CreateFunnelSprite( const Vector& origin, const Vector& color, float alpha, const char* pstrSpritename, bool reverse );
	extern void CreateFunnelSprite( const Vector& origin, const Vector& color, float alpha, Int32 modelindex, bool reverse );
	extern void CreateSphereModel( const Vector& origin, float speed, float life, UInt32 num, const char* pstrModelname, Int32 sound, float bouyancy, float waterfriction );
	extern void CreateSphereModel( const Vector& origin, float speed, float life, UInt32 num, Int32 modelindex, Int32 sound, float bouyancy, float waterfriction );
	extern void CreateTempSprite( const Vector& origin, const Vector& velocity, float life, float scale, const char* pstrSpritename, rendermode_t rendermode, Int32 renderfx, float alpha, Int32 sound, Int32 flags );
	extern void CreateTempSprite( const Vector& origin, const Vector& velocity, float life, float scale, Int32 modelindex, rendermode_t rendermode, Int32 renderfx, float alpha, Int32 sound, Int32 flags );
	extern void CreateParticleExplosion1( const Vector& origin );
	extern void CreateParticleExplosion2( const Vector& origin, Int32 colorstart, Int32 colorlength );
	extern void CreateBlobExplosion( const Vector& origin );
	extern void CreateRocketExplosion( const Vector& origin, Int32 color );
	extern void CreateParticleEffect( const Vector& origin, const Vector& velocity, Int32 color, UInt32 count );
	extern void CreateLavaSplash( const Vector& origin );
	extern void CreateTeleportSplash( const Vector& origin );
	extern void CreateRocketTrail( const Vector& start, const Vector& end, UInt32 type );
	extern void CreateSparkStreak( const Vector& origin, UInt32 count, const Vector& color, float alpha, float width, float length, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );
	extern void CreateStreakSplash( const Vector& origin, const Vector& direction, const Vector& color, float alpha, float width, float length, UInt32 count, float speed, float minLifetime, float maxLifetime, float minVelocity, float maxVelocity );
	extern void CreateLargeFunnel( const Vector& origin, bool reverse );
	extern void CreateBloodStream( const Vector& origin, const Vector& direction, UInt32 color, float speed );
	extern void CreateBloodParticles( const Vector& origin, const Vector& direction, UInt32 color, float speed );
	extern void CreateTracerImplosion( const Vector& destination, float radius, UInt32 count, float life, const Vector& color, float alpha, float width, float length, bool reverse );
	extern void PrecacheFixedNbSounds( const char* pstrPattern, UInt32 count );
	extern void PrecacheVariableNbSounds( const char* pstrPattern, UInt32& outcount );
	extern CString PlayRandomEntitySound( CBaseEntity* pEntity, const char* pstrPattern, Int32 count, snd_channels_t channel = SND_CHAN_AUTO, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE );
	extern CString PlayRandomAmbientSound( const Vector& origin, const char* pstrPattern, Int32 count, float volume = VOL_NORM, float attenuation = ATTN_NORM, Int32 pitch = PITCH_NORM, Int32 flags = SND_FL_NONE );
	extern void PlayWeaponClatterSound( const edict_t* pedict );
	extern void AlignEntityToSurface( edict_t* pedict );
	extern Vector GetRandomBloodVector( void );
	extern void ScreenShake( const Vector& origin, float amplitude, float frequency, float duration, float radius, bool inair = false, bool disruptcontrols = false );
	extern void ScreenShakeAll( const Vector& origin, float amplitude, float frequency, float duration );
	extern void CreateSparks( const Vector& origin );
	extern void CreateDynamicLight( const Vector& origin, float radius, Int32 r, Int32 g, Int32 b, float life, Int32 decay, float decaydelay, Byte flags, Int32 entindex = NO_ENTITY_INDEX, Int32 attachment = NO_POSITION, Int32 lightstyle = LS_NORMAL );
	extern void CreateDynamicLightWithSubkey( const Vector& origin, float radius, Int32 r, Int32 g, Int32 b, float life, Int32 decay, float decaydelay, Byte flags, Int32 entindex, Int32 subkey, Int32 attachment = NO_POSITION, Int32 lightstyle = LS_NORMAL );
	extern void ExplosionSound( const Vector& origin );
	extern void ReadColor24FromString( const char* pstrString, color24_t& outcolor );
	extern void ReadColor32FromString( const char* pstrString, color32_t& outcolor );
	extern float Approach( float target, float value, float speed );
	extern float ApproachAngle( float targetvalue, float curvalue, float speed );
	extern float AngleDistance( float next, float cur );
	extern void FixGroundEntities( const CBaseEntity* pGroundEntity, bool noDropToFloor = false );
	extern const char* GetDebrisSound( breakmaterials_t material );
	extern void PrecacheDebrisSounds( breakmaterials_t material );
	extern bool IsDataEmpty( const Byte* pdata, UInt32 size );
	extern void CreateRicochetEffect( const Vector& position, const Vector& normal );
	extern void PrecacheFlexScript( flextypes_t npctype, const char* pstrscriptname );
	extern bool IsInViewCone( const Vector& origin, const Vector& angles, float fieldOfView, const Vector& position );
	extern CBaseEntity* GetEntityFromTrace( const trace_t& tr );
	extern bool CheckTraceLine( const Vector& startPosition, const Vector& endPosition, bool ignoreNPCs = true, bool ignoreGlass = false, edict_t* pIgnoreEntity = nullptr );
	extern float VectorToYaw( const Vector& inVector );
	extern float VectorToPitch( const Vector& inVector );
	extern node_hull_types_t GetNodeHullForNPC( const CBaseEntity* pEntity );
	extern UInt64 GetNodeTypeForNPC( const CBaseEntity* pEntity );
	extern CBaseEntity* GetEntityByIndex( Int32 index );
	extern void FindLinkEntities( CBaseEntity* pLinkEntity, CArray<CBaseEntity*>& entitesArray, CBaseEntity* pNPC );
	extern void PrintScreenText( Int32 xcoord, Int32 ycoord, float lifetime, const char *fmt, ... );
	extern float DotPoints( const Vector& src, const Vector& check, const Vector& direction );
	extern bool CheckToss( CBaseEntity* pEntity, const Vector& spot1, const Vector& spot2, float gravityAdjust, Vector& outVelocity );
	extern bool CheckThrow( CBaseEntity* pEntity, const Vector& spot1, const Vector& spot2, float speed, float gravityAdjust, Vector& outVelocity );
	extern bool IsBoxVisible( CBaseEntity* pLooker, CBaseEntity* pTarget, Vector& targetOrigin, float size );
	extern void CreateBeamPoints( const Vector& startpos, const Vector& endpos, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamPoints( const Vector& startpos, const Vector& endpos, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamEntities( const CBaseEntity* pstartentity, const CBaseEntity* pendentity, Int32 attachment1, Int32 attachment2, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamEntities( const CBaseEntity* pstartentity, const CBaseEntity* pendentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamEntityPoint( const CBaseEntity* pentity, const Vector& endpos, Int32 attachment, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamEntityPoint( const CBaseEntity* pentity, const Vector& endpos, Int32 attachment, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamSprite( const Vector& startpos, const Vector& endpos, const char* pstrBeamSpriteName, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags, float sprscale, rendermode_t sprrendermode, float spralpha );
	extern void CreateBeamSprite( const Vector& startpos, const Vector& endpos, Int32 modelindex, Int32 sprmodelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags, float sprscale, rendermode_t sprrendermode, float spralpha );
	extern void CreateBeamTorus( const Vector& startpos, const Vector& endpos, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamTorus( const Vector& startpos, const Vector& endpos, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamDisk( const Vector& startpos, const Vector& endpos, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamDisk( const Vector& startpos, const Vector& endpos, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamCylinder( const Vector& startpos, const Vector& endpos, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamCylinder( const Vector& startpos, const Vector& endpos, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamOfType( beam_types_t type, const Vector& startpos, const Vector& endpos, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamFollow( const CBaseEntity* pentity, Int32 attachment, const char* pstrSpriteName, float life, float width, float brightness, float r, float g, float b );
	extern void CreateBeamFollow( const CBaseEntity* pentity, Int32 attachment, Int32 modelindex, float life, float width, float brightness, float r, float g, float b );
	extern void CreateBeamRing( const CBaseEntity* pstartentity, const CBaseEntity* pendentity, Int32 attachment1, Int32 attachment2, const char* pstrSpriteName, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void CreateBeamRing( const CBaseEntity* pstartentity, const CBaseEntity* pendentity, Int32 attachment1, Int32 attachment2, Int32 modelindex, UInt32 startframe, float framerate, float life, float width, float amplitude, float brightness, float speed, float noisespeed, float r, float g, float b, Int32 flags = FL_BEAM_NONE );
	extern void KillEntityBeams( const CBaseEntity* pentity );
	extern Int32 GetBoneIndexFromTrace( const trace_t& tr );
	extern Int64 GetBodyValueForSubmodel( const char* pstrModelName, const char* pstrSubmodelName );
};
#endif //UTIL_H