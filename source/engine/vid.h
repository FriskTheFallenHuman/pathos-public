/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef VID_H
#define VID_H

extern bool VID_Init( void );
extern void VID_Shutdown( void );
extern void VID_Reload( void );
extern void VID_Draw( void );
extern void VID_Restart( void );
extern void VID_InitCommands( void );
extern void VID_DrawLoadingScreen( const char* pstrText = nullptr );
extern void VID_BeginLoading( bool drawUI );
extern void VID_EndLoading( void );
extern void VID_DrawSceneOnly( void );
extern void VID_GetScreenContents( UInt32& width, UInt32& height, UInt32& bpp, Byte** pdata );
extern void VID_ShaderCompileCallback( const char* pstrShaderName, UInt32 totalCount, UInt32 completedCount, bool buildingCache );
#endif