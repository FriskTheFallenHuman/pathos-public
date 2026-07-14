/*
===============================================
Pathos Engine - Created by Andrew Stephen "Overfloater" Lucas

Copyright 2016
All Rights Reserved.
===============================================
*/

#ifndef CBUFFER_INLINE_HPP
#define CBUFFER_INLINE_HPP

//=============================================
// @brief Appends data to the buffer
//
// @param pdata Pointer to data
// @param datasize Size of data to append
// @return true if buffer was resized, false otherwise
//=============================================
DO_INLINE bool CBuffer::append( const void* pdata, Uint32 datasize )
{
	bool wasresized = false;
	const Uint32 finalSize = m_bufferDataPosition + datasize;
	if(finalSize >= m_bufferSize)
	{
		CArray<Int64> pointerOffsetsArray;
		if(!m_pointersArray.empty())
		{
			const Byte* pbaseptr = static_cast<Byte*>(m_pBufferData);

			pointerOffsetsArray.resize(m_pointersArray.size());
			for(Uint32 i = 0; i < m_pointersArray.size(); i++)
			{
				const Byte* pointer = static_cast<Byte*>(*m_pointersArray[i]);
				Int64 offset = pointer - pbaseptr;
				pointerOffsetsArray[i] = offset;
			}
		}

		Int32 multiplier = 1;
		const Uint32 memNeeded = finalSize - (m_bufferSize - m_bufferDataPosition);
		if(memNeeded > m_bufferAllocSize)
		{
			const float nbTimes = static_cast<float>(static_cast<float>(memNeeded/(float)m_bufferAllocSize));
			multiplier = static_cast<Int32>(ceil(nbTimes));
		}

		// Resize the message data buffer
		m_pBufferData = Common::ResizeArray(m_pBufferData, sizeof(Byte), m_bufferSize, m_bufferAllocSize*multiplier);
		m_bufferSize = m_bufferSize + m_bufferAllocSize*multiplier;

		// Restore pointers
		if(!pointerOffsetsArray.empty())
		{
			Byte* pbaseptr = static_cast<Byte*>(m_pBufferData);
			for(Uint32 i = 0; i < pointerOffsetsArray.size(); i++)
			{
				void* pfinal = pbaseptr + pointerOffsetsArray[i];
				(*m_pointersArray[i]) = pfinal;
			}
		}

		wasresized = true;
	}

	if(pdata)
	{
		// Only write data if the pointer is not null, otherwise just reserve it
		Byte *pdest = static_cast<Byte*>(m_pBufferData) + m_bufferDataPosition;
		memcpy(pdest, pdata, sizeof(Byte)*datasize);
	}

	// Add to offset
	m_bufferDataPosition += datasize;
	return wasresized;
}

//=============================================
// @brief Returns the data in the buffer
//
// @return Reference to data pointer
//=============================================
DO_INLINE void*& CBuffer::getbufferdata( void )
{
	return m_pBufferData;
}

//=============================================
// @brief Retreives the writing offset into the buffer data
//
// @return Current writind position
//=============================================
DO_INLINE Uint32 CBuffer::getdatasize( void ) const
{
	return m_bufferDataPosition;
}

//=============================================
// @brief Returns the current allocated buffer size
//
// @return Current allocated buffer size
//=============================================
DO_INLINE Uint32 CBuffer::getbuffersize( void ) const
{
	return m_bufferSize;
}

//=============================================
// @brief Resets the writing position to zero
//
//=============================================
DO_INLINE void CBuffer::reset( void )
{
	m_bufferDataPosition = 0;
}

//=============================================
// @brief Adds a pointer to the list of pointers this buffer will rebase when resized
//
// @param ptr Pointer that is to be added
//=============================================
DO_INLINE void CBuffer::addpointer( void** ptr )
{
	if (!ptr || !(*ptr))
		return;

	const Byte* pbaseptr = static_cast<Byte*>(m_pBufferData);
	const Byte* pointer = static_cast<Byte*>(*ptr);

	const Int64 offset = (pointer - pbaseptr);
	if(offset < 0 || offset > m_bufferSize)
		assert(false);

	for(Uint32 i = 0; i < m_pointersArray.size(); i++)
	{
		if(m_pointersArray[i] == ptr)
			return;
	}

	m_pointersArray.push_back(ptr);
}

//=============================================
// @brief Removes a pointer to the list of pointers to rebase
//
// @param ptr Pointer to remove
//=============================================
DO_INLINE void CBuffer::removepointer( const void** ptr )
{
	for(Uint32 i = 0; i < m_pointersArray.size(); i++)
	{
		if(m_pointersArray[i] == ptr)
		{
			m_pointersArray.erase(i);
			return;
		}
	}
}

//=============================================
// @brief Removes a pointer to the list of pointers to rebase
//
// @param ptr Pointer to remove
//=============================================
DO_INLINE void CBuffer::removepointer( void** ptr )
{
	for(Uint32 i = 0; i < m_pointersArray.size(); i++)
	{
		if(m_pointersArray[i] == ptr)
		{
			m_pointersArray.erase(i);
			return;
		}
	}
}

//=============================================
// @brief Initializes the buffer with the allocation size
//
//=============================================
DO_INLINE void CBuffer::initbuffer( void )
{
	m_pBufferData = new Byte[m_bufferAllocSize];
	memset(m_pBufferData, 0, sizeof(Byte)*m_bufferAllocSize);

	m_bufferSize = m_bufferAllocSize;
}
#endif //CBUFFER_INLINE_HPP