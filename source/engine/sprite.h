/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef SPRITE_H
#define SPRITE_H

#include "sprformat.h"

// Loads a sprite
extern msprite_t* Sprite_Load( const Byte* pfile, UInt32 filesize );
extern const mspriteframe_t* Sprite_GetFrame( const msprite_t* psprite, UInt32 frame, float time );
#endif //SPRITE_H