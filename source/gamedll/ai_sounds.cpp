/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "gd_includes.h"
#include "ai_sounds.h"
#include "baseentity.h"

// Object declaration
CAISounds gAISounds;

//=============================================
// @brief
//
//=============================================
CAISounds::CAISounds( void ):
	m_currentIdentifier(0)
{
}

//=============================================
// @brief
//
//=============================================
CAISounds::~CAISounds( void )
{
}

//=============================================
// @brief
//
//=============================================
ai_sound_t* CAISounds::GetSoundForEmitter( CBaseEntity* pEmitterEntity )
{
	ai_sound_t* psound = nullptr;

	// Try to find an existing sound player by the emitter entity
	m_soundsList.begin();
	while(!m_soundsList.end())
	{
		ai_sound_t& sound = m_soundsList.get();
		if(sound.emitter == reinterpret_cast<const CBaseEntity*>(pEmitterEntity))
			return &sound;

		m_soundsList.next();
	}

	// Allocate a new sound
	psound = &m_soundsList.add(ai_sound_t())->_val;
	psound->identifier = m_currentIdentifier;
	psound->emitter = pEmitterEntity;
	m_currentIdentifier++;

	return psound;
}

//=============================================
// @brief
//
//=============================================
ai_sound_t* CAISounds::AddSound( CBaseEntity* pEmitterEntity, Int32 typebits, float radius, float volume, float duration )
{
	if(!pEmitterEntity)
		return nullptr;

	ai_sound_t* psound = nullptr;

	// Try to find an existing sound player by the emitter entity
	m_soundsList.begin();
	while(!m_soundsList.end())
	{
		ai_sound_t& sound = m_soundsList.get();
		if(sound.emitter == reinterpret_cast<const CBaseEntity*>(pEmitterEntity))
		{
			psound = &sound;
			break;
		}

		m_soundsList.next();
	}

	// Allocate a new sound
	if(!psound)
	{
		psound = &m_soundsList.add(ai_sound_t())->_val;
		psound->identifier = m_currentIdentifier;
		m_currentIdentifier++;
	}

	// Set values
	psound->emitter = pEmitterEntity;
	psound->position = pEmitterEntity->GetNavigablePosition();
	psound->life = g_pGameVars->time + duration;
	psound->typeflags |= typebits;
	psound->radius = radius;
	psound->volume = volume;

	return psound;
}

//=============================================
// @brief
//
//=============================================
void CAISounds::ClearEmitterSounds( CBaseEntity* pEmitterEntity )
{
	// Try to find an existing sound player by the emitter entity
	m_soundsList.begin();
	while(!m_soundsList.end())
	{
		ai_sound_t& sound = m_soundsList.get();
		if(sound.emitter == reinterpret_cast<const CBaseEntity*>(pEmitterEntity))
			m_soundsList.remove(m_soundsList.get_link());

		m_soundsList.next();
	}
}

//=============================================
// @brief
//
//=============================================
ai_sound_t* CAISounds::AddSound( Int32 typebits, const Vector& origin, float radius, float volume, float duration )
{
	// Add the new entry
	ai_sound_t* psound = &m_soundsList.add(ai_sound_t())->_val;

	// Set values
	psound->position = origin;
	psound->life = g_pGameVars->time + duration;
	psound->typeflags |= typebits;
	psound->radius = radius;
	psound->identifier = m_currentIdentifier;
	psound->emitter.reset();

	m_currentIdentifier++;
	return psound;
}

//=============================================
// @brief
//
//=============================================
void CAISounds::GetSoundList( const Vector& position, CLinkedList<ai_sound_t>& destList, UInt32 soundMask, float sensitivity )
{
	if(m_soundsList.empty())
		return;

	float sndsensitivity = Clamp(sensitivity, 0.0, 1.0);

	m_soundsList.begin();
	while(!m_soundsList.end())
	{
		ai_sound_t& sound = m_soundsList.get();
		if(sound.life < g_pGameVars->time || !(sound.typeflags & soundMask) || !sound.radius)
		{
			m_soundsList.next();
			continue;
		}

		float distance = (position - sound.position).Length();
		if(distance < sound.radius)
		{
			float soundatten = 1.0f - (distance/sound.radius);
			float soundvolume = soundatten*sound.volume;
			
			if(soundvolume >= sndsensitivity)
			{
				ai_sound_t* psoundonnpc = nullptr;

				destList.begin();
				while(!destList.end())
				{
					ai_sound_t* pchecksnd = &destList.get();
					if(pchecksnd->identifier == sound.identifier)
					{
						psoundonnpc = pchecksnd;
						break;
					}

					destList.next();
				}

				if(!psoundonnpc)
					psoundonnpc = &destList.add(ai_sound_t())->_val;

				// Update values on NPC's data
				psoundonnpc->emitter = sound.emitter;
				psoundonnpc->identifier = sound.identifier;
				psoundonnpc->life = sound.life;
				psoundonnpc->position = sound.position;
				psoundonnpc->radius = sound.radius;
				psoundonnpc->typeflags = sound.typeflags;
				psoundonnpc->volume = sound.volume;
			}
		}

		m_soundsList.next();
	}
}

//=============================================
// @brief
//
//=============================================
void CAISounds::Think( void )
{
	if(m_soundsList.empty())
		return;

	m_soundsList.begin();
	while(!m_soundsList.end())
	{
		ai_sound_t& sound = m_soundsList.get();
		if(sound.life < g_pGameVars->time)
		{
			m_soundsList.remove(m_soundsList.get_link());
			m_soundsList.next();
			continue;
		}
		
		if(sound.emitter)
			sound.position = sound.emitter->GetOrigin();

		m_soundsList.next();
	}
}

//=============================================
// @brief
//
//=============================================
void CAISounds::Clear( void )
{
	if(!m_soundsList.empty())
		m_soundsList.clear();
}