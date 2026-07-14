/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CL_MSG_H
#define CL_MSG_H

class CNetworking;

extern bool CL_ReadMessages( void );
extern bool CL_ReadClientData( void );
extern bool CL_ReadPacketEntities( void );
extern void CL_SendPlayerInfo( void );
extern void CL_DisconnectMsg( void );
extern bool CL_ReadResourceList( void );
extern bool CL_ReadMoveVars( void );
extern void CL_FileConsistencyMsg( void );
extern void CL_RegisterUserMessage( void );
extern void CL_ReadUserMessage( void );
extern bool CL_ParseServerInfo( void );
extern void CL_ParseClientCommand( void );
extern void CL_ParseViewSetAngles( void );
extern void CL_ParseAddAVelocity( void );
extern void CL_ParseHeartBeat( void );
extern bool CL_ParseLightEnvInfo( void );
extern void CL_ReadSoundEngineMessage( void );
extern void CL_ReadParticlePrecacheMessage( void );
extern void CL_ReadDecalPrecacheMessage( void );
extern void CL_ClientUserMessageEnd( void );
extern void CL_ClientUserMessageBegin( Int32 msgid );
extern Int32 CL_RegisterClientUserMessage( const char* pstrMsgName, Int32 msgsize );
extern void CL_ClientRegisterUserMessages( void );
extern void CL_Msg_WriteByte( Byte value );
extern void CL_Msg_WriteChar( char value );
extern void CL_Msg_WriteInt16( Int16 value );
extern void CL_Msg_WriteUint16( UInt16 value );
extern void CL_Msg_WriteInt32( Int32 value );
extern void CL_Msg_WriteUint32( UInt32 value );
extern void CL_Msg_WriteInt64( Int64 value );
extern void CL_Msg_WriteUint64( UInt64 value );
extern void CL_Msg_WriteSmallFloat( float value );
extern void CL_Msg_WriteFloat( float value );
extern void CL_Msg_WriteDouble( double value );
extern void CL_Msg_WriteBuffer( const Byte* pdata, UInt32 size );
extern void CL_Msg_WriteString( const char* pstring );
extern void CL_Msg_WriteEntindex( entindex_t entindex );
extern void CL_Msg_WriteBitSet( const Byte* pdataarray, UInt32 numbits, UInt32 numbytes );
#endif //CL_MSG_H