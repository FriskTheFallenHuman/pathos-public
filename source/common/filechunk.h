/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef FILECHUNK_H
#define FILECHUNK_H

struct filechunk_t
{
	filechunk_t():
		fileid(0),
		chunkindex(0),
		dataoffset(0),
		datasize(0)
		{}

	Int32 fileid;
	UInt32 chunkindex;

	UInt32 dataoffset;
	UInt32 datasize;
};
#endif