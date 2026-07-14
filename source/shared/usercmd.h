/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef USERCMD_H
#define USERCMD_H

class Vector;

struct usercmd_t
{
	usercmd_t():
		cmdidx(0),
		lerp_msec(0),
		msec(0),
		forwardmove(0),
		sidemove(0),
		upmove(0),
		weaponselect(0),
		impulse(0),
		buttons(0)
	{
	}

	UInt64 cmdidx;		// Index of usercmd

	UInt32 lerp_msec;	// interpolation time on client
	Byte msec;			// duration in ms of command
	Vector viewangles;	// view angles at time of cmd send

	float forwardmove;	// forward movement velocity
	float sidemove;		// side movement velocity
	float upmove;		// upwards movement velocity
	Byte weaponselect;	// weapon selection
	Byte impulse;		// impulse command value
	UInt32 buttons;		// buttons pressed
};

#endif //USERCMD_H