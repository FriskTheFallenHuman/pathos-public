/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

#ifndef R_VBO_H
#define R_VBO_H

// External functions class
class CGLExtF;

// For setting the offset in the datatype
#define OFFSET(type, variable) ((const void*)&(((type*)nullptr)->variable))
// For calls to glDrawElements
#define BUFFER_OFFSET(i) ((UInt32 *)nullptr + (i))

// Maximum GLSL attributes
#define MAX_ATTRIBS 32

// <attrib_t>
struct attrib_t
{
	attrib_t():
		ptr(nullptr),
		active(false),
		size(0),
		stride(0)
	{
	}

	const void *ptr;
	bool active;

	UInt32 size;
	UInt32 stride;
};

//====================
// CVBO
// 
//====================
class CVBO
{
public:
	friend class CGLSLShader;

public:
	CVBO( const CGLExtF& glExtF, const void *pvbodata, UInt32 ivbodatasize, const void *pibodata, UInt32 iibodatasize, bool keepcache = false, bool usevao = true );
	CVBO ( const CGLExtF& glExtF, bool bvbo, bool bibo, bool usevao = true );
	~CVBO( void );
	void Clear( void );

	void SetAttribPointer( Int32 index, UInt32 size, UInt32 type, UInt32 stride, const void *pointer );
	void DisableAttribPointer( Int32 index );

	void VBOSubBufferData( UInt32 offset, const void *pdata, UInt32 size );
	void IBOSubBufferData( UInt32 offset, const void *pdata, UInt32 size );

	void ClearGL( void );
	void RebindGL( void );

	UInt32 GetVBOSize( void ) const { return m_iVBOSize; }
	UInt32 GetIBOSize( void ) const { return m_iIBOSize; }

	bool Append( const void *pvbodata, UInt32 ivbodatasize, const void *pibodata, UInt32 iibodatasize );
	void DeleteCaches( void );

	bool IsValid( void ) const { return m_isValid; }
	bool IsVBOBound( void ) const { return m_isVBOBound; }
	bool IsIBOBound( void ) const { return m_isIBOBound; }
	bool IsVAOBound( void ) const { return m_isVAOBound; }
	bool HasIBO( void ) const { return (m_uiIBOIndex != 0) ? true : false; }

protected:
	void BindVBO( void );
	void UnBindVBO( void );

	void BindIBO( void );
	void UnBindIBO( void );

	void BindVAO( void );
	void UnbindVAO( void );

public:
	GLuint GetVBOIndex( void ) const { return m_uiVBOIndex; }
	GLuint GetIBOIndex( void ) const { return m_uiIBOIndex; }
	GLuint GetVAOIndex( void ) const { return m_uiVAOIndex; }

	const void* GetVBOData( void ) const { return m_pVBOData; }
	const UInt32 GetVBODataSize( void ) const { return m_iVBOSize; }

	const void* GetIBOData( void ) const { return m_pIBOData; }
	const UInt32 GetIBODataSize( void ) const { return m_iIBOSize; }

private:
	GLuint	m_uiVBOIndex;
	GLuint	m_uiIBOIndex;
	GLuint	m_uiVAOIndex;

	bool	m_isVAOBound;
	bool	m_isVBOBound;
	bool	m_isIBOBound;

	bool	m_bCache;
	bool	m_isValid;
	bool	m_useVAO;

	void *m_pVBOData;
	UInt32 m_iVBOSize;

	void *m_pIBOData;
	UInt32 m_iIBOSize;

	attrib_t m_pAttribPointers[MAX_ATTRIBS];

	// External functions class
	const CGLExtF& m_glExtF;
};
#endif // R_VBO_H