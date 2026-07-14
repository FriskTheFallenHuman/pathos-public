/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ENGINEFUNCS_H
#define ENGINEFUNCS_H

extern const en_material_t* Engine_GetMaterialScript( const char* pstrTextureName );
extern const Byte* Engine_LeafPVS( const mleaf_t& leaf );
extern const mleaf_t* Engine_PointInLeaf( const Vector& position );
extern const cache_model_t* Engine_LoadModel( const char* pstrModelPath );
extern const char* Engine_GetLevelName( void );
extern double Engine_GetEngineTime( void );
extern CCVar* Engine_CreateCVar( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription );
extern CCVar* Engine_CreateCVarCallback( cvar_type_t type, Int32 flags, const char* pstrName, const char* pstrValue, const char* pstrDescription, pfnCVarCallback_t pfnCallback );
extern CCVar* Engine_GetCVarPointer( const char* pstrName );
extern void Engine_SetCVarFloat( const char* pstrName, float value );
extern void Engine_SetCVarString( const char* pstrName, const char* pstrValue );
extern void Engine_CreateCommand( const char* name, cmdfunc_t pfn, const char* description );
extern UInt32 Engine_Cmd_Argc( void );
extern const char* Engine_Cmd_Argv( UInt32 index );
extern float Engine_GetCvarFloatValue( const char* pstrCvarName );
extern const char* Engine_GetCvarStringValue( const char* pstrCvarName );
extern UInt32 Engine_GetVISBufferSize( void );
#endif //ENGINEFUNCS_H