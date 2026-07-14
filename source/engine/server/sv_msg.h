/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SV_MSG_H
#define SV_MSG_H

extern bool SV_CheckFileConsistency( sv_client_t& cl, const char* pstrFilename, const char* pstrHash );
extern void SV_RequestClientConsistencyChecks( sv_client_t& cl );
extern void SV_AddClientConsistencyCheck( sv_client_t& cl, rs_type_t type, const char* pstrFilename );
extern void SV_ReadPauseMessage( sv_client_t& cl );

extern bool SV_WriteEntitiesToClient( sv_client_t* pclient );
extern void SV_UpdateClientData( void );
extern void SV_ClientPrintf( const edict_t* pclient, const char *fmt, ... );

extern bool SV_PrecacheParticleScript( const char* pstrfilepath, part_script_type_t type );

extern void SV_PrecacheDecal( const char* pstrDecalName );
extern void SV_PrecacheDecalGroup( const char* pstrDecalName );

extern Int32 SV_PrecacheSound( const char* pstrPath );
extern void SV_PlayEntitySound( entindex_t entindex, const char* pstrPath, Int32 flags, Int32 channel, float volume, float attenuation, Int32 pitch, float timeoffset, Int32 dest_player );
extern void SV_PlayAmbientSound( entindex_t entindex, const char* pstrPath, const Vector& origin, Int32 flags, float volume, float attenuation, Int32 pitch, float timeoffset, Int32 dest_player );
extern void SV_ApplySoundEffect( entindex_t entindex, const char* pstrPath, Int32 channel, enum snd_effects_t effect, float duration, float targetvalue, Int32 dest_player );
extern void SV_StopEntitySounds( entindex_t entindex, Int32 channel, Int32 dest_player );
extern void SV_PlayMusic( const char* pstrPath, Int32 channel, Int32 flags, float timeOffset, float fadeInTime, Int32 dest_player );
extern void SV_StopMusic( Int32 dest_player, const char* pstrFilename, Int32 channel, float fadeTime );
extern void SV_SetRoomType( Int32 roomtype );
extern void SV_MuteAllSounds( bool mutesounds );

extern void SV_ClearUpload( sv_client_t& cl );
extern bool SV_SendResourceLists( sv_client_t& cl );
extern void SV_WriteMoveVars( const sv_client_t& cl );

extern sv_clstate_t SV_ReadClientMessages( sv_client_t& cl );
extern bool SV_ReadResourceMessage( sv_client_t& cl );
extern bool SV_PrepareUpload( sv_client_t& cl );
extern void SV_ChunkSizeCvarCallBack( class CCVar* pCVar );

extern Int32 SV_RegisterUserMessage( const char* pstrMsgName, Int32 msgsize );
extern void SV_UserMessageBegin( msgdest_t dest, Int32 msgid, const Vector* porigin, const edict_t* pedict );
extern void SV_UserMessageEnd( void );
extern void SV_ClientRegisterUserMessages( const sv_client_t& cl );
extern UInt32 SV_FindUserMessageByName( const char* pstrName );
extern bool SV_SendUserMessages( sv_client_t& cl );

extern void SV_ReadClientUserMessage( sv_client_t& cl );
extern void SV_RegisterClientUserMessage( void );

extern void SV_Msg_WriteByte( Byte value );
extern void SV_Msg_WriteChar( char value );
extern void SV_Msg_WriteInt16( Int16 value );
extern void SV_Msg_WriteUint16( UInt16 value );
extern void SV_Msg_WriteInt32( Int32 value );
extern void SV_Msg_WriteUint32( UInt32 value );
extern void SV_Msg_WriteInt64( Int64 value );
extern void SV_Msg_WriteUint64( UInt64 value );
extern void SV_Msg_WriteSmallFloat( float value );
extern void SV_Msg_WriteFloat( float value );
extern void SV_Msg_WriteDouble( double value );
extern void SV_Msg_WriteBuffer( const Byte* pdata, UInt32 size );
extern void SV_Msg_WriteString( const char* pstring );
extern void SV_Msg_WriteEntindex( entindex_t entindex );
extern void SV_Msg_WriteBitSet( const Byte* pdataarray, UInt32 numbits, UInt32 numbytes );
#endif //SV_MSG_H