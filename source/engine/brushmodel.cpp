/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "com_math.h"
#include "textures_shared.h"
#include "brushmodel.h"
#include "frustum.h"
#include "system.h"
#include "r_common.h"
#include "r_lightstyles.h"

//=============================================
// @brief
//
//=============================================
const mleaf_t* Mod_PointInLeaf( const Vector& position, const brushmodel_t& model )
{
	if(!model.pnodes)
		return nullptr;

	mnode_t* pnode = model.pnodes;
	while(true)
	{
		if(pnode->contents < 0)
			return reinterpret_cast<mleaf_t*>(pnode);

		plane_t* pplane = pnode->pplane;
		float dp = Math::DotProduct(position, pplane->normal) - pplane->dist;
		if(dp > 0)
			pnode = pnode->pchildren[0];
		else
			pnode = pnode->pchildren[1];
	}

	return nullptr;
}

//=============================================
// @brief
//
//=============================================
Byte* Mod_DecompressVIS( Byte* pbuffer, UInt32 bufsize, Byte* pin, const brushmodel_t& model, UInt32 bytecount )
{
	Byte* pout = pbuffer;
	Byte *ppin = pin;

	if(!ppin)
	{
		// Make all visible if there's no vis info
		for(UInt32 i = 0; i < bytecount; i++)
		{
			(*pout) = 0xFF;
			pout++;

			if((pout-pbuffer) >= bufsize)
			{
				Con_EPrintf("VIS buffer overflow.\n");
				return pbuffer;
			}
		}

		return pbuffer;
	}

	// Mark visible visleafs
	while(pout < pbuffer + bytecount)
	{
		if(ppin - model.pvisdata >= model.visdatasize)
			break;

		if(*ppin)
		{
			(*pout) = (*ppin);
			pout++; ppin++;

			if((pout - pbuffer) >= bufsize)
			{
				Con_EPrintf("VIS buffer overflow.\n");
				return pbuffer;
			}

			continue;
		}

		UInt32 count = ppin[1];
		ppin += 2;

		if(count > pbuffer + bytecount - pout)
			count = pbuffer + bytecount - pout;

		memset(pout, 0, sizeof(Byte)*count);
		pout += count;

		if((pout - pbuffer) >= bufsize)
		{
			Con_EPrintf("VIS buffer overflow.\n");
			return pbuffer;
		}
	}

	return pbuffer;
}

//=============================================
// @brief
//
//=============================================
Byte* Mod_DecompressPAS( Byte* pbuffer, UInt32 bufsize, Byte* pin, const brushmodel_t& model, UInt32 bytecount )
{
	Byte* pout = pbuffer;
	Byte *ppin = pin;

	if(!ppin)
	{
		// Make all visible if there's no vis info
		for(UInt32 i = 0; i < bytecount; i++)
		{
			(*pout) = 0xFF;
			pout++;

			if((pout-pbuffer) >= bufsize)
			{
				Con_EPrintf("VIS buffer overflow.\n");
				return pbuffer;
			}
		}

		return pbuffer;
	}

	// Mark visible visleafs
	while(pout < pbuffer + bytecount)
	{
		if(ppin - model.ppasdata >= model.pasdatasize)
			break;

		if(*ppin)
		{
			(*pout) = (*ppin);
			pout++; ppin++;

			if((pout - pbuffer) >= bufsize)
			{
				Con_EPrintf("VIS buffer overflow.\n");
				return pbuffer;
			}

			continue;
		}

		UInt32 count = ppin[1];
		ppin += 2;

		if(count > pbuffer + bytecount - pout)
			count = pbuffer + bytecount - pout;

		memset(pout, 0, sizeof(Byte)*count);
		pout += count;

		if((pout - pbuffer) >= bufsize)
		{
			Con_EPrintf("VIS buffer overflow.\n");
			return pbuffer;
		}
	}

	return pbuffer;
}

