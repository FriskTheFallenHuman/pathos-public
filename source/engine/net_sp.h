/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef NET_SP_H
#define NET_SP_H

/*
=======================
CSPNetworking

=======================
*/
class CSPNetworking : public CNetworking
{
public:
	CSPNetworking( void );
	virtual ~CSPNetworking( void );

public:
	// Initializes networking functions
	virtual bool Init( const char* pstrhost ) override;

	// Close off and cache a message
	virtual void SVC_MessageEnd( void ) override;
	// Retrieves a cache pointer
	virtual net_msgcache_t* SVC_GetWriteCache( UInt32 clientidx ) override;

	// Close off and cache a message
	virtual void CLS_MessageEnd( void ) override;
	// Retrieves a cache pointer
	virtual net_msgcache_t* CLS_GetWriteCache( void ) override;

	// Disconnects from the host server
	virtual void Disconnect( UInt32 clindex ) override {};

	// Tries to reconnect to the host server
	virtual bool AttemptConnection( void ) override { return true; };
};
#endif //NET_SP_H