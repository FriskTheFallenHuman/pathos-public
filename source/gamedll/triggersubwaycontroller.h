/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef TRIGGERSUBWAYCONTROLLER_H
#define TRIGGERSUBWAYCONTROLLER_H

#include "pointentity.h"

//=============================================
//
//=============================================
class CTriggerSubwayController : public CPointEntity
{
public:
	enum
	{
		FL_SUBWAY_DUMMY = (1<<0)
	};

public:
	// Subway destination id for Bergen st.
	static const char BERGEN_ST_DEST_ID[];
	// Subway destination id for I B Mann st.
	static const char IBMANN_ST_DEST_ID[];
	// Subway destination id for Marshall
	static const char MARSHALL_ST_DEST_ID[];
	// Subway destination id for Eckhart st.
	static const char ECKHART_ST_DEST_ID[];
	// Subway destination id for Kassarr st
	static const char KASSAR_ST_DEST_ID[];
	// Subway destination id for Aiello
	static const char AIELLO_ST_DEST_ID[];

public:
	explicit CTriggerSubwayController( edict_t* pedict );
	virtual ~CTriggerSubwayController( void );

public:
	virtual bool Spawn( void ) override;
	virtual bool KeyValue( const keyvalue_t& kv ) override;
	virtual void CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value ) override;
	virtual void DeclareSaveFields( void ) override;

public:
	void FireTarget( CBaseEntity* pPlayer, const char* pstrdestinationid );

public:
	string_t m_destination1Target;
	string_t m_destination2Target;
	string_t m_destination3Target;
	string_t m_destination4Target;

	Int32 m_subwayLine;
};

#endif //TRIGGERSUBWAYCONTROLLER_H