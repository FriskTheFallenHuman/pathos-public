/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "r_vbo.h"
#include "textschemas.h"
#include "file.h"
#include "fontset.h"
#include "r_text.h"
#include "system.h"
#include "r_main.h"
#include "window.h"

// Path to the folder containing the schemas
const Char CTextSchemas::SCHEMA_FOLDER_PATH[] = "/resources/textschemas/";

CTextSchemas gTextSchemas;

//====================================
//
//====================================
CTextSchemas::CTextSchemas( void )
{
}

//====================================
//
//====================================
CTextSchemas::~CTextSchemas( void )
{
}

//====================================
//
//====================================
void CTextSchemas::Init( void )
{
}

//====================================
//
//====================================
void CTextSchemas::Clear( void )
{
	if(m_schemasList.empty())
		return;

	m_schemasList.clear();
}

//====================================
//
//====================================
const font_set_t* CTextSchemas::GetSchemaFontSet( const Char* schemaFileName )
{
	const textschema_t* pschema = nullptr;

	if(!m_schemasList.empty())
	{
		m_schemasList.begin();
		while(!m_schemasList.end())
		{
			textschema_t& schema = m_schemasList.get();
			if(!qstrcmp(schema.filename, schemaFileName))
			{
				pschema = &schema;
				break;
			}

			m_schemasList.next();
		}
	}

	if(!pschema)
	{
		pschema = LoadSchema(schemaFileName);
		if(!pschema)
			return nullptr;
	}

	const font_set_t* pset = gText.LoadFont(pschema->fontsetname.c_str(), pschema->fontsize, pschema->outlineradius > 0 ? true : false, &pschema->outlinecolor, pschema->outlineradius);
	if(!pset)
	{
		Con_EPrintf("%s - Unable to load font set '%s' for schema '%s'.\n", __FUNCTION__, pschema->fontsetname.c_str(), pschema->internalname.c_str());
		return nullptr;
	}

	return pset;
}

//====================================
//
//====================================
const font_set_t* CTextSchemas::GetResolutionSchemaFontSet( const Char* schemaFileName, Uint32 resolution )
{
	const textschema_t* pschema = nullptr;

	if(!m_schemasList.empty())
	{
		m_schemasList.begin();
		while(!m_schemasList.end())
		{
			textschema_t& schema = m_schemasList.get();
			if(!qstrcmp(schema.filename, schemaFileName))
			{
				pschema = &schema;
				break;
			}

			m_schemasList.next();
		}
	}

	if(!pschema)
	{
		pschema = LoadSchema(schemaFileName);
		if(!pschema)
			return nullptr;
	}

	text_reschema_t* pbestschema = nullptr;
	for(Uint32 i = 0; i < pschema->resolutions.size(); i++)
	{
		text_reschema_t* preschema = &pschema->resolutions[i];
		if(!pbestschema)
		{
			pbestschema = preschema;
			continue;
		}

		Int32 prevdiff = SDL_abs(pbestschema->screenheight - resolution);
		Int32 curdiff = SDL_abs(preschema->screenheight - resolution);
		if(prevdiff > curdiff)
			pbestschema = preschema;
	}

	const font_set_t* pset = nullptr;
	if(!pbestschema)
	{
		pset = gText.LoadFont(pschema->fontsetname.c_str(), pschema->fontsize, pschema->outlineradius > 0 ? true : false, &pschema->outlinecolor, pschema->outlineradius);
		if(!pset)
		{
			Con_EPrintf("%s - Unable to load font set '%s' for schema '%s'.\n", __FUNCTION__, pschema->fontsetname.c_str(), pschema->internalname.c_str());
			return nullptr;
		}
	}
	else
	{
		pset = gText.LoadFont(pschema->fontsetname.c_str(), pbestschema->fontsize, pbestschema->outlineradius > 0 ? true : false, &pschema->outlinecolor, pbestschema->outlineradius);
		if(!pset)
		{
			Con_EPrintf("%s - Unable to load font set '%s' for schema '%s'.\n", __FUNCTION__, pschema->fontsetname.c_str(), pschema->internalname.c_str());
			return nullptr;
		}
	}

	return pset;
}

