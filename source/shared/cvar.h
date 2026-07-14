/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CVAR_H
#define CVAR_H

class CConsole;

enum cvar_flags_t
{
	FL_CV_NONE			= 0, // No special flags
	FL_CV_SAVE			= 1, // Save to config file
	FL_CV_SV_ONLY		= 2, // Created by server dll
	FL_CV_PROTECTED		= 4, // Cheat protected
	FL_CV_NOTIFY		= 8, // Notify of changes
	FL_CV_CLIENT		= 16, // Can only be set by the client
	FL_CV_GL_DEPENDENT	= 32 // Depends on a GL context being present
};

enum cvar_type_t
{
	CVAR_FLOAT = 0, // Int or float
	CVAR_STRING // String
};

typedef void (*pfnCVarCallback_t)( class CCVar* pCVar );
typedef void (*pfnCon_EPrintf_t)( const char *fmt, ... );

/*
=================================
CCVar

=================================
*/
class CCVar
{
	friend class CConsole;
public:
	CCVar( cvar_type_t type, Int32 flags, const char* pstrName, pfnCVarCallback_t pfnCallback, pfnCon_EPrintf_t pfnCon_EPrintf );

	virtual ~CCVar( void );

public:
	// Retrieves a string value
	virtual const char* GetStrValue( void ) const = 0;
	// Retrieves a float value
	virtual float GetValue( void ) const = 0;

	// Retrieves the type
	cvar_type_t GetType( void ) const { return m_type; }
	// Retrieves the flags
	Int32 GetFlags( void ) const { return m_flags; }
	// Retrieves the name
	const char* GetName( void ) const { return m_name.c_str(); }
	
private:
	// These should never be called outside CConsole
	// Sets a string value for the cvar
	virtual bool SetValue( const char* pstrValue ) = 0;
	// Sets a float value
	virtual bool SetValue( float value ) = 0;

protected:
	// Type of the cvar
	cvar_type_t m_type;
	// Flags for the cvar
	Int32 m_flags;
	// Name of the cvar
	CString m_name;
	// Callback function
	pfnCVarCallback_t m_pfnCallbackFn;
	// Error print function ptr
	pfnCon_EPrintf_t m_pfnCon_EPrintf;
};

/*
=================================
CStringCVar

=================================
*/
class CStringCVar : public CCVar
{
public:
	CStringCVar( Int32 flags, const char* pstrName, pfnCVarCallback_t pfnCallback, pfnCon_EPrintf_t pfnCon_EPrintf );
	virtual ~CStringCVar( void );

public:
	// Retrieves a string value
	const char* GetStrValue( void ) const override;
	// Retrieves a float value
	float GetValue( void ) const override;

private:
	// These should never be called outside CConsole
	// Sets a string value for the cvar
	bool SetValue( const char* pstrValue ) override;
	// Sets a float value
	bool SetValue( float value ) override;

private:
	// Value of the cvar
	CString m_value;
};

/*
=================================
CFloatCVar

=================================
*/
class CFloatCVar : public CCVar
{
public:
	CFloatCVar( Int32 flags, const char* pstrName, pfnCVarCallback_t pfnCallback, pfnCon_EPrintf_t pfnCon_EPrintf );
	virtual ~CFloatCVar( void );

public:
	// Retrieves a string value
	const char* GetStrValue( void ) const override;
	// Retrieves a float value
	float GetValue( void ) const override;

private:
	// These should never be called outside CConsole
	// Sets a string value for the cvar
	bool SetValue( const char* pstrValue ) override;
	// Sets a float value
	bool SetValue( float value ) override;

private:
	// Value of the cvar
	float m_value;
};
#endif // CVAR_H