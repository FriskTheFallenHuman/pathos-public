/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef R_LIGHTSTYLES_H
#define R_LIGHTSTYLES_H

#include "r_fbo.h"
#include "r_vbo.h"
#include "r_glsl.h"
#include "dlight.h"

/*
=================================
CLightStyleManager

=================================
*/
class CLightStyleManager
{
public:
	// Custom lightstyle start index(for dynamic lights)
	static const UInt32 CUSTOM_LIGHTSTYLE_START_INDEX;
	// Default lightstyle framerate
	static const char DEFAULT_LIGHTSTYLE_FRAMERATE;
	// Maximum lightstyle string length
	static const UInt32	MAX_STYLESTRING;

public:
	struct lightstyle_t
	{
		lightstyle_t():
			index(0),
			length(0),
			framerate(0),
			interp(false)
		{}

		Int32 index;
		Int32 length;
		Int32 framerate;
		CArray<char> map;

		bool interp;
	};

public:
	CLightStyleManager( void );
	~CLightStyleManager( void );

public:
	// Initializes class
	bool Init( void );
	// Shuts down the class
	void Shutdown( void );
	// Initializes for a game
	bool InitGame( void );
	// Clears lights
	void ClearGame( void );

	// Applies a lightstyle to a light value
	void ApplyLightStyle( cl_dlight_t* dl, Vector& color );
	// Returns the lightstyle value for a given style index
	float GetLightStyleValue( UInt32 styleIndex );
	// Adds a custom lightstyle
	void AddCustomLightStyle( UInt32 index, Int32 framerate, bool interpolate, const char* pstring );
	// Sets a lightstyle
	void SetLightStyle( UInt32 index, Int32 framerate, bool interpolate, const char* pstring );
	// Animates lightstyles
	void AnimateStyles( void );

	// Returns a pointer to the lightstyles CArray object
	CArray<float>* GetLightStyleValuesArray( void );

private:
	// Resets lightstyles
	void ResetStyles( void );

private:
	// lightstyle related
	CArray<lightstyle_t> m_lightStyles;
	// Lightstyle values
	CArray<float> m_lightStyleValues;
};
extern CLightStyleManager gLightStyles;
#endif