/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef GDLL_INTERFACE_H
#define GDLL_INTERFACE_H

#include "cvar.h"
#include "cmd_shared.h"
#include "save_shared.h"
#include "net_shared.h"
#include "globalstate_shared.h"
#include "snd_shared.h"
#include "cache_model.h"

struct edict_t;
struct usercmd_t;
struct gamevars_t;
struct trace_interface_t;
struct cache_model_t;
struct trace_t;
struct entity_state_t;
struct en_material_t;
struct mnode_t;
struct brushmodel_t;
struct mleaf_t;
struct brushmodel_t;
struct save_globalentity_t;

enum cmodel_type_t;
enum savefile_type_t;
enum entfieldtype_t;
enum msgdest_t;
enum part_script_type_t;
enum npc_movetype_t;
enum edict_removed_t;

// GameDLL interface version
#define GDLL_INTERFACE_VERSION 1

struct gdll_funcs_t
{
	bool			(*pfnGameDLLInit)( void );
	void			(*pfnGameDLLShutdown)( void );

	bool			(*pfnGameInit)( void );
	void			(*pfnGameShutdown)( void );
	void			(*pfnServerFrame)( void );

	bool			(*pfnDispatchSpawn)( edict_t* pedict );
	bool			(*pfnDispatchRestore)( edict_t* pedict, bool isglobal );
	void			(*pfnDispatchThink)( edict_t* pedict );
	void			(*pfnDispatchTouch)( edict_t* pedict, edict_t* pOther );
	void			(*pfnDispatchBlocked)( edict_t* pedict, edict_t* pOther );
	void			(*pfnDispatchCrossedWater)( edict_t* pedict, bool entering );
	void			(*pfnDispatchDeclareSaveFields)( edict_t* pedict );
	void			(*pfnDispatchReleaseSaveFields)( edict_t* pedict );
	bool			(*pfnShouldCollide)( edict_t* pedict, edict_t* pOther );
	void			(*pfnSetAbsBox)( edict_t* pedict );
	bool			(*pfnRunEntityPhysics)( edict_t* pedict );
	void			(*pfnPrecacheResources)( void );
	void			(*pfnPostSpawnGame)( void );

	bool			(*pfnKeyValue)( edict_t* pedict, const struct keyvalue_t& keyvalue );
	void			(*pfnFreeEntity)( edict_t* pedict, edict_removed_t freeMode );
	void			(*prnOnAimentFreed)( edict_t* pedict );

	void			(*pfnGetHullSizes)( Int32 hullIndex, Vector& pmins, Vector& pmaxs );
	void			(*pfnSetupVisibility)( edict_t* pclient, Byte*& ppvs, Byte*& ppas );
	bool			(*pfnAddPacketEntity)( entity_state_t& state, entindex_t entindex, edict_t& entity, const edict_t& client, const Byte* pset );

	void			(*pfnCmdStart)( const usercmd_t& cmd, edict_t* pclient );
	void			(*pfnCmdEnd)( edict_t* pclient );

	void			(*pfnRunPlayerMovement)( const usercmd_t& cmd, struct pm_info_t* pminfo );

	edict_t*		(*pfnFindEntityByString)( edict_t* pStartEntity, const char* pstrFieldName, const char* pstrValue );

	bool			(*pfnClientCommand)( edict_t* pclient );
	void			(*pfnClientPreThink)( edict_t* pclient );
	void			(*pfnClientPostThink)( edict_t* pclient );

	bool			(*pfnClientConnect)( edict_t* pclient, const char* pname, const char* paddress, CString& rejectReason );
	void			(*pfnClientDisconnected)( edict_t* pclient );
	void			(*pfnInitializeClientData)( edict_t* pclient );

	void			(*pfnSaveEntityStateData)( edict_t* pedict, bool istransitionsave );
	void			(*pfnSaveEntityFieldsData)( edict_t* pedict, bool istransitionsave );
	void			(*pfnSaveEntityClassData)( edict_t* pedict, bool istransitionsave );

