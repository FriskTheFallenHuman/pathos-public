/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

//
// The original decal script that Pathos relies upon
// was created by BUzer
//

#include "includes.h"
#include "decallist.h"

#undef clamp
#include "toml.hpp"

//====================================
//
//====================================
CDecalList::CDecalList( void )
{
}

//====================================
//
//====================================
CDecalList::~CDecalList( void )
{
}

//====================================
//
//====================================
bool CDecalList::LoadDecalList( const char* pfile, UInt32 isize )
{
	// Clear this
	if(!m_errorString.empty())
		m_errorString.clear();

	// Also clear this
	if (!m_decalGroupsArray.empty())
		m_decalGroupsArray.clear();

	try
	{
		// Turn pfile into a std::string
		const toml::value data = toml::parse_str(pfile);

		// data must be a table
		if(!data.is_table())
		{
			m_errorString = "Root TOML element is not a table.";
			return false;
		}

		// Iterate over all top‑level tables (each is a decal group)
		const auto& rootTable = data.as_table();
		for(auto it = rootTable.begin(); it != rootTable.end(); ++it)
		{
			const std::string& groupName = it->first;
			const toml::value& groupValue = it->second;

			// groupValue must be a table
			if(!groupValue.is_table())
			{
				m_errorString << "Entry '" << groupName.c_str() << "' is not a table; skipping.";
				continue;
			}

			// Check for "entries" array
			if(!groupValue.contains("entries") || !groupValue.at("entries").is_array())
			{
				m_errorString << "Group '" << groupName.c_str() << "' has no 'entries' array; skipping.";
				continue;
			}

			const auto& entriesArray = groupValue.at("entries").as_array();
			if(entriesArray.empty())
				continue;

			// Create a new group
			const Uint32 newGroupIndex = m_decalGroupsArray.size();
			m_decalGroupsArray.resize(newGroupIndex + 1);
			decalgroup_t& group = m_decalGroupsArray[newGroupIndex];
			group.name = groupName.c_str();

			// Reserve space
			group.entries.resize(entriesArray.size());

			// Process each entry
			for(std::size_t i = 0; i < entriesArray.size(); ++i)
			{
				const toml::value& entryVal = entriesArray[i];

				if(!entryVal.is_table())
				{
					m_errorString << "Entry in group '" << groupName.c_str() << "' is not a table; skipping.";
					continue;
				}

				if(!entryVal.contains("name") || !entryVal.at("name").is_string())
				{
					m_errorString << "Entry missing 'name' in group '" << groupName.c_str() << "'; skipping.";
					continue;
				}
				if(!entryVal.contains("width") || !entryVal.at("width").is_integer())
				{
					m_errorString << "Entry missing 'width' in group '" << groupName.c_str() << "'; skipping.";
					continue;
				}
				if(!entryVal.contains("height") || !entryVal.at("height").is_integer())
				{
					m_errorString << "Entry missing 'height' in group '" << groupName.c_str() << "'; skipping.";
					continue;
				}

				// Extract values
				std::string name = toml::find<std::string>(entryVal, "name");
				Int32 width = toml::find<Int32>(entryVal, "width");
				Int32 height = toml::find<Int32>(entryVal, "height");

				// Fill the entry
				decalgroupentry_t& entry = group.entries[i];
				entry.name = name.c_str();
				entry.xsize = width / 2;
				entry.ysize = height / 2;
				entry.ptexture = nullptr;
				entry.pgroup = &group;
			}
		}

		if(m_decalGroupsArray.empty())
		{
			m_errorString = "No decal groups loaded from TOML file.";
			return false;
		}

		return true;
	}
	catch(const toml::syntax_error& e)
	{
		m_errorString << "TOML syntax error in %s:\n%s\n" << pfile << e.what();
		return false;
	}
	catch(const toml::type_error& e)
	{
		m_errorString << "Type error in %s:\n%s\n" << pfile << e.what();
		return false;
	}
	catch(const std::exception& e)
	{
		m_errorString << "Unexpected error reading %s:\n%s\n" << pfile << e.what();
		return false;
	}

	return true;
}

//====================================
//
//====================================
void CDecalList::Clear( void )
{
	if(m_decalGroupsArray.empty())
		return;

	m_decalGroupsArray.clear();
}

//====================================
//
//====================================
decalgroupentry_t *CDecalList::GetRandom( const char *szgroupname )
{
	for(UInt32 i = 0; i < m_decalGroupsArray.size(); i++)
	{
		if(!qstrcmp(m_decalGroupsArray[i].name, szgroupname))
		{
			decalgroup_t *pgroup = &m_decalGroupsArray[i];
			Int32 index = Common::RandomLong(0, pgroup->entries.size()-1);

			decalgroupentry_t *pentry = &pgroup->entries[index];
			return pentry;
		}
	}

	return nullptr;
}

//====================================
//
//====================================
decalgroupentry_t *CDecalList::GetByName( const char *szdecalname )
{
	for(UInt32 i = 0; i < m_decalGroupsArray.size(); i++)
	{
		decalgroup_t *pgroup = &m_decalGroupsArray[i];
		for(UInt32 j = 0; j < pgroup->entries.size(); j++)
		{
			if(!qstrcmp(pgroup->entries[j].name, szdecalname))
			{
				decalgroupentry_t *pentry = &pgroup->entries[j];
				return pentry;
			}
		}
	}

	return nullptr;
}

//====================================
//
//====================================
decalgroup_t* CDecalList::GetGroup( const char *szgroupname )
{
	for(UInt32 i = 0; i < m_decalGroupsArray.size(); i++)
	{
		decalgroup_t *pgroup = &m_decalGroupsArray[i];
		if(!qstrcmp(pgroup->name, szgroupname))
			return pgroup;
	}

	return nullptr;
}

//====================================
//
//====================================
decalgroup_t* CDecalList::GetGroup( UInt32 index )
{
	if(index >= m_decalGroupsArray.size())
		return nullptr;
	else
		return &m_decalGroupsArray[index];
}

//====================================
//
//====================================
UInt32 CDecalList::GetNbGroups( void ) const
{
	return m_decalGroupsArray.size();
}