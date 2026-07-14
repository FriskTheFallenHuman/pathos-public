/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef VBMUTILS_H
#define VBMUTILS_H

extern Int32 VBM_FindSequenceByActivity( const cache_model_t* pmodel, Int32 activity );
extern Int32 VBM_FindSequenceWithHeaviestActivity( const cache_model_t* pmodel, Int32 activity );
extern void VBM_GetSequenceInfo( const cache_model_t* pmodel, Int32 sequence, float* pframerate, float* pgroundspeed );
extern Int32 VBM_GetSequenceFlags( const cache_model_t* pmodel, Int32 sequence );
extern UInt32 VBM_GetSequenceNumber( const cache_model_t* pmodel );
extern float VBM_SetBlending( const cache_model_t* pmodel, UInt32 blendingindex, Int32 sequence, float value, float* pblending );
extern UInt32 VBM_GetNumSequenceBlenders( const cache_model_t* pmodel, Int32 sequence );
extern void VBM_GetEyePosition( const cache_model_t* pmodel, Vector& eyeposition );
extern void VBM_PrecacheSequenceResources( const cache_model_t* pmodel, const char* pstrsequencename );
extern Int32 VBM_FindTransition( const cache_model_t* pmodel, Int32 endanim, Int32 startanim, Int32* pdirection );
extern void VBM_SetBodyGroup( const cache_model_t* pmodel, Int32 groupindex, Int32 value, Int64& body );
extern Int32 VBM_GetBodyGroupIndexByName( const cache_model_t* pmodel, const char* pstrBodyGroupName );
extern Int32 VBM_GetSubmodelIndexByName( const cache_model_t* pmodel, Int32 bodyGroupIndex, const char* pstrSubmodelName );
extern Int32 VBM_GetBodyGroupValue( const cache_model_t* pmodel, Int32 groupindex, Int64 body );
extern UInt32 VBM_GetNumSequenceFrames( const cache_model_t* pmodel, Int32 sequence );
extern bool VBM_GetSequenceBoundingBox( const cache_model_t* pmodel, Int32 sequence, Vector& mins, Vector& maxs );
#endif //VBMUTILS_H