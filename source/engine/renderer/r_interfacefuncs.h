/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef R_INTERFACEFUNCS_H
#define R_INTERFACEFUNCS_H

/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "texturemanager.h"
#include "r_vbo.h"
#include "r_glsl.h"
#include "r_basicdraw.h"
#include "r_glextf.h"
#include "r_main.h"
#include "r_interface.h"
#include "r_text.h"
#include "window.h"

struct cl_dlight_t;

extern en_texture_t* R_GetDummyTexture( void );
extern en_material_t* R_GetDummyMaterial( void );
extern en_texalloc_t* R_AllocTextureIndex( rs_level_t level );
extern en_texture_t* R_LoadTexture( const char* pstrFilename, rs_level_t level, Int32 flags, const GLint* pborder );
extern en_texture_t* R_LoadTextureFromMemory( const char* pstrTextureName, rs_level_t level, Int32 flags, const Byte* pdata, UInt32 width, UInt32 height, UInt32 bpp );
extern en_material_t* R_LoadMaterialScript( const char* pstrFilename, rs_level_t level );
extern bool R_EnableBasicDraw( void );
extern void R_DisableBasicDraw( void );
extern bool R_BasicDrawEnableTextures( void );
extern bool R_BasicDrawDisableTextures( void );
extern void R_BasicDrawBegin( CBasicDraw::primitivetype_t primitiveType );
extern void R_BasicDrawEnd( void );
extern void R_BasicDrawSetProjection( const float* pMatrix );
extern void R_BasicDrawSetModelView( const float* pMatrix );
extern void R_BasicDrawColor4f( float r, float g, float b, float a );
extern void R_BasicDrawColor4fv( const float* pfc );
extern void R_BasicDrawTexCoord2f( float u, float v );
extern void R_BasicDrawTexCoord2fv( const float* ptc );
extern void R_BasicDrawVertex3f( float x, float y, float z );
extern void R_BasicDrawVertex3fv( const float* pfv );
extern const CGLExtF& R_GetExportFunctionsClass( void );
extern CMatrix& R_GetProjectionMatrix( void );
extern CMatrix& R_GetModelViewMatrix( void );
extern const ref_params_t&	R_GetViewParams( void );
extern const font_set_t* R_GetDefaultFontSet( void );
extern const font_set_t* R_LoadFontSet( const char *pstrFilename, Int32 fontSize );
extern void R_GetScreenSize( UInt32& scrwidth, UInt32& scrheight );
extern bool R_BasicDrawIsActive( void );
extern void R_GetStringSize( const font_set_t *pset, const char *pstring, UInt32 *width, UInt32 *height, Int32 *ymin );
extern Int32 R_EstimateStringHeight( const font_set_t *pset, const char *pstrString, UInt32 minlineheight );
extern void R_SetStringRectangle( Int16 minx, Int16 miny, Int16 maxx, Int16 maxy, Int32 insetx, Int32 insety );
extern const char* R_GetStringDrawError( void );
extern bool R_VBMPrepareDraw( void );
extern void R_VBMEndDraw( void );
extern bool R_DrawVBMModel( cl_entity_t* pentity, Int32 renderflags );
extern bool R_VBMPrepareVSMDraw( cl_dlight_t* pdlight );
extern void R_VBMEndVSMDraw( void );
extern bool R_DrawVBMModelVSM( cl_entity_t* pentity, cl_dlight_t* pdlight );
extern const char* R_VBMGetShaderError( void );
extern void R_InitRenderInterface( r_interface_t &renderFuncs );
extern UInt32 R_GetNumRenderEntities( void );
extern cl_entity_t* R_GetRenderEntityByIndex( UInt32 index );
extern void R_IF_ValidateShader( CGLSLShader* pShader );
extern void R_IF_ValidateBasicDraw( void );
#endif //R_INTERFACEFUNCS_H