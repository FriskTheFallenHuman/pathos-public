/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "enginestate.h"
#include "window.h"
#include "common.h"
#include "file.h"
#include "cvar.h"
#include "cl_main.h"

#include "r_vbo.h"
#include "r_glsl.h"
#include "r_text.h"
#include "system.h"
#include "r_menu.h"

#include "uielements.h"
#include "uimanager.h"
#include "config.h"
#include "textschemas.h"

#undef clamp
#include "toml.hpp"

// I had a hard time deciding whether to keep liblist.gam or create something else

// Default font schema name
static const char DEFAULT_FONT_SCHEMA_NAME[] = "DefaultFont";

//=============================================
// @brief Returns the optimal frame limit
//
// @return The frame limit to be used for frame capping
//=============================================
bool Sys_LoadDefaultFont( const char* pstr )
{
	const font_set_t* pDefaultSet = gTextSchemas.GetSchemaFontSet(DEFAULT_FONT_SCHEMA_NAME);
	if(!pDefaultSet)
		pDefaultSet = gText.LoadFont(DEFAULT_FONTSET_NAME, DEFAULT_FONT_SIZE);

	if(!pDefaultSet)
	{
		Sys_ErrorPopup("%s - Failed to load default font set.\n", __FUNCTION__);
		return false;
	}
	
	gText.SetDefaultFont(pDefaultSet);
	return true;
}


//=============================================
// @brief Loads the gameinfo file
//
// @return Success status
//=============================================
bool Sys_LoadGameInfo( CArray<CString>* argsArray )
{
	UInt32 fileSize = 0;
	const Byte* pfile = FL_LoadFile(GAMEINFO_FILENAME, &fileSize);
	if(!pfile)
	{
		Sys_ErrorPopup("Failed to load %s.\n", GAMEINFO_FILENAME);
		return false;
	}

	const char* pFileStr = reinterpret_cast<const char*>(pfile);

	try
	{
		const toml::value data = toml::parse_str(pFileStr);

		// Helper lambdas
		auto getString = [&](const std::string& key, const std::string& fallback = "") -> std::string
		{
			if(data.contains(key) && data.at(key).is_string())
			{
				return toml::find<std::string>(data, key);
			}

			return fallback;
		};

		auto getInt = [&](const std::string& key, Int32 default_val, Int32 min, Int32 max) -> Int32
		{
			if(data.contains(key) && data.at(key).is_integer())
			{
				Int32 val = toml::find<Int32>(data, key);
				if (val >= min && val <= max)
					return val;

				Con_Printf("Value for '%s' (%d) out of range [%d..%d]; using default %d\n", key.c_str(), val, min, max, default_val);
			}
			return default_val;
		};

		if(data.contains("Name") && data.at("Name").is_table())
		{
			const auto& name = data.at("Name");
			if(name.contains("Game") && name.at("Game").is_string())
			{
				ens.gametitle = toml::find<std::string>(name, "Game").c_str();
			}

			if(ens.gametitle.empty())
			{
				Sys_ErrorPopup("Missing or invalid 'title' in %s\n", GAMEINFO_FILENAME);
				FL_FreeFile(pfile);
				return false;
			}

			if(name.contains("Title") && name.at("Title").is_string())
			{
				ens.gamemainmenutitle = toml::find<std::string>(name, "Title").c_str();
			}

			if(name.contains("GameLogo") && name.at("GameLogo").is_boolean())
			{
				ens.gamelogo = toml::find<bool>(name, "GameLogo");
			}
		}

		if(data.contains("Metadata") && data.at("Metadata").is_table())
		{
			const auto& metadata = data.at("Metadata");
			if(metadata.contains("Icon") && metadata.at("Icon").is_string())
			{
				ens.gameicon = toml::find<std::string>(metadata, "Icon").c_str();
			}
		}

		if(data.contains("Options") && data.at("Options").is_table())
		{
			const auto& options = data.at("Options");
			if(options.contains("StartMap") && options.at("StartMap").is_string())
			{
				ens.startmap = toml::find<std::string>(options, "StartMap").c_str();
			}

			if(ens.startmap.empty())
			{
				Sys_ErrorPopup("Missing or invalid 'startmap' in %s\n", GAMEINFO_FILENAME);
				FL_FreeFile(pfile);
				return false;
			}

			if(ens.arg_max_edicts == 0)
			{
				if(options.contains("MaxEdicts") && options.at("MaxEdicts").is_integer())
				{
					Int32 maxEdicts = toml::find<Int32>(options, "MaxEdicts");
					if(maxEdicts >= 1 && maxEdicts <= MAX_SERVER_ENTITIES)
						ens.arg_max_edicts = maxEdicts;
					else
						Con_Printf("MaxEdicts value %d invalid; must be 1..%d\n", 
								   maxEdicts, MAX_SERVER_ENTITIES);
				}
				else
				{
					ens.arg_max_edicts = MAX_SERVER_ENTITIES;
				}
			}

			if(options.contains("CommandLine") && options.at("CommandLine").is_array())
			{
				const auto& arr = options.at("CommandLine").as_array();
				for(const auto& elem : arr)
				{
					if(elem.is_string())
					{
						std::string arg = elem.as_string();
						argsArray->push_back(arg.c_str());
					}
					else
					{
						Con_Printf("CommandLine contains non‑string element; skipping\n");
					}
				}
			}
		}

		if(data.contains("Display") && data.at("Display").is_table())
		{
			const auto& display = data.at("Display");
			if(display.contains("StencilBits") && display.at("StencilBits").is_integer())
			{
				Int32 depthBits = toml::find<Int32>(display, "StencilBits");
				gConfig.SetValue("Display", "StencilBits", depthBits);
			}
		}

		// Free the file
		FL_FreeFile(pfile);
		return true;
	}
	catch(const toml::syntax_error& e)
	{
		Sys_ErrorPopup("TOML syntax error in %s:\n%s\n", GAMEINFO_FILENAME, e.what());
		FL_FreeFile(pfile);
		return false;
	}
	catch(const toml::type_error& e)
	{
		Sys_ErrorPopup("Type error in %s:\n%s\n", GAMEINFO_FILENAME, e.what());
		FL_FreeFile(pfile);
		return false;
	}
	catch(const std::exception& e)
	{
		Sys_ErrorPopup("Unexpected error reading %s:\n%s\n", GAMEINFO_FILENAME, e.what());
		FL_FreeFile(pfile);
		return false;
	}
}

