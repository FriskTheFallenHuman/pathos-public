/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef MULTIMANAGER_H
#define MULTIMANAGER_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CMultiManager : public CPointEntity
{
public:
	// Maximum targets a multimanager can have
	static const UInt32 MAX_MULTIMANAGER_TARGETS = 128;

public:
	enum
	{
		FL_MULTITHREAD = (1<<0)
	};

public:
	explicit CMultiManager( edict_t* pedict );
	virtual ~CMultiManager( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual Int32 GetEntityFlags( void ) override { return CBaseEntity::GetEntityFlags() & ~FL_ENTITY_TRANSITION; }
	virtual float GetDelay( void ) override;

public:
	bool IsClone( void ) const;
	bool ShouldClone( void ) const;
	CMultiManager* CloneManager( void );

public:
	UInt32 GetNbTargets( void ) const;
	string_t GetTargetNameByIndex( UInt32 index ) const;
	float GetTargetDelayByIndex( UInt32 index ) const;
	void SetIsClone( bool isclone );

	void AddTarget( const char* pstrTargetName, float delay );
	void SortTargets( void );

public:
	void EXPORTFN TriggerThink( void );

public:
	bool m_isClone;
	bool m_isRunning;
	double m_startTime;
	float m_delay;

	string_t m_targetNamesArray[MAX_MULTIMANAGER_TARGETS];
	float m_targetDelaysArray[MAX_MULTIMANAGER_TARGETS];
	UInt32 m_nbTargets;
	UInt32 m_currentIndex;

	CEntityHandle m_activator;
};
#endif //MULTIMANAGER_H