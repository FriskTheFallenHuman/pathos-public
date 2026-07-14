/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef DLIGHT_H
#define DLIGHT_H

class CDynamicLightManager;
struct shadowmap_t;

struct cl_dlight_t
{
friend class CDynamicLightManager;

public:
	cl_dlight_t():
		radius(0),
		spawntime(0),
		die(0),
		decay(0),
		decay_delay(0),
		cone_size(0),
		key(0),
		subkey(0),
		lastframe(0),
		lightstyle(0),
		textureindex(0),
		followentity(false),
		attachment(NO_POSITION),
		isstatic(false),
		noshadow(false),
		nomaincull(false),
		pshadowmap(nullptr),
		psmcubemap(nullptr),
		psceneinfo(nullptr),
		psceneinfo_nonstatic(nullptr),
		prevradius(0),
		prevconesize(0),
		pfrustum(nullptr)
	{
	}
	const shadowmap_t* getProjShadowMap( void ) const
	{
		return pshadowmap;
	}
	const shadowmap_t* getCubeShadowMap( void ) const
	{
		return psmcubemap;
	}
	bool isStatic( void ) const
	{
		return isstatic;
	}
	bool noShadow( void ) const
	{
		return noshadow;
	}
	void setDontCull( void )
	{
		nomaincull = true;
	}

public:
	Vector	origin;
	Vector	color;
	Vector	angles;

	float	radius;
	double	spawntime;
	double	die;
	float	decay;
	float	decay_delay;
	float	cone_size;

	Int32		key;
	Int32		subkey;
	Int32		lastframe;
	UInt32		lightstyle;

	UInt32 textureindex;

	bool	followentity;
	Int32	attachment;

	Vector	mins;
	Vector	maxs;

private:
	bool	isstatic;
	bool	noshadow;
	bool	nomaincull;

	struct shadowmap_t *pshadowmap;
	struct shadowmap_t *psmcubemap;

	struct dlight_sceneinfo_t* psceneinfo;
	struct dlight_sceneinfo_t* psceneinfo_nonstatic;

	Vector prevorigin;
	Vector prevangles;
	float prevradius;
	float prevconesize;

public:
	class CFrustum* pfrustum;
};
#endif //DLIGHT_H