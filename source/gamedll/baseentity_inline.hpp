/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef BASEENTITY_INLINE_H
#define BASEENTITY_INLINE_H

#include "util.h"
#include "gamevars.h"

//=============================================
// @brief
//
//=============================================
DO_INLINE entindex_t CBaseEntity::GetEntityIndex( void ) const
{
	return m_pState->entindex;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const edict_t* CBaseEntity::GetEdict( void ) const
{
	return m_pEdict;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetOrigin( void ) const
{
	return m_pEdict->state.origin;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetAngles( void ) const
{
	return m_pEdict->state.angles;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetOrigin( const Vector& origin )
{
	m_pState->origin = origin;
	gd_engfuncs.pfnSetOrigin(m_pEdict, m_pState->origin);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetAngles( const Vector& angles )
{
	m_pState->angles = angles;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetVelocity( void ) const
{
	return m_pState->velocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetVelocity( const Vector& velocity )
{
	m_pState->velocity = velocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetAngularVelocity( void ) const
{
	return m_pState->avelocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetAngularVelocity( const Vector& velocity )
{
	m_pState->avelocity = velocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetBaseVelocity( void ) const
{
	return m_pState->basevelocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetBaseVelocity( const Vector& basevelocity )
{
	m_pState->basevelocity = basevelocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetFlags( UInt64 flagbits )
{
	m_pState->flags |= flagbits;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::RemoveFlags( UInt64 flagbits )
{
	m_pState->flags &= ~flagbits;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int64 CBaseEntity::GetFlags( void ) const
{
	return m_pState->flags;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasTargetName( void ) const
{
	return (m_pFields->targetname == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetTargetName( void ) const
{
	if(m_pFields->targetname == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->targetname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetTargetName( const char* pstrtargetname )
{
	if(!pstrtargetname || !qstrlen(pstrtargetname))
		m_pFields->targetname = NO_STRING_VALUE;
	else
		m_pFields->targetname = gd_engfuncs.pfnAllocString(pstrtargetname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetTargetName( const string_t targetname )
{
	m_pFields->targetname = targetname;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasModelName( void ) const
{
	return (m_pFields->modelname == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetModelName( void ) const
{
	if(m_pFields->modelname == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->modelname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetModelName( const char* pstrmodelname )
{
	if(!pstrmodelname || !qstrlen(pstrmodelname))
		m_pFields->modelname = NO_STRING_VALUE;
	else
		m_pFields->modelname = gd_engfuncs.pfnAllocString(pstrmodelname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetModelName( const string_t modelname )
{
	m_pFields->modelname = modelname;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int32 CBaseEntity::GetModelIndex( void ) const
{
	return m_pState->modelindex;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasTarget( void ) const
{
	return (m_pFields->target == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetTarget( void ) const
{
	if(m_pFields->target == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->target);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetTarget( const char* pstrtarget )
{
	if(!pstrtarget || !qstrlen(pstrtarget))
		m_pFields->target = NO_STRING_VALUE;
	else
		m_pFields->target = gd_engfuncs.pfnAllocString(pstrtarget);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetTarget( const string_t target )
{
	m_pFields->target = target;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetClassName( void ) const
{
	if(m_pFields->classname == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->classname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE takedamage_t CBaseEntity::GetTakeDamage( void ) const
{
	return (takedamage_t)m_pState->takedamage;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE solid_t CBaseEntity::GetSolidity( void ) const
{
	return (solid_t)m_pState->solid;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetSolidity( solid_t solid )
{
	m_pState->solid = solid;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetAbsMins( void ) const
{
	return m_pState->absmin;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetAbsMaxs( void ) const
{
	return m_pState->absmax;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetMinsMaxs( const Vector& mins, const Vector& maxs )
{
	gd_engfuncs.pfnSetMinsMaxs(m_pEdict, mins, maxs);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetMins( void ) const
{
	return m_pState->mins;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetMaxs( void ) const
{
	return m_pState->maxs;
}


//=============================================
// @brief
//
//=============================================
DO_INLINE Int32 CBaseEntity::GetButtonBits( void ) const
{
	return m_pState->buttons;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetButtonBits( Int32 bitflags )
{
	m_pState->buttons |= bitflags;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::ClearButtonBits( Int32 bitflags )
{
	m_pState->buttons &= ~bitflags;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Vector CBaseEntity::GetViewOffset( bool fromNavigable ) const
{
	if(!fromNavigable)
	{
		return m_pState->view_offset;
	}
	else
	{
		Vector checkPosition = m_pState->origin + m_pState->view_offset;
		checkPosition = checkPosition - GetNavigablePosition();
		return checkPosition;
	}
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetViewOffset( const Vector& offset )
{
	m_pState->view_offset = offset;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetViewAngles( void ) const
{
	return m_pState->viewangles;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetViewAngles( const Vector& angles )
{
	m_pState->viewangles = angles;
	if(IsPlayer())
		m_pState->fixangles = true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetAiment( CBaseEntity* pEntity )
{
	if(!pEntity)
		m_pState->aiment = NO_ENTITY_INDEX;
	else
		m_pState->aiment = pEntity->GetEntityIndex();
}

//=============================================
// @brief
//
//=============================================
DO_INLINE CBaseEntity* CBaseEntity::GetAiment( void ) const
{
	if(m_pState->aiment == NO_ENTITY_INDEX)
		return nullptr;

	edict_t* pedict = gd_engfuncs.pfnGetEdictByIndex(m_pState->aiment);
	if(Util::IsNullEntity(pedict))
	{
		m_pState->aiment = NO_ENTITY_INDEX;
		return nullptr;
	}
	
	CBaseEntity* paiment = CBaseEntity::GetClass(pedict);
	return paiment;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetOwner( CBaseEntity* pEntity )
{
	if(!pEntity)
		m_pState->owner = NO_ENTITY_INDEX;
	else
		m_pState->owner = pEntity->GetEntityIndex();
}

//=============================================
// @brief
//
//=============================================
DO_INLINE CBaseEntity* CBaseEntity::GetOwner( void ) const
{
	if(m_pState->owner == NO_ENTITY_INDEX)
		return nullptr;

	edict_t* pedict = gd_engfuncs.pfnGetEdictByIndex(m_pState->owner);
	if(Util::IsNullEntity(pedict))
	{
		m_pState->owner = NO_ENTITY_INDEX;
		return nullptr;
	}
	
	CBaseEntity* powner = CBaseEntity::GetClass(pedict);
	return powner;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetGroundEntity( CBaseEntity* pEntity )
{
	if(!pEntity)
		m_pState->groundent = NO_ENTITY_INDEX;
	else
		m_pState->groundent = pEntity->GetEntityIndex();
}

//=============================================
// @brief
//
//=============================================
DO_INLINE CBaseEntity* CBaseEntity::GetGroundEntity( void ) const
{
	if(m_pState->groundent == NO_ENTITY_INDEX)
		return nullptr;

	edict_t* pedict = gd_engfuncs.pfnGetEdictByIndex(m_pState->groundent);
	if(Util::IsNullEntity(pedict))
	{
		m_pState->groundent = NO_ENTITY_INDEX;
		return nullptr;
	}
	
	CBaseEntity* pgroundent = CBaseEntity::GetClass(pedict);
	return pgroundent;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE waterlevel_t CBaseEntity::GetWaterLevel( void ) const
{
	return (waterlevel_t)m_pState->waterlevel;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetWaterLevel( waterlevel_t level )
{
	m_pState->waterlevel = level;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetSize( void ) const
{
	return m_pState->size;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetSize( const Vector& size )
{
	gd_engfuncs.pfnSetSize(m_pEdict, size);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetPunchAngle( void ) const
{
	return m_pState->punchangles;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetPunchAngle( const Vector& value )
{
	m_pState->punchangles = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetPunchAmount( void ) const
{
	return m_pState->punchamount;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetPunchAmount( const Vector& value )
{
	m_pState->punchamount = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int64 CBaseEntity::GetSpawnFlags( void ) const
{
	return m_pState->spawnflags;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::HasSpawnFlag( Int64 bit ) const
{ 
	return (m_pState->spawnflags & bit) ? true : false; 
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetSpawnFlag( Int64 flag )
{
	m_pState->spawnflags |= flag;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::RemoveSpawnFlag( Int64 flag )
{
	m_pState->spawnflags &= ~flag;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Vector& CBaseEntity::GetRenderColor( void ) const
{
	return m_pState->rendercolor;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetRenderColor( const Vector& color )
{
	m_pState->rendercolor.x = Clamp(color.x, 0, 255);
	m_pState->rendercolor.y = Clamp(color.y, 0, 255);
	m_pState->rendercolor.z = Clamp(color.z, 0, 255);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetRenderColor( Int32 r, Int32 g, Int32 b )
{
	m_pState->rendercolor.x = Clamp(r, 0, 255);
	m_pState->rendercolor.y = Clamp(g, 0, 255);
	m_pState->rendercolor.z = Clamp(b, 0, 255);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE rendermode_t CBaseEntity::GetRenderMode( void ) const
{
	return (rendermode_t)m_pState->rendermode;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetRenderMode( rendermode_t rendermode )
{
	m_pState->rendermode = rendermode;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const float CBaseEntity::GetRenderAmount( void ) const
{
	return m_pState->renderamt;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetRenderAmount( float amount )
{
	m_pState->renderamt = Clamp(amount, 0, 255);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const Int32 CBaseEntity::GetRenderFx( void ) const
{
	return m_pState->renderfx;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetRenderFx( Int32 renderfx )
{
	m_pState->renderfx = renderfx;
}
 
//=============================================
// @brief Gets the render type
//
//=============================================
DO_INLINE const rendertype_t CBaseEntity::GetRenderType( void ) const
{
	return (rendertype_t)m_pState->rendertype;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int64 CBaseEntity::GetEffectFlags( void ) const
{
	return m_pState->effects;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::HasEffectFlag( Int64 bit ) const
{ 
	return (m_pState->effects & bit) ? true : false; 
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetEffectFlag( Int64 flag )
{
	m_pState->effects |= flag;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::RemoveEffectFlag( Int64 flag )
{
	m_pState->effects &= ~flag;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetSpeed( void ) const
{
	return m_pState->speed;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetSpeed( float speed )
{
	m_pState->speed = speed;
}

//=============================================
// @brief
//
//=============================================
float CBaseEntity::GetFallingVelocity( void ) const
{
	return m_pState->fallvelocity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::DropToFloor( void )
{
	return gd_engfuncs.pfnDropToFloor(m_pEdict);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE CBaseEntity* CBaseEntity::GetParent( void ) const
{
	if(m_pState->parent == NO_ENTITY_INDEX)
		return nullptr;

	edict_t* pedict = gd_engfuncs.pfnGetEdictByIndex(m_pState->parent);
	if(Util::IsNullEntity(pedict))
	{
		m_pState->groundent = NO_ENTITY_INDEX;
		return nullptr;
	}
	
	CBaseEntity* pparent = CBaseEntity::GetClass(pedict);
	return pparent;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetParent( CBaseEntity* pEntity )
{
	if(pEntity == nullptr)
	{
		m_pState->parent = NO_ENTITY_INDEX;
		m_pState->flags &= ~FL_PARENTED;
	}
	else
	{
		m_pState->parent = pEntity->GetEntityIndex();
		m_pState->flags |= FL_PARENTED;
	}
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::IsParented( void ) const
{
	return (m_pState->parent == NO_ENTITY_INDEX) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int32 CBaseEntity::GetSkin( void ) const
{
	return m_pState->skin;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetSkin( Int32 value )
{
	m_pState->skin = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int64 CBaseEntity::GetBody( void ) const
{
	return m_pState->body;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetBody( Int64 value )
{
	m_pState->body = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetHealth( void ) const
{
	return m_pState->health;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetHealth( float value )
{
	m_pState->health = value;
}

//=============================================
// @brief Returns the max health value
//
//=============================================
DO_INLINE float CBaseEntity::GetMaxHealth( void ) const
{
	return m_pState->maxhealth;
}

//=============================================
// @brief Sets the max health value
//
//=============================================
DO_INLINE void CBaseEntity::SetMaxHealth( float value )
{
	m_pState->maxhealth = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetArmorValue( void ) const
{
	return m_pState->armorvalue;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetArmorValue( float value )
{
	m_pState->armorvalue = value;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasNetname( void ) const
{
	return (m_pFields->netname == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetNetname( void ) const
{
	if(m_pFields->netname == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->netname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetNetname( const char* pstrValue )
{
	m_pFields->netname = gd_engfuncs.pfnAllocString(pstrValue);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasMessage( void ) const
{
	return (m_pFields->message == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetMessage( void ) const
{
	if(m_pFields->message == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->message);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetMessage( const char* pstrValue )
{
	m_pFields->message = gd_engfuncs.pfnAllocString(pstrValue);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::HasGlobalName( void ) const
{
	return (m_pFields->globalname == NO_STRING_VALUE) ? false : true;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CBaseEntity::GetGlobalName( void ) const
{
	if(m_pFields->globalname == NO_STRING_VALUE)
		return "";
	else
		return gd_engfuncs.pfnGetString(m_pFields->globalname);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetGlobalName( const char* pstrValue )
{
	m_pFields->globalname = gd_engfuncs.pfnAllocString(pstrValue);
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const float CBaseEntity::GetScale( void ) const
{
	return m_pState->scale;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetScale( float scale )
{
	m_pState->scale = scale;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE movetype_t CBaseEntity::GetMoveType( void ) const
{
	return (movetype_t)m_pState->movetype;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetMoveType( movetype_t movetype )
{
	m_pState->movetype = movetype;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE double CBaseEntity::GetNextThinkTime( void ) const
{
	return m_pState->nextthink;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetNextThinkTime( double thinktime )
{
	m_pState->nextthink = thinktime;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetNextThink( double delay )
{
	if(!delay)
		m_pState->nextthink = 0;
	else
		m_pState->nextthink = g_pGameVars->time + delay;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE double CBaseEntity::GetLocalTime( void ) const
{
	return m_pState->ltime;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetGravity( void ) const
{
	return m_pState->gravity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetGravity( float gravity )
{
	m_pState->gravity = gravity;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetFriction( void ) const
{
	return m_pState->friction;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetFriction( float friction )
{
	m_pState->friction = friction;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE float CBaseEntity::GetPlaneZCap( void ) const
{
	return m_pState->planezcap;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetPlaneZCap( float planeZCap )
{
	m_pState->planezcap = planeZCap;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE deathstate_t CBaseEntity::GetDeadState( void ) const
{
	return (deathstate_t)m_pState->deadstate;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetDeadState( deathstate_t state )
{
	m_pState->deadstate = state;
}

//=============================================
// @brief Returns the weapons value
//
//=============================================
DO_INLINE Int64 CBaseEntity::GetWeapons( void ) const
{
	return m_pState->weapons;
}

//=============================================
// @brief Sets the weapons value
//
//=============================================
DO_INLINE void CBaseEntity::SetWeapons( Int64 weapons )
{
	m_pState->weapons = weapons;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::SetModel( const char* pstrModelName, bool setbounds )
{
	if(gd_engfuncs.pfnSetModel(m_pEdict, pstrModelName, setbounds))
	{
		PostModelSet();
		return true;
	}
	else
		return false;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE bool CBaseEntity::SetModel( string_t modelNameString, bool setbounds )
{
	if(modelNameString == NO_STRING_VALUE)
		return false;

	if(gd_engfuncs.pfnSetModel(m_pEdict, gd_engfuncs.pfnGetString(modelNameString), setbounds))
	{
		PostModelSet();
		return true;
	}
	else
		return false;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const float CBaseEntity::GetIdealYaw( void ) const
{
	return m_pState->idealyaw;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetIdealYaw( float idealyaw )
{
	m_pState->idealyaw = idealyaw;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const float CBaseEntity::GetFramerate( void ) const
{
	return m_pState->framerate;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetFramerate( float framerate )
{
	m_pState->framerate = framerate;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const float CBaseEntity::GetFrame( void ) const
{
	return m_pState->frame;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE void CBaseEntity::SetFrame( float frame )
{
	m_pState->frame = frame;
}

// 
//=============================================
// @brief Gets the animation time
//
//=============================================
DO_INLINE const double CBaseEntity::GetAnimationTime( void ) const
{
	return m_pState->animtime;
}

//=============================================
// @brief Sets the animation time
//
//=============================================
DO_INLINE void CBaseEntity::SetAnimationTime( double animtime )
{
	m_pState->animtime = animtime;
}

//=============================================
// @brief Tells if the entity is a visible entity
//
//=============================================
DO_INLINE bool CBaseEntity::IsVisible( void ) const
{
	return (!m_pState->modelindex  || (m_pState->effects & EF_NODRAW)) ? false : true;
}

#endif //BASEENTITY_INLINE_H