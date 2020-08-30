/****************************************************************************
* Title                 :   SCHEDULER   
* Filename              :   SCHEDULER_uint16erface.h
* Author                :   Mohamed Hafez
* Origin Date           :   10/08/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template 
*
*****************************************************************************/
/*************** uint16ERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  10/8/20   1.0.0   Mohamed Hafez   uint16erface Created.
*
*****************************************************************************/
/** @file  SCHEDULER_uint16erface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef SCHEDULER_uint16ERFACE_H_
#define SCHEDULER_uint16ERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

typedef void (*ptr_TaskCode)(void *);

/*!<Task Structure*/
typedef struct
{
   ptr_TaskCode Task_PtrCode;
   uint16          Task_uint16ReleaseTime;
   uint16          Task_uint16Period;
   char         Task_u8RunMeFlag;
   void    *    Task_PtrVoidParameter;
}Task_t;

typedef Task_t* PtrStructTask_QueueENTRY;

/*!<Queue Definitions*/
typedef struct queuenode
{
    PtrStructTask_QueueENTRY  QueueNode_Entry;
    struct queuenode        * QueueNode_Next;
}QueueNode_t;

typedef struct Queue
{
    QueueNode_t * Queue_Front;
    QueueNode_t * Queue_Rear;
    uint16           Queue_Size;
}Queue_t;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

uint16  SCHEDULER_uint16CreateTask(ptr_TaskCode Copy_PtrTaskCode,uint16 Copy_uint16ReleaseTime, uint16 Copy_uint16Period, char Copy_Flag , void * Copy_PtrTaskParameter);
void SCHEDULER_voidInitScheduler(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidStartScheduler(void);
uint16  SCHEDULER_uint16AddTask(PtrStructTask_QueueENTRY  Copy_PtrQueueEntry,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidUpdateScheduler(void * Copy_voidPtrQueue);
void SCHEDULER_voidDispatchTasks(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidDeleteTask(uint16 Copy_uint16TaskPosition,Queue_t * Copy_PtrQueue);
void SCHEDULER_voidServeDleteTask(PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
void SCHEDULER_voidReplaceTask(uint16 Copy_uint16TaskPosition, PtrStructTask_QueueENTRY * Copy_PtrQueueEntry, Queue_t * Copy_PtrQueue);
uint16  SCHEDULER_uint16IsQueueEmpty(Queue_t * Copy_PtrQueue);
uint16  SCHEDULER_uint16IsQueueFull(Queue_t * Copy_PtrQueue);
uint16  SCHEDULER_uint16QueueSize(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidClearQueue(Queue_t * Copy_PtrQueue);
void SCHEDULER_voidTraverseQueue(Queue_t * Copy_PtrQueue, void (*PF)(PtrStructTask_QueueENTRY Copy_QueueEntry));


#endif /*File_H_*/

/*** End of File **************************************************************/
