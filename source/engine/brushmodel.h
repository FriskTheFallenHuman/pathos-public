/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef BRUSHMODEL_H
#define BRUSHMODEL_H

#include "brushmodel_shared.h"

//
// Functions dealing with bsp data
//
extern const mleaf_t* Mod_PointInLeaf( const Vector& position, const brushmodel_t& model );
extern Byte* Mod_DecompressVIS( Byte* pbuffer, Byte* pin, const brushmodel_t& model, UInt32 bytecount );
extern const Byte* Mod_LeafPVS( Byte* pbuffer, UInt32 bufsize, const mleaf_t& leaf, const brushmodel_t& model );
extern const Byte* Mod_LeafPAS( Byte* pbuffer, UInt32 bufsize, const mleaf_t& leaf, const brushmodel_t& model );
extern Byte* Mod_CompressVIS( const Byte* pin, UInt32* psize, const brushmodel_t& model, Int32 visbuffersize );
extern const msurface_t* Mod_SurfaceAtPoint( const brushmodel_t* pmodel, const mnode_t* pnode, const Vector& start, const Vector& end );
extern void Mod_FindTouchedLeafs( const brushmodel_t* pworld, CArray<UInt32>& leafnumsarray, UInt32& leafcount, const Vector& mins, const Vector& maxs, mnode_t* pnode );
extern bool Mod_RecursiveLightPoint( const brushmodel_t* pworld, mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutcolors, Byte* poutstyles = nullptr );
extern bool Mod_RecursiveLightPoint_BumpData( const brushmodel_t* pworld, mnode_t *pnode, const Vector &start, const Vector &end, Vector* poutambientcolors, Vector* poutdiffusecolors, Vector* poutlightdirs, Vector* poutsurfnormal, Byte* poutstyles = nullptr );
extern Int32 Mod_StyleIndex ( const msurface_t *psurface, UInt32 style );
#endif //BMODEL_H