	bool			(*pfnShouldTransitionEntity)( edict_t* pedict );
	bool			(*pfnIsGlobalTransitioningEntity)( edict_t* pedict );
	bool			(*pfnShouldSaveEntity)( edict_t* pedict );

	void			(*pfnGetSaveGameTitle)( char* pstrBuffer, Int32 maxlength );
	void			(*pfnBeginLoadSave)( bool isLoadSave, bool isTransitionSave, bool isTransitionLoad, const Vector* pLandmarkOffset, const CArray<entindex_t>& entityIndexArray );
	bool			(*pfnReadEntityStateData)( edict_t* pedict, const char* fieldname, const Byte* pdata, UInt32 datasize, UInt32 blockindex, bool istransferglobalentity );
	bool			(*pfnReadEntityFieldData)( edict_t* pedict, const char* fieldname, const Byte* pdata, UInt32 datasize, UInt32 blockindex, bool istransferglobalentity );
	bool			(*pfnPrepareEntityClassData)( edict_t* pedict, const char* fieldname, UInt32 numblocks, bool istransferglobalentity );
	bool			(*pfnReadEntityClassData)( edict_t* pedict, const char* fieldname, const Byte* pdata, UInt32 datasize, UInt32 blockindex, bool istransferglobalentity );
	edict_t*		(*pfnFindGlobalEntity)( const char* pstrClassname, const char* pstrGlobalName );
	void			(*pfnAdjustEntityPositions)( edict_t* pedict, Vector prevmins );

	bool			(*pfnInconsistentFile)( const char* pstrFilename );

	UInt32			(*pfnGetNbGlobalStates)( void );
	void			(*pfnSaveGlobalStates)( void );
	void			(*pfnReadGlobalStateData)( const char* pstrglobalname, const char* pstrlevelname, enum globalstate_state_t state );

	bool			(*pfnAreCheatsEnabled)( void );

	bool			(*pfnGetTransitioningEntities)( const Byte* pPVS, const Vector* pTransitionMins, const Vector* pTransitionMaxs, const char* pstrLandmarkName, const Vector& landmarkPosition, Int32 *pTransitionList, UInt32& numEntities, UInt32 maxEntities );
	void			(*pfnAdjustLandmarkPVSData) ( edict_t* pLandmarkEdict, Byte* pPVS, UInt32 pvsBufferSize );
	bool			(*pfnCanSaveGame)( enum savefile_type_t type );
	bool			(*pfnCanLoadGame)( void );

	void			(*pfnShowSaveGameMessage)( void );
	void			(*pfnShowAutoSaveGameMessage)( void );
	void			(*pfnShowSaveGameBlockedMessage)( void );

	void			(*pfnRestoreDecal)( const Vector& origin, const Vector& normal, edict_t* pedict, const char* pstrDecalTexture, Int32 decalflags );
	void			(*pfnFormatKeyValue)( const char* pstrKeyValueName, char* pstrValue, UInt32 maxLength );
};

struct gdll_engfuncs_t
{
	Int32					(*pfnPrecacheModel)( const char* pstrFilepath );
	Int32					(*pfnPrecacheSound)( const char* pstrFilepath );
	void					(*pfnPrecacheGeneric)( const char* pstrresourcename );
	bool					(*pfnPrecacheParticleScript)( const char* pstrFilepath, part_script_type_t type );
	void					(*pfnPrecacheDecal)( const char* pstrDecalName );
	void					(*pfnPrecacheDecalGroup)( const char* pstrDecalName );

	bool					(*pfnSetModel)( edict_t* pedict, const char* pstrFilepath, bool setbounds );
	void					(*pfnSetMinsMaxs)( edict_t* pedict, const Vector& mins, const Vector& maxs );
	void					(*pfnSetSize)( edict_t* pedict, const Vector& size );
	void					(*pfnSetOrigin)( edict_t* pedict, const Vector& origin );