//====================================
//
//====================================
const CTextSchemas::textschema_t* CTextSchemas::LoadSchema( const Char* schemaFileName )
{
	// Build the path and load the file
	CString path;
	path << SCHEMA_FOLDER_PATH << schemaFileName << ".json";

	const byte* pfile = FL_LoadFile(path.c_str(), nullptr);
	if(!pfile)
	{
		Con_EPrintf("%s - Could not load schema definition file '%s'.\n", __FUNCTION__, schemaFileName);
		return nullptr;
	}

	// Convert file content to string
	CString jsonStr(reinterpret_cast<const Char*>(pfile));
	FL_FreeFile(pfile);

	// Parse JSON
	parse_options opts;
	opts.throw_exception = false;  // we handle errors manually
	opts.strict = false; // relax

	TJValue* root = TJ::parse(jsonStr.c_str(), opts);
	if(!root)
	{
		Con_EPrintf("%s - Failed to parse JSON in '%s'.\n", __FUNCTION__, path.c_str());
		return nullptr;
	}

	if(!root->is_object())
	{
		Con_EPrintf("%s - Root must be an object in '%s'.\n", __FUNCTION__, path.c_str());
		delete root;
		return nullptr;
	}

	const TJValueObject* obj = static_cast<const TJValueObject*>(root);

	// Check $schema field
	if(!obj->has_key("$schema") || !obj->try_get_value("$schema")->is_string())
	{
		Con_EPrintf("%s - Missing or invalid '$schema' field in '%s'.\n", __FUNCTION__, path.c_str());
		delete root;
		return nullptr;
	}

	const TJCHAR* schemaType = obj->try_get_value("$schema")->get_string();
	if(qstrcmp(schemaType, "TextSchema") != 0)
	{
		Con_EPrintf("%s - '$schema' must be 'TextSchema' in '%s'.\n", __FUNCTION__, path.c_str());
		delete root;
		return nullptr;
	}

	textschema_t schema;
	schema.filename = schemaFileName;

	// internalname
	if(!obj->has_key("internalname") || !obj->try_get_value("internalname")->is_string())
	{
		Con_EPrintf("%s - Missing or invalid 'internalname' in '%s'.\n", __FUNCTION__, path.c_str());
		delete root;
		return nullptr;
	}
	schema.internalname = obj->try_get_value("internalname")->get_string();

	// Helper lambda to parse a color array (RGBA)
	auto parseColor = [&](const TJCHAR* key, color32_t& outColor) -> bool
	{
		if(!obj->has_key(key))
		{
			return true;
		}

		const TJValue* val = obj->try_get_value(key);
		if(!val->is_array())
		{
			Con_EPrintf("%s - '%s' must be an array in '%s'.\n", __FUNCTION__, key, path.c_str());
			return false;
		}

		const TJValueArray* arr = static_cast<const TJValueArray*>(val);
		if(arr->get_number_of_items() != 4)
		{
			Con_EPrintf("%s - '%s' must have exactly 4 elements in '%s'.\n", __FUNCTION__, key, path.c_str());
			return false;
		}

		for(unsigned int i = 0; i < 4; ++i)
		{
			const TJValue* elem = arr->at(i);
			if(!elem->is_number())
			{
				Con_EPrintf("%s - '%s' element %d is not a number in '%s'.\n", __FUNCTION__, key, i, path.c_str());
				return false;
			}

			long long valNum = elem->get_number();
			if(valNum < 0 || valNum > 255)
			{
				Con_EPrintf("%s - '%s' element %d out of range (0‑255) in '%s'.\n", __FUNCTION__, key, i, path.c_str());
				return false;
			}

			switch (i)
			{
				case 0: outColor.r = static_cast<byte>(valNum); break;
				case 1: outColor.g = static_cast<byte>(valNum); break;
				case 2: outColor.b = static_cast<byte>(valNum); break;
				case 3: outColor.a = static_cast<byte>(valNum); break;
			}
		}
		return true;
	};

	// Parse colors
	if(!parseColor("fontcolor", schema.color))
	{
		delete root;
		return nullptr;
	}

	if(!parseColor("outlinecolor", schema.outlinecolor))
	{
		delete root;
		return nullptr;
	}

	// fontset
	if (obj->has_key("fontset"))
	{
		const TJValue* val = obj->try_get_value("fontset");
		if(!val->is_string())
		{
			Con_EPrintf("%s - 'fontset' must be a string in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}
		schema.fontsetname = val->get_string();
	}

	// fontsize
	if(obj->has_key("fontsize"))
	{
		const TJValue* val = obj->try_get_value("fontsize");
		if(!val->is_number())
		{
			Con_EPrintf("%s - 'fontsize' must be a number in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}

		long long fontSize = val->get_number();
		if(fontSize < 4 || fontSize > 256)
		{
			Con_EPrintf("%s - 'fontsize' out of range (4‑256) in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}
		schema.fontsize = static_cast<Uint32>(fontSize);
	}

	// outlineradius (optional)
	if(obj->has_key("outlineradius"))
	{
		const TJValue* val = obj->try_get_value("outlineradius");
		if(!val->is_number())
		{
			Con_EPrintf("%s - 'outlineradius' must be a number in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}

		long long radius = val->get_number();
		if(radius < 0 || radius > 4)
		{
			Con_EPrintf("%s - 'outlineradius' out of range (0‑4) in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}
		schema.outlineradius = static_cast<Uint32>(radius);
	}

	// resolutions
	if(obj->has_key("resolutions"))
	{
		const TJValue* resVal = obj->try_get_value("resolutions");
		if(!resVal->is_array())
		{
			Con_EPrintf("%s - 'resolutions' must be an array in '%s'.\n", __FUNCTION__, path.c_str());
			delete root; return nullptr;
		}

		const TJValueArray* resArr = static_cast<const TJValueArray*>(resVal);
		for(unsigned int i = 0; i < resArr->get_number_of_items(); ++i)
		{
			const TJValue* item = resArr->at(i);
			if(!item->is_object())
			{
				Con_EPrintf("%s - Each resolution must be an object in '%s'.\n", __FUNCTION__, path.c_str());
				delete root; return nullptr;
			}
			const TJValueObject* resObj = static_cast<const TJValueObject*>(item);

			text_reschema_t resInfo;

			// screenheight
			if(!resObj->has_key("screenheight") || !resObj->try_get_value("screenheight")->is_number())
			{
				Con_EPrintf("%s - Missing or invalid 'screenheight' in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
				delete root; return nullptr;
			}

			long long screenH = resObj->try_get_value("screenheight")->get_number();
			if(screenH < 480)
			{
				Con_EPrintf("%s - 'screenheight' too low in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
				delete root; return nullptr;
			}
			resInfo.screenheight = static_cast<Uint32>(screenH);

			// fontsize
			if(resObj->has_key("fontsize"))
			{
				const TJValue* fsize = resObj->try_get_value("fontsize");
				if(!fsize->is_number())
				{
					Con_EPrintf("%s - 'fontsize' must be a number in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
					delete root; return nullptr;
				}

				long long val = fsize->get_number();
				if(val < 4 || val > 256)
				{
					Con_EPrintf("%s - 'fontsize' out of range in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
					delete root; return nullptr;
				}
				resInfo.fontsize = static_cast<Uint32>(val);
			}
			else
			{
				resInfo.fontsize = schema.fontsize; // fallback to global
			}

			// outlineradius
			if(resObj->has_key("outlineradius"))
			{
				const TJValue* rad = resObj->try_get_value("outlineradius");
				if(!rad->is_number())
				{
					Con_EPrintf("%s - 'outlineradius' must be a number in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
					delete root; return nullptr;
				}

				long long val = rad->get_number();
				if(val < 0 || val > 4)
				{
					Con_EPrintf("%s - 'outlineradius' out of range in resolution %u in '%s'.\n", __FUNCTION__, i, path.c_str());
					delete root; return nullptr;
				}
				resInfo.outlineradius = static_cast<Uint32>(val);
			}
			else
			{
				resInfo.outlineradius = schema.outlineradius;
			}

			schema.resolutions.push_back(resInfo);
		}
	}

	delete root;
	return &m_schemasList.add(schema)->_val;
}