//=============================================
// @brief
//
//=============================================
const Byte* Mod_LeafPVS( Byte* pbuffer, UInt32 bufsize, const mleaf_t& leaf, const brushmodel_t& model )
{
	UInt32 bytecount = (model.numleafs + 7) >> 3;
	if(&leaf == model.pleafs)
		return Mod_DecompressVIS(pbuffer, bufsize, nullptr, model, bytecount);
	else
		return Mod_DecompressVIS(pbuffer, bufsize, leaf.pcompressedvis, model, bytecount);
}

//=============================================
// @brief
//
//=============================================
const Byte* Mod_LeafPAS( Byte* pbuffer, UInt32 bufsize, const mleaf_t& leaf, const brushmodel_t& model )
{
	UInt32 bytecount = (model.numleafs + 7) / 8;
	if(&leaf == model.pleafs)
		return Mod_DecompressPAS(pbuffer, bufsize, nullptr, model, bytecount);
	else
		return Mod_DecompressPAS(pbuffer, bufsize, leaf.pcompressedpas, model, bytecount);
}

//=============================================
// @brief
//
//=============================================
Byte* Mod_CompressVIS( const Byte* pin, UInt32* psize, const brushmodel_t& model, Int32 visbuffersize )
{
	Int32 rownum = (model.numleafs+7)>>3;
	Byte* pvisdata = new Byte[visbuffersize];
	Byte* pdest = pvisdata;

	for(Int32 j = 0; j < rownum; j++)
	{
		*pdest = pin[j];
		pdest++;

		if(pin[j])
			continue;

		Int32 rep = 1;
		for(j++; j < rownum; j++)
		{
			if(pin[j] || rep == 255)
				break;
			else
				rep++;
		}
		
		*pdest = rep;
		pdest++;

		j--;
	}

	if(psize)
		(*psize) = pdest - pvisdata;

	return pvisdata;
}

//=============================================
// @brief
//
//=============================================
const msurface_t* Mod_SurfaceAtPoint( const brushmodel_t* pmodel, const mnode_t* pnode, const Vector& start, const Vector& end )
{
	if(pnode->contents < 0)
		return nullptr;

	plane_t* pplane = pnode->pplane;
	float front = Math::DotProduct(start, pplane->normal) - pplane->dist;
	float back = Math::DotProduct(end, pplane->normal) - pplane->dist;

	bool s = (front < 0.0f) ? true : false;
	bool t = (back < 0.0f) ? true : false;

	if(t == s)
		return Mod_SurfaceAtPoint(pmodel, pnode->pchildren[s], start, end);

	Vector mid, point;
	float frac = front / (front - back);
	Math::VectorSubtract(end, start, point);
	Math::VectorMA(start, frac, point, mid);

	const msurface_t* psurface = Mod_SurfaceAtPoint(pmodel, pnode->pchildren[s], start, mid);
	if(psurface)
		return psurface;

	for(UInt32 i = 0; i < pnode->numsurfaces; i++)
	{
		psurface = &pmodel->psurfaces[pnode->firstsurface + i];
		mtexinfo_t *ptexinfo = psurface->ptexinfo;

		Int32 ds = static_cast<Int32>(Math::DotProduct(mid, ptexinfo->vecs[0]) + ptexinfo->vecs[0][3]);
		Int32 dt = static_cast<Int32>(Math::DotProduct(mid, ptexinfo->vecs[1]) + ptexinfo->vecs[1][3]);

		if(ds >= psurface->texturemins[0] && dt >= psurface->texturemins[1])
		{
			if((ds - psurface->texturemins[0]) <= psurface->extents[0] &&
				(dt - psurface->texturemins[1]) <= psurface->extents[1])
				return psurface;
		}
	}

	return Mod_SurfaceAtPoint(pmodel, pnode->pchildren[s ^ 1], mid, end);
}

