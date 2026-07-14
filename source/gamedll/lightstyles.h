/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef LIGHTSTYLES_H
#define LIGHTSTYLES_H

//=============================================
//
//=============================================
class CLightStyles
{
public:
	CLightStyles( void );
	virtual ~CLightStyles( void );

public:
	// start lightstyle index for dynlights
	static const UInt32 CUSTOM_LIGHTSTYLE_START_INDEX;
	// Default framerate value
	static const float DEFAULT_LIGHTSTYLE_FRAMERATE;

public:
	struct lightstyle_t
	{
		lightstyle_t():
			interpolate(false),
			styleindex(0),
			framerate(0)
			{
			}

		CString pattern;
		bool interpolate;
		UInt32 styleindex;
		float framerate;
	};

public:
	void ResetStyles( void );
	void SendLightStylesToClient( edict_t* pPlayer );
	void Think( void );

	void SetLightStyle( const char* pstrpattern, bool interpolate, float framerate, UInt32 styleindex );
	Int32 AddCustomLightStyle( const char* pstrpattern, bool interpolate, float framerate );
	CArray<float>* GetLightStyleValuesArray( void );

private:
	// Array of custom lightstyles
	CArray<lightstyle_t> m_lightStylesArray;
	// Next available lightstyle index
	UInt32 m_nextLightStyleIndex;

	// Lightstyle values array
	CArray<float> m_lightStyleValuesArray;
};
extern CLightStyles gSVLightStyles;
#endif //LIGHTSTYLES_H