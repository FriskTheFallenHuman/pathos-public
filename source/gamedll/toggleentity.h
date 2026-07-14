/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef TOGGLEENTITY_H
#define TOGGLEENTITY_H

#include "delayentity.h"
#include "ehandle.h"

class CToggleEntity;

#ifdef _DEBUG
typedef void (CToggleEntity::*MOVEDONEPTR)( void );

#define SetMoveDone( function ) _SetMoveDone(static_cast <void (CToggleEntity::*)( void )>(function), #function)
#else
#define SetMoveDone( function ) m_pfnMoveDoneFunction = static_cast <void (CToggleEntity::*)( void )>(function)
#endif

//=============================================
//
//=============================================
class CToggleEntity : public CDelayEntity
{
public:
	explicit CToggleEntity( edict_t* pedict );
	virtual ~CToggleEntity( void );

public:
	virtual void Precache( void ) override;
	virtual void DeclareSaveFields( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual togglestate_t GetToggleState( void ) override;
	virtual bool IsLockedByMaster( void ) override;
	virtual float GetWaitTime( void ) override { return m_waitTime; }

public:
	virtual float GetDelay( void ) override;

	void PlayLockSounds( bool locked, bool button, float waittime, double& nextSoundTime );

	void LinearMove( const Vector& destPosition, float speed );
	void AngularMove( const Vector& destAngle, float speed );

	void EXPORTFN LinearMoveDone( void );
	void EXPORTFN AngularMoveDone( void );

	const Vector& GetPosition1( void ) const;
	const Vector& GetPosition2( void ) const;

public:
#ifdef _DEBUG
public:
	// Sets the move done function in Debug mode
	MOVEDONEPTR _SetMoveDone( MOVEDONEPTR pfnptr, const char* pstrFunctionName );
#endif

private:
	void SyncGroundEntities( const Vector& adjustVec );

protected:
	Int32 m_toggleState;
	double m_activateFinished;

	float m_moveDistance;
	float m_waitTime;
	float m_lip;
	float m_tWidth;
	float m_tLength;

	Vector m_position1;
	Vector m_position2;

	Vector m_angle1;
	Vector m_angle2;

	Vector m_finalDest;
	Vector m_finalAngle;

	float m_height;

	CEntityHandle m_activator;

	float m_damageDealt;
	Int32 m_damageBits;

	string_t m_masterEntityName;
	string_t m_moveSoundFile;
	string_t m_stopSoundFile;
	string_t m_lockedSoundFile;
	string_t m_unlockedSoundFile;

protected:
	// Move done function pointer
	void (CToggleEntity::*m_pfnMoveDoneFunction)( void );
};
#endif //TOGGLEENTITY_H
