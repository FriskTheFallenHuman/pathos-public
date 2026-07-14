/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef PLAYERLOADSAVED_H
#define PLAYERLOADSAVED_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CPlayerLoadSaved : public CPointEntity
{
public:
	explicit CPlayerLoadSaved( edict_t* pedict );
	virtual ~CPlayerLoadSaved( void );

public:
	virtual bool Spawn( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	
public:
	float GetDuration( void );
	float GetHoldTime( void );
	float GetMessageTime( void );
	float GetLoadTime( void );

	void SetDuration( float duration );
	void SetHoldTime( float holdtime );
	void SetMessageTime( float messagetime );
	void SetLoadTime( float loadtime );

public:
	void EXPORTFN MessageThink( void );
	void EXPORTFN LoadThink( void );

public:
	static void ClearSaveGameBlock( void );
	static bool IsBlockingSaving( void );

private:
	float m_messageTime;
	float m_loadTime;
	float m_duration;
	float m_holdTime;

private:
	static bool m_isBlockingSaveGame;
};
#endif //PLAYERLOADSAVED_H