	Byte*					(*pfnSetPAS)( const Vector& origin );
	Byte*					(*pfnSetPVS)( const Vector& origin );

	void					(*pfnCon_Printf)( const char *fmt, ... );
	void					(*pfnCon_DPrintf)( const char *fmt, ... );
	void					(*pfnCon_VPrintf)( const char *fmt, ... );
	void					(*pfnCon_WPrintf)( const char *fmt, ... );
	void					(*pfnCon_EPrintf)( const char *fmt, ... );
	void					(*pfnClientPrintf)( const edict_t* pclient, const char *fmt, ... );

	Int32					(*pfnGetNbEdicts)( void );
	edict_t*				(*pfnGetEdictByIndex)( entindex_t entindex );
	edict_t*				(*pfnCreateEntity)( const char* pstrClassName );
	void					(*pfnRemoveEntity)( edict_t* pentity );
	bool					(*pfnDropToFloor)( edict_t* pentity );

	const cache_model_t*	(*pfnGetModel)( Int32 modelindex );
	void					(*pfnGetModelBounds)( const cache_model_t& model, Vector& mins, Vector& maxs );
	cmodel_type_t			(*pfnGetModelType)( const cache_model_t& model );
	UInt32					(*pfnGetNbCachedModels)( void );
	const cache_model_t*	(*pfnGetModelByName)( const char* pstrModelName );

	void					(*pfnAddToTouched)( entindex_t hitent, trace_t& trace, const Vector& velocity );
	const mleaf_t*			(*pfnPointInLeaf)( const Vector& position, const brushmodel_t& model );
	const Byte*				(*pfnLeafPVS)( Byte* pbuffer, UInt32 bufsize, const mleaf_t& leaf, const brushmodel_t& model );

	void					(*pfnSetGroupMask)( Int32 mask, Int32 op );

	void					(*pfnPlayEntitySound)( entindex_t entindex, const char* pstrPath, Int32 flags, Int32 channel, float volume, float attenuation, Int32 pitch, float timeoffset, Int32 dest_player );
	void					(*pfnPlayAmbientSound)( entindex_t entindex, const char* pstrPath, const Vector& origin, Int32 flags, float volume, float attenuation, Int32 pitch, float timeoffset, Int32 dest_player );
	void					(*pfnApplySoundEffect)( entindex_t entindex, const char* pstrPath, Int32 channel, enum snd_effects_t effect, float duration, float targetvalue, Int32 dest_player );
	void					(*pfnStopEntitySounds)( entindex_t entindex, Int32 channel, Int32 dest_player );
	void					(*pfnSetMuteAllSounds)( bool mutesounds );
	void					(*pfnSetRoomType)( Int32 roomtype );

	void					(*pfnPlayMusic)( const char* sample, Int32 channel, Int32 flags, float timeOffset, float fadeInTime, Int32 dest_player );
	void					(*pfnStopMusic)( Int32 dest_player, const char* pstrFilename, Int32 channel, float fadeTime );

	const char*				(*pfnNameForFunction)( const void* functionPtr );
	void*					(*pfnFunctionFromName)( const char* pstrName );

	const en_material_t*	(*pfnGetMaterialScript)( const char* pstrTextureName );
	const en_material_t*	(*pfnGetMapTextureMaterialScript)( const char* pstrtexturename );
	const en_material_t*	(*pfnGetModelTextureMaterialScript)( Int32 modelindex, const char* pstrtexturename );

	UInt32					(*pfnAllocString)( const char* pString );
	const char*				(*pfnGetString)( string_t stringindex );

