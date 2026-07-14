/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef R_FBOCACHE_H
#define R_FBOCACHE_H

#include <gl/GL.h>
#include "r_fbo.h"

/*
====================
CFBOCache

====================
*/
class CFBOCache
{
public:
	// Time until an FBO is freed
	static const float FBO_FREE_DELAY;

public:
	struct cache_fbo_t
	{
		cache_fbo_t() :
			width(0),
			height(0),
			freetime(0)
		{}

		UInt32 width;
		UInt32 height;

		fbobind_t fbo;

		double freetime;
	};

public:
	CFBOCache(void);
	~CFBOCache(void);

public:
	bool Init(void);
	void Shutdown(void);

	bool InitGame(void);
	void ClearGame(void);

	bool InitGL(void);
	void ClearGL(void);

	void Think(void);

public:
	cache_fbo_t* Alloc(UInt32 width, UInt32 height, bool depthbuffer);
	void Free(cache_fbo_t* pfbo);

private:
	CLinkedList<cache_fbo_t*> m_cacheList;
};
extern CFBOCache gFBOCache;
#endif // R_FBOCACHE_H