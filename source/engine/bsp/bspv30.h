/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef BSPV30_H
#define BSPV30_H

//
// BSP version
//
static constexpr UInt32 BSPV30_VERSION = 30;

//
// Load functions
//
brushmodel_t* BSPV30_Load( const Byte* pfile, const dv30header_t* pheader, const char* pstrFilename );

//
// Functions for loading specific lumps
//
extern bool BSPV30_LoadVertexes( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadEdges( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadSurfedges( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadTextures( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadLighting( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadPlanes( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadTexinfo( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadFaces( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadMarksurfaces( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadVisibility( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadLeafs( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadNodes( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadClipnodes( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadEntities( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
extern bool BSPV30_LoadSubmodels( const Byte* pfile, brushmodel_t& model, const dv30lump_t& lump );
#endif //BSPV30_H