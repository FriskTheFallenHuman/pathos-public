/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef TEXTSCHEMAS_H
#define TEXTSCHEMAS_H

struct font_set_t;

/*
====================
CTextSchemas

====================
*/
class CTextSchemas
{
public:
	// Path to the folder containing the schemas
	static const char SCHEMA_FOLDER_PATH[];

public:
	struct text_reschema_t
	{
		text_reschema_t():
			screenheight(0),
			fontsize(0),
			outlineradius(0)
			{
			}

		UInt32 screenheight;
		UInt32 fontsize;
		UInt32 outlineradius;
	};

	struct textschema_t
	{
		textschema_t():
			fontsize(0),
			outlineradius(0)
			{}

		CString filename;
		CString internalname;

		color32_t color; // TODO: make this be used
		color32_t outlinecolor;
		CString fontsetname;

		UInt32 fontsize;
		UInt32 outlineradius;

		CArray<text_reschema_t> resolutions;
	};

public:
	CTextSchemas( void );
	~CTextSchemas( void );

public:
	void Init( void );
	void Clear( void );

public:
	const font_set_t* GetSchemaFontSet( const char* schemaFileName );
	const font_set_t* GetResolutionSchemaFontSet( const char* schemaFileName, UInt32 resolution );

private:
	const textschema_t* LoadSchema( const char* schemaFileName );

public:
	// List of schemas
	CLinkedList<textschema_t> m_schemasList;
};
extern CTextSchemas gTextSchemas;
#endif //R_TEXTSCHEMAS_H