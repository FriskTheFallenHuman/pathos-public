/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#include "includes.h"
#include "sprite.h"
#include "system.h"

//=============================================
// @brief
//
//=============================================
mspriteframe_t* Sprite_LoadFrame( const dspriteframe_t* pdframe, const Byte* pdata )
{
	mspriteframe_t* pframe = new mspriteframe_t();
			
	pframe->width = pdframe->width;
	pframe->height = pdframe->height;
	pframe->up = pdframe->originy;
	pframe->left = pdframe->originx;
	pframe->down = pdframe->originy - pframe->height;
	pframe->right = pframe->width + pdframe->originx;

	Byte* ptexturedata = new Byte[pframe->width*pframe->height];
	const Byte* pdatasrc = pdata + sizeof(dspriteframe_t);
	memcpy(ptexturedata, pdatasrc, sizeof(Byte)*pframe->width*pframe->height);
	pframe->pdata = ptexturedata;

	return pframe;
}

//=============================================
// @brief
//
//=============================================
msprite_t* Sprite_Load( const Byte* pfile, UInt32 filesize )
{
	const dsprite_t* pheader = reinterpret_cast<const dsprite_t*>(pfile);
	if(pheader->id != IDSPRITEHEADER)
	{
		Con_Printf("%s - Wrong header id for sprite.\n", __FUNCTION__);
		return nullptr;
	}

	if(pheader->version != SPRITE_VERSION)
	{
		Con_Printf("%s - Wrong version for sprite.\n", __FUNCTION__);
		return nullptr;
	}

	// Create header
	msprite_t* psprite = new msprite_t();
	psprite->type = pheader->type;
	psprite->format = pheader->format;
	psprite->maxwidth = pheader->maxwidth;
	psprite->maxheight = pheader->maxheight;
	psprite->radius = pheader->boundingradius;
	psprite->beamlength = pheader->beamlength;
	psprite->synctype = pheader->synctype;
	const Byte* pdata = pfile + sizeof(dsprite_t);

	// Retreive palette size and allocate data
	UInt32 palettesize = Common::ByteToUint16(pfile+sizeof(dsprite_t));
	pdata += sizeof(UInt16);

	// Copy palette data
	psprite->palette = new Byte[palettesize*sizeof(color24_t)];
	const Byte* ppalettedata = pfile+sizeof(dsprite_t)+sizeof(UInt16);
	memcpy(psprite->palette, ppalettedata, sizeof(color24_t)*palettesize);
	pdata += palettesize*sizeof(color24_t);

	// Retreive list of frames
	psprite->frames.resize(pheader->numframes);
	for(UInt32 i = 0; i < pheader->numframes; i++)
	{
		mspriteframedesc_t* pframedesc = &psprite->frames[i];
		pframedesc->type = static_cast<spr_frametype_t>(Common::ByteToUint32(pdata));
		pdata += sizeof(UInt32);

		if(pframedesc->type == SPR_SINGLE)
		{
			const dspriteframe_t* pframedata = reinterpret_cast<const dspriteframe_t*>(pdata);
			mspriteframe_t* pframe = Sprite_LoadFrame(pframedata, pdata);
			pframedesc->pframeptr = pframe;

			UInt32 texturedatasize = pframe->width*pframe->height;
			pdata += sizeof(dspriteframe_t)+sizeof(Byte)*texturedatasize;
		}
		else if(pframedesc->type == SPR_GROUP)
		{
			UInt32 numgroupframes = Common::ByteToUint32(pdata);
			pdata += sizeof(UInt32);

			mspritegroup_t* pgroup = new mspritegroup_t();
			pframedesc->pgroupptr = pgroup;

			pgroup->intervals.resize(numgroupframes);

			const float* pintervals = reinterpret_cast<const float*>(pdata);
			pdata += sizeof(float)*numgroupframes;

			for(UInt32 j = 0; j < numgroupframes; j++)
			{
				// Set interval value
				pgroup->intervals[j] = pintervals[j];
				if(pgroup->intervals[j] <= 0)
					pgroup->intervals[j] = 1;

				const dspriteframe_t* pframedata = reinterpret_cast<const dspriteframe_t*>(pdata);
				mspriteframe_t* pframe = Sprite_LoadFrame(pframedata, pdata);
				pgroup->frames.push_back(pframe);

				UInt32 texturedatasize = pframe->width*pframe->height;
				pdata += sizeof(dspriteframe_t)+sizeof(Byte)*texturedatasize;
			}
		}
		else
		{
			// Error case
			Con_Printf("%s - Invalid sprite frametype %d.\n", __FUNCTION__, static_cast<Int32>(pframedesc->type));
			delete psprite;
			return nullptr;
		}
	}

	return psprite;
}

//====================================
//
//====================================
const mspriteframe_t* Sprite_GetFrame( const msprite_t* psprite, UInt32 frame, float time )
{
	if(frame >= psprite->frames.size())
	{
		Con_Printf ("%s - No such frame %d\n", __FUNCTION__, frame);
		frame = 0;
	}

	const mspriteframe_t *pspriteframe;
	if (psprite->frames[frame].type == SPR_SINGLE)
	{
		pspriteframe = psprite->frames[frame].pframeptr;
	}
	else
	{
		mspritegroup_t* pspritegroup = psprite->frames[frame].pgroupptr;
		UInt32 numframes = pspritegroup->frames.size();
		float fullinterval = pspritegroup->intervals[numframes-1];

		// when loading in Mod_LoadSpriteGroup, we guaranteed all interval values
		// are positive, so we don't have to worry about division by 0
		float targettime = time - (static_cast<Int32>(time / fullinterval)) * fullinterval;

		UInt32 i = 0;
		for(; i < (numframes-1); i++)
		{
			if (pspritegroup->intervals[i] > targettime)
				break;
		}

		pspriteframe = pspritegroup->frames[i];
	}

	return pspriteframe;
}
