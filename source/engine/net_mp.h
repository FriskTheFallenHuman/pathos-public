/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef NET_MP_H
#define NET_MP_H

/*
=======================
CMPNetworking

=======================
*/
class CMPNetworking : public CNetworking
{
public:
	CMPNetworking( void );
	virtual ~CMPNetworking( void );

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

	// Manages a connecting client
	virtual void ClientConnect( ENetEvent* pevent );
	// Disconnects from the host server
	virtual void Disconnect( UInt32 clindex ) override;

	// Retrieve any packets
	virtual void Poll( void ) override;

	// Tries to reconnect to the host server
	virtual bool AttemptConnection( void ) override;

private:
	// Initializes server networking
	bool InitServerNetworking( UInt32 port );
	// Initializes client networking
	bool InitClientNetworking( UInt32 port, const char* pstrhost );

	// Retrieve any packets
	virtual void Poll_Host( void );
	// Retrieve any packets
	virtual void Poll_Client( void );

	// Reads an incoming message
	void ReadUDPMessage( net_msgcache_t* pcache, ENetEvent* pevent );
	// Sends a message to a peer
	bool SendUDPMessage( msgdest_t dest, Byte* pdata, UInt32 msgsize, ENetPeer* ptrpeer );

	// Rejects a client and tells them why
	virtual void RejectClient( ENetPeer* ptrpeer, const char* pstrreason );
	
	// Called when connection is lost with the remote
	void ConnectionLost( UInt32 clindex );

private:
	// Write cache used for remotes
	net_msgcache_t* m_pWriteCache;
	// Host object
	ENetHost* m_pHost;

	// Host address
	CString m_hostAddress;
	// Host port
	UInt32 m_hostPort;
	// Last time we attempted to reconnect
	double m_lastReconnectAttemptTime;

	// Connect id->player index map
	CArray<UInt32> m_connectIdPlayerIdxArray;
};
#endif //NET_MP_H