//=============================================
//
//=============================================
void Mod_FindTouchedLeafs( const brushmodel_t* pworld, CArray<UInt32>& leafnumsarray, UInt32& leafcount, const Vector& mins, const Vector& maxs, mnode_t* pnode )
{
	if(pnode->contents == CONTENTS_SOLID)
		return;

	if(pnode->contents < 0)
	{
		mleaf_t* pleaf = reinterpret_cast<mleaf_t*>(pnode);
		UInt32 leafnum = pleaf - pworld->pleafs - 1;

		if(leafnumsarray.size() <= leafcount)
			leafnumsarray.resize(leafnumsarray.size() + LEAFNUM_ALLOC_COUNT);

		leafnumsarray[leafcount] = leafnum;
		leafcount++;
		return;
	}

	plane_t* pplane = pnode->pplane;
	Int32 sides = BoxOnPlaneSide(mins, maxs, pplane);

	// Recurse down the sides
	if(sides & 1)
		Mod_FindTouchedLeafs(pworld, leafnumsarray, leafcount, mins, maxs, pnode->pchildren[0]);

	if(sides & 2)
		Mod_FindTouchedLeafs(pworld, leafnumsarray, leafcount, mins, maxs, pnode->pchildren[1]);
}

//=============================================
//
//=============================================
bool Mod_RecursiveLightPoint( const brushmodel_t* pworld, mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutcolors, Byte* poutstyles )
{
	if (pnode->contents < 0)
		return false;
	
	plane_t* pplane = pnode->pplane;
	float front = Math::DotProduct (start, pplane->normal) - pplane->dist;
	float back = Math::DotProduct (end, pplane->normal) - pplane->dist;
	Int32 side = front < 0;
	
	if ( (back < 0) == side )
		return Mod_RecursiveLightPoint(pworld, pnode->pchildren[side], start, end, poutcolors, poutstyles);
	
	Vector mid;
	float frac = front / (front-back);
	mid[0] = start[0] + (end[0] - start[0])*frac;
	mid[1] = start[1] + (end[1] - start[1])*frac;
	mid[2] = start[2] + (end[2] - start[2])*frac;
	
	// go down front side	
	if (Mod_RecursiveLightPoint(pworld, pnode->pchildren[side], start, mid, poutcolors, poutstyles)) 
		return true;
		
	if ((back < 0) == side)
		return true;

	msurface_t* psurfaces = pworld->psurfaces + pnode->firstsurface;
	for (UInt32 i = 0; i < pnode->numsurfaces; i++)
	{
		msurface_t* psurf = &psurfaces[i];
		if (psurf->flags & (SURF_DRAWTURB | SURF_DRAWSKY) || !psurf->psamples)
			continue;	// no lightmaps

		mtexinfo_t* ptexinfo = psurf->ptexinfo;
		Int32 s = Math::DotProduct(mid, ptexinfo->vecs[0])+ptexinfo->vecs[0][3];
		Int32 t = Math::DotProduct(mid, ptexinfo->vecs[1])+ptexinfo->vecs[1][3];

		if (s < psurf->base_texturemins[0] || t < psurf->base_texturemins[1])
			continue;
		
		Int32 ds = s - psurf->base_texturemins[0];
		Int32 dt = t - psurf->base_texturemins[1];
		
		if (ds > psurf->base_extents[0] || dt > psurf->base_extents[1])
			continue;

		ds = ds / psurf->base_samplesize;
		dt = dt / psurf->base_samplesize;

		color24_t* plightmap = psurf->psamples[SURF_LIGHTMAP_DEFAULT];
		plightmap += dt * ((psurf->base_extents[0] / psurf->base_samplesize)+1) + ds;

		float flIntensity = (plightmap->r + plightmap->g + plightmap->b)/3;
		float flScale = flIntensity/35;

		if(flScale > 1.0) 
			flScale = 1.0;

		Vector color;
		Common::ParseColor(color, plightmap);
		Math::VectorScale(color, flScale, poutcolors[BASE_LIGHTMAP_INDEX]);

		// Check styles
		if(poutstyles)
		{
			UInt32 xsize = (psurf->base_extents[0] / psurf->base_samplesize) + 1;
			UInt32 ysize = (psurf->base_extents[1] / psurf->base_samplesize) + 1;
			UInt32 size = xsize*ysize;

			for(UInt32 k = 1; k < MAX_SURFACE_STYLES; k++)
			{
				if(psurf->styles[k] == NULL_LIGHTSTYLE_INDEX)
					break;

				// Skip to next lightmap
				plightmap += size;

				// Parse it into the approrpiate position
				Common::ParseColor(poutcolors[k], plightmap);
			}
		}

		// See if we need to set destination styles
		if(poutstyles)
		{
			for(UInt32 k = 0; k < MAX_SURFACE_STYLES; k++)
				poutstyles[k] = psurf->styles[k];
		}

		return true;
	}

	// go down back side
	return Mod_RecursiveLightPoint(pworld, pnode->pchildren[!side], mid, end, poutcolors, poutstyles);
}

