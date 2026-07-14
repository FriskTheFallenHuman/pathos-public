/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef MCDFORMAT_H
#define MCDFORMAT_H

#include "constants.h"
#include "plane.h"

// MCD file id
static const Int32 MCD_FORMAT_HEADER = (('D'<<24)+('C'<<16)+('M'<<8)+'P');
// MCD file version
static const Int32 MCD_FORMAT_VERSION = 1;

struct mcdheader_t;
struct mcdbvhnode_t;
struct mcdsubmodel_t;

enum mcdcollisiontype_t
{
	MCD_COLLISION_NULL = -1,
	MCD_COLLISION_TRIANGLES,		// The pure triangle data
	MCD_COLLISION_BVH,				// Bounding volume hierarchy information

	// Must be last
	NB_MCD_COLLISION_TYPES,
};

struct mcdcollisiontypemodel_t
{
	mcdcollisiontypemodel_t():
		type(MCD_COLLISION_NULL),
		dataoffset(0)
	{}

	const void* getTypeData( const mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<const Byte*>(phdr) + dataoffset;
	}

	void* getTypeData( mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<Byte*>(phdr) + dataoffset;
	}

	mcdcollisiontype_t type;
	UInt32 dataoffset;
};

struct mcdsubmodel_t
{
	mcdsubmodel_t():
		collisiontypesoffset(0),
		numcollisiontypes(0)
	{
		memset(name, 0, sizeof(name));
	}

	const void* getTypeData( const mcdheader_t* phdr, mcdcollisiontype_t type ) const
	{
		assert(phdr != nullptr);
		assert(type >= MCD_COLLISION_TRIANGLES && type < NB_MCD_COLLISION_TYPES);
		if(type >= numcollisiontypes)
			return nullptr;

		const mcdcollisiontypemodel_t* ptypemodel = reinterpret_cast<const mcdcollisiontypemodel_t*>(reinterpret_cast<const Byte*>(phdr) + collisiontypesoffset) + (Int32)type;
		assert(ptypemodel->type == type);
		if(type != type)
			return nullptr;
		else
			return ptypemodel->getTypeData(phdr);
	}

	void* getTypeData( mcdheader_t* phdr, mcdcollisiontype_t type )
	{
		assert(phdr != nullptr);
		assert(type >= MCD_COLLISION_TRIANGLES && type < NB_MCD_COLLISION_TYPES);
		if(type >= numcollisiontypes)
			return nullptr;

		mcdcollisiontypemodel_t* ptypemodel = reinterpret_cast<mcdcollisiontypemodel_t*>(reinterpret_cast<Byte*>(phdr) + collisiontypesoffset) + (Int32)type;
		assert(ptypemodel->type == type);
		if(type != type)
			return nullptr;
		else
			return ptypemodel->getTypeData(phdr);
	}

	char name[128];

	Vector mins;
	Vector maxs;

	UInt32 collisiontypesoffset;
	UInt32 numcollisiontypes;
};

struct mcdbodypart_t
{
	mcdbodypart_t():
		base(0),
		submodeloffset(0),
		numsubmodels(0)
	{
		memset(name, 0, sizeof(name));
	}

	const mcdsubmodel_t* getSubmodel( const mcdheader_t* phdr, Int32 index ) const
	{
		assert(index >= 0 && index < numsubmodels);
		return reinterpret_cast<const mcdsubmodel_t*>(reinterpret_cast<const Byte*>(phdr) + submodeloffset) + index;
	}

	mcdsubmodel_t* getSubmodel( mcdheader_t* phdr, Int32 index ) const
	{
		assert(index >= 0 && index < numsubmodels);
		return reinterpret_cast<mcdsubmodel_t*>(reinterpret_cast<Byte*>(phdr) + submodeloffset) + index;
	}

	char name[128];

	UInt32 base;
	UInt32 submodeloffset;
	UInt32 numsubmodels;
};

struct mcdbone_t
{
	mcdbone_t():
		parentindex(NO_POSITION)
	{
		memset(name, 0, sizeof(name));
	}

	char name[64];
	Vector position;
	Vector rotation;
	Int32 parentindex;
};

struct mcdvertex_t
{
	mcdvertex_t():
		boneindex(NO_POSITION)
	{}

	Vector origin;
	Int32 boneindex;
};

struct mcdtrimeshtriangle_t
{
	mcdtrimeshtriangle_t():
		skinref(NO_POSITION),
		distance(0),
		planetype(PLANE_AZ),
		signbits(0)
	{
		for(UInt32 i = 0; i < 3; i++)
			trivertexes[i] = 0;
	}

	Int32 skinref;
	Vector normal;
	float distance;
	Int32 planetype;
	Int32 signbits;
	UInt32 trivertexes[3];
};

struct mcdtrimeshtype_t
{
	mcdtrimeshtype_t():
		triangleoffset(0),
		numtriangles(0),
		vertexoffset(0),
		numvertexes(0)
	{}

