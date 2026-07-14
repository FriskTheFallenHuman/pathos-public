/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef ANIMINFO_H
#define ANIMINFO_H

#include "entity_state.h"

typedef CArray<pmatrix3x4_t> BoneTransformArray_t;

struct entity_animinfo_t
{
	entity_animinfo_t():
		numbones(0),
		lastframe(0),
		lastsequence(0),
		prevframe_frame(0),
		prevframe_sequence(0),
		lastmouth(0),
		scale(0),
		lastsequencetime(0)
	{
		memset(rotation, 0, sizeof(rotation));
		memset(lastcontroller, 0, sizeof(lastcontroller));
		memset(lastblending, 0, sizeof(lastblending));
	}

	BoneTransformArray_t bones;
	BoneTransformArray_t weightbones;

	Int32	numbones;

	float	lastframe;
	Int32	lastsequence;

	// Used for events
	float	prevframe_frame;
	Int32	prevframe_sequence;

	float	rotation[3][4];
	Vector	lastangles;
	Vector	lastorigin;

	Byte	lastmouth;
	Byte	lastcontroller[MAX_CONTROLLERS];
	Byte	lastblending[MAX_BLENDING];

	float	scale;

	// Used by interpolation
	double	lastsequencetime;
};
#endif //ANIMINFO_H