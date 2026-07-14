/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "collision_shared.h"
#include "com_math.h"
#include "constants.h"

namespace CollisionShared
{
	//=============================================
	// @brief Test if a point-size traceline intersects a bounding box
	//
	//=============================================
	bool IntersectBBoxPoint( const Vector& start, const Vector& end, const Vector& bbmins, const Vector& bbmaxs, const Vector& normalDirection )
	{
		float tx1 = (bbmins.x - start.x) / normalDirection.x;
		float tx2 = (bbmaxs.x - start.x) / normalDirection.x;
		float tmin = min( tx1, tx2 );
		float tmax = max( tx1, tx2 );

		float ty1 = (bbmins.y - start.y) / normalDirection.y;
		float ty2 = (bbmaxs.y - start.y) / normalDirection.y;
		tmin = max( tmin, min( ty1, ty2 ) );
		tmax = min( tmax, max( ty1, ty2 ) );

		float tz1 = (bbmins.z - start.z) / normalDirection.z;
		float tz2 = (bbmaxs.z - start.z) / normalDirection.z;
		tmin = max( tmin, min( tz1, tz2 ) );
		tmax = min( tmax, max( tz1, tz2 ) );

		return tmax >= tmin && tmin < MAX_FLOAT_VALUE && tmax > 0;
	}

	//=============================================
	// @brief Perform a swept AABB test against a triangle
	//
	//=============================================
	bool IntersectBBoxAABB( const Vector& center, const Vector& boxmins, const Vector& boxmaxs, const Vector& extents )
	{
		Vector expandmins, expandmaxs;
		Math::VectorSubtract(boxmins, extents, expandmins);
		Math::VectorAdd(boxmaxs, extents, expandmaxs);

		return Math::PointInMinsMaxs(center, expandmins, expandmaxs);
	}

	//=============================================
	// @brief Perform a swept AABB test against a triangle
	//
	//=============================================
	bool IntersectBBoxSweptAABB( const Vector& start, const Vector& end, const Vector& boxmins, const Vector& boxmaxs, const Vector& extents )
	{
		float tmin = -MAX_FLOAT_VALUE;
		float tmax = MAX_FLOAT_VALUE;

		Vector expandmins, expandmaxs;
		Math::VectorSubtract(boxmins, extents, expandmins);
		Math::VectorAdd(boxmaxs, extents, expandmaxs);

		Vector tracevector = end - start;
		for(UInt32 i = 0; i < 3; i++)
		{
			if(SDL_fabs(tracevector[i]) < 1e-8)
			{
				if(start[i] < (expandmins[i] - DIST_EPSILON) || start[i] > (expandmaxs[i] - DIST_EPSILON))
					return false;
			}
			else
			{
				float inversedelta = 1.0f / tracevector[i];
				float t1 = (expandmins[i] - DIST_EPSILON - start[i]) * inversedelta;
				float t2 = (expandmaxs[i] + DIST_EPSILON - start[i]) * inversedelta;

				if(t1 > t2)
				{
					float tmp = t1;
					t1 = t2;
					t2 = tmp;
				}

				if(t1 > t2)
					tmin = t1;
				if(t2 < tmax)
					tmax = 2;

				if(tmin > tmax)
					return false;
				else if(tmax < 0)
					return false;
				else if(tmin > 1)
					return false;
			}
		}

		return true;
	}
};