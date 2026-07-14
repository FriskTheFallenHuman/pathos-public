/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef DLLEXPORTS_H
#define DLLEXPORTS_H

struct sectionheader_t
{
	sectionheader_t():
		VirtualSize(0),
		VirtualAddress(0),
		SizeOfRawData(0),
		PointerToRawData(0),
		PointerToRelocations(0),
		PointerToLineNumbers(0),
		NumberOfRelocations(0),
		NumberOfLineNumbers(0),
		Characteristics(0)
		{
			memset(Name, 0, sizeof(Name));
		}

	Byte Name[8];
	UInt32 VirtualSize;
	UInt32 VirtualAddress;
	UInt32 SizeOfRawData;
	UInt32 PointerToRawData;
	UInt32 PointerToRelocations;
	UInt32 PointerToLineNumbers;
	UInt16 NumberOfRelocations;
	UInt16 NumberOfLineNumbers;
	UInt32 Characteristics;
};

bool EnumExportedFunctions ( const char *szFilename, void (*pfnCallBack)(char*) );
#endif //DLLEXPORTS_H