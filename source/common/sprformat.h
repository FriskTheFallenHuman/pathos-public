/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SPRFORMAT_H
#define SPRFORMAT_H

struct en_texture_t;

#define SPRITE_VERSION	2
#define IDSPRITEHEADER	(('P'<<24)+('S'<<16)+('D'<<8)+'I')

enum spr_frametype_t
{ 
	SPR_SINGLE = 0, 
	SPR_GROUP
};

struct dsprite_t
{
	dsprite_t():
		id(0),
		version(0),
		type(0),
		format(0),
		boundingradius(0),
		maxwidth(0),
		maxheight(0),
		numframes(0),
		beamlength(0),
		synctype(0)
		{}

	Int32 id;
	Int32 version;

	UInt32 type;
	UInt32 format;

	float boundingradius;
	UInt32 maxwidth;
	UInt32 maxheight;
	UInt32 numframes;

	float beamlength;

	UInt32 synctype;
};

struct dspriteframe_t
{
	dspriteframe_t():
		originx(0),
		originy(0),
		width(0),
		height(0)
		{}

	Int32 originx;
	Int32 originy;
	UInt32 width;
	UInt32 height;
};

enum spr_orientation_t
{
	SPR_VP_PARALLEL_UPRIGHT	= 0,
	SPR_FACING_UPRIGHT,
	SPR_VP_PARALLEL,
	SPR_ORIENTED,
	SPR_VP_PARALLEL_ORIENTED
};

enum spr_rendermode_t
{
	SPR_NORMAL = 0,
	SPR_ADDITIVE,
	SPR_INDEXALPHA,
	SPR_ALPHTEST
};

struct mspriteframe_t
{
	mspriteframe_t():
		width(0),
		height(0),
		up(0),
		down(0),
		left(0),
		right(0),
		ptexture(nullptr),
		pdata(nullptr)
		{}
	~mspriteframe_t()
	{
		if(pdata)
			delete[] pdata;
	}

	Int32				width;
	Int32				height;
	float				up;
	float				down;
	float				left;
	float				right;
	en_texture_t*		ptexture;
	Byte				*pdata;
};

struct mspritegroup_t
{
	mspritegroup_t()
		{}
	~mspritegroup_t()
	{
		for(UInt32 i = 0; i < frames.size(); i++)
			delete frames[i];
	}

	CArray<float>			intervals;
	CArray<mspriteframe_t*> frames;
};

struct mspriteframedesc_t
{
	mspriteframedesc_t():
		type(SPR_SINGLE),
		pframeptr(nullptr),
		pgroupptr(nullptr)
		{}
	~mspriteframedesc_t()
	{
		if(pframeptr)
			delete pframeptr;

		if(pgroupptr)
			delete[] pgroupptr;
	}

	spr_frametype_t type;
	mspriteframe_t *pframeptr;
	mspritegroup_t* pgroupptr;
};

struct msprite_t
{
	msprite_t():
		type(0),
		format(0),
		maxwidth(0),
		maxheight(0),
		radius(0),
		beamlength(0),
		synctype(0),
		palette(nullptr)
		{}
	~msprite_t()
	{
		if(palette)
			delete[] palette;
	}

	Int32 type;
	Int32 format;
	Int32 maxwidth;
	Int32 maxheight;
	Int32 radius;
	Int32 beamlength;
	Int32 synctype;

	CArray<mspriteframedesc_t>	frames;
	Byte* palette;
};
#endif //SPRFORMAT_H