	const mcdtrimeshtriangle_t* getTriangles( const mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<const mcdtrimeshtriangle_t*>(reinterpret_cast<const Byte*>(phdr) + triangleoffset);
	}

	mcdtrimeshtriangle_t* getTriangles( mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<mcdtrimeshtriangle_t*>(reinterpret_cast<Byte*>(phdr) + triangleoffset);
	}

	const mcdvertex_t* getVertexes( const mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<const mcdvertex_t*>(reinterpret_cast<const Byte*>(phdr) + vertexoffset);
	}

	mcdvertex_t* getVertexes( mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<mcdvertex_t*>(reinterpret_cast<Byte*>(phdr) + vertexoffset);
	}

	UInt32 triangleoffset;
	UInt32 numtriangles;

	UInt32 vertexoffset;
	UInt32 numvertexes;
};

struct mcdbvhnode_t
{
	mcdbvhnode_t():
		index(NO_POSITION),
		isleaf(false),
		triindexoffset(0),
		numtriangles(0)
	{
		for(UInt32 i = 0; i < 2; i++)
			children[i] = NO_POSITION;
	}

	const Int32* getTriangleIndexes( const mcdheader_t* phdr ) const
	{
		assert(phdr != nullptr);
		return reinterpret_cast<const Int32*>(reinterpret_cast<const Byte*>(phdr) + triindexoffset);
	}

	Int32* getTriangleIndexes( mcdheader_t* phdr )
	{
		assert(phdr != nullptr);
		return reinterpret_cast<Int32*>(reinterpret_cast<Byte*>(phdr) + triindexoffset);
	}

	Int32 index;
	Vector mins;
	Vector maxs;
	Int32 children[2];
	bool isleaf;

	UInt32 triindexoffset;
	UInt32 numtriangles;
};

struct mcdbvhtype_t
{
	mcdbvhtype_t():
		bvhnodeoffset(0),
		numbvhnodes(0)
	{}

	const mcdbvhnode_t* getNode( const mcdheader_t* phdr, Int32 index ) const
	{
		assert(phdr != nullptr);
		assert(index >= 0 && index < numbvhnodes);
		return reinterpret_cast<const mcdbvhnode_t*>(reinterpret_cast<const Byte*>(phdr) + bvhnodeoffset) + index;
	}

	mcdbvhnode_t* getNode( mcdheader_t* phdr, Int32 index )
	{
		assert(phdr != nullptr);
		assert(index >= 0 && index < numbvhnodes);
		return reinterpret_cast<mcdbvhnode_t*>(reinterpret_cast<Byte*>(phdr) + bvhnodeoffset) + index;
	}

	UInt32 bvhnodeoffset;
	UInt32 numbvhnodes;
};

struct mcdtexture_t
{
	mcdtexture_t():
		dataptr(0),
		index(NO_POSITION)
	{
		memset(name, 0, sizeof(name));
	}

	char name[128];
	UInt64 dataptr;
	Int32 index;
};

struct mcdheader_t
{
	mcdheader_t():
		id(0),
		version(0),
		bodypartoffset(0),
		numbodyparts(0),
		textureoffset(0),
		numtextures(0),
		boneoffset(0),
		numbones(0),
		size(0)
	{
		memset(name, 0, sizeof(name));
	}

	const mcdbodypart_t* getBodyPart( Int32 index ) const
	{
		assert(index >= 0 && index < numbodyparts);
		return reinterpret_cast<const mcdbodypart_t*>(reinterpret_cast<const Byte*>(this) + bodypartoffset) + index;
	}

	mcdbodypart_t* getBodyPart( Int32 index )
	{
		assert(index >= 0 && index < numbodyparts);
		return reinterpret_cast<mcdbodypart_t*>(reinterpret_cast<Byte*>(this) + bodypartoffset) + index;
	}

	const mcdtexture_t* getTexture( Int32 index ) const
	{
		assert(index >= 0 && index < numtextures);
		return reinterpret_cast<const mcdtexture_t*>(reinterpret_cast<const Byte*>(this) + textureoffset) + index;
	}

	mcdtexture_t* getTexture( Int32 index )
	{
		assert(index >= 0 && index < numtextures);
		return reinterpret_cast<mcdtexture_t*>(reinterpret_cast<Byte*>(this) + textureoffset) + index;
	}
	
	const mcdbone_t* getBoneInfo( Int32 index ) const
	{
		assert(index >= 0 && index < numbones);
		return reinterpret_cast<const mcdbone_t*>(reinterpret_cast<const Byte*>(this) + boneoffset) + index;
	}

	mcdbone_t* getBoneInfo( Int32 index )
	{
		assert(index >= 0 && index < numbones);
		return reinterpret_cast<mcdbone_t*>(reinterpret_cast<Byte*>(this) + boneoffset) + index;
	}

	Int32 id;
	Int32 version;

	char name[256];

	UInt32 bodypartoffset;
	UInt32 numbodyparts;

	UInt32 textureoffset;
	UInt32 numtextures;

	UInt32 boneoffset;
	UInt32 numbones;

	UInt32 size;
};
#endif