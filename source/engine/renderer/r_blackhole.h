/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef R_BLACKHOLE_H
#define R_BLACKHOLE_H

struct cl_entity_t;
struct en_texalloc_t;
struct cl_particle_t;
struct tempentity_t;

class Vector;

#include "r_glsl.h"

struct blackhole_vertex_t
{
	blackhole_vertex_t()
	{
		memset(origin, 0, sizeof(origin));
		memset(padding, 0, sizeof(padding));
	}

	vec4_t origin;
	Byte padding[16];
};

struct blackhole_attribs
{
	blackhole_attribs():
		a_vertex(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_modelview(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_projection(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_texture(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_texturerect(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_screensize(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_screenpos(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_distance(CGLSLShader::PROPERTY_UNAVAILABLE),
		u_size(CGLSLShader::PROPERTY_UNAVAILABLE),
		d_rectangle(CGLSLShader::PROPERTY_UNAVAILABLE)
		{
		}

	Int32 a_vertex;

	Int32 u_modelview;
	Int32 u_projection;

	Int32 u_texture;
	Int32 u_texturerect;

	Int32 u_screensize;
	Int32 u_screenpos;
	Int32 u_distance;
	Int32 u_size;

	Int32 d_rectangle;
};

/*
====================
CBlackHoleRenderer

====================
*/
class CBlackHoleRenderer
{
public:
	// Max black hole entities in the stack
	static const UInt32 MAX_BLACKHOLE_ENTITIES = 16;
	// Max black hole entities in the stack
	static const UInt32 NUM_BLACKHOLE_VERTEXES = 6;

public:
	// Black hole reference size
	static const float BLACK_HOLE_REFERENCE_SIZE;

public:
	// Black hole object
	struct blackhole_t
	{
		blackhole_t():
			key(0),
			spawntime(0),
			life(0),
			scale(0),
			strength(0),
			growthtime(0),
			shrinktime(0),
			rotation(0)
			{}

		Int32 key;
		double spawntime;
		float life;
		float scale;
		float strength;
		float growthtime;
		float shrinktime;
		float rotation;
		Vector origin;
	};

public:
	CBlackHoleRenderer( void );
	~CBlackHoleRenderer( void );

public:
	// Initializes the class
	bool Init( void );

	// Initializes OpenGL objects
	bool InitGL( void );
	// Clears OpenGL objects
	void ClearGL( void );

	// Clears game states
	void ClearGame( void );

	// Performs think functions
	void Think( void );
	// Draw black holes
	bool DrawBlackHoles( void );

	// Makes black holes affect a particle
	bool AffectObject( const Vector& origin, Vector& velocity, float gravity );
	// Returns scale affected by growth/shrinking
	float GetBlackHoleScale( const blackhole_t& blackhole ) const;

	// Adds a black hole entity to be rendered
	void CreateBlackHole( Int32 key, const Vector& origin, float life, float scale, float strength, float rotation, float growthtime, float shrinktime );
	// Kills a black hole
	void KillBlackHole( Int32 key );

private:
	// GLSL shader
	class CGLSLShader *m_pShader;
	// VBO
	class CVBO *m_pVBO;

	// Black hole shader attributes
	blackhole_attribs m_attribs;

	// Cvar to toggle black hole rendering
	CCVar* m_pCvarDrawBlackHoles;
	// Black hole strength debug cvar
	CCVar* m_pStrengthDebugCvar;

private:
	// List of black holes
	CLinkedList<blackhole_t> m_blackHolesList;
	// Vertexes for black hole rendering
	blackhole_vertex_t m_blackHoleVertexes[NUM_BLACKHOLE_VERTEXES];
};

extern CBlackHoleRenderer gBlackHoleRenderer;
#endif