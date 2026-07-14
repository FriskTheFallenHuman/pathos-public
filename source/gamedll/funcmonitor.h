/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FUNCMONITOR_H
#define FUNCMONITOR_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CFuncMonitor : public CBaseEntity
{
public:
	enum
	{
		FL_START_OFF = (1<<0)
	};
public:
	explicit CFuncMonitor( edict_t* pedict );
	virtual ~CFuncMonitor( void );

public:
	virtual bool Spawn( void ) override;
	virtual bool Restore( void ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;

	virtual Int32 GetEntityFlags( void ) override { return CBaseEntity::GetEntityFlags() & ~FL_ENTITY_TRANSITION; }
	virtual bool IsFuncMonitorEntity( void ) const override { return true; }
	virtual const CBaseEntity* GetCameraEntity( void ) const override;
	virtual void InitEntity( void ) override;
	
public:
	static void ClearMonitorList( void );
	static void AddMonitor( CBaseEntity* pMonitor );

	static UInt32 GetNbMonitors( void );
	const edict_t* GetMonitorByIndex( UInt32 index ) const;
	static bool CheckVISForEntity( const edict_t* pclient, const edict_t* pedict, const Byte* pset );

private:
	static CArray<CBaseEntity*> m_pMonitorsArray;
};
#endif //FUNCMONITOR_H