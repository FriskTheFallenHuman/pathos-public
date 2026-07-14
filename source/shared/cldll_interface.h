/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CLDLL_INTERFACE_H
#define CLDLL_INTERFACE_H

#include "cmd_shared.h"
#include "cvar.h"
#include "snd_shared.h"
#include "cache_model.h"
#include "flex_shared.h"

struct edict_t;
struct usercmd_t;
struct cl_entity_t;
struct ref_params_t;
struct movevars_t;
struct en_material_t;
struct cache_model_t;
struct brushmodel_t;
struct mleaf_t;
struct entity_extrainfo_t;
struct mnode_t;
struct decalgroupentry_t;
struct ui_schemeinfo_t;
struct ui_windowdescription_t;
struct cl_dlight_t;
struct font_set_t;

enum cmodel_type_t;
enum snd_effects_t;

class Vector;
class CDecalList;
class CUIWindow;

// client dll interface version
#define CLDLL_INTERFACE_VERSION 1

struct cldll_funcs_t
{
	bool (*pfnClientDLLInit)( void );
	void (*pfnClientDLLShutdown)( void );

	void (*pfnClientConnected)( void );
	void (*pfnClientDisconnected)( void );
	void (*pfnClientFrame)( void );

	bool (*pfnGameInit)( void );
	void (*pfnGameReset)( void );

	bool (*pfnGLInit)( void );
	void (*pfnGLClear)( void );

	void (*pfnCalcRefDef)( ref_params_t& params );
	void (*pfnSetupView)( const ref_params_t& params );
	bool (*pfnDrawNormal)( void );
	bool (*pfnDrawTransparent)( void );
	bool (*pfnDrawHUD)( bool hudOnly );

	void (*pfnClientPreCmdThink)( void );
	void (*pfnInMove)( usercmd_t& cmd );
	void (*pfnMouseMove)( usercmd_t& cmd );

	void (*pfnRunPlayermove)( const usercmd_t& cmd, struct pm_info_t* pminfo, bool playSounds );

	void (*pfnAddEntities)( void );
	void (*pfnDecalExternalEntities)( const Vector& vpos, const Vector& vnorm, decalgroupentry_t *texptr, Int32 flags );

	void (*pfnGetClientEntityList)( const struct entitydata_t*& pEntitiesPtr, UInt32& numEntities );
	void (*pfnParseEntityList)( void );
	void (*pfnFreeEntityData)( void );
	void (*pfnVBMEvent)( const struct mstudioevent_t* pvbmevent, struct cl_entity_t* pentity );

	cl_entity_t* (*pfnGetViewModel)( void );

	bool (*pfnAddSubtitle)( const char* pstrSubtitleName, float duration );
	void (*pfnRemoveSubtitle)( const char* pstrSubtitleName );

	void (*pfnGetViewInfo)( Vector& vOrigin, Vector& vAngles );

	bool (*pfnIsInputOverridden)( void );
	bool (*pfnIsMouseOverridden)( void );
	bool (*pfnIsEscapeKeyOverridden)( void );
	void (*pfnKeyEvent)( Int32 button, Int16 mod, bool keyDown );
	void (*pfnMouseButtonEvent)( Int32 button, bool keyDown );
	void (*pfnMouseWheelEvent)( Int32 button, bool keyDown, Int32 scroll );

	void (*pfnWindowFocusLost)( void );
	void (*pfnWindowFocusRegained)( void );

	bool (*pfnDrawViewObjects)( void );
	bool (*pfnDrawViewObjectsForVSM)( cl_dlight_t* dl );
		 
	bool (*pfnDrawLadders)( void );
	bool (*pfnDrawLaddersForVSM)( cl_dlight_t* dl );

	void (*pfnAdjustEntityTimers)( struct entity_state_t* pstate, double jointime );

	bool (*pfnShouldDrawPausedLogo)( void );
	void (*pfnClientLevelChange)( void );
};

struct cldll_engfuncs_t
{
	double					(*pfnGetClientTime)( void );
	double					(*pfnGetEngineTime)( void );
	double					(*pfnGetFrameTime)( void );
	cl_entity_t*			(*pfnGetLocalPlayer)( void );
	cl_entity_t*			(*pfnGetEntityByIndex)( Int32 index );

	const Vector&			(*pfnGetViewAngles)( void );
	void					(*pfnSetViewAngles)( const Vector& angles );

	void					(*pfnCon_Printf)( const char *fmt, ... );
	void					(*pfnCon_DPrintf)( const char *fmt, ... );
	void					(*pfnCon_VPrintf)( const char *fmt, ... );
	void					(*pfnCon_WPrintf)( const char *fmt, ... );
	void					(*pfnCon_EPrintf)( const char *fmt, ... );
	void					(*pfnErrorPopup)( const char *fmt, ... );

	void					(*pfnCreateCommand)( const char* name, cmdfunc_t pfn, const char* description );
	void					(*pfnResetInputCommand)( const char* name );

	UInt32					(*pfnCmd_Argc)( void );
	const char*				(*pfnCmd_Argv)( UInt32 index );

	void					(*pfnGetMousePosition)( Int32& x, Int32& y );
	void					(*pfnGetMouseDelta)( Int32& deltaX, Int32& deltaY );
	const movevars_t*		(*pfnGetMoveVars)( void );

	cmodel_type_t			(*pfnGetModelType)( const cache_model_t& model );
	void					(*pfnGetModelBounds)( const cache_model_t& model, Vector& mins, Vector& maxs );
	const cache_model_t*	(*pfnGetModel)( Int32 modelindex );
	const cache_model_t*	(*pfnGetModelByName)( const char* pstrModelName );
	UInt32					(*pfnGetNbModels)( void );

