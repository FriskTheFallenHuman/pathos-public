/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef PLATFORMS_H
#define PLATFORMS_H

// Win32
#if defined(WIN32) || defined(_WIN32)
	#ifdef __CYGWIN__
		#define DLLEXPORT __attribute__((visibility ("default")))

		#define FORCE_INLINE __attribute__((always_inline)) inline
		#define DO_INLINE inline
		#define STATIC_INLINE

		#define ENGINE_SPRINTF_S(buffer, size, fmt, ...) ::snprintf((buffer), (size), (fmt), ##__VA_ARGS__)
		#define ENGINE_VSPRINTF_S(buffer, size, fmt, args) ::vsnprintf((buffer), (size), (fmt), (args))
	#else
		#define DLLEXPORT __declspec( dllexport )

		#define FORCE_INLINE __forceinline
		#define DO_INLINE __inline
		#define STATIC_INLINE static

		#define ENGINE_SPRINTF_S(buffer, size, fmt, ...) ::sprintf_s((buffer), (size), (fmt), __VA_ARGS__)
		#define ENGINE_VSPRINTF_S(buffer, size, fmt, args) ::vsprintf_s((buffer), (size), (fmt), (args))
	#endif
#endif

// Mac OSX
#if defined(MACOS_X) || defined(__APPLE__)
	#define DLLEXPORT __attribute__((visibility ("default")))
	#define FORCE_INLINE __attribute__((always_inline)) inline
	#define DO_INLINE inline
	#define STATIC_INLINE
	#define ENGINE_SPRINTF_S(buffer, size, fmt, ...) ::snprintf((buffer), (size), (fmt), ##__VA_ARGS__)
	#define ENGINE_VSPRINTF_S(buffer, size, fmt, args) ::vsnprintf((buffer), (size), (fmt), (args))
#endif

// Unix
#ifdef __unix__
	#define DLLEXPORT __attribute__((visibility ("default")))
	#define FORCE_INLINE __attribute__((always_inline)) inline
	#define DO_INLINE inline
	#define STATIC_INLINE
	#define ENGINE_SPRINTF_S(buffer, size, fmt, ...) ::snprintf((buffer), (size), (fmt), ##__VA_ARGS__)
	#define ENGINE_VSPRINTF_S(buffer, size, fmt, args) ::vsnprintf((buffer), (size), (fmt), (args))
#endif

#endif