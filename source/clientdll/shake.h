/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SHAKE_H
#define SHAKE_H

struct screenshake_t 
{
	screenshake_t():
		endtime(0),
		duration(0),
		amplitude(0),
		frequency(0),
		nextshake(0),
		shakebegin(0),
		angle(0)
		{}

	double endtime;
	double duration;
	float amplitude;
	float frequency;
	double nextshake;
	double shakebegin;

	Vector offset;
	float angle;
};

/*
====================
CScreenShake

====================
*/
class CScreenShake
{
private:
	static const int MAX_SHAKES = 32;

public:
	CScreenShake( void );
	~CScreenShake( void );

public:
	// Initializes the class
	bool Init( void );
	// Clears class game states
	void ClearGame( void );

	// Calculates the shake
	void CalcShake( void );
	// Applies the shake
	void ApplyShake( Vector& origin, Vector& angles, float factor );
	// Read a shake message
	void AddScreenShake( float amplitude, float duration, float frequency );

private:
	// Allocates a new shake object
	screenshake_t* AllocShake( void );

private:
	// View shake offset
	Vector m_shakeOffset;
	// View shake angle
	float m_shakeAngle;

	// Array of shakes
	CLinkedList<screenshake_t> m_shakesList;
};
extern CScreenShake gShake;
#endif