	Int32					(*pfnGetNumEntities)( void );
	UInt32					(*pfnGetMaxClients)( void );

	void					(*pfnPlayEntitySound)( entindex_t entindex, Int32 channel, const CString& sample, float volume, float attenuation, Int32 pitch, Int32 flags, float timeoffset );
	void					(*pfnPlayAmbientSound)( entindex_t entindex, const Vector& origin, Int32 channel, const CString& sample, float volume, float attenuation, Int32 pitch, Int32 flags, float timeoffset );
	Int32					(*pfnPrecacheSound)( const char* pstrSample, rs_level_t level );
	void					(*pfnApplySoundEffect)( entindex_t entindex, const char *sample,  Int32 channel, snd_effects_t effect, float duration, float targetvalue );
	const char*				(*pfnGetSoundFileForServerIndex)( Int32 serverindex );

	void					(*pfnPrecacheDecal)( const char* pstrDecalName );
	void					(*pfnPrecacheDecalGroup)( const char* pstrDecalName );

	void					(*pfnPlayMusic)( const CString& sample, Int32 channel, float timeOffset, float fadeInTime, Int32 flags );
	void					(*pfnStopMusic)( Int32 channel );

	const en_material_t*	(*pfnGetMaterialScript)( const char* pstrTextureName );
	const en_material_t*	(*pfnGetMapTextureMaterialScript)( const char* pstrTextureName );
	const en_material_t*	(*pfnGetModelTextureMaterialScript)( Int32 modelindex, const char* pstrtexturename );

	void					(*pfnAddEntity)( cl_entity_t* pentity );

	const Byte*				(*pfnLeafPVS)( const mleaf_t& leaf );
	const mleaf_t*			(*pfnPointInLeaf)( const Vector& position );

	const cache_model_t*	(*pfnLoadModel)( const char* pstrModelName );

	entity_extrainfo_t*		(*pfnGetEntityExtraData)( cl_entity_t* pentity );
	void					(*pfnFindTouchedLeafs)( const brushmodel_t* pworld, CArray<UInt32>& leafnumsarray, UInt32& leafcount, const Vector& mins, const Vector& maxs, mnode_t* pnode );
	bool					(*pfnRecursiveLightPoint)( const brushmodel_t* pworld, struct mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutcolors, Byte* poutstyles, float* poutstylevalues );
	bool					(*pfnRecursiveLightPointBumpData)( const brushmodel_t* pworld, struct mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutambientcolors, Vector* poutdiffusecolors, Vector* poutlightdirs, Vector* poutsurfnormal, Byte* poutstyles, float* poutstylevalues );

	void					(*pfnPrecacheFlexScript)( enum flextypes_t npctype, const char* pstrscript );
	void					(*pfnSetFlexScript)( entindex_t entindex, const char* pstrscript );

	Vector					(*pfnGetAttachment)( entindex_t entindex, UInt32 attachment );
	Vector					(*pfnGetBonePosition)( entindex_t entindex, const char* pstrbonename );
	void					(*pfnUpdateAttachments)( cl_entity_t* pentity );

	void					(*pfnServerCommand)( const char* pstrCommand );
	void					(*pfnClientCommand)( const char* pstrCommand );

	void					(*pfnShowMouse)( void );
	void					(*pfnHideMouse)( void );
	void					(*pfnSetShouldHideMouse)( bool shouldhide );
	void					(*pfnUpdateMousePositions)( void );
	void					(*pfnResetMouse)( void );

	Int32					(*pfnRegisterClientUserMessage)( const char* pstrMsgName, Int32 msgsize );
	void					(*pfnClientUserMessageBegin)( Int32 msgid );
	void					(*pfnClientUserMessageEnd)( void );

	void					(*pfnMsgWriteByte)( Byte value );
	void					(*pfnMsgWriteChar)( char value );
	void					(*pfnMsgWriteInt16)( Int16 value );
	void					(*pfnMsgWriteUint16)( UInt16 value );
	void					(*pfnMsgWriteInt32)( Int32 value );
	void					(*pfnMsgWriteUint32)( UInt32 value );
	void					(*pfnMsgWriteInt64)( Int64 value );
	void					(*pfnMsgWriteUint64)( UInt64 value );
	void					(*pfnMsgWriteSmallFloat)( float value );
	void					(*pfnMsgWriteFloat)( float value );
	void					(*pfnMsgWriteDouble)( double value );
	void					(*pfnMsgWriteBuffer)( const Byte* pdata, UInt32 size );
	void					(*pfnMsgWriteString)( const char* pdata );
	void					(*pfnMsgWriteEntindex)( entindex_t entindex );
	void					(*pfnMsgWriteBitSet)( const Byte* pdataarray, UInt32 numbits, UInt32 numbytes );

	CCVar*					(*pfnCreateCVar)( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription );
	CCVar*					(*pfnCreateCVarCallback)( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription, pfnCVarCallback_t pfnCallback );
	CCVar*					(*pfnGetCVarPointer)( const char* pstrName );
	void					(*pfnSetCVarFloat)( const char* pstrName, float value );
	void					(*pfnSetCVarString)( const char* pstrName, const char* pstrValue );
	float					(*pfnGetCvarFloatValue)( const char* pstrCvarName );
	const char*				(*pfnGetCvarStringValue)( const char* pstrCvarName );

	const font_set_t*		(*pfnGetSchemaFontSet)( const char* schemaFileName );
	const font_set_t*		(*pfnGetResolutionSchemaFontSet)( const char* schemaFileName, UInt32 resolution );

	void					(*pfnSetPaused)( bool isPaused, bool pauseOveride );
};

#endif //CLDLL_INTERFACE_H