/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "gd_includes.h"
#include "globalstate.h"

// Max damage force
static const float MAX_DAMAGE_FORCE = 1000.0f;

//=============================================
// @brief
//
//=============================================
CBaseEntity::CBaseEntity( edict_t* pedict ):
	m_pfnThinkFunction( nullptr ),
	m_pfnTouchFunction(nullptr),
	m_pfnBlockedFunction(nullptr),
	m_pfnUseFunction(nullptr),
	m_pState(&pedict->state),
	m_pFields(&pedict->fields),
	m_pEdict(pedict),
	m_lastThinkTime(0),
	m_visibilityCullDistance(0)
{
}

//=============================================
// @brief
//
//=============================================
CBaseEntity::~CBaseEntity( void )
{
}

//=============================================
// @brief
//
//=============================================
CBaseEntity* CBaseEntity::GetClass( edict_t* pedict )
{
	assert(pedict->pprivatedata != nullptr);
	return reinterpret_cast<CBaseEntity*>(pedict->pprivatedata);
}

//=============================================
// @brief
//
//=============================================
const CBaseEntity* CBaseEntity::GetClass( const edict_t* pedict )
{
	assert(pedict->pprivatedata != nullptr);
	return reinterpret_cast<const CBaseEntity*>(pedict->pprivatedata);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::SetObjectCollisionBox( void )
{
	// Note to self:
	// DO NOT modify m_pState->mins/m_pState->maxs, as that has to
	// be the original bsp model's mins/maxs for proper functioning of
	// func_door_rotating entities. Only set absmin/absmax

	if(m_pState->solid == SOLID_BSP && !Math::IsVectorZero(m_pState->angles))
	{
		float max = 0;
		for(UInt32 i = 0; i < 3; i++)
		{
			float size = SDL_fabs(m_pState->mins[i]);
			if(size > max)
				max = size;

			size = SDL_fabs(m_pState->maxs[i]);
			if(size > max)
				max = size;
		}

		for(UInt32 i = 0; i < 3; i++)
		{
			m_pState->absmin[i] = m_pState->origin[i] - 512;
			m_pState->absmax[i] = m_pState->origin[i] + 512;
		}
	}
	else
	{
		Math::VectorAdd(m_pState->origin, m_pState->mins, m_pState->absmin);
		Math::VectorAdd(m_pState->origin, m_pState->maxs, m_pState->absmax);
	}

	for(UInt32 i = 0; i < 3; i++)
	{
		m_pState->absmax[i] += 1;
		m_pState->absmin[i] -= 1;
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::DeclareSaveFields( void )
{
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_pfnThinkFunction, EFIELD_FUNCPTR));
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_pfnTouchFunction, EFIELD_FUNCPTR));
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_pfnBlockedFunction, EFIELD_FUNCPTR));
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_pfnUseFunction, EFIELD_FUNCPTR));
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_visibilityCullDistance, EFIELD_INT32));
	DeclareSaveField(DEFINE_DATA_FIELD(CBaseEntity, m_lastThinkTime, EFIELD_TIME));
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::ReleaseSaveFields( void )
{
	if(m_saveFieldsList.empty())
		return;

	m_saveFieldsList.clear();
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::MakeEntityDormant( void )
{
	m_pState->flags |= FL_DORMANT;

	m_pState->solid = SOLID_NOT;
	m_pState->movetype = MOVETYPE_NONE;
	m_pState->nextthink = 0;
	m_pState->effects |= EF_NODRAW;

	gd_engfuncs.pfnSetOrigin(m_pEdict, m_pState->origin);
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::IsDormant( void )
{
	return (m_pState->flags & FL_DORMANT) ? true : false;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::ShouldToggle( usemode_t useMode, bool currentState )
{
	if(useMode != USE_TOGGLE && useMode != USE_SET && currentState && useMode == USE_ON || !currentState && useMode == USE_OFF)
		return false;
	else
		return true;
}

//=============================================
// @brief
//
//=============================================
const char* CBaseEntity::GetDamageDecal( Int32 damageFlags )
{
	if(m_pState->rendermode != RENDER_NORMAL)
		return "shot_glass";
	else
		return "shot";
}

//=============================================
// @brief
//
//=============================================
CBaseEntity* CBaseEntity::CreateEntity( const char* pstrClassName, const Vector& origin, const Vector& angles, CBaseEntity* powner )
{
	edict_t* pedict = gd_engfuncs.pfnCreateEntity(pstrClassName);
	if(!pedict)
	{
		gd_engfuncs.pfnCon_WPrintf("Couldn't create entity class '%s'.\n", pstrClassName);
		return nullptr;
	}

	if(powner)
		pedict->state.owner = powner->GetEntityIndex();
	else
		pedict->state.owner = NO_ENTITY_INDEX;

	pedict->state.origin = origin;
	pedict->state.angles = angles;

	return CBaseEntity::GetClass(pedict);
}

//=============================================
// @brief
//
//=============================================
CBaseEntity* CBaseEntity::CreateEntity( const char* pstrClassName, CBaseEntity* powner )
{
	edict_t* pedict = gd_engfuncs.pfnCreateEntity(pstrClassName);
	if(!pedict)
	{
		gd_engfuncs.pfnCon_WPrintf("Couldn't create entity class '%s'.\n", pstrClassName);
		return nullptr;
	}

	if(powner)
		pedict->state.owner = powner->GetEntityIndex();
	else
		pedict->state.owner = NO_ENTITY_INDEX;

	return CBaseEntity::GetClass(pedict);
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::Spawn( void )
{
	// Call precache functions
	Precache();

	return true;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::KeyValue( const keyvalue_t& kv )
{
	if(!qstrcmp(kv.keyname, "visdistance"))
	{
		m_visibilityCullDistance = SDL_atoi(kv.value);
		return true;
	}
	else
		return false;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::Restore( void )
{
	// Set origin so entity gets linked up
	gd_engfuncs.pfnSetOrigin(m_pEdict, m_pState->origin);

	// Re-set the model index
	if(m_pFields->modelname != NO_STRING_VALUE)
	{
		if(!SetModel(m_pFields->modelname, ShouldSetBoundsOnRestore()))
			return false;
	}

	// TODO: fix parenting somehow
	if(!m_pState->parentoffset.IsZero())
		m_pState->parentoffset.Clear();

	return true;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::AdjustEntityPositions( const Vector& posAdj )
{
	m_saveFieldsList.begin();
	while(!m_saveFieldsList.end())
	{
		entity_data_desc_t& field = m_saveFieldsList.get();

		// Do not modify global fields of transitioning entities
		if(field.flags & EFIELD_GLOBAL)
		{
			m_saveFieldsList.next();
			continue;
		}

		for(UInt32 j = 0; j < field.size; j++)
		{
			Byte* pdata = (reinterpret_cast<Byte*>(this) + field.offset);

			switch(field.type)
			{
			case EFIELD_COORD:
				{
					Vector& vecValue = *(reinterpret_cast<Vector*>(pdata) + j);
					vecValue -= posAdj;
				}
				break;
			default:
				break;
			}
		}

		m_saveFieldsList.next();
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::FreeEntity( edict_removed_t freeMode )
{
	// Release any relevant data on client side
	gd_engfuncs.pfnUserMessageBegin(MSG_ALL, g_usermsgs.freeentitydata, nullptr, nullptr);
	gd_engfuncs.pfnMsgWriteInt16(GetEntityIndex());
	gd_engfuncs.pfnMsgWriteByte(GetFreeMessageFlags());
	gd_engfuncs.pfnUserMessageEnd();

	// If we have a global name, set global state
	if(m_pFields->globalname != NO_STRING_VALUE)
	{
		const char* pstrGlobalname = gd_engfuncs.pfnGetString(m_pFields->globalname);
		gGlobalStates.SetGlobalState(pstrGlobalname, GLOBAL_DEAD);
	}

	// Notify owner
	if(m_pState->owner != NO_ENTITY_INDEX)
	{
		CBaseEntity* pOwner = GetOwner();
		if(pOwner)
			pOwner->ChildEntityRemoved(this);
	}

	// Notify parent
	if(m_pState->parent != NO_ENTITY_INDEX)
	{
		CBaseEntity* pParent = GetParent();
		if(pParent)
			pParent->ChildEntityRemoved(this);
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::DeclareSaveField( entity_data_desc_t desc )
{
	// Make sure this field hasn't been added before
	m_saveFieldsList.begin();
	while(!m_saveFieldsList.end())
	{
		entity_data_desc_t& checkdesc = m_saveFieldsList.get();
		if(!qstrcmp(checkdesc.fieldname.c_str(), desc.fieldname.c_str()))
		{
			gd_engfuncs.pfnCon_Printf("Error: Save field with name '%s' already declared.\n", desc.fieldname.c_str());
			return;
		}

		m_saveFieldsList.next();
	}

	// Add it to the list
	m_saveFieldsList.add(desc);
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::GetEntityFieldDataForSave( const entity_data_desc_t& field, Byte*& dataPtr, UInt32& fieldSize )
{
	// Get pointer to the object in the class data
	Byte* pdata = (reinterpret_cast<Byte*>(this) + field.offset);

	switch (field.type)
	{
	case EFIELD_FLOAT:
	case EFIELD_DOUBLE:
	case EFIELD_STRING:
	case EFIELD_ENTINDEX:
	case EFIELD_ENTPOINTER:
	case EFIELD_EDICT:
	case EFIELD_ENTSTATE:
	case EFIELD_EHANDLE:
	case EFIELD_VECTOR:
	case EFIELD_COORD:
	case EFIELD_INT16:
	case EFIELD_UINT16:
	case EFIELD_INT32:
	case EFIELD_UINT32:
	case EFIELD_INT64:
	case EFIELD_UINT64:
	case EFIELD_FUNCPTR:
	case EFIELD_BOOLEAN:
	case EFIELD_BYTE:
	case EFIELD_CHAR:
	case EFIELD_TIME:
	case EFIELD_MODELNAME:
	case EFIELD_SOUNDNAME:
		{
			dataPtr = pdata;
			fieldSize = field.size;
		}
		break;
	case EFIELD_CARRAY_FLOAT:
		{
			CArray<float>& arrayObject = (*reinterpret_cast<CArray<float>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_DOUBLE:
		{
			CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_STRING:
		{
			CArray<string_t>& arrayObject = (*reinterpret_cast<CArray<string_t>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_ENTINDEX:
		{
			CArray<entindex_t>& arrayObject = (*reinterpret_cast<CArray<entindex_t>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_ENTPOINTER:
		{
			CArray<CBaseEntity*>& arrayObject = (*reinterpret_cast<CArray<CBaseEntity*>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_EDICT:
		{
			CArray<edict_t*>& arrayObject = (*reinterpret_cast<CArray<edict_t*>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_ENTSTATE:
		{
			CArray<entity_state_t*>& arrayObject = (*reinterpret_cast<CArray<entity_state_t*>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_EHANDLE:
		{
			CArray<CEntityHandle>& arrayObject = (*reinterpret_cast<CArray<CEntityHandle>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_VECTOR:
		{
			CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_COORD:
		{
			CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_INT16:
		{
			CArray<Int16>& arrayObject = (*reinterpret_cast<CArray<Int16>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_UINT16:
		{
			CArray<UInt16>& arrayObject = (*reinterpret_cast<CArray<UInt16>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_INT32:
		{
			CArray<Int32>& arrayObject = (*reinterpret_cast<CArray<Int32>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_UINT32:
		{
			CArray<UInt32>& arrayObject = (*reinterpret_cast<CArray<UInt32>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_INT64:
		{
			CArray<Int64>& arrayObject = (*reinterpret_cast<CArray<Int64>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_UINT64:
		{
			CArray<UInt64>& arrayObject = (*reinterpret_cast<CArray<UInt64>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_BOOLEAN:
		{
			CArray<bool>& arrayObject = (*reinterpret_cast<CArray<bool>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	case EFIELD_CARRAY_TIME:
		{
			CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
			if(arrayObject.empty())
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
				fieldSize = arrayObject.size();
			}
		}
		break;
	default:
	case EFIELD_CBITSET:
		{
			CBitSet& bitSetObject = (*reinterpret_cast<CBitSet*>(pdata));
			if(bitSetObject.size() <= 0)
			{
				dataPtr = nullptr;
				fieldSize = 0;
			}
			else
			{
				dataPtr = reinterpret_cast<Byte*>(bitSetObject.getData());
				fieldSize = bitSetObject.size();
			}
		}
		break;
	case EFIELD_UNDEFINED:
		{
			dataPtr = nullptr;
			fieldSize = 0;
			return false;
		}
		break;
	}

	return true;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::GetEntityFieldDataForRestore( const entity_data_desc_t& field, Byte*& dataPtr, UInt32 arrayIndex, UInt32 dataSize )
{
	// Get pointer to the object in the class data
	Byte* pdata = (reinterpret_cast<Byte*>(this) + field.offset);

	switch (field.type)
	{
	case EFIELD_FLOAT:
	case EFIELD_DOUBLE:
	case EFIELD_STRING:
	case EFIELD_ENTINDEX:
	case EFIELD_ENTPOINTER:
	case EFIELD_EDICT:
	case EFIELD_ENTSTATE:
	case EFIELD_EHANDLE:
	case EFIELD_VECTOR:
	case EFIELD_COORD:
	case EFIELD_INT16:
	case EFIELD_UINT16:
	case EFIELD_INT32:
	case EFIELD_UINT32:
	case EFIELD_INT64:
	case EFIELD_UINT64:
	case EFIELD_FUNCPTR:
	case EFIELD_BOOLEAN:
	case EFIELD_BYTE:
	case EFIELD_CHAR:
	case EFIELD_TIME:
	case EFIELD_MODELNAME:
	case EFIELD_SOUNDNAME:
		{
			dataPtr = pdata;
		}
		break;
	case EFIELD_CARRAY_FLOAT:
		{
			CArray<float>& arrayObject = (*reinterpret_cast<CArray<float>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_DOUBLE:
		{
			CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_STRING:
		{
			CArray<string_t>& arrayObject = (*reinterpret_cast<CArray<string_t>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_ENTINDEX:
		{
			CArray<entindex_t>& arrayObject = (*reinterpret_cast<CArray<entindex_t>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_ENTPOINTER:
		{
			CArray<CBaseEntity*>& arrayObject = (*reinterpret_cast<CArray<CBaseEntity*>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_EDICT:
		{
			CArray<edict_t*>& arrayObject = (*reinterpret_cast<CArray<edict_t*>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_ENTSTATE:
		{
			CArray<entity_state_t*>& arrayObject = (*reinterpret_cast<CArray<entity_state_t*>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_EHANDLE:
		{
			CArray<CEntityHandle>& arrayObject = (*reinterpret_cast<CArray<CEntityHandle>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_VECTOR:
		{
			CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_COORD:
		{
			CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_INT16:
		{
			CArray<Int16>& arrayObject = (*reinterpret_cast<CArray<Int16>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_UINT16:
		{
			CArray<UInt16>& arrayObject = (*reinterpret_cast<CArray<UInt16>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_INT32:
		{
			CArray<Int32>& arrayObject = (*reinterpret_cast<CArray<Int32>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_UINT32:
		{
			CArray<UInt32>& arrayObject = (*reinterpret_cast<CArray<UInt32>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_INT64:
		{
			CArray<Int64>& arrayObject = (*reinterpret_cast<CArray<Int64>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_UINT64:
		{
			CArray<UInt64>& arrayObject = (*reinterpret_cast<CArray<UInt64>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_BOOLEAN:
		{
			CArray<bool>& arrayObject = (*reinterpret_cast<CArray<bool>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CARRAY_TIME:
		{
			CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
			assert(arrayObject.size() > arrayIndex);
			dataPtr = reinterpret_cast<Byte*>(&arrayObject[0]);
		}
		break;
	case EFIELD_CBITSET:
		{
			CBitSet& bitsetObject = (*reinterpret_cast<CBitSet*>(pdata));
			assert(bitsetObject.size() == dataSize);
			dataPtr = reinterpret_cast<Byte*>(bitsetObject.getData());
		}
		break;
	default:
	case EFIELD_UNDEFINED:
		{
			dataPtr = nullptr;
			return false;
		}
		break;
	}

	return true;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::SaveEntityClassData( bool istransitionsave )
{
	m_saveFieldsList.begin();
	while(!m_saveFieldsList.end())
	{
		entity_data_desc_t& field = m_saveFieldsList.get();

		// Get field data from class
		Byte* pdata;
		UInt32 fieldsize;
		if (!GetEntityFieldDataForSave(field, pdata, fieldsize))
		{
			gd_engfuncs.pfnCon_EPrintf("Error: Failed to get data for field '%s' for CBaseEntity.\n", field.fieldname.c_str());
			m_saveFieldsList.next();
			continue;
		}

		if(!pdata || !fieldsize)
		{
			m_saveFieldsList.next();
			continue;
		}

		// Manage based on type
		switch(field.type)
		{
		case EFIELD_FLOAT:
		case EFIELD_CARRAY_FLOAT:
			{
				if(field.type != EFIELD_CARRAY_FLOAT && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(float)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteFloat(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_DOUBLE:
		case EFIELD_CARRAY_DOUBLE:
			{
				if(field.type != EFIELD_CARRAY_DOUBLE && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(double)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteDouble(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_ENTINDEX:
		case EFIELD_CARRAY_ENTINDEX:
			{
				if(field.type != EFIELD_CARRAY_ENTINDEX && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS))
				{
					UInt32 i = 0;
					for(; i < fieldsize; i++)
					{
						const entindex_t* pvalue = reinterpret_cast<entindex_t*>(pdata)+i;
						if(*pvalue != NO_ENTITY_INDEX)
							break;
					}

					if(i == fieldsize)
					{
						m_saveFieldsList.next();
						continue;
					}
				}

				gd_engfuncs.pfnSaveWriteEntindex(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_ENTPOINTER:
		case EFIELD_CARRAY_ENTPOINTER:
			{
				bool hasData = false;
				entindex_t *ptempbuffer = new entindex_t[fieldsize];
				for(UInt32 j = 0; j < fieldsize; j++)
				{
					CBaseEntity* pEntity = (reinterpret_cast<CBaseEntity**>(pdata))[j];
					if(pEntity)
					{
						ptempbuffer[j] = pEntity->GetEntityIndex();
						hasData = true;
					}
					else
						ptempbuffer[j] = NO_ENTITY_INDEX;
				}

				if(field.type != EFIELD_CARRAY_ENTPOINTER && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && !hasData)
				{
					m_saveFieldsList.next();
					delete[] ptempbuffer;
					continue;
				}

				gd_engfuncs.pfnSaveWriteEntindex(field.fieldname.c_str(), reinterpret_cast<Byte*>(ptempbuffer), fieldsize, field.type);
				delete[] ptempbuffer;
			}
			break;
		case EFIELD_EDICT:
		case EFIELD_CARRAY_EDICT:
			{
				bool hasData = false;
				entindex_t *ptempbuffer = new entindex_t[fieldsize];
				for(UInt32 j = 0; j < fieldsize; j++)
				{
					edict_t* pEntity = (reinterpret_cast<edict_t**>(pdata))[j];
					if(pEntity)
					{
						ptempbuffer[j] = pEntity->entindex;
						hasData = true;
					}
					else
						ptempbuffer[j] = NO_ENTITY_INDEX;
				}

				if(field.type != EFIELD_CARRAY_EDICT && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && !hasData)
				{
					m_saveFieldsList.next();
					delete[] ptempbuffer;
					continue;
				}

				gd_engfuncs.pfnSaveWriteEntindex(field.fieldname.c_str(), reinterpret_cast<Byte*>(ptempbuffer), fieldsize, field.type);
				delete[] ptempbuffer;
			}
			break;
		case EFIELD_ENTSTATE:
		case EFIELD_CARRAY_ENTSTATE:
			{
				bool hasData = false;
				entindex_t *ptempbuffer = new entindex_t[fieldsize];
				for(UInt32 j = 0; j < fieldsize; j++)
				{
					entity_state_t* pEntity = (reinterpret_cast<entity_state_t**>(pdata))[j];
					if(pEntity)
					{
						ptempbuffer[j] = pEntity->entindex;
						hasData = true;
					}
					else
						ptempbuffer[j] = NO_ENTITY_INDEX;
				}

				if(field.type != EFIELD_CARRAY_ENTSTATE && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && !hasData)
				{
					m_saveFieldsList.next();
					delete[] ptempbuffer;
					continue;
				}

				gd_engfuncs.pfnSaveWriteEntindex(field.fieldname.c_str(), reinterpret_cast<Byte*>(ptempbuffer), fieldsize, field.type);
				delete[] ptempbuffer;
			}
			break;
		case EFIELD_EHANDLE:
		case EFIELD_CARRAY_EHANDLE:
			{
				bool hasData = false;
				entindex_t *ptempbuffer = new entindex_t[fieldsize];
				for(UInt32 j = 0; j < fieldsize; j++)
				{
					CEntityHandle* pEntity = reinterpret_cast<CEntityHandle*>(pdata) + j;
					if(*pEntity)
					{
						ptempbuffer[j] = pEntity->get()->entindex;
						hasData = true;
					}
					else
						ptempbuffer[j] = NO_ENTITY_INDEX;
				}

				if(field.type != EFIELD_CARRAY_EHANDLE && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && !hasData)
				{
					m_saveFieldsList.next();
					delete[] ptempbuffer;
					continue;
				}

				gd_engfuncs.pfnSaveWriteEntindex(field.fieldname.c_str(), reinterpret_cast<Byte*>(ptempbuffer), fieldsize, field.type);
				delete[] ptempbuffer;
			}
			break;
		case EFIELD_VECTOR:
		case EFIELD_CARRAY_VECTOR:
			{
				if(field.type != EFIELD_CARRAY_VECTOR && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS))
				{
					UInt32 i = 0;
					for(; i < fieldsize; i++)
					{
						const Vector* pvalue = reinterpret_cast<Vector*>(pdata)+i;
						if(!pvalue->IsZero())
							break;
					}

					if(i == fieldsize)
					{
						m_saveFieldsList.next();
						continue;
					}
				}

				gd_engfuncs.pfnSaveWriteVector(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_COORD:
		case EFIELD_CARRAY_COORD:
			{
				// Coord should always be written, because when restored, we need this entry to do so, and
				// entities like brush models can have zero origins that are still valid positions
				gd_engfuncs.pfnSaveWriteCoord(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_INT16:
		case EFIELD_CARRAY_INT16:
			{
				if(field.type != EFIELD_CARRAY_INT16 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(Int16)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteInt16(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_UINT16:
		case EFIELD_CARRAY_UINT16:
			{
				if(field.type != EFIELD_CARRAY_UINT16 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(UInt16)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteUint16(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_INT32:
		case EFIELD_CARRAY_INT32:
			{
				if(field.type != EFIELD_CARRAY_INT32 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(Int32)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteInt32(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_UINT32:
		case EFIELD_CARRAY_UINT32:
			{
				if(field.type != EFIELD_CARRAY_UINT32 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(UInt32)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteUint32(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_INT64:
		case EFIELD_CARRAY_INT64:
			{
				if(field.type != EFIELD_CARRAY_INT64 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(Int64)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteInt64(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_UINT64:
		case EFIELD_CARRAY_UINT64:
			{
				if(field.type != EFIELD_CARRAY_UINT64 && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(UInt64)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteUint64(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_FUNCPTR:
			{
				CString functionName;
				void** functionPtr = reinterpret_cast<void**>(&(*pdata));
				if(*functionPtr)
				{
					// Get function name based on pointer address
					functionName = gd_engfuncs.pfnNameForFunction(*functionPtr);

					// Report error
					if(functionName.empty())
						gd_engfuncs.pfnCon_Printf("Couldn't find name for %s function '%p'.\n", field.fieldname.c_str(), reinterpret_cast<void*>(&*functionPtr));
				}
				
				if(!istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && functionName.empty())
				{
					// No value, so skip
					m_saveFieldsList.next();
					continue;
				}
					
				gd_engfuncs.pfnSaveWriteRawString(field.fieldname.c_str(), reinterpret_cast<const Byte*>(functionName.c_str()), field.type);
			}
			break;
		case EFIELD_BOOLEAN:
		case EFIELD_CARRAY_BOOLEAN:
			{
				if(field.type != EFIELD_CARRAY_BOOLEAN && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(bool)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteBool(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_BYTE:
			{
				if(!istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(Byte)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteByte(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_CHAR:
			{
				if(!istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(char)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteChar(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_TIME:
		case EFIELD_CARRAY_TIME:
			{
				if(field.type != EFIELD_CARRAY_TIME && !istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS) && Util::IsDataEmpty(pdata, sizeof(double)*fieldsize))
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteTime(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_STRING:
		case EFIELD_CARRAY_STRING:
		case EFIELD_MODELNAME:
		case EFIELD_SOUNDNAME:
			{
				if(!istransitionsave && !(field.flags & EFIELD_SAVE_ALWAYS))
				{
					UInt32 i = 0;
					for(; i < fieldsize; i++)
					{
						string_t stringIndex = Common::ByteToUint32(reinterpret_cast<Byte *>(pdata) + sizeof(string_t)*i);
						if(stringIndex != NO_STRING_VALUE)
							break;
					}

					if(i == fieldsize)
					{
						m_saveFieldsList.next();
						continue;
					}
				}

				gd_engfuncs.pfnSaveWriteString(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		case EFIELD_CBITSET:
			{
				if(fieldsize <= 0)
				{
					m_saveFieldsList.next();
					continue;
				}

				gd_engfuncs.pfnSaveWriteBitset(field.fieldname.c_str(), pdata, fieldsize, field.type);
			}
			break;
		default:
			gd_engfuncs.pfnCon_EPrintf("Error: Invalid field type %d for field '%s' for CBaseEntity.\n", field.type, field.fieldname.c_str());
			break;
		}

		m_saveFieldsList.next();
	}
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::PrepareEntityClassData( const char* fieldname, UInt32 numblocks, bool istransferglobalentity )
{
	m_saveFieldsList.begin();
	while(!m_saveFieldsList.end())
	{
		entity_data_desc_t& field = m_saveFieldsList.get();
		if(!qstrcmp(fieldname, field.fieldname))
		{
			// Do not modify global fields of transitioning entities
			if(istransferglobalentity && (field.flags & EFIELD_GLOBAL))
				return true;

			// Get pointer to the object in the class data
			Byte* pdata = (reinterpret_cast<Byte*>(this) + field.offset);

			switch (field.type)
			{
			case EFIELD_FLOAT:
			case EFIELD_DOUBLE:
			case EFIELD_STRING:
			case EFIELD_ENTINDEX:
			case EFIELD_ENTPOINTER:
			case EFIELD_EDICT:
			case EFIELD_ENTSTATE:
			case EFIELD_EHANDLE:
			case EFIELD_VECTOR:
			case EFIELD_COORD:
			case EFIELD_INT16:
			case EFIELD_UINT16:
			case EFIELD_INT32:
			case EFIELD_UINT32:
			case EFIELD_INT64:
			case EFIELD_UINT64:
			case EFIELD_FUNCPTR:
			case EFIELD_BOOLEAN:
			case EFIELD_BYTE:
			case EFIELD_CHAR:
			case EFIELD_TIME:
			case EFIELD_MODELNAME:
			case EFIELD_SOUNDNAME:
				{
					// Nothing to do here
					return true;
				}
				break;
			case EFIELD_CARRAY_FLOAT:
				{
					CArray<float>& arrayObject = (*reinterpret_cast<CArray<float>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_DOUBLE:
				{
					CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_STRING:
				{
					CArray<string_t>& arrayObject = (*reinterpret_cast<CArray<string_t>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_ENTINDEX:
				{
					CArray<entindex_t>& arrayObject = (*reinterpret_cast<CArray<entindex_t>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_ENTPOINTER:
				{
					CArray<CBaseEntity*>& arrayObject = (*reinterpret_cast<CArray<CBaseEntity*>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_EDICT:
				{
					CArray<edict_t*>& arrayObject = (*reinterpret_cast<CArray<edict_t*>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_ENTSTATE:
				{
					CArray<entity_state_t*>& arrayObject = (*reinterpret_cast<CArray<entity_state_t*>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_EHANDLE:
				{
					CArray<CEntityHandle>& arrayObject = (*reinterpret_cast<CArray<CEntityHandle>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_VECTOR:
				{
					CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_COORD:
				{
					CArray<Vector>& arrayObject = (*reinterpret_cast<CArray<Vector>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_INT16:
				{
					CArray<Int16>& arrayObject = (*reinterpret_cast<CArray<Int16>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_UINT16:
				{
					CArray<UInt16>& arrayObject = (*reinterpret_cast<CArray<UInt16>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_INT32:
				{
					CArray<Int32>& arrayObject = (*reinterpret_cast<CArray<Int32>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_UINT32:
				{
					CArray<UInt32>& arrayObject = (*reinterpret_cast<CArray<UInt32>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_INT64:
				{
					CArray<Int64>& arrayObject = (*reinterpret_cast<CArray<Int64>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_UINT64:
				{
					CArray<UInt64>& arrayObject = (*reinterpret_cast<CArray<UInt64>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_BOOLEAN:
				{
					CArray<bool>& arrayObject = (*reinterpret_cast<CArray<bool>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CARRAY_TIME:
				{
					CArray<double>& arrayObject = (*reinterpret_cast<CArray<double>*>(pdata));
					if(arrayObject.size() < numblocks)
						arrayObject.resize(numblocks);

					return true;
				}
				break;
			case EFIELD_CBITSET:
				{
					CBitSet& bitsetObject = (*reinterpret_cast<CBitSet*>(pdata));
					if(bitsetObject.size() < numblocks)
						bitsetObject.resize(numblocks);

					return true;
				}
				break;
			default:
			case EFIELD_UNDEFINED:
				{
					gd_engfuncs.pfnCon_EPrintf("%s - Field '%s' has an invalid field type.\n", __FUNCTION__, fieldname);
					return false;
				}
				break;
			}
		}
		m_saveFieldsList.next();
	}

	// Manage any missing fields
	gd_engfuncs.pfnCon_EPrintf("%s - Field '%s' not found in entity class data.\n", __FUNCTION__, fieldname);
	return true;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::ReadEntityClassData( const char* fieldname, const Byte* pdata, UInt32 datasize, UInt32 blockindex, bool istransferglobalentity )
{
	m_saveFieldsList.begin();
	while(!m_saveFieldsList.end())
	{
		entity_data_desc_t& field = m_saveFieldsList.get();
		if(!qstrcmp(fieldname, field.fieldname))
		{
			// Do not modify global fields of transitioning entities
			if(istransferglobalentity && (field.flags & EFIELD_GLOBAL))
				return true;

			// Retrieve pointer to data
			Byte* pdestdata;
			if(!GetEntityFieldDataForRestore(field, pdestdata, blockindex, datasize))
			{
				gd_engfuncs.pfnCon_EPrintf("%s - Couldn't get restore data for field '%s' for CBaseEntity.\n", __FUNCTION__, fieldname);
				return false;
			}

			switch(field.type)
			{
			case EFIELD_CHAR:
				{
					char *pDestPtr = reinterpret_cast<char*>(pdestdata);
					memcpy(pDestPtr, pdata, sizeof(Byte)*field.size);
				}
				break;
			case EFIELD_BYTE:
				{
					memcpy(pdestdata, pdata, sizeof(Byte)*field.size);
				}
				break;
			case EFIELD_ENTINDEX:
			case EFIELD_CARRAY_ENTINDEX:
				{
					entindex_t entindex = Common::ByteToInt32(pdata);
					if(entindex != NO_ENTITY_INDEX)
						entindex = (*g_saveRestoreData.pentityindexarray)[entindex];

					entindex_t *pDestPtr = reinterpret_cast<entindex_t *>(pdestdata) + blockindex;
					(*pDestPtr) = entindex;
				}
				break;
			case EFIELD_ENTPOINTER:
			case EFIELD_CARRAY_ENTPOINTER:
				{
					entindex_t entindex = Common::ByteToInt32(pdata);
					if(entindex == NO_ENTITY_INDEX)
						return true;

					entindex_t realindex = (*g_saveRestoreData.pentityindexarray)[entindex];
					if(realindex == NO_ENTITY_INDEX)
						return true;

					edict_t* pEdict = gd_engfuncs.pfnGetEdictByIndex(realindex);
					CBaseEntity* pEntity = CBaseEntity::GetClass(pEdict);

					CBaseEntity **pDestPtr = reinterpret_cast<CBaseEntity **>(pdestdata) + blockindex;
					(*pDestPtr) = pEntity;
				}
				break;
			case EFIELD_EDICT:
			case EFIELD_CARRAY_EDICT:
				{
					entindex_t entindex = Common::ByteToInt32(pdata);
					if(entindex == NO_ENTITY_INDEX)
						return true;

					entindex_t realindex = (*g_saveRestoreData.pentityindexarray)[entindex];
					if(realindex == NO_ENTITY_INDEX)
						return true;

					edict_t* pEdict = gd_engfuncs.pfnGetEdictByIndex(realindex);

					edict_t** pDestPtr = reinterpret_cast<edict_t**>(pdestdata) + blockindex;
					(*pDestPtr) = pEdict;
				}
				break;
			case EFIELD_ENTSTATE:
			case EFIELD_CARRAY_ENTSTATE:
				{
					entindex_t entindex = Common::ByteToInt32(pdata);
					if(entindex == NO_ENTITY_INDEX)
						return true;

					entindex_t realindex = (*g_saveRestoreData.pentityindexarray)[entindex];
					if(realindex == NO_ENTITY_INDEX)
						return true;

					edict_t* pEdict = gd_engfuncs.pfnGetEdictByIndex(realindex);

					entity_state_t** pEntStatePtr = reinterpret_cast<entity_state_t**>(pdestdata) + blockindex;
					(*pEntStatePtr) = &pEdict->state;
				}
				break;
			case EFIELD_EHANDLE:
			case EFIELD_CARRAY_EHANDLE:
				{
					entindex_t entindex = Common::ByteToInt32(pdata);
					if(entindex == NO_ENTITY_INDEX)
						return true;

					entindex_t realindex = (*g_saveRestoreData.pentityindexarray)[entindex];
					if(realindex == NO_ENTITY_INDEX)
						return true;

					edict_t* pEdict = gd_engfuncs.pfnGetEdictByIndex(realindex);

					CEntityHandle* pEntityHandlePtr = reinterpret_cast<CEntityHandle*>(pdestdata) + blockindex;
					(*pEntityHandlePtr) = CBaseEntity::GetClass(pEdict);
				}
				break;
			case EFIELD_TIME:
			case EFIELD_CARRAY_TIME:
				{
					double timeValue = Common::ByteToDouble(pdata);
					if(g_saveRestoreData.transitionsave && timeValue != 0)
						timeValue += g_pGameVars->time;

					Byte* pdest = pdestdata + blockindex * sizeof(double);
					memcpy(pdest, &timeValue, sizeof(double));
				}
				break;
			case EFIELD_FLOAT:
			case EFIELD_CARRAY_FLOAT:
				{
					float floatValue = Common::ByteToFloat(pdata);
					Byte* pdest = pdestdata + blockindex * sizeof(float);
					memcpy(pdest, &floatValue, sizeof(float));
				}
				break;
			case EFIELD_DOUBLE:
			case EFIELD_CARRAY_DOUBLE:
				{
					double doubleValue = Common::ByteToDouble(pdata);
					Byte* pdest = pdestdata + blockindex * sizeof(double);
					memcpy(pdest, &doubleValue, sizeof(double));
				}
				break;
			case EFIELD_INT16:
			case EFIELD_CARRAY_INT16:
				{
					Int16 intValue = Common::ByteToInt16(pdata);
					(*(reinterpret_cast<Int16*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_UINT16:
			case EFIELD_CARRAY_UINT16:
				{
					UInt16 intValue = Common::ByteToUint16(pdata);
					(*(reinterpret_cast<UInt16*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_INT32:
			case EFIELD_CARRAY_INT32:
				{
					Int32 intValue = Common::ByteToInt32(pdata);
					(*(reinterpret_cast<Int32*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_UINT32:
			case EFIELD_CARRAY_UINT32:
				{
					UInt32 intValue = Common::ByteToUint32(pdata);
					(*(reinterpret_cast<UInt32*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_INT64:
			case EFIELD_CARRAY_INT64:
				{
					Int64 intValue = Common::ByteToInt64(pdata);
					(*(reinterpret_cast<Int64*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_UINT64:
			case EFIELD_CARRAY_UINT64:
				{
					UInt64 intValue = Common::ByteToUint64(pdata);
					(*(reinterpret_cast<UInt64*>(pdestdata) + blockindex)) = intValue;
				}
				break;
			case EFIELD_VECTOR:
			case EFIELD_CARRAY_VECTOR:
				{
					Vector vecValue = *reinterpret_cast<const Vector*>(pdata);
					(*(reinterpret_cast<Vector*>(pdestdata) + blockindex)) = vecValue;
				}
				break;
			case EFIELD_COORD:
			case EFIELD_CARRAY_COORD:
				{
					Vector vecValue = *reinterpret_cast<const Vector*>(pdata);
					if(g_saveRestoreData.transitionsave)
						Math::VectorAdd(vecValue, g_saveRestoreData.landmarkOffset, vecValue);

					(*(reinterpret_cast<Vector*>(pdestdata) + blockindex)) = vecValue;
				}
				break;
			case EFIELD_BOOLEAN:
			case EFIELD_CARRAY_BOOLEAN:
				{
					bool boolValue = ((*pdata) == 0) ? false : true;
					(*(reinterpret_cast<bool*>(pdestdata) + blockindex)) = boolValue;
				}
				break;
			case EFIELD_FUNCPTR:
				{
					CString value(reinterpret_cast<const char*>(pdata), datasize);
					void** pfnPtr = reinterpret_cast<void**>(pdestdata);

					if(value.empty())
						(*pfnPtr) = nullptr;
					else
						(*pfnPtr) = gd_engfuncs.pfnFunctionFromName(value.c_str());
				}
				break;
			case EFIELD_MODELNAME:
			case EFIELD_SOUNDNAME:
			case EFIELD_STRING:
			case EFIELD_CARRAY_STRING:
				{
					CString value(reinterpret_cast<const char*>(pdata), datasize);
					string_t& str = (*(reinterpret_cast<string_t*>(pdestdata) + blockindex));
					str = gd_engfuncs.pfnAllocString(value.c_str());
				}
				break;
			case EFIELD_CBITSET:
				{
					// Get destination bitset
					UInt32 bitsetByteCount = SDL_ceil((float)datasize / (float)CBitSet::NB_BITS_IN_BYTE);
					memcpy(pdestdata, pdata, sizeof(Byte)*bitsetByteCount);
				}
				break;
			default:
				gd_engfuncs.pfnCon_EPrintf("%s - Invalid field type %d for keyvalue '%s' for CBaseEntity.\n", __FUNCTION__, field.type, fieldname);
				return false;
			}

			return true;
		}

		m_saveFieldsList.next();
	}

	// Manage any missing fields
	gd_engfuncs.pfnCon_EPrintf("%s - Field '%s' not found in entity class data.\n", __FUNCTION__, fieldname);
	return true;
}

//=============================================
// @brief
//
//=============================================
Vector CBaseEntity::GetBrushModelCenter( void ) const
{
	return m_pState->absmin + m_pState->size * 0.5;
}

//=============================================
// @brief
//
//=============================================
Vector CBaseEntity::GetCenter( void )
{
	const Vector& mins = m_pState->absmin;
	const Vector& maxs = m_pState->absmax;
	return (mins + maxs)*0.5;
}

//=============================================
// @brief
//
//=============================================
Vector CBaseEntity::GetBodyTarget( const Vector& targetingPosition )
{
	return GetCenter();
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::TakeHealth( float amount, Int32 damageFlags )
{
	if(m_pState->takedamage == TAKEDAMAGE_NO)
		return false;

	// Cap at max health
	if(m_pState->health >= m_pState->maxhealth)
		return false;

	m_pState->health += amount;
	if(m_pState->health > m_pState->maxhealth)
		m_pState->health = m_pState->maxhealth;

	return true;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::TakeDamage( CBaseEntity* pInflictor, CBaseEntity* pAttacker, float amount, Int32 damageFlags )
{
	if(!pInflictor || !pAttacker)
		return false;

	if(m_pState->takedamage == TAKEDAMAGE_NO)
		return false;

	// Get the vector from the attacker
	Vector attackdir = pInflictor->GetOrigin() - GetBrushModelCenter();
	Math::VectorNormalize(attackdir);

	// Determine momentum and add it
	if((m_pState->movetype == MOVETYPE_WALK || m_pState->movetype == MOVETYPE_STEP) && pAttacker->GetSolidity() != SOLID_TRIGGER)
	{
		Vector direction = m_pState->origin - (pInflictor->GetAbsMins() + pInflictor->GetAbsMaxs())*0.5;
		Math::VectorNormalize(direction);

		// what is the math behind this actually?
		float force = Util::GetDamageForce(*m_pEdict, amount);

		// Set velocity
		Math::VectorMA(m_pState->velocity, force, direction, m_pState->velocity);
	}

	// Reduct health
	m_pState->health -= amount;
	if(m_pState->health <= 0)
	{
		Killed(pAttacker, GIB_NORMAL);
		return false;
	}

	return true;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::TraceAttack( CBaseEntity* pAttacker, float damage, const Vector& direction, trace_t& tr, Int32 damageFlags )
{
	if(m_pState->takedamage == TAKEDAMAGE_NO)
		return;

	// Add to multi damage
	gMultiDamage.AddDamage(this, damage, damageFlags);

	if(GetBloodColor() != BLOOD_NONE && damage > 0)
	{
		// Offset from impact by 4 units
		Vector bloodOrigin = tr.endpos + direction*-4;

		// Create blood particle spray
		Util::SpawnBloodParticles(tr, GetBloodColor(), IsPlayer());

		// Create decals on walls or other npcs
		SpawnBloodDecals(damage, direction, tr, damageFlags);
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::SpawnBloodDecals( float damage, const Vector& direction, trace_t& tr, Int32 damageFlags )
{
	bloodcolor_t bloodcolor = GetBloodColor();
	if(bloodcolor == BLOOD_NONE || damage <= 0)
		return;

	if(!(damageFlags & DMG_BLOODDECAL))
		return;

	// Based on dmg
	float noise = 0;
	UInt32 numdecals = 0;

	if(damage < 10)
	{
		noise = 0.1;
		numdecals = 1;
	}
	else if(damage < 25)
	{
		noise = 0.2;
		numdecals = 2;
	}
	else
	{
		noise = 0.3;
		numdecals = 4;
	}

	trace_t btr;
	Vector tracedir;

	// Spawn the decals
	for(UInt32 i = 0; i < numdecals; i++)
	{
		Vector endpos;
		Math::VectorScale(direction, -1, tracedir);

		// Calculate endpoint
		for(UInt32 j = 0; j < 3; j++)
			endpos[j] = tr.endpos[j] + (tracedir[j]+Common::RandomFloat(-noise, noise))*(-180);

		// Trace against npcs here
		Util::TraceLine(tr.endpos, endpos, false, true, m_pEdict, btr);
		if(btr.fraction != 1.0)
			Util::SpawnBloodDecal(btr, bloodcolor, true);

		if(btr.fraction == 1.0 || !Util::IsNullEntity(tr.hitentity) && Util::IsVBMEntity(tr.hitentity))
		{
			// Trace against world/brush models only if we hit a vbm entity
			Util::TraceLine(tr.endpos, endpos, false, true, m_pEdict, btr);
			if(btr.fraction != 1.0)
				Util::SpawnBloodDecal(btr, bloodcolor, false);
		}
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::Killed( CBaseEntity* pAttacker, gibbing_t gibbing, deathmode_t deathMode )
{
	m_pState->takedamage = TAKEDAMAGE_NO;
	m_pState->deadstate = DEADSTATE_DEAD;
	Util::RemoveEntity(this);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::InitParenting( void )
{
	if(m_pFields->parent == NO_STRING_VALUE || m_pState->parent != NO_ENTITY_INDEX)
		return;

	edict_t* pparent = Util::FindEntityByTargetName(nullptr, gd_engfuncs.pfnGetString(m_pFields->parent));
	if(!pparent)
	{
		gd_engfuncs.pfnCon_EPrintf("%s - Entity '%s' couldn't find parent '%s'.\n", __FUNCTION__, gd_engfuncs.pfnGetString(m_pFields->targetname), gd_engfuncs.pfnGetString(m_pFields->parent));
		return;
	}

	CBaseEntity* pEntity = CBaseEntity::GetClass(pparent);
	if(!pEntity)
		return;

	// Set parented flag
	m_pState->flags |= FL_PARENTED;
	m_pState->effects |= EF_NOVIS;

	// Set this
	// TODO: Fix parenting somehow
	//m_pState->parentoffset = m_pState->origin - pEntity->GetOrigin();
	m_pState->parent = pEntity->GetEntityIndex();
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::FlagForRemoval( void )
{
	// Disable touch
	SetTouch(nullptr);

	m_pState->solid = SOLID_NOT;
	m_pState->effects |= EF_NODRAW;
	m_pState->modelindex = 0;

	SetThink(&CBaseEntity::RemoveThink);
	m_pState->nextthink = g_pGameVars->time + 0.1;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::IsAlive( void ) const
{
	return (m_pState->deadstate == DEADSTATE_NONE) ? true : false;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::UseTargets( CBaseEntity* pActivator, usemode_t useMode, float value, string_t target )
{
	string_t targetentityname;
	if(target != NO_STRING_VALUE)
		targetentityname = target;
	else
		targetentityname = m_pFields->target;

	if(targetentityname == NO_STRING_VALUE)
		return;

	Util::FireTargets(gd_engfuncs.pfnGetString(targetentityname), pActivator, this, useMode, value);
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::ShouldOverrideKeyValue( const char* pstrKeyValue )
{
	// lightorigin in field declarations is of vector type, 
	// but the data in the entity is string type
	if(!qstrcmp(pstrKeyValue, "lightorigin"))
		return true;
	else
		return false;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::GetUseReticleMinsMaxs( Vector& outMins, Vector& outMaxs, CBaseEntity* pPlayer )
{
	outMins = GetAbsMins();
	outMaxs = GetAbsMaxs();
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CallThink( void ) 
{ 
	if(!m_pfnThinkFunction) 
		return;
		
	(this->*m_pfnThinkFunction)(); 

	// Update this
	UpdateLastThinkTime();
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CallTouch( CBaseEntity* pOther ) 
{ 
	if(!m_pfnTouchFunction)
		return;
		
	(this->*m_pfnTouchFunction)(pOther); 
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CallBlocked( CBaseEntity* pOther ) 
{ 
	if(!m_pfnBlockedFunction)
		return;
		
	(this->*m_pfnBlockedFunction)(pOther); 
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CallUse( CBaseEntity* pActivator, CBaseEntity* pCaller, usemode_t useMode, float value )
{
	if(!m_pfnUseFunction)
		return;

	(this->*m_pfnUseFunction)(pActivator, pCaller, useMode, value);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::ClearThinkFunctions( void )
{
	SetThink(nullptr);
	m_pState->nextthink = 0;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CallUseToggleThink( void )
{
	CallUse(this, this, USE_TOGGLE, 0);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::RemoveThink( void )
{
	if(m_pState->health > 0)
		gd_engfuncs.pfnCon_DPrintf("%s called on entity with health > 0.\n", __FUNCTION__);

	Util::RemoveEntity(this);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::FadeBeginThink( void )
{
	if(m_pState->rendermode == RENDER_NORMAL)
	{
		m_pState->renderamt = 255;
		m_pState->rendermode = RENDER_TRANSTEXTURE_LIT;
	}

	m_pState->solid = SOLID_NOT;
	m_pState->avelocity.Clear();

	m_pState->nextthink = g_pGameVars->time + 0.1;
	SetThink(&CBaseEntity::FadeThink);
}

//=============================================
// @brief
//
//=============================================
CBaseEntity* CBaseEntity::GetNextTarget( void )
{
	if(m_pFields->target == NO_STRING_VALUE)
		return nullptr;

	edict_t* pEdict = Util::FindEntityByTargetName(nullptr, gd_engfuncs.pfnGetString(m_pFields->target));
	if(Util::IsNullEntity(pEdict))
		return nullptr;

	return CBaseEntity::GetClass(pEdict);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::FadeThink( void )
{
	double delta = g_pGameVars->time - m_lastThinkTime;
	m_pState->nextthink = g_pGameVars->time + 0.1;

	float reduction = delta * ENTITY_FADE_SPEED;
	if(m_pState->renderamt > reduction)
	{
		m_pState->renderamt -= reduction;
	}
	else
	{
		m_pState->renderamt = 0;
		SetThink(&CBaseEntity::RemoveThink);
	}
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::SetFallingVelocity( float velocity )
{
	m_pState->fallvelocity = velocity;
}

#ifdef _DEBUG
//=============================================
// @brief
//
//=============================================
void CBaseEntity::CheckFunction( void* pfnptr, const char* pstrFunctionName )
{
	if(!pfnptr || gd_engfuncs.pfnNameForFunction(pfnptr))
		return;

	gd_engfuncs.pfnCon_Printf("Function '%s' is not exported as '_declspec( dllexport )'.\n", pstrFunctionName);
}

//=============================================
// @brief
//
//=============================================
THINKFNPTR CBaseEntity::_SetThink( THINKFNPTR pfnptr, const char* pstrFunctionName )
{
	m_pfnThinkFunction = pfnptr;
	CheckFunction(reinterpret_cast<void*>(*(reinterpret_cast<Int64*>(reinterpret_cast<Byte*>(this) + offsetof(CBaseEntity, m_pfnThinkFunction)))), pstrFunctionName);
	return m_pfnThinkFunction;
}

//=============================================
// @brief
//
//=============================================
INTERACTFNPTR CBaseEntity::_SetTouch( INTERACTFNPTR pfnptr, const char* pstrFunctionName )
{
	m_pfnTouchFunction = pfnptr;
	CheckFunction(reinterpret_cast<void*>(*(reinterpret_cast<Int64*>(reinterpret_cast<Byte*>(this) + offsetof(CBaseEntity, m_pfnTouchFunction)))), pstrFunctionName);
	return m_pfnTouchFunction;
}

//=============================================
// @brief
//
//=============================================
INTERACTFNPTR CBaseEntity::_SetBlocked( INTERACTFNPTR pfnptr, const char* pstrFunctionName )
{
	m_pfnBlockedFunction = pfnptr;
	CheckFunction(reinterpret_cast<void*>(*(reinterpret_cast<Int64*>(reinterpret_cast<Byte*>(this) + offsetof(CBaseEntity, m_pfnBlockedFunction)))), pstrFunctionName);
	return m_pfnBlockedFunction;
}

//=============================================
// @brief
//
//=============================================
USEFNPTR CBaseEntity::_SetUse( USEFNPTR pfnptr, const char* pstrFunctionName )
{
	m_pfnUseFunction = pfnptr;
	CheckFunction(reinterpret_cast<void*>(*(reinterpret_cast<Int64*>(reinterpret_cast<Byte*>(this) + offsetof(CBaseEntity, m_pfnUseFunction)))), pstrFunctionName);
	return m_pfnUseFunction;
}
#endif

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::IsBrushModel( void ) const
{
	if(m_pState->modelindex == 0)
		return false;

	const cache_model_t* pmodel = gd_engfuncs.pfnGetModel(m_pState->modelindex);
	if(!pmodel)
		return false;

	return (pmodel->type == MOD_BRUSH) ? true : false;
}

//=============================================
// @brief Tells if the model we use has an MCD file attached
//
//=============================================
bool CBaseEntity::HasMCDCollisions( void ) const
{
	if(m_pState->modelindex == 0)
		return false;

	const cache_model_t* pmodel = gd_engfuncs.pfnGetModel(m_pState->modelindex);
	if(!pmodel)
		return false;

	return (pmodel->type == MOD_VBM && (pmodel->cacheflags & CACHE_FL_HAS_MCD)) ? true : false;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::CullByVisibilityDistance( const edict_t* pclient ) const
{
	if(!m_visibilityCullDistance)
		return false;

	// Construct our culling bbox
	Vector mins, maxs;
	for(UInt32 i = 0; i < 3; i++)
	{
		mins[i] = m_pState->origin[i] - m_visibilityCullDistance;
		maxs[i] = m_pState->origin[i] + m_visibilityCullDistance;
	}

	// Construct player's bbox
	Vector cmins = pclient->state.origin + pclient->state.mins;
	Vector cmaxs = pclient->state.origin + pclient->state.maxs;
	
	return !Math::CheckMinsMaxs(cmins, cmaxs, mins, maxs);
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::UpdateLastThinkTime( void )
{
	m_lastThinkTime = g_pGameVars->time;
}

//=============================================
// @brief
//
//=============================================
void CBaseEntity::CopyEdictData( CBaseEntity* pSrcEntity )
{
	const edict_t* pSrcEdict = pSrcEntity->GetEdict();
	if(!pSrcEdict)
		return;

	// Copy state data
	m_pEdict->state = pSrcEdict->state;
	// Copy fields data
	m_pEdict->fields = pSrcEdict->fields;
}

//=============================================
// @brief
//
//=============================================
bool CBaseEntity::WalkMove( float yaw, float dist, walkmove_t movemode )
{
	return gd_engfuncs.pfnWalkMove(m_pEdict, yaw, dist, movemode);
}