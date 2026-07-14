/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "uischema.h"

#include "r_common.h"
#include "textures_shared.h"

//=============================================
// @brief Constructor
//
//=============================================
CUISchemaManager::CUISchemaManager( const file_interface_t& fileInterface, pfnGetDummyTexture_t pfnGetDummyTexture, pfnLoadTexture_t pfnLoadTexture ):
	m_fileInterface( fileInterface ),
	m_pfnGetDummyTexture(pfnGetDummyTexture),
	m_pfnLoadTexture(pfnLoadTexture)
{
}

//=============================================
// @brief Destructor
//
//=============================================
CUISchemaManager::~CUISchemaManager( void )
{
	Clear();
}

//=============================================
// @brief
//
//=============================================
void CUISchemaManager::Clear( void )
{
	if(m_tabSchemeArray.empty())
		return;

	for(UInt32 i = 0; i < m_tabSchemeArray.size(); i++)
		delete m_tabSchemeArray[i];

	m_tabSchemeArray.clear();
}

//=============================================
// @brief
//
//=============================================
ui_schemeinfo_t* CUISchemaManager::LoadSchemaFile( const char* pstrFilename )
{
	// Try to find it in the cache first
	for(UInt32 i = 0; i < m_tabSchemeArray.size(); i++)
	{
		if(!qstrcmp(m_tabSchemeArray[i]->schemeName, pstrFilename))
			return m_tabSchemeArray[i];
	}

	// Load in the file
	CString scriptPath;
	scriptPath << "resources/schemas/" << pstrFilename;

	UInt32 fileSize = 0;
	const char* pfile = reinterpret_cast<const char*>(m_fileInterface.pfnLoadFile(scriptPath.c_str(), &fileSize));
	if(!pfile)
	{
		m_errorString << "Failed to load UI schema script '" << scriptPath.c_str() << "'";
		return nullptr;
	}

	CString jsonStr(reinterpret_cast<const char*>(pfile));
	m_fileInterface.pfnFreeFile(pfile);

	// Parse JSON
	parse_options opts;
	opts.throw_exception = false;
	opts.strict = false;

	TJValue* root = TJ::parse(jsonStr.c_str(), opts);
	if(!root)
	{
		m_errorString << "Failed to parse JSON in '" << scriptPath.c_str() << "'";
		return nullptr;
	}

	if(!root->is_array())
	{
		m_errorString << "Root must be an array in '" << scriptPath.c_str() << "'";
		delete root;
		return nullptr;
	}

	const TJValueArray* rootArr = static_cast<const TJValueArray*>(root);

	// Allocate new object
	ui_schemeinfo_t* pNew = new ui_schemeinfo_t;
	pNew->schemeName = pstrFilename;

	for(unsigned int i = 0; i < rootArr->get_number_of_items(); ++i)
	{
		const TJValue* item = rootArr->at(i);
		if(!item->is_object())
		{
			m_errorString << "Each item in array must be an object in '" << scriptPath.c_str() << "'";
			delete root;
			delete pNew;
			return nullptr;
		}

		const TJValueObject* obj = static_cast<const TJValueObject*>(item);

		const TJCHAR* typeStr = obj->try_get_string("type");
		if(!typeStr)
		{
			m_errorString << "Missing 'type' in object at index " << i << " in '" << scriptPath.c_str() << "'";
			delete root;
			delete pNew;
			return nullptr;
		}

		ui_schemeobject_t newObject;
		newObject.typeName = typeStr;

		// Helper lambdas
		auto readString = [&](const char* key) -> CString
		{
			if(obj->has_key(key))
			{
				const TJValue* val = obj->try_get_value(key);
				if(val && val->is_string())
				{
					return CString(val->get_string());
				}
			}
			return CString();
		};

		auto readInt = [&](const char* key, int& out) -> bool
		{
			if(obj->has_key(key))
			{
				const TJValue* val = obj->try_get_value(key);
				if(val && val->is_number())
				{
					out = static_cast<int>(val->get_number());
					return true;
				}
			}
			return false;
		};

		int width = 0, height = 0;
		readInt("width", width);
		readInt("height", height);

		CString defaultTex = readString("default");
		CString focusTex = readString("focus");
		CString clickTex = readString("clicked");
		CString disabledTex = readString("disabled");

		// Helper to load a texture and set width/height if not set
		auto loadTexture = [&](const CString& filename, en_texture_t*& outTex)
		{
			if(filename.empty())
			{
				return;
			}

			// If it's a texture resource, load it in
			CString texturePath;
			texturePath << "ui/" << filename;

			// Load it in
			en_texture_t* ptex = m_pfnLoadTexture(texturePath.c_str(), RS_WINDOW_LEVEL, TX_FL_NOMIPMAPS, nullptr);
			if(!ptex)
			{
				ptex = m_pfnGetDummyTexture();
			}
			outTex = ptex;
			
			if(!width)
			{
				width = ptex->width;
			}
			if(!height)
			{
				height = ptex->height;
			}
		};

		loadTexture(defaultTex, newObject.defaultTexture);
		loadTexture(focusTex, newObject.focusTexture);
		loadTexture(clickTex, newObject.clickTexture);
		loadTexture(disabledTex, newObject.disabledTexture);

		newObject.width = width;
		newObject.height = height;

		// Add it to the object
		pNew->tabObjects.push_back(newObject);
	}

	delete root;
	// Add this scheme object to the array
	m_tabSchemeArray.push_back(pNew);
	return pNew;
}

//=============================================
// @brief
//
//=============================================
UInt32 CUISchemaManager::GetNbWarnings( void ) const
{
	return m_warningStringArray.size();
}

//=============================================
// @brief
//
//=============================================
CString CUISchemaManager::GetWarning( UInt32 index ) const
{
	if(index > m_warningStringArray.size())
		return CString();
	else
		return m_warningStringArray[index];
}

//=============================================
// @brief
//
//=============================================
void CUISchemaManager::ClearWarnings( void )
{
	if(m_warningStringArray.empty())
		return;

	m_warningStringArray.clear();
}

//=============================================
// @brief
//
//=============================================
const CString& CUISchemaManager::GetErrorString( void ) const
{
	return m_errorString;
}