	void					(*pfnSaveWriteBool)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteByte)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteBitset)( const char* fieldname, const Byte* pdata, UInt32 numberofbits, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteChar)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteInt16)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteUint16)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteInt32)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteUint32)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteInt64)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteUint64)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteFloat)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteDouble)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteTime)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteString)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteRawString)( const char* fieldname, const Byte* pdata, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteVector)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteCoord)( const char* fieldname, const Byte* pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteEntindex)( const char* fieldname, const Byte* const pdata, UInt32 fieldsize, entfieldtype_t fieldtype );
	void					(*pfnSaveWriteGlobalState)( UInt32 index, const char* pstrglobalname, const char* pstrlevelname, enum globalstate_state_t state );

	Int32					(*pfnRegisterUserMessage)( const char* pstrMsgName, Int32 msgsize );
	void					(*pfnUserMessageBegin)( msgdest_t dest, Int32 msgid, const Vector* porigin, const edict_t* pedict );
	void					(*pfnUserMessageEnd)( void );

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

	void					(*pfnServerCommand)( const char* pstrCmd );
	void					(*pfnClientCommand)( edict_t* pclient, const char* pstrCmd );
	void					(*pfnCreateCommand)( const char* name, cmdfunc_t pfn, const char* description );
	edict_t*				(*pfnGetInvokerPlayer)( void );

	bool					(*pfnGetBonePositionByName)( edict_t* pedict, const char* pstrbonename, Vector& position );
	bool					(*pfnGetBonePositionByIndex)( edict_t* pedict, UInt32 boneindex, Vector& position );
	bool					(*pfnGetAttachment)( edict_t* pedict, UInt32 index, Vector& position );

	bool					(*pfnRecursiveLightPoint)( const brushmodel_t* pworld, struct mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutcolors, Byte* poutstyles );
	bool					(*pfnRecursiveLightPointBumpData)( const brushmodel_t* pworld, struct mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutambientcolors, Vector* poutdiffusecolors, Vector* poutlightdirs, Vector* poutsurfnormal, Byte* poutstyles );

	CCVar*					(*pfnCreateCVar)( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription );
	CCVar*					(*pfnCreateCVarCallback)( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription, pfnCVarCallback_t pfnCallback );
	CCVar*					(*pfnGetCVarPointer)( const char* pstrName );
	void					(*pfnSetCVarFloat)( const char* pstrName, float value );
	void					(*pfnSetCVarString)( const char* pstrName, const char* pstrValue );
	float					(*pfnGetCvarFloatValue)( const char* pstrCvarName );
	const char*				(*pfnGetCvarStringValue)( const char* pstrCvarName );

	UInt32					(*pfnCmd_Argc)( void );
	const char*				(*pfnCmd_Argv)( UInt32 index );

	float					(*pfnGetSoundDuration)( const char* pstrfilename, UInt32 pitch );
	UInt32					(*pfnGetVISBufferSize)( void );
	UInt64					(*pfnGetModelFrameCount)( Int32 modelindex );

	void					(*pfnAddLevelConnection)( const char* pstrLevelName, const char* pstrOtherLevelName, const char* pstrLandmarkName, const char* pstrMapSaveFileName );
	void					(*pfnBeginLevelChange)( const char* pstrlevelname, const char* pstrlandmarkname, const Vector& landmarkposition );
	void					(*pfnGetTransitionList)( const Int32** pEntityList, UInt32& numEntities );

	void					(*pfnAddSavedDecal)( const Vector& origin, const Vector& normal, entindex_t entityindex, const char* pstrDecalTexture, Int32 decalflags );

	bool					(*pfnWalkMove)( edict_t* pentity, float yaw, float dist, enum walkmove_t movemode );
	void					(*pfnMoveToOrigin)( edict_t* pedict, const Vector& goalPosition, float moveyaw, float dist, npc_movetype_t movetype );
	bool					(*pfnCheckBottom)( edict_t* pedict );
	edict_t*				(*pfnFindClientInPVS)( const edict_t* pedict );

	void					(*pfnEndGame)( const char* pstrEndGameCode );
	double					(*pfnFloatTime)( void );
};
#endif //GDLL_INTERFACE_H