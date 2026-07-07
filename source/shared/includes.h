/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef INCLUDES_H
#define INCLUDES_H

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <exception>
#include <tchar.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include <Windows.h>
#endif

#ifndef NO_SDL
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <SDL_video.h>
#include <SDL_endian.h>
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	#define STB_VORBIS_BIG_ENDIAN
#endif
#endif

#include "imgui.h"
#ifndef NO_SDL
#include "imgui_impl_sdl2.h"
#endif
#include "imgui_impl_opengl3.h"

#include "datatypes.h"
#include "common.h"

#include "cstring.h"
#include "carray.h"
#include "cbitset.h"
#include "clinkedlist.h"
#include "vector.h"
#include "cbuffer.h"
#include "hashlist.h"
#include "TinyJSON.h"

using namespace std;
using namespace TinyJSON;
#endif