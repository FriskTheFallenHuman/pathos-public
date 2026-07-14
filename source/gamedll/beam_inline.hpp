/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef BEAM_INLINE_H
#define BEAM_INLINE_H

//=============================================
// @brief Sets the beam type
//
//=============================================
DO_INLINE void CBeam::SetBeamType( beam_msgtype_t type )
{
	m_pState->iuser1 = type;
}

//=============================================
// @brief Returns the beam type
//
//=============================================
DO_INLINE beam_msgtype_t CBeam::GetBeamType( void ) const
{
	return (beam_msgtype_t)m_pState->iuser1;
}

//=============================================
// @brief Sets a beam flag
//
//=============================================
DO_INLINE void CBeam::SetBeamFlags( Int32 flags )
{
	m_pState->iuser2 = flags;
}

//=============================================
// @brief Returns the beam flags
//
//=============================================
DO_INLINE Int32 CBeam::GetBeamFlags( void ) const
{
	return m_pState->iuser2;
}

//=============================================
// @brief Sets the start position
//
//=============================================
DO_INLINE void CBeam::SetBeamStartPosition( const Vector& position )
{
	m_pState->origin = position;
}

//=============================================
// @brief Returns the beam's starting position
//
//=============================================
DO_INLINE const Vector& CBeam::GetBeamStartPosition( void ) const
{
	if(GetBeamType() == BEAM_MSG_BEAMENTS && m_startEntity)
		return m_startEntity->GetOrigin();	
	else
		return m_pState->origin;
}

//=============================================
// @brief Sets the end position
//
//=============================================
DO_INLINE void CBeam::SetBeamEndPosition( const Vector& position )
{
	m_pState->vuser1 = position;
}

//=============================================
// @brief Returns the beam's starting position
//
//=============================================
DO_INLINE const Vector& CBeam::GetBeamEndPosition( void ) const
{
	beam_msgtype_t type = GetBeamType();
	if(type != BEAM_MSG_BEAMPOINTS && m_endEntity)
		return m_endEntity->GetOrigin();	
	else
		return m_pState->vuser1;
}

//=============================================
// @brief Sets the start entity attachment
//
//=============================================
DO_INLINE void CBeam::SetBeamStartEntityAttachment( Int32 attachmentindex )
{
	m_attachment1Index = attachmentindex;
	m_pState->iuser5 = attachmentindex;
}

//=============================================
// @brief Returns the start entity attachment
//
//=============================================
DO_INLINE Int32 CBeam::GetBeamStartEntityAttachment( void )
{
	return m_pState->iuser5;
}

//=============================================
// @brief Sets the end entity attachment
//
//=============================================
DO_INLINE void CBeam::SetBeamEndEntityAttachment( Int32 attachmentindex )
{
	m_attachment2Index = attachmentindex;
	m_pState->iuser6 = attachmentindex;
}

//=============================================
// @brief Returns the end entity attachment
//
//=============================================
DO_INLINE Int32 CBeam::GetBeamEndEntityAttachment( void )
{
	return m_pState->iuser5;
}

//=============================================
// @brief Sets the start entity
//
//=============================================
DO_INLINE void CBeam::SetBeamStartEntity( CBaseEntity* pEntity )
{
	m_startEntity = pEntity;
	if(pEntity)
		m_pState->iuser3 = pEntity->GetEntityIndex();
	else
		m_pState->iuser3 = NO_ENTITY_INDEX;

	if(m_startEntity)
	{
		m_pState->aiment = m_startEntity->GetEntityIndex();
		m_pState->movetype = MOVETYPE_FOLLOW;
	}
}

//=============================================
// @brief Returns the start entity index
//
//=============================================
DO_INLINE CBaseEntity* CBeam::GetBeamStartEntity( void )
{
	return m_startEntity;
}

//=============================================
// @brief Sets the end entity
//
//=============================================
DO_INLINE void CBeam::SetBeamEndEntity( CBaseEntity* pEntity )
{
	m_endEntity = pEntity;
	if(pEntity)
		m_pState->iuser4 = pEntity->GetEntityIndex();
	else
		m_pState->iuser4 = NO_ENTITY_INDEX;
}

//=============================================
// @brief Returns the start entity index
//
//=============================================
DO_INLINE CBaseEntity* CBeam::GetBeamEndEntity( void )
{
	return m_endEntity;
}

