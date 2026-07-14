/*
===============================================
Pathos Engine - Copyright Andrew Lucas

2016-2024
All Rights Reserved.
===============================================
*/

#ifndef AI_SCHEDULE_H
#define AI_SCHEDULE_H

#include "ai_tasks.h"

//=============================================
//
//=============================================
class CAISchedule
{
public:
	CAISchedule( ai_task_t* pTasks, UInt32 nbTasks, const CBitSet& conditionMask, UInt64 soundMask, const char* pstrName );
	CAISchedule( ai_task_t* pTasks, UInt32 nbTasks, const CBitSet& conditionMask, const CBitSet& inverseConditionMask, UInt64 soundMask, const char* pstrName );
	CAISchedule( ai_task_t* pTasks, UInt32 nbTasks, const CBitSet& conditionMask, const CBitSet& inverseConditionMask, Int32 specialInterruptSchedule, const CBitSet& specialInterruptConditionMask, const CBitSet& specialInterruptExceptionMask, const CBitSet& specialInterruptRequirementMask, UInt64 soundMask, const char* pstrName );
	~CAISchedule();

public:
	// Returns the number of tasks
	DO_INLINE UInt32 GetNumTasks( void ) const;
	// Returns a task for an index
	DO_INLINE const ai_task_t& GetTaskByIndex( UInt32 index ) const;
	// Returns the condition interrupt mask
	DO_INLINE const CBitSet& GetInterruptMask( void ) const;
	// Returns the inverse condition interrupt mask
	DO_INLINE const CBitSet& GetInverseInterruptMask( void ) const;
	// Returns the special interrupt schedule index
	DO_INLINE Int32 GetSpecialInterruptScheduleIndex( void ) const;
	// Returns the special condition interrupt mask
	DO_INLINE const CBitSet& GetSpecialInterruptMask( void ) const;
	// Returns the special condition interrupt exception mask
	DO_INLINE const CBitSet& GetSpecialInterruptExceptionMask( void ) const;
	// Returns the special condition interrupt exception mask
	DO_INLINE const CBitSet& GetSpecialInterruptRequirementMask( void ) const;
	// Returns the smell mask
	DO_INLINE UInt64 GetSoundMask( void ) const;
	// Returns the name for the task
	DO_INLINE const char* GetName( void ) const;

private:
	// Array of tasks
	CArray<ai_task_t> m_tasksArray;
	// AI condition interrupt mask
	CBitSet m_aiCondInterruptMask;
	// AI condition inverse interrupt mask
	CBitSet m_aiCondInverseInterruptMask;
	// Special interrupt schedule index
	Int32 m_specialInterruptSchedule;
	// Special interrupt schedule condition mask
	CBitSet m_specialInterruptConditionMask;
	// Special interrupt schedule exception mask
	CBitSet m_specialInterruptExceptionMask;
	// Special interrupt requirement mask
	CBitSet m_specialInterruptRequirementMask;
	// Sound mask
	UInt64 m_soundMask;
	// Name of the schedule
	CString m_scheduleName;
};

#include "ai_schedule_inline.hpp"
#endif //AI_SCHEDULE_H