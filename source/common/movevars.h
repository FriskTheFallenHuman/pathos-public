/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef MOVEVARS_H
#define MOVEVARS_H

struct movevars_t
{
	movevars_t():
		gravity(0),
		stopspeed(0),
		maxspeed(0),
		accelerate(0),
		airaccelerate(0),
		wateraccelerate(0),
		friction(0),
		edgefriction(0),
		waterfriction(0),
		entgravity(0),
		bounce(0),
		stepsize(0),
		maxvelocity(0),
		waterdist(0),
		maxclients(0),
		holdtoduck(false)
	{}

	float gravity;
	float stopspeed;
	float maxspeed;
	
	float accelerate;
	float airaccelerate;
	float wateraccelerate;

	float friction;
	float edgefriction;
	float waterfriction;

	float entgravity;
	float bounce;
	float stepsize;
	float maxvelocity;
	float waterdist;

	UInt32 maxclients;
	bool holdtoduck;
};
#endif