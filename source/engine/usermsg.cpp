/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.

===============================================
*/

#include "includes.h"
#include "usermsg.h"
#include "enginestate.h"
#include "system.h"
#include "networking.h"

//=============================================
//
//=============================================
Int32 UserMSG_RegisterUserMessage( CArray<usermsg_t>& usermsgarray, const char* pstrMsgName, Int32 msgsize )
{
	// Make sure it's not called on an active game
	if(ens.gamestate == GAME_RUNNING)
	{
		Con_Printf("%s - This function can only be called during game library load.\n", __FUNCTION__);
		return 0;
	}

	// See if it's already registered
	for(UInt32 i = 0; i < usermsgarray.size(); i++)
	{
		if(!qstrcmp(usermsgarray[i].name, pstrMsgName))
		{
			Con_Printf("%s - User message %s already registered.\n", __FUNCTION__, pstrMsgName);
			return i+1;
		}
	}

	// Index we're adding in at
	Int32 addindex = usermsgarray.size();

	// Create the new user message
	usermsg_t newmsg;
	newmsg.name = pstrMsgName;
	newmsg.bufsize = msgsize;
	newmsg.id = addindex+1;

	// Add it to the list and give back the id
	usermsgarray.push_back(newmsg);
	return addindex+1;
}

//=============================================
//
//=============================================
void UserMSG_UserMessageBegin( CArray<usermsg_t>& usermsgarray, usermsgdata_t& msgdata, msgdest_t dest, Int32 msgid, const Vector* porigin, const edict_t* pedict )
{
	// Make sure the message is valid
	if(msgid <= 0 || msgid > static_cast<Int32>(usermsgarray.size()))
	{
		Con_EPrintf("%s - Bogus message id %d.\n", __FUNCTION__, msgid);
		return;
	}

	// Get message index
	Int32 msgidx = msgid - 1;
	usermsg_t& msg = usermsgarray[msgidx];

	msgdata.pusermsg = &msg;
	msgdata.pedict = pedict;
	msgdata.destination = dest;
	msgdata.msgsize = 0;

	if(porigin)
	{
		msgdata.pvsorigin = (*porigin);
		msgdata.originset = true;
	}
	else
	{
		// Origin was not set
		msgdata.originset = false;
	}
}

//=============================================
//
//=============================================
void UserMSG_Msg_CheckBuffer( usermsgdata_t& msgdata, UInt32 size )
{
	UInt32 finalSize = msgdata.msgsize + size;
	if(finalSize < msgdata.bufsize)
		return;

	// Determine alloc size needed
	Int32 multiplier = 1;
	UInt32 memNeeded = finalSize - (msgdata.bufsize - msgdata.msgsize);
	if(memNeeded > USERMSG_ALLOC_SIZE)
	{
		float nbTimes = (static_cast<float>(memNeeded)/ static_cast<float>(USERMSG_ALLOC_SIZE));
		multiplier = static_cast<Int32>(SDL_ceil(nbTimes));
	}

	// Resize the message data buffer
	void* pnewbuffer = Common::ResizeArray(msgdata.pmsgbuffer, sizeof(Byte), msgdata.bufsize, USERMSG_ALLOC_SIZE*multiplier);
	msgdata.pmsgbuffer = static_cast<Byte*>(pnewbuffer);
	msgdata.bufsize = msgdata.bufsize + USERMSG_ALLOC_SIZE*multiplier;
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteByte( usermsgdata_t& msgdata, Byte value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(Byte));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	*pdata = value;
	msgdata.msgsize += sizeof(Byte);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteChar( usermsgdata_t& msgdata, char value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(value));

	char* pdata = reinterpret_cast<char*>(msgdata.pmsgbuffer)
		+ msgdata.msgsize;

	*pdata = value;
	msgdata.msgsize += sizeof(Byte);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteInt16( usermsgdata_t& msgdata, Int16 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(Int16));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(Int16));
	msgdata.msgsize += sizeof(Int16);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteUint16( usermsgdata_t& msgdata, UInt16 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(UInt16));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(UInt16));
	msgdata.msgsize += sizeof(UInt16);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteInt32( usermsgdata_t& msgdata, Int32 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(Int32));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(Int32));
	msgdata.msgsize += sizeof(Int32);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteUint32( usermsgdata_t& msgdata, UInt32 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(UInt32));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(UInt32));
	msgdata.msgsize += sizeof(UInt32);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteInt64( usermsgdata_t& msgdata, Int64 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(Int64));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(Int64));
	msgdata.msgsize += sizeof(Int64);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteUint64( usermsgdata_t& msgdata, UInt64 value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(UInt64));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(UInt64));
	msgdata.msgsize += sizeof(UInt64);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteSmallFloat( usermsgdata_t& msgdata, float value )
{
	Int16 intvalue = static_cast<Int16>(SDL_floor(value * 8));
	UserMSG_Msg_WriteInt16(msgdata, intvalue);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteFloat( usermsgdata_t& msgdata, float value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(float));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(float));

	msgdata.msgsize += sizeof(float);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteDouble( usermsgdata_t& msgdata, double value )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, sizeof(double));

	Byte* pdata = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	memcpy(pdata, &value, sizeof(double));

	msgdata.msgsize += sizeof(double);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteBuffer( usermsgdata_t& msgdata, const Byte* pdata, UInt32 size )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	UserMSG_Msg_CheckBuffer(msgdata, size);

	Byte* pdest = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	for(UInt32 i = 0; i < size; i++)
		pdest[i] = pdata[i];
		
	msgdata.msgsize += size;
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteString( usermsgdata_t& msgdata, const char* pstrstring )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	if(!pstrstring)
	{
		// Write the size
		UserMSG_Msg_WriteUint16(msgdata, 1);

		// Check for size
		UserMSG_Msg_CheckBuffer(msgdata, 1);
		Byte* pdest = msgdata.pmsgbuffer 
			+ msgdata.msgsize;

		*pdest = '\0';
		msgdata.msgsize++;
		return;
	}

	// Write string length
	UInt32 strlength = qstrlen(pstrstring)+1;
	UserMSG_Msg_WriteUint16(msgdata, strlength);

	// Check buffer and write
	UserMSG_Msg_CheckBuffer(msgdata, strlength);

	Byte* pdest = msgdata.pmsgbuffer 
		+ msgdata.msgsize;

	for(UInt32 i = 0; i < strlength; i++)
		pdest[i] = static_cast<Byte>(pstrstring[i]);
		
	msgdata.msgsize += strlength;
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteEntindex( usermsgdata_t& msgdata, entindex_t entindex )
{
	// Is this function even neeeded?
	UserMSG_Msg_WriteInt32(msgdata, entindex);
}

//=============================================
//
//=============================================
void UserMSG_Msg_WriteBitSet( usermsgdata_t& msgdata, const Byte* pdataarray, UInt32 numbits, UInt32 numbytes )
{
	if(msgdata.pusermsg == nullptr)
	{
		Con_EPrintf("%s - No message begin called.\n", __FUNCTION__);
		return;
	}

	// Tell of the size of the bitset
	UserMSG_Msg_WriteUint32(msgdata, numbits);
	// Tell of the number of bytes
	UserMSG_Msg_WriteUint32(msgdata, numbytes);
	// Now write it as a buffer
	UserMSG_Msg_WriteBuffer(msgdata, pdataarray, numbytes);
}