//=============================================
//
//=============================================
bool Mod_RecursiveLightPoint_BumpData( const brushmodel_t* pworld, mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutambientcolors, Vector* poutdiffusecolors, Vector* poutlightdirs, Vector* poutsurfnormal, Byte* poutstyles )
{
	if (pnode->contents < 0)
		return false;
	
	plane_t* pplane = pnode->pplane;
	float front = Math::DotProduct (start, pplane->normal) - pplane->dist;
	float back = Math::DotProduct (end, pplane->normal) - pplane->dist;
	Int32 side = front < 0;
	
	if ( (back < 0) == side )
		return Mod_RecursiveLightPoint_BumpData(pworld, pnode->pchildren[side], start, end, poutambientcolors, poutdiffusecolors, poutlightdirs, poutsurfnormal, poutstyles);
	
	Vector mid;
	float frac = front / (front-back);
	mid[0] = start[0] + (end[0] - start[0])*frac;
	mid[1] = start[1] + (end[1] - start[1])*frac;
	mid[2] = start[2] + (end[2] - start[2])*frac;
	
	// go down front side	
	if (Mod_RecursiveLightPoint_BumpData(pworld, pnode->pchildren[side], start, mid, poutambientcolors, poutdiffusecolors, poutlightdirs, poutsurfnormal, poutstyles)) 
		return true;
		
	if ((back < 0) == side)
		return true;

	msurface_t* psurfaces = pworld->psurfaces + pnode->firstsurface;
	for (UInt32 i = 0; i < pnode->numsurfaces; i++)
	{
		msurface_t* psurf = &psurfaces[i];
		if (psurf->flags & (SURF_DRAWTURB | SURF_DRAWSKY))
			continue;	// no lightmaps

		mtexinfo_t* ptexinfo = psurf->ptexinfo;
		Int32 s = Math::DotProduct(mid, ptexinfo->vecs[0])+ptexinfo->vecs[0][3];
		Int32 t = Math::DotProduct(mid, ptexinfo->vecs[1])+ptexinfo->vecs[1][3];

		if (s < psurf->base_texturemins[0] || t < psurf->base_texturemins[1])
			continue;
		
		Int32 ds = s - psurf->base_texturemins[0];
		Int32 dt = t - psurf->base_texturemins[1];
		
		if (ds > psurf->base_extents[0] || dt > psurf->base_extents[1])
			continue;

		if (!psurf->psamples)
			continue;

		ds = ds / psurf->base_samplesize;
		dt = dt / psurf->base_samplesize;

		// Fail if the surface has no bump data
		if(!psurf->psamples[SURF_LIGHTMAP_AMBIENT] 
			|| !psurf->psamples[SURF_LIGHTMAP_DIFFUSE]
			|| !psurf->psamples[SURF_LIGHTMAP_VECTORS])
			return false;

		UInt32 xsize = (psurf->base_extents[0] / psurf->base_samplesize)+1;
		UInt32 ysize = (psurf->base_extents[1] / psurf->base_samplesize)+1;
		UInt32 size = xsize*ysize;

		// Use base lighting as reference for overdarkening
		color24_t* pbaselightmap = psurf->psamples[SURF_LIGHTMAP_DEFAULT];
		pbaselightmap += dt * xsize + ds;

		float flIntensity = (pbaselightmap->r + pbaselightmap->g + pbaselightmap->b)/3;
		float flScale = flIntensity/35;
		if(flScale > 1.0)
			flScale = 1.0;

		// Now process along with styles
		for(UInt32 j = 0; j < MAX_SURFACE_STYLES; j++)
		{
			if(psurf->styles[j] == NULL_LIGHTSTYLE_INDEX)
				break;

			float styleScale;
			if(j == BASE_LIGHTMAP_INDEX)
			{
				// Only overdarkening is applied to base lightmap
				styleScale = flScale;
			}
			else
			{
				// If not checking styles, skip additional style layers
				if(!poutstyles)
					break;

				// Only apply lightstyle value scaling to other styles,
				// no ovedarkening
				styleScale = 1.0;
			}

			// Get light direction
			color24_t* plightdirdata = psurf->psamples[SURF_LIGHTMAP_VECTORS] + size * j;
			plightdirdata += dt * xsize + ds;

			Vector tangent;
			Math::VectorCopy(ptexinfo->vecs[0], tangent);
			Math::VectorNormalize(tangent);

			Vector binormal;
			Math::VectorCopy(ptexinfo->vecs[1], binormal);
			Math::VectorNormalize(binormal);

			Vector normal;
			Math::VectorCopy(psurf->pplane->normal, normal);
			if(psurf->flags & SURF_PLANEBACK)
				Math::VectorScale(normal, -1, normal);

			// Turn byte data to light vectors
			Vector tmp;
			Common::ParseVectorColor(tmp, plightdirdata);

			// Note: Trying to get this to work right, I ended up doing what Paranoia does here
			Math::VectorScale(tangent, (tmp[0]*2-1), poutlightdirs[j]);
			Math::VectorMA(poutlightdirs[j], (tmp[1]*2-1), binormal, poutlightdirs[j]);
			Math::VectorMA(poutlightdirs[j], (tmp[2]*2-1), normal, poutlightdirs[j]);

			// Get ambient light
			color24_t* pambientlightmap = psurf->psamples[SURF_LIGHTMAP_AMBIENT] + size * j;
			pambientlightmap += dt * xsize + ds;

			Vector ambientcolor;
			Common::ParseColor(ambientcolor, pambientlightmap);
			Math::VectorScale(ambientcolor, styleScale, ambientcolor);

			// Get diffuse light
			color24_t* pdiffuselightmap = psurf->psamples[SURF_LIGHTMAP_DIFFUSE] + size * j;
			pdiffuselightmap += dt * xsize + ds;

			Vector diffusecolor;
			Common::ParseColor(diffusecolor, pdiffuselightmap);
			Math::VectorScale(diffusecolor, styleScale, diffusecolor);

			// Note: Trying to get this to work right, I ended up doing what Paranoia does here
			// Still looks like shit though in 60% of cases
			Vector scale;
			float dp = tmp[2] * 2 - 1;
			Math::VectorScale(diffusecolor, dp, scale);
			Math::VectorAdd(scale, ambientcolor, scale);
			Math::VectorScale(scale, 2.0, scale);// ???

			for(UInt32 k = 0; k < 3; k++)
				poutdiffusecolors[j][k] = diffusecolor[k] * scale[k];

			for(UInt32 k = 0; k < 3; k++)
				poutambientcolors[j][k] = ambientcolor[k] * scale[k];
		}

		// See if we need to set destination styles
		if(poutstyles)
		{
			for(UInt32 k = 0; k < MAX_SURFACE_STYLES; k++)
				poutstyles[k] = psurf->styles[k];
		}

		// Set normal if specified
		if(poutsurfnormal)
		{
			Math::VectorCopy(psurf->pplane->normal, (*poutsurfnormal));
			if(psurf->flags & SURF_PLANEBACK)
				Math::VectorScale((*poutsurfnormal), -1, (*poutsurfnormal));
		}

		return true;
	}

	// go down back side
	return Mod_RecursiveLightPoint_BumpData(pworld, pnode->pchildren[!side], mid, end, poutambientcolors, poutdiffusecolors, poutlightdirs, poutsurfnormal, poutstyles);
}

//=============================================
//
//=============================================
Int32 Mod_StyleIndex ( const msurface_t *psurface, UInt32 style )
{
	for (UInt32 j = 0 ; j < MAX_SURFACE_STYLES && psurface->styles[j] != NULL_LIGHTSTYLE_INDEX ; j++)
	{
		if (psurface->styles[j] == style)
			return j;
	}

	return NO_POSITION;
}