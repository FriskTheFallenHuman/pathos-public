/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef MD5_H
#define MD5_H

// MD5 block size
#define MD5_BLOCKSIZE 64

// MD5 hash generator
// - Thanks to Frank Thilo for his C++ implementation
// MD5 algorythm by "RSA Data Security, Inc."

/*
=======================
CMD5

=======================
*/
class CMD5
{
public:
	// MD5 hash size
	static const Uint32 MD5_HASH_SIZE = 33;

public:
	CMD5();
	CMD5( const Byte* pbuffer, Uint32 bufsize );

public:
	void Init( void );
	void Update( const Byte *pinput, Uint32 length );
	CMD5& Finalize( void );
	CString HexDigest( void ) const;

private:
	void Transform( const Byte* pblock );
	static void Decode( Uint32* poutput, const Byte* pinput, Uint32 length );
	static void Encode( Byte* poutput, const Uint32* pinput, Uint32 length );

private:
	// true if the hash is finalized
	bool m_isFinalized;

	// bytes that didn't fit in tthe last 64-byte chunk
	Byte m_buffer[MD5_BLOCKSIZE];
	// 64-bit counter for number of bits(lo, hi)
	Uint32 m_count[2];
	// Digest so far
	Uint32 m_state[4];
	// The result
	Byte m_digest[16];

	// Low level logic operations
	STATIC_INLINE DO_INLINE Uint32 F( Uint32 x, Uint32 y, Uint32 z ) { return x&y | ~x&z; };
	STATIC_INLINE DO_INLINE Uint32 G( Uint32 x, Uint32 y, Uint32 z ) { return x&z | y&~z; };
	STATIC_INLINE DO_INLINE Uint32 H( Uint32 x, Uint32 y, Uint32 z ) { return x^y^z; };
	STATIC_INLINE DO_INLINE Uint32 I( Uint32 x, Uint32 y, Uint32 z ) { return y ^ (x | ~z); };
	STATIC_INLINE DO_INLINE Uint32 RotateLeft( Uint32 x, Int32 n ) { return (x<<n) | (x>>(32-n)); }
	STATIC_INLINE DO_INLINE void FF( Uint32& a, Uint32 b, Uint32 c, Uint32 d, Uint32 x, Uint32 s, Uint32 ac ) { a = RotateLeft(a+F(b,c,d) + x + ac, s) + b; }
	STATIC_INLINE DO_INLINE void GG( Uint32& a, Uint32 b, Uint32 c, Uint32 d, Uint32 x, Uint32 s, Uint32 ac ) { a = RotateLeft(a+G(b,c,d) + x + ac, s) + b; }
	STATIC_INLINE DO_INLINE void HH( Uint32& a, Uint32 b, Uint32 c, Uint32 d, Uint32 x, Uint32 s, Uint32 ac ) { a = RotateLeft(a+I(b,c,d) + x + ac, s) + b; }
	STATIC_INLINE DO_INLINE void II( Uint32& a, Uint32 b, Uint32 c, Uint32 d, Uint32 x, Uint32 s, Uint32 ac ) { a = RotateLeft(a+H(b,c,d) + x + ac, s) + b; }
};

#endif //MD5_H