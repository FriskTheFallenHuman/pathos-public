/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef PBSPV2_H
#define PBSPV2_H

//
// Load functions
//
brushmodel_t* PBSPV2_Load( const Byte* pfile, const dpbspv2header_t* pheader, const char* pstrFilename );

//
// Functions for loading specific lumps
//
extern bool PBSPV2_LoadVertexes( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadEdges( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadSurfedges( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadTextures( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadDefaultLighting( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadLightingDataLayer( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump, surf_lmap_layers_t layer );
extern bool PBSPV2_LoadPlanes( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadTexinfo( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadFaces( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadMarksurfaces( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadVisibility( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadLeafs( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadNodes( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadClipnodes( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadEntities( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadSubmodels( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump );
extern bool PBSPV2_LoadVertexLighting( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump, baked_vertexlight_layers_t layer );
extern bool PBSPV2_DecompressLightingData( const Byte* pfile, brushmodel_t& model, const dpbspv2lump_t& lump, color24_t*& pdestptr, UInt32& destsize, Byte*& poriginaldataptr, UInt32& originalsize, Int32& compression, Int32 compressionlevel );
#endif //PBSPV2_H