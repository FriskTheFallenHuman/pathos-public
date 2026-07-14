/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "vector.h"

// Autoaim adjust speed
const float AUTOAIM_ADJ_SPEED = 6;

//=============================================
//
//=============================================
void CL_UpdateAutoAim( double frametime, const Vector& idealAutoAim, Vector& currentAutoAim )
{
	if(frametime > 1.0)
		frametime = 1.0;

	float diffX = SDL_fabs(idealAutoAim[0] - currentAutoAim[0]);
	float diffY = SDL_fabs(idealAutoAim[1] - currentAutoAim[1]);
	if(!diffX && !diffY)
		return;

	float mod[2] = {0,0};
	if(diffX == diffY)
	{
		mod[0] = 1.0;
		mod[1] = 1.0;
	}
	else if(diffX > diffY)
	{
		mod[0] = 1.0;
		mod[1] = diffY / diffX;
	}
	else
	{
		mod[0] = diffX / diffY;
		mod[1] = 1.0;
	}

	for(UInt32 i = 0; i < 2; i++)
	{
		float diff = idealAutoAim[i] - currentAutoAim[i];
		float sgn = diff > 0 ? 1 : -1;
		diff = SDL_fabs(diff);

		float add = AUTOAIM_ADJ_SPEED * frametime * mod[i];
		if(add > diff)
			currentAutoAim[i] = idealAutoAim[i];
		else
			currentAutoAim[i] += add * sgn;
	}
}