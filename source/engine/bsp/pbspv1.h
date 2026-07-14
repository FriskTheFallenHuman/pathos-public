/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef PBSPV1_H
#define PBSPV1_H

//
// Load functions
//
brushmodel_t* PBSPV1_Load( const Byte* pfile, const dpbspv1header_t* pheader, const char* pstrFilename );

//
// Functions for loading specific lumps
//
extern bool PBSPV1_LoadVertexes( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadEdges( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadSurfedges( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadTextures( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadLighting( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadPlanes( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadTexinfo( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadFaces( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadMarksurfaces( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadVisibility( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadLeafs( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadNodes( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadClipnodes( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadEntities( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
extern bool PBSPV1_LoadSubmodels( const Byte* pfile, brushmodel_t& model, const dpbspv1lump_t& lump );
#endif //PBSPV1_H