/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef INFOMONITORCAMERA_H
#define INFOMONITORCAMERA_H

#include "pointentity.h"
#include "monitor_shared.h"

//=============================================
//
//=============================================
class CInfoMonitorCamera : public CPointEntity
{
public:
	explicit CInfoMonitorCamera( edict_t* pedict );
	virtual ~CInfoMonitorCamera( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override;
	virtual bool Restore( void ) override;
	virtual void FreeEntity( edict_removed_t freeMode ) override;
	
public:
	virtual bool IsInfoMonitorCameraEntity( void ) const override { return true; }
	virtual void AddCameraMonitorEntity( const edict_t* pedict ) override;
	virtual bool CheckCameraBBox( const edict_t* pedict ) const override;

	virtual UInt32 GetNbCameraMonitors( void ) const override;
	virtual const edict_t* GetMonitorByIndex( UInt32 index ) const override;

	virtual void SetPVSData( void ) override;
	virtual const Byte* GetPVSData( void ) const override;

public:
	// Do not save-restore this
	Byte* m_pPVSData;

	// Do not save-restore
	const edict_t* m_pCameraMonitors[MAX_MONITOR_ENTITIES];
	Int32 m_numCameraMonitors;
};
#endif //INFOMONITORCAMERA_H