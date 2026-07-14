/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef MATRIX_H
#define MATRIX_H

/*
====================
CMatrix

====================
*/
class CMatrix
{
public:
	struct matrix_t
	{
		// Constructor for matrix_t
		matrix_t():
			next(nullptr)
		{
			for(Uint32 i = 0; i < 16; i++)
				matrix[i] = 0;
		}

		float matrix[16];
		matrix_t *next;
	};

public:
	CMatrix ( void );
	explicit CMatrix ( const float *pMatrix );
	virtual ~CMatrix( void );
	CMatrix( const CMatrix& src );

public:
	const float *GetMatrix( void );
	const float *GetInverse( void );
	const float *Transpose( void );
	void SetMatrix( const float *pMatrix );

	void LoadIdentity( void );
	void PushMatrix( void );
	void PopMatrix( void );

	void MultMatrix ( const float *pMatrix );
	void Translate ( float x, float y, float z );
	void Rotate ( float angle, float x, float y, float z );
	void Scale ( float x, float y, float z );

	void SetFrustum( float l, float r, float b, float t, float n, float f );
	void Ortho(float l, float r, float b, float t, float n, float f);
	void LookAt( float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz );

public:
	DO_INLINE void operator=( const CMatrix& src );

private:
	// working matrix
	float	m_workingMatrix[16];
	// output matrix
	float	m_outMatrix[16];
	// multiply matrix
	float	m_multMatrix[16];
	// rotation matrix
	float	m_rotationMatrix[16];
	// inverse transpose matrix
	float	m_matrixTranspose[16];

private:
	// pointer to current
	float *m_pCurrentMatrix;
	// matrix stack
	matrix_t *m_pMatrixHeader;
};
#endif