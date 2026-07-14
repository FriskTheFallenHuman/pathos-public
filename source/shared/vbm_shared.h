/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef VBM_SHARED_H
#define VBM_SHARED_H

// Notes:
// Part of this implementation is referenced from the implementation in the Half-Life SDK
// The studiomodel format is Valve's original work, and I take no ownership of it
// No copyright infringement intended

enum vbm_renderflags_t
{
	VBM_RENDER		= (1<<0), // Render the model
	VBM_ANIMEVENTS	= (1<<1), // Trigger animevents
	VBM_SETUPBONES	= (1<<2), // Only set up bones
	VBM_DEBUG_ONLY	= (1<<3), // Draw debug only
};

struct studiohdr_t;
struct model_t;
struct mstudioseqdesc_t;
struct mstudiobone_t;
struct mstudioanim_t;
struct vbmheader_t;
struct vbmsubmodel_t;
struct entity_state_t;
struct en_material_t;
struct cache_model_t;

#include "vbmformat.h"

extern float VBM_EstimateInterpolant( float time, float animtime, float prevanimtime );
extern void VBM_CalculateRotations( const studiohdr_t* phdr, float time, float animtime, float prevanimtime, CArray<Vector>& positions, CArray<vec4_t>& quaternions, const mstudioseqdesc_t* pseqdesc, const mstudioanim_t* panim, float frame, const float* pcontroller1, const float* pcontroller2, Byte mouth );
extern void VBM_CalculateBoneAdjustments( const studiohdr_t* phdr, float dadt, float* padj, const float* pcontroller1, const float* pcontroller2, Byte mouth );
extern void VBM_InterpolateBones( const studiohdr_t* phdr, const CArray<vec4_t>& quaternions1, const CArray<Vector>& positions1, CArray<vec4_t>& quaternions2, const CArray<Vector>& positions2, float interpolant, CArray<vec4_t>& outquaternions, CArray<Vector>& outpositions );
extern const mstudioanim_t* VBM_GetAnimation( const studiohdr_t* phdr, const mstudioseqdesc_t* psequencedesc );
extern void VBM_CalculateBoneQuaternion( Int32 frame, float interpolant, const mstudiobone_t* pbone, const mstudioanim_t* panimation, const float* padj, vec4_t& quaternion );
extern void VBM_CalculateBonePosition( Int32 frame, float interpolant, const mstudiobone_t* pbone, const mstudioanim_t* panimation, const float* padj, Vector& outpos );
extern float VBM_EstimateFrame( const mstudioseqdesc_t* pseqdesc, double time, float entframe, double animtime, float framerate, Int64 effects );
extern bool VBM_HasTransparentParts( vbmheader_t* pvbmheader, UInt64 body, Int32 skin );
extern void VBM_NormalizeWeights( float* pflweights, UInt32 maxweights );
extern Int32 VBM_FindSequence( const studiohdr_t* pstudiohdr, const char* pstrsequencename );
extern float VBM_GetSequenceTime( const studiohdr_t* pstudiohdr, Int32 sequence, float framerate );
extern bool VBM_PostLoadVBMCheck( vbmheader_t* pvbm, en_material_t* (*pfnFindMaterialScriptByIndex)( Int32 index ) );
extern float VBM_SetController( const cache_model_t* pmodel, UInt32 controllerindex, float value, float* pcontrollers, void (*pfnCon_Printf)( const char *fmt, ... ) );
#endif //VBM_SHARED_H