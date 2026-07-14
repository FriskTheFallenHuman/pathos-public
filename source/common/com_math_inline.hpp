/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef COM_MATH_INLINE_HPP
#define COM_MATH_INLINE_HPP

namespace Math
{
	//=============================================
	// @brief Compares a vector to another vector
	//
	// @param v1 First vector to compare
	// @param v2 Second vector to compare
	// @return true if vectors match, false otherwise
	//=============================================
	DO_INLINE bool VectorCompare( const Vector& v1, const Vector& v2 )
	{
		for(Uint32 i = 0; i < 3; i++)
		{
			if(v1[i] != v2[i])
				return false;
		}

		return true;
	}

	//=============================================
	// @brief Copies a vector into another vector
	//
	// @param src Source vector
	// @param dest Destination vector
	//=============================================
	DO_INLINE void VectorCopy( const Vector& src, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = src[i];
	}

	//=============================================
	// @brief Copies a float array of 3 floats into a vector
	//
	// @param src Source array of floating point values
	// @param dest Destination vector
	//=============================================
	DO_INLINE void VectorCopy( const float* psrc, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = psrc[i];
	}

	//=============================================
	// @brief Copies a floating point array of 3 floats
	// into another array of 3 floats
	//
	// @param src Source array of floating point values
	// @param dest Destination array of floating point values
	//=============================================
	DO_INLINE void VectorCopy( const float* psrc, float* pdest )
	{
		for(Uint32 i = 0; i < 3; i++)
			pdest[i] = psrc[i];
	}

	//=============================================
	// @brief Copies a vector into an array of 3 
	// floating point values
	//
	// @param src Source vector
	// @param dest Destination array of floating point values
	//=============================================
	DO_INLINE void VectorCopy( const Vector& src, float* pdest )
	{
		for(Uint32 i = 0; i < 3; i++)
			pdest[i] = src[i];
	}

	//=============================================
	// @brief Clears a vector to zero values
	//
	// @param dest Vector to clear
	//=============================================
	DO_INLINE void VectorClear( Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = 0;
	}

	//=============================================
	// @brief Subtracts one vector from another
	//
	// @param v1 Vector to subtract from
	// @param v2 Vector to subtract
	// @param dest Destination vector to hold the result
	//=============================================
	DO_INLINE void VectorSubtract( const Vector& v1, const Vector& v2, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = v1[i] - v2[i];
	}

	//=============================================
	// @brief Adds a vector to another vector
	//
	// @param v1 Vector to add to
	// @param v2 Vector to add
	// @param dest Destination vector to hold the result
	//=============================================
	DO_INLINE void VectorAdd( const Vector& v1, const Vector& v2, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = v1[i] + v2[i];
	}

	//=============================================
	// @brief Multiplies and adds a vector to another vector
	//
	// @param v1 Vector to add to
	// @param scale Value to scale v2 by
	// @param v2 Vector to multiply then add
	// @param dest Destination vector to hold the result
	//=============================================
	DO_INLINE void VectorMA( const Vector& v1, float scale, const Vector& v2, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = v1[i] + v2[i]*scale;
	}

	//=============================================
	// @brief Scales a vector
	//
	// @param src Vector to scale
	// @param scale Amount to scale the vector by
	// @param dest Destination vector to hold the result
	//=============================================
	DO_INLINE void VectorScale( const Vector& src, float scale, Vector& dest )
	{
		for(Uint32 i = 0; i < 3; i++)
			dest[i] = src[i]*scale;
	}

	//=============================================
	// @brief Performs a dot product on two vectors
	//
	// @param v1 First vector of dot product
	// @param v2 Second vector of dot product
	// @return Result of dot product
	//=============================================
	DO_INLINE float DotProduct( const Vector& v1, const Vector& v2 )
	{
		return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
	}

	//=============================================
	// @brief Performs a dot product on two vectors
	//
	// @param v1 First vector of dot product
	// @param pv2 Pointer to second vector of dot product
	// @return Result of dot product
	//=============================================
	DO_INLINE float DotProduct( const Vector& v1, const float *pv2 )
	{
		return (v1[0] * pv2[0] + v1[1] * pv2[1] + v1[2] * pv2[2]);
	}

	//=============================================
	// @brief Performs a dot product on two float arrays with 4 elements
	//
	// @param v1 First float array of dot product
	// @param v2 Second float array of dot product
	// @return Result of dot product
	//=============================================
	DO_INLINE float DotProduct4( const float* pv1, const float *pv2 )
	{
		return (pv1[0] * pv2[0] + pv1[1] * pv2[1] + pv1[2] * pv2[2] + pv1[3] * pv2[3]);
	}

