/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef AI_SCHEDULE_INLINE_HPP
#define AI_SCHEDULE_INLINE_HPP

//=============================================
// @brief
//
//=============================================
DO_INLINE UInt32 CAISchedule::GetNumTasks( void ) const
{
	return m_tasksArray.size();
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const ai_task_t& CAISchedule::GetTaskByIndex( UInt32 index ) const
{
	assert(index < m_tasksArray.size());
	return m_tasksArray[index];
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const CBitSet& CAISchedule::GetInterruptMask( void ) const
{
	return m_aiCondInterruptMask;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const CBitSet& CAISchedule::GetInverseInterruptMask( void ) const
{
	return m_aiCondInverseInterruptMask;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE Int32 CAISchedule::GetSpecialInterruptScheduleIndex( void ) const
{
	return m_specialInterruptSchedule;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const CBitSet& CAISchedule::GetSpecialInterruptMask( void ) const
{
	return m_specialInterruptConditionMask;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const CBitSet& CAISchedule::GetSpecialInterruptExceptionMask( void ) const
{
	return m_specialInterruptExceptionMask;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const CBitSet& CAISchedule::GetSpecialInterruptRequirementMask( void ) const
{
	return m_specialInterruptRequirementMask;
}


//=============================================
// @brief
//
//=============================================
DO_INLINE UInt64 CAISchedule::GetSoundMask( void ) const
{
	return m_soundMask;
}

//=============================================
// @brief
//
//=============================================
DO_INLINE const char* CAISchedule::GetName( void ) const
{
	return m_scheduleName.c_str();
}
#endif //AI_SCHEDULE_INLINE_HPP