/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef IMPACTEFFECTS_H
#define IMPACTEFFECTS_H

#include "constants.h"

/*
====================
CMaterialDefinitions

====================
*/
class CMaterialDefinitions
{
public:
	struct penetration_t
	{
		penetration_t():
			bullettypeindex(0),
			penetrationdepth(0),
			maxpenetration(0),
			penetrationchance(0),
			damagefalloff(0),
			chancedecrease(0)
			{
			}

		Int32 bullettypeindex;
		float penetrationdepth;
		UInt32 maxpenetration;
		UInt32 penetrationchance;
		float damagefalloff;
		UInt32 chancedecrease;
	};

	struct ricochetinfo_t
	{
		ricochetinfo_t():
			bullettypeindex(0),
			maxangle(0),
			maxdeviation(0),
			ricochetchance(0),
			maxricochets(0),
			ricochetdmgfalloff(0)
			{}

		Int32 bullettypeindex;
		float maxangle;
		float maxdeviation;
		UInt32 ricochetchance;
		UInt32 maxricochets;
		float ricochetdmgfalloff;
	};

	struct materialdefinition_t
	{
		materialdefinition_t():
			scripttype(PART_SCRIPT_SYSTEM)
			{
			}

		const penetration_t* getPenetrationInfo(bullet_types_t bulletType) const
		{
			for (UInt32 i = 0; i < penetrationinfos.size(); i++)
			{
				if (penetrationinfos[i].bullettypeindex == bulletType)
					return &penetrationinfos[i];
			}

			return nullptr;
		}

		const ricochetinfo_t* getRicochetInfo(bullet_types_t bulletType) const
		{
			for (UInt32 i = 0; i < ricochetinfos.size(); i++)
			{
				if (ricochetinfos[i].bullettypeindex == bulletType)
					return &ricochetinfos[i];
			}

			return nullptr;
		}

		CString materialname;
		CString decalgroup;
		CString particlescript;
		part_script_type_t scripttype;
		CArray<CString> sounds;
		CArray<penetration_t> penetrationinfos;
		CArray<ricochetinfo_t> ricochetinfos;
	};

public:
	CMaterialDefinitions( void );
	~CMaterialDefinitions( void );

public:
	// Initializes the class
	bool Init( const char* pscriptfile );
	// Clears the class
	void Clear( void );

	// Gets the impact effect info for a material type
	const materialdefinition_t* GetDefinitionForMaterial( const char* pstrmaterialname ) const;
	// Returns the error string
	const char* GetError( void ) const { return m_errorString.c_str(); }

	// Returns the number of effect definitions
	UInt32 GetNbDefinitions( void ) const;
	// Returns an effect definition
	const materialdefinition_t* GetDefinition( UInt32 index ) const;

private:
	// Array of impact effects for materials
	CArray<materialdefinition_t> m_materialDefinitionsArray;
	// Error string
	CString m_errorString;
};
extern CMaterialDefinitions gMaterialDefinitions;
#endif //IMPACTEFFECTS_H