	//=============================================
	// @brief Get forward vector of an angle
	//
	// @param angles Angles to get vectors from
	// @param pforward Forward vector result
	//=============================================
	DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward )
	{
		Math::AngleVectors(angles, pforward, nullptr, nullptr);
	}

	//=============================================
	// @brief Get forward and right vectors of an angle
	//
	// @param angles Angles to get vectors from
	// @param pforward Forward vector result
	// @param pright Right vector result
	//=============================================
	DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward, Vector* pright )
	{
		Math::AngleVectors(angles, pforward, pright, nullptr);
	}

	//=============================================
	// @brief Get forward, right and up vectors of an angle
	//
	// @param angles Angles to get vectors from
	// @param pforward Forward vector result
	// @param pright Right vector result
	// @param pup Up vector result
	//=============================================
	DO_INLINE void AngleVectors( const Vector& angles, Vector* pforward, Vector* pright, Vector* pup )
	{
		float angle = static_cast<float>(angles[YAW] * (M_PI * 2 / 360));
		const float sy = sin(angle);
		const float cy = cos(angle);
		angle = static_cast<float>(angles[PITCH] * (M_PI * 2 / 360));
		const float sp = sin(angle);
		const float cp = cos(angle);
		angle = static_cast<float>(angles[ROLL] * (M_PI * 2 / 360));
		const float sr = sin(angle);
		const float cr = cos(angle);

		if (pforward)
		{
			pforward->x = cp*cy;
			pforward->y = cp*sy;
			pforward->z = -sp;
		}

		if (pright)
		{
			pright->x = (-1*sr*sp*cy+-1*cr*-sy);
			pright->y = (-1*sr*sp*sy+-1*cr*cy);
			pright->z = -1*sr*cp;
		}

		if (pup)
		{
			pup->x = (cr*sp*cy+-sr*-sy);
			pup->y = (cr*sp*sy+-sr*cy);
			pup->z = cr*cp;
		}
	}

	//=============================================
	// @brief Get transpose forward vector of an angle
	//
	// @param angles Angles to get vectors of
	// @param pforward Forward vector result
	//=============================================
	DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward )
	{
		Math::AngleVectorsTranspose(angles, pforward, nullptr, nullptr);
	}

	//=============================================
	// @brief Get transpose forward and right vectors of an angle
	//
	// @param angles Angles to get vectors from
	// @param pforward Forward vector result
	// @param pright Right vector result
	//=============================================
	DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward, Vector* pright )
	{
		Math::AngleVectorsTranspose(angles, pforward, pright, nullptr);
	}

	//=============================================
	// @brief Get transpose forward, right and up vectors of an angle
	//
	// @param angles Angles to get vectors from
	// @param pforward Forward vector result
	// @param pright Right vector result
	// @param pup Up vector result
	//=============================================
	DO_INLINE void AngleVectorsTranspose( const Vector& angles, Vector* pforward, Vector* pright, Vector* pup )
	{
		float angle = static_cast<float>(angles[YAW] * (M_PI * 2 / 360));
		const float sy = sin(angle);
		const float cy = cos(angle);
		angle = static_cast<float>(angles[PITCH] * (M_PI * 2 / 360));
		const float sp = sin(angle);
		const float cp = cos(angle);
		angle = static_cast<float>(angles[ROLL] * (M_PI * 2 / 360));
		const float sr = sin(angle);
		const float cr = cos(angle);

		if (pforward)
		{
			pforward->x	= cp*cy;
			pforward->y	= (sr*sp*cy+cr*-sy);
			pforward->z	= (cr*sp*cy+-sr*-sy);
		}
	
		if (pright)
		{
			pright->x	= cp*sy;
			pright->y	= (sr*sp*sy+cr*cy);
			pright->z	= (cr*sp*sy+-sr*cy);
		}

		if (pup)
		{
			pup->x		= -sp;
			pup->y		= sr*cp;
			pup->z		= cr*cp;
		}
	}

	//=============================================
	// @brief Returns the cross product of two vectors
	//
	// @param v1 First vector
	// @param v2 Second vector
	// @param dest Destination to hold cross product
	//=============================================
	DO_INLINE void CrossProduct( const Vector& v1, const Vector& v2, Vector& dest )
	{
		dest[0] = v1[1]*v2[2] - v1[2]*v2[1];
		dest[1] = v1[2]*v2[0] - v1[0]*v2[2];
		dest[2] = v1[0]*v2[1] - v1[1]*v2[0];
	}

	//=============================================
	// @brief Normalizes an angle into the 0-360 range
	//
	// @param angle Angle value to normalize
	// @result Normalized angle
	//=============================================
	DO_INLINE float AngleMod( float angle )
	{
		float _angle;
		if(angle > 360)
			_angle = angle - (static_cast<Int32>(angle/360))*360;
		else if(angle < 0)
			_angle = angle + (static_cast<Int32>(angle/360) + 1)*360;
		else
			_angle = angle;

		return _angle;
	}

	//=============================================
	// @brief Returns the difference between two angles
	//
	// @param destangle Target angle value
	// @param srcangle Current angle value
	// @result Difference between the two angles
	//=============================================
	DO_INLINE float AngleDiff( float destangle, float srcangle )
	{
		float delta = destangle - srcangle;
		if(destangle > srcangle)
		{
			if(delta >= 180)
				delta -= 360;
		}
		else
		{
			if(delta <= -380)
				delta += 360;
		}

		return delta;
	}

	//=============================================
	// @brief Normalizes a vector
	//
	// @param v Vector to normalize
	// @result Original length of the vector
	//=============================================
	DO_INLINE float VectorNormalize( Vector& v )
	{
		float length = Math::DotProduct(v, v);
		length = sqrt(length);

		if (length)
		{
			float ilength = 1/length;
			v[0] *= ilength;
			v[1] *= ilength;
			v[2] *= ilength;
		}
		
		return length;
	}

	//=============================================
	// @brief Tells if a vector has only zero values
	//
	// @param v Vector to test
	// @return true if the vector only has zero values,
	// false otherwise
	//=============================================
	DO_INLINE bool IsVectorZero( const Vector& v )
	{
		if(v[0] || v[1] || v[2])
			return false;
		else
			return true;
	}

	//=============================================
	// @brief Checks if two bounding boxes touch eachother
	//
	// @param mins1 Mins of first bounding box
	// @param maxs1 Maxs of first bounding box
	// @param mins2 Mins of second bounding box
	// @param maxs2 Maxs of second bounding box
	// @return true if bounding boxes intersect, false otherwise
	//=============================================
	DO_INLINE bool CheckMinsMaxs( const Vector& mins1, const Vector& maxs1, const Vector& mins2, const Vector& maxs2 )
	{
		if (mins1[0] > maxs2[0]) 
			return true;

		if (mins1[1] > maxs2[1]) 
			return true;

		if (mins1[2] > maxs2[2]) 
			return true;

		if (maxs1[0] < mins2[0]) 
			return true;

		if (maxs1[1] < mins2[1]) 
			return true;

		if (maxs1[2] < mins2[2]) 
			return true;

		return false;
	}

	//=============================================
	// @brief Tells if a coordinate is inside a bounding box
	//
	// @param point Coordinate to test
	// @param mins Mins of bounding box
	// @param maxs Maxs of bounding box
	// @return true if point is inside the bounding box,
	// false otherwise
	//=============================================
	DO_INLINE bool PointInMinsMaxs( const Vector& point, const Vector& mins, const Vector& maxs )
	{
		for(Uint32 i = 0; i < 3; i++)
		{
			if(point[i] < mins[i])
				return false;

			if(point[i] > maxs[i])
				return false;
		}

		return true;
	}

	//=============================================
	// @brief Rotates a vector into the entity's local space
	//
	// @param angles Angles of entity
	// @param vec Reference to vector to rotate to local space
	//=============================================
	DO_INLINE void RotateToEntitySpace( const Vector& angles, Vector& vec )
	{
		Vector vtemp, vforward, vright, vup;
		Math::VectorCopy(vec, vtemp);

		Math::AngleVectors(angles, &vforward, &vright, &vup);
		vec[0] = Math::DotProduct(vtemp, vforward);
		vec[1] = -Math::DotProduct(vtemp, vright);
		vec[2] = Math::DotProduct(vtemp, vup);
	}

	//=============================================
	// @brief Takes a vector and rotates it from entity space
	// into world space
	//
	// @param angles Angles of entity to rotate from
	// @param vec Reference to vector to rotate to world space
	//=============================================
	DO_INLINE void RotateFromEntitySpace( const Vector& angles, Vector& vec )
	{
		Vector vtemp, vforward, vright, vup;
		Math::VectorCopy(vec, vtemp);

		Math::AngleVectorsTranspose(angles, &vforward, &vright, &vup);
		vec[0] = Math::DotProduct(vtemp, vforward);
		vec[1] = Math::DotProduct(vtemp, vright);
		vec[2] = Math::DotProduct(vtemp, vup);
	}

	//=============================================
	// @brief Takes the angles of an entity, and builds
	// a rotation matrix from said angles
	//
	// @param angles Angles of entity
	// @param pmatrix Output matrix of 3x4 floats to hold the
	// rotation matrix
	//=============================================
	DO_INLINE void AngleMatrix( const Vector& angles, float (*pmatrix)[4] )
	{
		float angle = angles[YAW]*(M_PI*2/360);
		float sy = SDL_sin(angle);
		float cy = SDL_cos(angle);

		angle = angles[PITCH]*(M_PI*2/360);
		float sp = SDL_sin(angle);
		float cp = SDL_cos(angle);

		angle = angles[ROLL]*(M_PI*2/360);
		float sr = SDL_sin(angle);
		float cr = SDL_cos(angle);

		pmatrix[0][0] = cp*cy;
		pmatrix[1][0] = cp*sy;
		pmatrix[2][0] = -sp;

		pmatrix[0][1] = sr*sp*cy+cr*-sy;
		pmatrix[1][1] = sr*sp*sy+cr*cy;
		pmatrix[2][1] = sr*cp;

		pmatrix[0][2] = (cr*sp*cy+-sr*-sy);
		pmatrix[1][2] = (cr*sp*sy+-sr*cy);
		pmatrix[2][2] = cr*cp;

		pmatrix[0][3] = 0;
		pmatrix[1][3] = 0;
		pmatrix[2][3] = 0;
	}

	//=============================================
	// @brief Takes the angles of an entity, and builds
	// an inverse rotation matrix from said angles
	//
	// @param angles Angles of entity
	// @param pmatrix Output matrix of 3x4 floats to hold the
	// inverse rotation matrix
	//=============================================
	DO_INLINE void AngleInverseMatrix( const Vector& angles, float (*pmatrix)[4] )
	{
		float angle = angles[YAW] * (M_PI*2 / 360);
		float sy = sin(angle);
		float cy = cos(angle);
		angle = angles[PITCH] * (M_PI*2 / 360);
		float sp = sin(angle);
		float cp = cos(angle);
		angle = angles[ROLL] * (M_PI*2 / 360);
		float sr = sin(angle);
		float cr = cos(angle);

		pmatrix[0][0] = cp*cy;
		pmatrix[0][1] = cp*sy;
		pmatrix[0][2] = -sp;

		pmatrix[1][0] = sr*sp*cy+cr*-sy;
		pmatrix[1][1] = sr*sp*sy+cr*cy;
		pmatrix[1][2] = sr*cp;

		pmatrix[2][0] = (cr*sp*cy+-sr*-sy);
		pmatrix[2][1] = (cr*sp*sy+-sr*cy);
		pmatrix[2][2] = cr*cp;

		pmatrix[0][3] = 0;
		pmatrix[1][3] = 0;
		pmatrix[2][3] = 0;
	}

	//=============================================
	// @brief Rotates a vector by a matrix
	//
	// @param vec Vector to rotate
	// @param pmatrix 3x4 matrix to rotate with
	// @param out Reference to vector to hold the result
	//=============================================
	DO_INLINE void VectorRotate( const Vector& vec, const float (*pmatrix)[4], Vector& out )
	{
		out[0] = (vec[0] * pmatrix[0][0]) + (vec[1] * pmatrix[0][1]) + (vec[2] * pmatrix[0][2]);
		out[1] = (vec[0] * pmatrix[1][0]) + (vec[1] * pmatrix[1][1]) + (vec[2] * pmatrix[1][2]);
		out[2] = (vec[0] * pmatrix[2][0]) + (vec[1] * pmatrix[2][1]) + (vec[2] * pmatrix[2][2]);
	}

	//=============================================
	// @brief Rotates a vector by a matrix, but inverse
	//
	// @param vec Vector to rotate
	// @param pmatrix 3x4 matrix to rotate with
	// @param out Reference to vector to hold the result
	//=============================================
	DO_INLINE void VectorInverseRotate( const Vector& vec, const float (*pmatrix)[4], Vector& out )
	{
		out[0] = vec[0]*pmatrix[0][0] + vec[1]*pmatrix[1][0] + vec[2]*pmatrix[2][0];
		out[1] = vec[0]*pmatrix[0][1] + vec[1]*pmatrix[1][1] + vec[2]*pmatrix[2][1];
		out[2] = vec[0]*pmatrix[0][2] + vec[1]*pmatrix[1][2] + vec[2]*pmatrix[2][2];
	}

	//=============================================
	// @brief Takes a forward and a left vector, and
	// turns it into their resulting angles
	//
	// @param forward Forward vector defining the forward direction
	// @param left Left vector
	// @result Angles calculated from forward and left vectors
	//=============================================
	DO_INLINE Vector VectorToAngles( const Vector& forward, const Vector& left )
	{
		// I think I referenced the Source SDK for this math solution, so credit
		// goes to Valve for the code I referenced.
		Vector angles;
	
		const float xyDist = sqrtf( forward[0] * forward[0] + forward[1] * forward[1] );
		if ( xyDist > 0.001f )
		{
			angles[1] = RAD2DEG( SDL_atan2f( forward[1], forward[0] ) );
			angles[0] = RAD2DEG( SDL_atan2f( -forward[2], xyDist ) );
			const float up_z = (left[1] * forward[0]) - (left[0] * forward[1]);
			angles[2] = RAD2DEG( SDL_atan2f( left[2], up_z ) );
		}
		else
		{
			angles[0] = RAD2DEG( SDL_atan2f( -forward[2], xyDist ) );
			angles[1] = RAD2DEG( SDL_atan2f( -left[0], left[1] ) );
			angles[2] = 0;
		}	

		return angles;
	}

	//=============================================
	// @brief Takes a forward vector, and turns it
	// into an angle. Not as reliable or precise as
	// using both a forward and a left vector.
	//
	// @param forward Forward vector defining the forward direction
	// @result Angles calculated from forward vector
	//=============================================
	DO_INLINE Vector VectorToAngles( const Vector& forward )
	{
		float yaw = 0;
		float pitch = 0;

		if(forward[1] == 0 && forward[0] == 0)
		{
			yaw = 0;
			if(forward[2] > 0)
				pitch = 90;
			else
				pitch = 270;
		}
		else
		{
			yaw = static_cast<float>(SDL_atan2(forward[1], forward[0]) * 180/M_PI);
			if(yaw < 0)
				yaw += 360.0f;

			const float tmp = SDL_sqrt(forward[0]*forward[0]+forward[1]*forward[1]);
			pitch = static_cast<float>(SDL_atan2(forward[2], tmp)*180/M_PI);
			if(pitch < 0)
				pitch += 360.0f;
		}

		Vector angles;
		angles[PITCH] = pitch;
		angles[YAW] = yaw;
		angles[ROLL] = 0;

		return angles;
	}

	//=============================================
	// @brief Multiplies a position vector by a 4x4 matrix
	//
	// @param flmatrix The 16 element float matrix to multiply with
	// @param vecin Vector to multiply with the matrix
	// @param vecout Result vector
	//=============================================
	DO_INLINE void MatMultPosition( const float *flmatrix, const Vector& vecin, Vector *vecout )
	{
		vecout->x = vecin[0]*flmatrix[0] + vecin[1]*flmatrix[4] + vecin[2]*flmatrix[8] + flmatrix[12];
		vecout->y = vecin[0]*flmatrix[1] + vecin[1]*flmatrix[5] + vecin[2]*flmatrix[9] + flmatrix[13];
		vecout->z = vecin[0]*flmatrix[2] + vecin[1]*flmatrix[6] + vecin[2]*flmatrix[10] + flmatrix[14];
	}

	//=============================================
	// @brief Multiplies a vector by a 4x4 matrix
	//
	// @param flmatrix The 16 element float matrix to multiply with
	// @param vecin Vector to multiply with the matrix
	// @param vecout Result vector
	//=============================================
	DO_INLINE void MatMult( const float *flmatrix, const Vector& vecin, Vector *vecout )
	{
		vecout->x = vecin[0]*flmatrix[0] + vecin[1]*flmatrix[4] + vecin[2]*flmatrix[8];
		vecout->y = vecin[0]*flmatrix[1] + vecin[1]*flmatrix[5] + vecin[2]*flmatrix[9];
		vecout->z = vecin[0]*flmatrix[2] + vecin[1]*flmatrix[6] + vecin[2]*flmatrix[10];
	}

	//=============================================
	// @brief Multiplies a 4 element vector by a 4x4 matrix
	//
	// @param flmatrix The 16 element float matrix to multiply with
	// @param vecin 4 element vector to multiply with the matrix
	// @param vecout Result vector
	//=============================================
	DO_INLINE void MatMult4( const float *flmatrix, const float *vecin, float *vecout )
	{
		vecout[0] = vecin[0]*flmatrix[0] + vecin[1]*flmatrix[4] + vecin[2]*flmatrix[8] + vecin[3]*flmatrix[12];
		vecout[1] = vecin[0]*flmatrix[1] + vecin[1]*flmatrix[5] + vecin[2]*flmatrix[9] + vecin[3]*flmatrix[13];
		vecout[2] = vecin[0]*flmatrix[2] + vecin[1]*flmatrix[6] + vecin[2]*flmatrix[10] + vecin[3]*flmatrix[14];
		vecout[3] = vecin[0]*flmatrix[3] + vecin[1]*flmatrix[7] + vecin[2]*flmatrix[11] + vecin[3]*flmatrix[15];
	}

	//=============================================
	// @brief Returns the up and right vectors generated from a forward vector
	//
	// @param forward Forward vector
	// @param up Result up vector
	// @param right Result right vector
	//=============================================
	DO_INLINE void GetUpRight( const Vector& forward, Vector &up, Vector &right )
	{
		// Thanks to BUzer for the original code.
		Math::VectorClear(up);

		if (forward.x || forward.y)
			up.z = 1;
		else
			up.x = 1;

		Math::CrossProduct(forward, up, right);
		Math::VectorNormalize(right);

		Math::CrossProduct(forward, right, up);
		Math::VectorNormalize(up);
	};

	//=============================================
	// @brief Transforms a vector by a 3x4 float matrix
	//
	// @param in Vector to transform
	// @param pmatrix The 3x4 matrix to multiply with
	// @param out Result vector
	//=============================================
	DO_INLINE void VectorTransform( const Vector& in, float (*pmatrix)[4], Vector& out )
	{
		out[0] = (in[0] * pmatrix[0][0]) + (in[1] * pmatrix[0][1]) + (in[2] * pmatrix[0][2]) + pmatrix[0][3];
		out[1] = (in[0] * pmatrix[1][0]) + (in[1] * pmatrix[1][1]) + (in[2] * pmatrix[1][2]) + pmatrix[1][3];
		out[2] = (in[0] * pmatrix[2][0]) + (in[1] * pmatrix[2][1]) + (in[2] * pmatrix[2][2]) + pmatrix[2][3];
	}

	//=============================================
	// @brief Transforms a vector by a matrix, but inverse
	//
	// @param vec Vector to transform
	// @param pmatrix 3x4 matrix to rotate with
	// @param out Reference to vector to hold the result
	//=============================================
	DO_INLINE void VectorInverseTransform( const Vector& vec, const float (*pmatrix)[4], Vector& out )
	{
		// We first have to subtract the position, THEN inverse rotate
		Vector tmp;
		for(Uint32 i = 0; i < 3; i++)
			tmp[i] = vec[i] - pmatrix[i][3];

		out[0] = tmp[0]*pmatrix[0][0] + tmp[1]*pmatrix[1][0] + tmp[2]*pmatrix[2][0];
		out[1] = tmp[0]*pmatrix[0][1] + tmp[1]*pmatrix[1][1] + tmp[2]*pmatrix[2][1];
		out[2] = tmp[0]*pmatrix[0][2] + tmp[1]*pmatrix[1][2] + tmp[2]*pmatrix[2][2];
	}

	//=============================================
	// @brief Takes a quaternion, and turns it into a 3x4 matrix
	//
	// @param quaternion Input quaternion
	// @param pmatrix Result 3x4 matrix
	//=============================================
	DO_INLINE void QuaternionMatrix( const vec4_t& quaternion, float (*pmatrix)[4] )
	{
		pmatrix[0][0] = 1.0 - 2.0 * quaternion[1] * quaternion[1] - 2.0 * quaternion[2] * quaternion[2];
		pmatrix[1][0] = 2.0 * quaternion[0] * quaternion[1] + 2.0 * quaternion[3] * quaternion[2];
		pmatrix[2][0] = 2.0 * quaternion[0] * quaternion[2] - 2.0 * quaternion[3] * quaternion[1];

		pmatrix[0][1] = 2.0 * quaternion[0] * quaternion[1] - 2.0 * quaternion[3] * quaternion[2];
		pmatrix[1][1] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[2] * quaternion[2];
		pmatrix[2][1] = 2.0 * quaternion[1] * quaternion[2] + 2.0 * quaternion[3] * quaternion[0];

		pmatrix[0][2] = 2.0 * quaternion[0] * quaternion[2] + 2.0 * quaternion[3] * quaternion[1];
		pmatrix[1][2] = 2.0 * quaternion[1] * quaternion[2] - 2.0 * quaternion[3] * quaternion[0];
		pmatrix[2][2] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[1] * quaternion[1];
	}

	//=============================================
	// @brief Blends two quaternions together into an output quaternion
	//
	// @param q1 First quaternion
	// @param q2 Second quaternion
	// @param interp A value from 0-1 determining how the quaternions are blended together
	// @param outq Reference to vec4_t to hold the resulting quaternion
	//=============================================
	DO_INLINE void QuaternionBlend( const vec4_t& q1, const vec4_t& q2, float interp, vec4_t& outq )
	{
		float a = 0;
		float b = 0;

		vec4_t quat1;
		for(Uint32 i = 0; i < 4; i++)
		{
			a += (q1[i]-q2[i])*(q1[i]-q2[i]);
			b += (q1[i]+q2[i])*(q1[i]+q2[i]);
		}

		if(a > b)
		{
			for(Uint32 i = 0; i < 4; i++)
				quat1[i] = -q1[i];
		}
		else
		{
			for(Uint32 i = 0; i < 4; i++)
				quat1[i] = q1[i];
		}

		float sclq1;
		float sclq2;
		const float cosom = Math::DotProduct4(quat1, q2);
		if(1.0+cosom > 0.000001f)
		{
			if(1.0-cosom > 0.00001f)
			{
				const float omega = SDL_acos(cosom);
				const float sinom = SDL_sin(omega);
				sclq1 = SDL_sin((1.0f-interp)*omega)/sinom;
				sclq2 = SDL_sin(interp*omega)/sinom;
			}
			else
			{
				sclq1 = 1.0-interp;
				sclq2 = interp;
			}
		}
		else
		{
			quat1[0] = -q2[1];
			quat1[1] = q2[0];
			quat1[2] = -q2[3];
			quat1[3] = q2[2];

			sclq1 = SDL_sin((1.0f-interp) * (0.5f*M_PI));
			sclq2 = SDL_sin(interp*(0.5f*M_PI));
		}

		for(Uint32 i = 0; i < 4; i++)
			outq[i] = sclq1*quat1[i] + sclq2*q2[i];
	}

	//=============================================
	// @brief Takes an angle and turns it into a quaternion
	//
	// @param angles Input angles
	// @param quaternion Result quaternion
	//=============================================
	DO_INLINE void AngleQuaternion( const Vector& angles, vec4_t& quaternion )
	{
		// FIXME: rescale the inputs to 1/2 angle
		float angle = angles[2] * 0.5;
		float sy = sin(angle);
		float cy = cos(angle);
		angle = angles[1] * 0.5;
		float sp = sin(angle);
		float cp = cos(angle);
		angle = angles[0] * 0.5;
		float sr = sin(angle);
		float cr = cos(angle);

		quaternion[0] = sr*cp*cy-cr*sp*sy; // X
		quaternion[1] = cr*sp*cy+sr*cp*sy; // Y
		quaternion[2] = cr*cp*sy-sr*sp*cy; // Z
		quaternion[3] = cr*cp*cy+sr*sp*sy; // W
	}

	//=============================================
	// @brief Transforms a 3x4 matrix by another 3x4 matrix
	//
	// @param pin1 Input 3x4 matrix 1
	// @param pin2 Input 3x4 matrix 2
	// @param pout Output 3x4 matrix
	//=============================================
	DO_INLINE void ConcatTransforms( const float (*pin1)[4], const float (*pin2)[4], float (*pout)[4] )
	{
		pout[0][0] = pin1[0][0] * pin2[0][0] + pin1[0][1] * pin2[1][0] + pin1[0][2] * pin2[2][0];
		pout[0][1] = pin1[0][0] * pin2[0][1] + pin1[0][1] * pin2[1][1] + pin1[0][2] * pin2[2][1];
		pout[0][2] = pin1[0][0] * pin2[0][2] + pin1[0][1] * pin2[1][2] + pin1[0][2] * pin2[2][2];
		pout[0][3] = pin1[0][0] * pin2[0][3] + pin1[0][1] * pin2[1][3] + pin1[0][2] * pin2[2][3] + pin1[0][3];
		pout[1][0] = pin1[1][0] * pin2[0][0] + pin1[1][1] * pin2[1][0] + pin1[1][2] * pin2[2][0];
		pout[1][1] = pin1[1][0] * pin2[0][1] + pin1[1][1] * pin2[1][1] + pin1[1][2] * pin2[2][1];
		pout[1][2] = pin1[1][0] * pin2[0][2] + pin1[1][1] * pin2[1][2] + pin1[1][2] * pin2[2][2];
		pout[1][3] = pin1[1][0] * pin2[0][3] + pin1[1][1] * pin2[1][3] + pin1[1][2] * pin2[2][3] + pin1[1][3];
		pout[2][0] = pin1[2][0] * pin2[0][0] + pin1[2][1] * pin2[1][0] + pin1[2][2] * pin2[2][0];
		pout[2][1] = pin1[2][0] * pin2[0][1] + pin1[2][1] * pin2[1][1] + pin1[2][2] * pin2[2][1];
		pout[2][2] = pin1[2][0] * pin2[0][2] + pin1[2][1] * pin2[1][2] + pin1[2][2] * pin2[2][2];
		pout[2][3] = pin1[2][0] * pin2[0][3] + pin1[2][1] * pin2[1][3] + pin1[2][2] * pin2[2][3] + pin1[2][3];
	}

	//=============================================
	// @brief Copies a 3x4 matrix into another
	//
	// @param pin Input 3x4 matrix
	// @param pout Result 3x4 matrix
	//=============================================
	DO_INLINE void CopyMatrix( const float (*pin)[4], float (*pout)[4] )
	{
		for(Uint32 i = 0; i < 3; i++)
		{
			for(Uint32 j = 0; j < 4; j++)
				pout[i][j] = pin[i][j];
		}
	}

	//=============================================
	// @brief Adjusts an angle to a surface normal
	//
	// @param normal Surface normal to adjust to
	// @param angles Angles to adjust
	// @result Angles adjusted to surface normal
	//=============================================
	DO_INLINE Vector AdjustAnglesToNormal( const Vector& normal, const Vector& angles )
	{
		// Thanks to Magic Nipples for the code to align the bike
		Vector planeAngle = Math::VectorToAngles(normal);
		float playerYawX = angles[1];
		if (playerYawX > 180) 
			playerYawX -= 360;
		if (playerYawX < -180) 
			playerYawX += 360;

		float planeYaw = planeAngle[1];
		if (planeYaw > 180) 
			planeYaw -= 360;
		if (planeYaw < -180) 
			planeYaw += 360;

		float yawDiffX = planeYaw - playerYawX;
		if (yawDiffX > 180) 
			yawDiffX -= 360;
		if (yawDiffX < -180) 
			yawDiffX += 360;

		yawDiffX = SDL_fabs(yawDiffX);
		const float crossYawX = ((planeAngle[0] * yawDiffX) / 90 - planeAngle[0]);
	
		float playerYawY = angles[1] + 90;
		if (playerYawY > 180) 
			playerYawY -= 360;
		if (playerYawY < -180) 
			playerYawY += 360;

		float yawDiffY = planeYaw - playerYawY;
		if (yawDiffY > 180) 
			yawDiffY -= 360;
		if (yawDiffY < -180) 
			yawDiffY += 360;

		yawDiffY = SDL_fabs(yawDiffY);

		float targetX;
		float targetY;
		float crossYawY = ((planeAngle[0] * yawDiffY) / 90 - planeAngle[0]);
		if (planeAngle[0] == 90)
		{
			targetX = 0;
			targetY = 0;
		}
		else
		{
			targetX = crossYawX * SDL_fabs((planeAngle[0] - 90) * 0.016);
			targetY = crossYawY * SDL_fabs((planeAngle[0] - 90) * 0.016);
		}

		Vector outangles;
		outangles[0] = targetX; //magic nipples - engine divides pitch by 3.0. multiply for quick fix.
		outangles[1] = angles[1];
		outangles[2] = targetY;

		return outangles;
	}

	//=============================================
	// @brief Find minimum value out of 3 values
	//
	// @param v1 First value to check
	// @param v2 Second value to check
	// @param v3 Third value to check
	// @return Smallest value of the three
	//=============================================
	DO_INLINE float FindMinValueOf3( float v1, float v2, float v3 )
	{
		return _max(_max(v1, v2), v3);
	}

	//=============================================
	// @brief Find Maximum value out of 3 values
	//
	// @param v1 First value to check
	// @param v2 Second value to check
	// @param v3 Third value to check
	// @return Largest value of the three
	//=============================================
	DO_INLINE float FindMaxValueOf3( float v1, float v2, float v3 )
	{
		return _min(_min(v1, v2), v3);
	}

	//=============================================
	// @brief Find min and max values of 3
	//
	// @param v1 First value to check
	// @param v2 Second value to check
	// @param v3 Third value to check
	// @param min Smallest value of the three
	// @param max Largest value of the three
	//=============================================
	DO_INLINE void FindMinMaxValuesOf3( float v1, float v2, float v3, float& min, float& max )
	{
		min = FindMinValueOf3(v1, v2, v3);
		max = FindMaxValueOf3(v1, v2, v3);
	}
};
#endif //Common::MATH_INLINE_HPP