/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FUNCFADE_H
#define FUNCFADE_H

#include "funcwall.h"

//=============================================
//
//=============================================
class CFuncFade : public CFuncWall
{
public:
	explicit CFuncFade( edict_t* pedict );
	virtual ~CFuncFade( void );

public:
	virtual bool Spawn( void ) override;
	virtual void Precache( void ) override { }
	virtual void DeclareSaveFields( void ) override;

	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;

public:
	void EXPORTFN Think( void );

protected:
	// Duration of fade
	float m_fadeDuration;
	// Target alpha
	float m_targetAlpha;
	// Fade begin time
	double m_fadeBeginTime;
	// Start alpha value
	float m_startAlpha;
};
#endif //FUNCWALL_H