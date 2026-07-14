/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef COM_MATH_H
#define COM_MATH_H

namespace Math
{
	extern DO_INLINE bool VectorCompare( const Vector& v1, const Vector& v2 );
	extern DO_INLINE void VectorCopy( const Vector& src, Vector& dest );
	extern DO_INLINE void VectorCopy( const float* psrc, Vector& dest );
	extern DO_INLINE void VectorCopy( const float* psrc, float* pdest );
	extern DO_INLINE void VectorCopy( const Vector& src, float* pdest );
	extern DO_INLINE void VectorClear( Vector& dest );
	extern DO_INLINE void VectorSubtract( const Vector& v1, const Vector& v2, Vector& dest );
	extern DO_INLINE void VectorAdd( const Vector& v1, const Vector& v2, Vector& dest );
	extern DO_INLINE void VectorMA( const Vector& v1, float scale, const Vector& v2, Vector& dest );
	extern DO_INLINE void VectorScale( const Vector& src, float scale, Vector& dest );
	extern DO_INLINE float DotProduct( const Vector& v1, const Vector& v2 );
	extern DO_INLINE float DotProduct( const Vector& v1, const float* pv2 );
	extern DO_INLINE float DotProduct4( const float* pv1, const float* pv2 );
	extern DO_INLINE void CrossProduct( const Vector& v1, const Vector& v2, Vector& dest );
	extern DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward );
	extern DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward, Vector* pright );
	extern DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward, Vector* pright, Vector* pup );
	extern DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward );
	extern DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward, Vector* pright );
	extern DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward, Vector* pright, Vector* pup );
	extern DO_INLINE float AngleMod( float angle );
	extern DO_INLINE float AngleDiff( float destangle, float srcangle );
	extern DO_INLINE float VectorNormalize( Vector& v );
	extern DO_INLINE bool IsVectorZero( const Vector& v );
	extern DO_INLINE bool CheckMinsMaxs( const Vector& mins1, const Vector& maxs1, const Vector& mins2, const Vector& maxs2 );
	extern DO_INLINE void RotateToEntitySpace( const Vector& angles, Vector& vec );
	extern DO_INLINE void RotateFromEntitySpace( const Vector& angles, Vector& vec );
	extern DO_INLINE bool PointInMinsMaxs( const Vector& point, const Vector& mins, const Vector& maxs );
	extern DO_INLINE void AngleMatrix( const Vector& angles, float (*pmatrix)[4] );
	extern DO_INLINE void AngleInverseMatrix( const Vector& angles, float (*pmatrix)[4] );
	extern DO_INLINE void VectorRotate( const Vector& vec, const float (*pmatrix)[4], Vector& out );
	extern DO_INLINE void VectorInverseRotate( const Vector& vec, const float (*pmatrix)[4], Vector& out );
	extern DO_INLINE Vector VectorToAngles( const Vector& forward, const Vector& left );
	extern DO_INLINE Vector VectorToAngles( const Vector& forward );
	extern DO_INLINE void MatMultPosition( const float *flmatrix, const Vector& vecin, Vector *vecout );
	extern DO_INLINE void MatMult( const float *flmatrix, const Vector& vecin, Vector *vecout );
	extern DO_INLINE void MatMult4( const float *flmatrix, const float *vecin, float *vecout );
	extern DO_INLINE void GetUpRight( const Vector& forward, Vector &up, Vector &right );
	extern DO_INLINE void VectorTransform( const Vector& in, float (*pmatrix)[4], Vector& out );
	extern DO_INLINE void VectorInverseTransform( const Vector& vec, const float (*pmatrix)[4], Vector& out );
	extern DO_INLINE void QuaternionMatrix( const vec4_t& quaternion, float (*pmatrix)[4] );
	extern DO_INLINE void AngleQuaternion( const Vector& angles, vec4_t& quaternion );
	extern DO_INLINE void QuaternionBlend( const vec4_t& q1, const vec4_t& q2, float interp, vec4_t& outq );
	extern DO_INLINE void ConcatTransforms( const float (*pin1)[4], const float (*pin2)[4], float (*pout)[4] );
	extern DO_INLINE void CopyMatrix( const float (*pin)[4], float (*pout)[4] );
	extern DO_INLINE Vector AdjustAnglesToNormal( const Vector& normal, const Vector& angles );
	extern DO_INLINE float FindMinValueOf3( float v1, float v2, float v3 );
	extern DO_INLINE float FindMaxValueOf3( float v1, float v2, float v3 );
	extern DO_INLINE void FindMinMaxValuesOf3( float v1, float v2, float v3, float& min, float& max );
};
#include "com_math_inline.hpp"
#endif //Common::MATH_H