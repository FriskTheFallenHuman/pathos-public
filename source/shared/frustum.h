/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "plane.h"

// Number of view planes
#define NUM_FRUSTUM_PLANES 4

/*
=================================
CFrustum

=================================
*/
class CFrustum
{
public:
	CFrustum( void );
	~CFrustum( void );

public:
	// Sets up the frustum planes, etc
	void SetFrustum( const Vector& angles, const Vector& origin, float fov, float farplanedist );
	// Sets up the frustum planes, etc
	void SetFrustum( const Vector& angles, const Vector& origin, float fovx, float fovy, float farplanedist );
	// Tells if a bounding box was culled out
	bool CullBBox( const Vector& mins, const Vector& maxs ) const;

	// Sets the extra cull box
	void SetExtraCullBox( const Vector& vMins, const Vector& vMaxs );
	// Disables the extra cull box
	void DisableExtraCullBox( void ) { m_useExtraCullBox = false; }

private:
	// Checks the farplane cull box
	bool CheckCullBox( const Vector& mins, const Vector& maxs ) const;
	// Checks the extra cull box
	bool CheckExtraCullBox( const Vector& mins, const Vector& maxs ) const;

private:
	// Frustum planes
	plane_t m_frustumPlanes[NUM_FRUSTUM_PLANES];
	// Far clipping distance
	UInt32 m_farClipDistance;

	// bounding box mins
	Vector m_cullBoxMins;
	// bounding box maxs
	Vector m_cullBoxMaxs;
	// true if cullbox if used
	bool m_useCullBox;

	// bounding box mins
	Vector m_extraCullBoxMins;
	// bounding box maxs
	Vector m_extraCullBoxMaxs;
	// true if cullbox if used
	bool m_useExtraCullBox;
};

extern DO_INLINE UInt32 BoxOnPlaneSide( const Vector& mins, const Vector& maxs, const plane_t* pplane );
extern DO_INLINE void RotatePointAroundVector( const Vector& dir, const Vector& point, float deg, Vector& dest );
extern DO_INLINE float GetXFOVFromY( float fovY, float ratio );

#include "frustum_inline.hpp"
#endif //FRUSTUM_H