//=============================================
// @brief Sets the texture of the beam
//
//=============================================
DO_INLINE bool CBeam::SetBeamTexture( Int32 spriteindex )
{
	const cache_model_t* pModel = gd_engfuncs.pfnGetModel(spriteindex);
	if(!pModel)
		return false;

	return gd_engfuncs.pfnSetModel(m_pEdict, pModel->name.c_str(), false);
}

//=============================================
// @brief Sets the texture of the beam
//
//=============================================
DO_INLINE bool CBeam::SetBeamTexture( const char* pstrSpriteName )
{
	return gd_engfuncs.pfnSetModel(m_pEdict, pstrSpriteName, false);
}

//=============================================
// @brief Returns the sprite index
//
//=============================================
DO_INLINE Int32 CBeam::GetBeamTexture( void ) const
{
	return m_pState->modelindex;
}

//=============================================
// @brief Sets the width of the beam
//
//=============================================
DO_INLINE void CBeam::SetBeamWidth( float width )
{
	m_pState->scale = width * 0.1;
}

//=============================================
// @brief Returns the beam width
//
//=============================================
DO_INLINE float CBeam::GetBeamWidth( void ) const
{
	return m_pState->scale;
}

//=============================================
// @brief Sets the amplitude of the beam
//
//=============================================
DO_INLINE void CBeam::SetBeamAmplitude( float amplitude )
{
	m_pState->fuser2 = amplitude;
}

//=============================================
// @brief Returns the beam amplitude
//
//=============================================
DO_INLINE float CBeam::GetBeamAmplitude( void ) const
{
	return m_pState->fuser2;
}

//=============================================
// @brief Sets the color of the beam
//
//=============================================
DO_INLINE void CBeam::SetBeamColor( Int32 r, Int32 g, Int32 b )
{
	m_pState->rendercolor.x = Clamp(r, 0, 255);
	m_pState->rendercolor.y = Clamp(g, 0, 255);
	m_pState->rendercolor.z = Clamp(b, 0, 255);
}

//=============================================
// @brief Returns the beam color
//
//=============================================
DO_INLINE const Vector& CBeam::GetBeamColor( void ) const
{
	return m_pState->rendercolor;
}

//=============================================
// @brief Sets the brightness of the beam
//
//=============================================
DO_INLINE void CBeam::SetBeamBrightness( float brightness )
{
	m_pState->renderamt = Clamp(brightness, 0, 255);
}

//=============================================
// @brief Returns the beam brightness
//
//=============================================
DO_INLINE float CBeam::GetBeamBrightness( void ) const
{
	return m_pState->renderamt;
}

//=============================================
// @brief Sets the current frame
//
//=============================================
DO_INLINE void CBeam::SetBeamFrame( float frame )
{
	m_pState->frame = frame;
}

//=============================================
// @brief Returns the beam frame
//
//=============================================
DO_INLINE float CBeam::GetBeamFrame( void ) const
{
	return m_pState->frame;
}

//=============================================
// @brief Sets the scroll rate
//
//=============================================
DO_INLINE void CBeam::SetBeamScrollRate( float speed )
{
	m_pState->fuser1 = speed;
}

//=============================================
// @brief Returns the scroll rate
//
//=============================================
DO_INLINE float CBeam::GetBeamScrollRate( void ) const
{
	return m_pState->fuser1;
}

//=============================================
// @brief Sets the noise speed
//
//=============================================
DO_INLINE void CBeam::SetBeamNoiseSpeed( float speed )
{
	m_pState->fuser3 = speed;
}

//=============================================
// @brief Returns the noise speed
//
//=============================================
DO_INLINE float CBeam::GetBeamNoiseSpeed( void ) const
{
	return m_pState->fuser3;
}

//=============================================
// @brief Sets the beam to die after the given amount of time
//
//=============================================
DO_INLINE void CBeam::LiveForTime( float time )
{
	SetThink(&CBaseEntity::RemoveThink);
	m_pState->nextthink = g_pGameVars->time + time;
}

//=============================================
// @brief Deal instant damage
//
//=============================================
DO_INLINE void CBeam::BeamDamageInstant( trace_t& tr, float damage )
{
	m_beamDamage = damage;
	m_dmgTime = g_pGameVars->time - 1;
	BeamDamage(tr);
}
#endif //BEAM_INLINE_H