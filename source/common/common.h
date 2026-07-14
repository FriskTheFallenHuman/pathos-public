/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef COMMON_H
#define COMMON_H

class Vector;
template <typename T> class CArray;

#ifndef MAX_PATH
#define MAX_PATH			260
#endif //MAX_PATH

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif //M_PI

#ifndef DEG2RAD
#define DEG2RAD( a ) ( a * M_PI ) / 180.0F
#endif //DEG2RAD

#ifndef RAD2DEG
#define RAD2DEG( a ) ( a * 180.0F ) / M_PI
#endif //RAD2DEG

#ifndef Clamp
#define Clamp( val, min, max ) ( ((val) > (max)) ? (max) : ( ((val) < (min)) ? (min) : (val) ) )
#endif //Clamp

#ifndef _max
#define _max( max, val ) ( ((val) > (max)) ? (max) : (val) )
#endif //max

#ifndef _min
#define _min( min, val ) ( ((val) < (min)) ? (min) : (val) )
#endif //min

#ifndef DIST_EPSILON
#define DIST_EPSILON 0.03125f
#endif //DIST_EPSILON

// For SDL_GetTicks
#ifndef SECONDS_TO_MILLISECONDS
#define SECONDS_TO_MILLISECONDS 1000
#endif //SECONDS_TO_MILLISECONDS

// For converting seconds to milliseconds
#ifndef MILLISECONDS_TO_SECONDS
#define MILLISECONDS_TO_SECONDS 1.0f/1000.0f
#endif //MILLISECONDS_TO_SECONDS

#ifndef force_assert
#define force_assert(_Expression) (void)( (!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), __LINE__), 0) )
#endif

// NAN mask
static constexpr Int32 NANMASK = 0x7F800000;

// Valid slash used in paths
static constexpr char PATH_SLASH_CHAR = '/';

// Maximum line length
static constexpr Uint32 MAX_LINE_LENGTH = 4096;
// Maximum parse length
static constexpr Uint32 MAX_PARSE_LENGTH = 256;

// Resource levels, used to keep track of what needs to be
// freed, and when.
enum rs_level_t
{
	RS_LEVEL_UNDEFINED = 0,
	RS_GAME_LEVEL,				// Resources that get freed whenever a game reloads
	RS_WINDOW_LEVEL,			// Resources that get freed only when the window is destroyed
	RS_APP_LEVEL				// Resources that get freed only when the application exits
};

// Resource message types, used to handle precache lists
// sent by the server to the clients.
enum rs_msg_type_t
{
	RS_FINISHED = 0,
	RS_LIST_MODELS,
	RS_LIST_SOUNDS,
	RS_LIST_TEXTURES,
	RS_LIST_MATERIAL_SCRIPTS,
	RS_LIST_GENERIC,
	RS_LIST_PARTICLE_SCRIPTS,
	RS_LIST_DECALS
};

// Resource type, used to handle precache lists
// sent by the server to the clients.
enum rs_type_t
{
	RS_TYPE_UNDEFINED = -1,
	RS_TYPE_MODEL = 0,
	RS_TYPE_SOUND,
	RS_TYPE_TEXTURE,
	RS_TYPE_MATERIAL_SCRIPT,
	RS_TYPE_GENERIC,
	RS_TYPE_PARTICLE_SCRIPT,
	RS_TYPE_DECAL
};

// Resources cls msg types
enum rs_clmsg_t
{
	CL_RESOURCE_LIST = 0,
	CL_RESOURCE_FILEINFO,
	CL_RESOURCE_FILECHUNK,
	CL_RESOURCE_UNAVAILABLE
};

enum rs_svmsg_t
{
	SV_RESOURCES_OK = 0,
	SV_RESOURCE_DOWNLOAD_BEGIN,
	SV_RESOURCE_CHUNK_RECEIVED
};

enum wheel_type_t
{
	MOUSE_WHEEL_UP = 0,
	MOUSE_WHEEL_DOWN,
	MOUSE_WHEEL_RIGHT,
	MOUSE_WHEEL_LEFT
};

struct file_dateinfo_t
{
	file_dateinfo_t():
		year(0),
		month(0),
		day(0),
		hour(0),
		minute(0),
		second(0)
		{
		}

	Int32 year;
	Int32 month;
	Int32 day;
	Int32 hour;
	Int32 minute;
	Int32 second;
};

// up / down
#ifndef PITCH
#define	PITCH	0
#endif // PITCH

// left / right
#ifndef YAW
#define	YAW		1
#endif // YAW

// fall over
#ifndef ROLL
#define	ROLL	2 
#endif // ROLL

#ifndef PT_ARRAYSIZE
#define PT_ARRAYSIZE(ptr) (sizeof(ptr)/sizeof(ptr[0]))
#endif

class CString;