//=============================================
// @brief Returns the launch arg count
//
// @return Launch args count
//=============================================
UInt32 Sys_LaunchArgc( void )
{
	return ens.launchargs.size();
}

//=============================================
// @brief Returns the launch arg count
//
// @return Launch args count
//=============================================
const char* Sys_LaunchArgv( UInt32 index )
{
	assert(index < ens.launchargs.size());
	return ens.launchargs[index].c_str();
}

//=============================================
// @brief Returns the launch arg count
//
// @return Launch args count
//=============================================
Int32 Sys_CheckLaunchArgs( const char* pstrArg )
{
	if(ens.launchargs.empty())
		return NO_POSITION;

	for(UInt32 i = 0; i < ens.launchargs.size(); i++)
	{
		if(!qstrcmp(pstrArg, ens.launchargs[i]))
			return i;
	}

	return NO_POSITION;
}

//=============================================
// @brief
//
// @return
//=============================================
bool Sys_IsGameControlActive( void )
{
	if(gMenu.IsActive())
		return false;

	if(gUIManager.HasActiveWindows())
		return false;
	
	if(cls.dllfuncs.pfnIsInputOverridden())
		return false;

	return true;
}

//=============================================
// @brief
//
// @return
//=============================================
void Sys_AddTempFile( const char* pstrFilepath, rs_level_t level )
{
	ens.tempfileslist.begin();
	while(!ens.tempfileslist.end())
	{
		tempfile_t& tmp = ens.tempfileslist.get();
		if(!qstrcmp(tmp.filepath, pstrFilepath))
			return;

		ens.tempfileslist.next();
	}

	tempfile_t newfile;
	newfile.filepath = pstrFilepath;
	newfile.level = level;

	ens.tempfileslist.add(newfile);
}

//=============================================
// @brief
//
// @return
//=============================================
void Sys_DeleteTempFiles( rs_level_t level )
{
	if(ens.tempfileslist.empty())
		return;

	ens.tempfileslist.begin();
	while(!ens.tempfileslist.end())
	{
		tempfile_t& tmp = ens.tempfileslist.get();
		if(tmp.level <= level)
		{
			if(!FL_DeleteFile(tmp.filepath.c_str()))
				Con_EPrintf("%s - Failed to delete temporary file '%s'.\n", __FUNCTION__, tmp.filepath.c_str());

			ens.tempfileslist.remove(ens.tempfileslist.get_link());
			ens.tempfileslist.next();
			continue;
		}

		ens.tempfileslist.next();
	}
}