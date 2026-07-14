/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

#ifndef R_COMMON_H
#define R_COMMON_H

#include "carray.h"

struct msurface_t;
struct cl_entity_t;
struct en_texture_t;

class CMatrix;
class CGLSLShader;

enum screenratio_strings_t
{
	SCR_RATIO_NORMAL = 0,
	SCR_RATIO_WIDESCREEN,
	SCR_RATIO_ULTRAWIDE,

	// must be last
	NB_SCREENRATIO_STRINGS
};

extern const char* SCREEN_RATIO_STRINGS[NB_SCREENRATIO_STRINGS];

extern void R_AllocBlock ( UInt32 w, UInt32 h, UInt32 &x, UInt32 &y, UInt32& width, UInt32 &height, UInt32*& pallocations, UInt32 padamount );
extern void R_BuildLightmap( UInt16 light_s, UInt16 light_t, const color24_t *psamples, const msurface_t *psurface, color32_t *pout, Int32 index, UInt32 sizex, float overdarken, UInt32 padamount, bool isvectormap = false, bool fullbright = false );
extern bool R_IsEntityMoved( const cl_entity_t& entity );
extern bool R_IsEntityRotated( const cl_entity_t& entity );
extern bool R_IsEntityTransparent( const cl_entity_t& entity, bool ignoreVBMFlags = false );
extern void R_RotateForEntity( CMatrix& matrix, const cl_entity_t& entity );
extern bool R_CheckShaderVertexAttribute( Int32 attribindex, const char* pstrattribname, const CGLSLShader* pshader, void	(*pfnErrorPopup)( const char *fmt, ... ) );
extern bool R_CheckShaderDeterminator( Int32 attribindex, const char* pstrattribname, const CGLSLShader* pshader, void	(*pfnErrorPopup)( const char *fmt, ... ) );
extern bool R_CheckShaderUniform( Int32 attribindex, const char* pstrattribname, const CGLSLShader* pshader, void	(*pfnErrorPopup)( const char *fmt, ... ) );
extern bool R_WorldToScreenTransform( CMatrix& matrix, const Vector& src, Vector& screenstart );

extern Int32 R_GetRelativeX( Int32 xPos, Int32 baseWidth, Int32 windowWidth );
extern Int32 R_GetRelativeY( Int32 yPos, Int32 baseHeight, Int32 windowHeight );
extern void R_SetMatrixData( const float *pin, float* pout, bool transpose = false );
extern CString R_GetAspectRatio( UInt32 width, UInt32 height );
#endif