extern DO_INLINE Uint32 qstrlen( const char* pstr );
extern DO_INLINE char* qstrcpy( char* pdest, const char *psrc );
extern DO_INLINE char* qstrncpy( char* pdest, const char *psrc, Uint32 size );
extern DO_INLINE char* qstrcpy_s( char* pdest, const char *psrc, Uint32 m );
extern Int32 qstrcmp( const char* pstr1, const char* pstr2 );
extern Int32 qstrcmp( const CString& str1, const CString& str2 );
extern Int32 qstrcmp( const char* pstr1, const CString& str2 );
extern Int32 qstrcmp( const CString& str1, const char* pstr2 );
extern Int32 qstrcicmp( const char* pstr1, const char* pstr2 );
extern Int32 qstrcicmp( const CString& str1, const CString& str2 );
extern Int32 qstrcicmp( const char* pstr1, const CString& str2 );
extern Int32 qstrcicmp( const CString& str1, const char* pstr2 );
extern Int32 qstrncmp( const char* pstr1, const char* pstr2, Uint32 n );
extern Int32 qstrncmp( const CString& str1, const CString& str2, Uint32 n );
extern Int32 qstrncmp( const char* pstr1, const CString& str2, Uint32 n );
extern Int32 qstrncmp( const CString& str1, const char* pstr2, Uint32 n );
extern Int32 qstrncimp( const char* pstr1, const char* pstr2, Uint32 n );
extern void qstrins( const char* psrc, char *pdest, Uint32 offset );
extern DO_INLINE const char* qstrstr( const char* pstr, const char *psubstr );

extern DO_INLINE float qrsqrt( float value );
extern DO_INLINE float sgn(float a);

namespace Common
{
	extern const char* Parse( const char *pstr, char* pdest, const char* pbreakchars = nullptr, bool ignoreComma = false, bool checkCurlyBrackets = false );
	extern const char* Parse( const char *pstr, CString& str, const char* pbreakchars = nullptr, bool ignoreComma = false, bool checkCurlyBrackets = false );
	extern const char* ReadLine( const char* pstr, char* pdest );
	extern const char* ReadLine( const char* pstr, CString& str );
	extern void *ResizeArray( void *parray, Uint64 size, Uint64 count, Uint64 countNew = 1 );
	extern void Basename( const char *pstrin, char *pstrout );
	extern void Basename( const char *pstrin, CString& strOut );
	extern bool IsNumber( const char *pstr );
	extern bool IsNumber( const CString& str );
	extern char GetShiftedChar( char c );
	extern void StringToVector( const char* pstrString, Vector& outVector );
	extern void NormalizeAngles( Vector& angles );
	extern void ConvertStringToLowerCase( char* pstring );
	extern Uint32 GetStringCRC32Hash( const char* pstrString );
	extern void GetDirectoryPath( const char* pstrPath, CString& output );
	extern CString CleanupPath( const char* pstrPath );
	extern float BytesToMegaBytes( Uint32 bytesCount );

	extern DO_INLINE Int16 ByteToInt16( const Byte *pdata );
	extern DO_INLINE Uint16 ByteToUint16( const Byte *pdata );
	extern DO_INLINE Int32 ByteToInt32( const Byte *pdata );
	extern DO_INLINE Uint32 ByteToUint32( const Byte *pdata );
	extern DO_INLINE float ByteToFloat( const Byte *pdata );
	extern DO_INLINE Int64 ByteToInt64( const Byte *pdata );
	extern DO_INLINE Uint64 ByteToUint64( const Byte *pdata );
	extern DO_INLINE double ByteToDouble( const Byte *pdata );

	extern bool IsPowerOfTwo( Uint32 size );
	extern CString GetDate( void );
	extern CString GetDateFilename( void );
	extern Int32 IsPitchReversed( float pitch );
	extern void FixVector( float* pflVector );
	extern float RandomFloat( float low, float high );
	extern Int64 RandomLong( Int64 low, Int64 high );
	extern DO_INLINE bool IsNAN( float value );
	extern DO_INLINE float SplineFraction( float value, float scale );
	extern DO_INLINE void ScaleByte( Dword *nInput );
	extern CString FixSlashes( const char* pstring );
	extern bool CheckVisibility( const CArray<Uint32>& leafnums, Uint32 numleafs, const Byte* pset );
	extern bool GetWADList( const char* pstrEntityData, CArray<CString>& outputArray );
	extern Uint32 GetFileLineCount( const char* pstrdata );

	extern DO_INLINE void ParseColor( float* pout, const color24_t *plightmap );
	extern DO_INLINE void ParseVectorColor (float* pout, const color24_t *plightmap);
	extern DO_INLINE float RemapValue( float value, float a, float b, float c, float d );

	extern DO_INLINE bool ValueInRange( float comparisonValue, float referenceValue, float rangeMax );
	extern void ResizeTextureToPOT( Uint32& outwidth, Uint32& outheight, Byte*& pdata );
	extern void ResizeTexture32( Uint32 width, Uint32 height, Uint32 targetwidth, Uint32 targetheight, const color32_t* pindata, color32_t*& poutdata );
	extern void ResizeTexture24( Uint32 width, Uint32 height, Uint32 targetwidth, Uint32 targetheight, const color24_t* pindata, color24_t*& poutdata );
	extern void FlipTexture( Uint32 width, Uint32 height, Uint32 bpp, bool fliph, bool flipv, Byte*& pdata );
};
#include "common_inline.hpp"
#endif