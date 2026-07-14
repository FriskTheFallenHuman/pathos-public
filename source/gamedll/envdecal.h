/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENVDECAL_H
#define ENVDECAL_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CEnvDecal : public CPointEntity
{
public:
	explicit CEnvDecal( edict_t* pedict );
	virtual ~CEnvDecal( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual Int32 GetEntityFlags( void ) override;
	virtual void SendInitMessage( const CBaseEntity* pPlayer ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;

public:
	static void SpawnDecal( const Vector& origin, const char* pstrdecalname );

public:
	bool m_isActive;
	double m_spawnTime;
	float m_growthTime;
};

#endif //ENVDECAL_H