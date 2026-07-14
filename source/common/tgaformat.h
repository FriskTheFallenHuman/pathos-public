/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

#ifndef TGAFORMAT_H
#define TGAFORMAT_H

enum tga_datatype_t
{
	TGA_DATATYPE_EMPTY = 0,
	TGA_DATATYPE_COLORMAPPED,
	TGA_DATATYPE_RGB,
	TGA_DATATYPE_GRAYSCALE,
	TGA_DATATYPE_RLE_COLORMAPPED = 9,
	TGA_DATATYPE_RLE_RGB,
	TGA_DATATYPE_RLE_GRAYSCALE
};

struct tga_header_t
{
	Byte	idlength;
	Byte	colourmaptype;
	Byte	datatypecode;
	Byte	colourmaporigin[2]; //how come you have short ints there?
	Byte	colourmaplength[2];
	Byte	colourmapdepth;
	Byte	x_origin[2];
	Byte	y_origin[2];
	Byte	width[2];
	Byte	height[2];
	Byte	bitsperpixel;
	Byte	imagedescriptor;
};
#endif //TGAFORMAT_H