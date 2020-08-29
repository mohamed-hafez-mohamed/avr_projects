/****************************************************************************
* Title                 :   DRIVER   
* Filename              :   DRIVER_interface.h
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
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author          Description 
*  10/8/20   1.0.0   Mohamed Hafez   Interface Created.
*
*****************************************************************************/
/** @file  DRIVER_interface.h
 *  @brief This module TODO: WHAT DO I DO?
 * 
 *  This is the header file for the definition TODO: MORE ABOUT ME!
 */
//TODO: UPDATE MACRO BELOW
#ifndef DRIVER_INTERFACE_H_
#define DRIVER_INTERFACE_H_

/******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define SET                      1
#define CLEAR_REGISTER           0x00
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/
/*********************************Timer Configuration**************************/

typedef enum
{
	NO_CLK_SRC,          //Timer Disable
	NO_PRESCALING,
	PRESCALING_CLK8,
	PRESCALING_CLK64,
	PRESCALING_CLK256,
	PRESCALING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
}clk_selectType;

typedef enum    
{
	Normal,
	PWM_phase_correct,                           /*!<PWM Phase Correct wave*/
	CTC,                                         /*!<Clear Timer on Compare Match*/
	Fast_PWM                                     /*!<Fast PWM wave*/
}WAVE_FORM_GEN;

typedef enum
{
	Normal_port,                                 /*!<Normal port operation, OC0 disconnected*/
	Toggle_on_com,                               /*!<Toggle OC0 on compare match or reserved with other modes*/
	Clear_on_com,                                /*!<Clear OC0 on compare match or (non-inverting mode) with other modes*/
	Set_on_com                                   /*!<set OC0 on compare match or (inverting mode) with other modes*/
}COMPARE_MATCH_OUTPUT;

typedef enum                                     /*!<Timer/Counter0 over flow Interrupt Enable*/
{
	TOIE0_disable,
	TOIE0_enable
}TOVFIE0;

typedef enum                                     /*!<Timer/Counter0 Output Compare Match Interrupt Enable*/
{
	OCIE0_disable,
	OCIE0_enable
}OCMIE0;

typedef struct 
{
	clk_selectType        Timer0_clkSelect;
	WAVE_FORM_GEN         Timer0_mode;
	COMPARE_MATCH_OUTPUT  Timer0_COM;
}timer0_cnfg;
/******************************************************************************/

/***************************Scheduler Configuration****************************/
typedef void (*ptr_TaskCode)(void *);

/*!<Task Structure*/
typedef struct
{
   ptr_TaskCode p_TaskCode;
   int    ReleaseTime;
   int    Period;
   char   Runme_f;
   void * Parameter;
}Task_t;

typedef Task_t* pStructTask_QueueENTRY;

/*!<Queue Definitions*/
typedef struct queuenode
{
    pStructTask_QueueENTRY entry;
    struct queuenode       *next;
}QueueNode_t;

typedef struct Queue
{
    QueueNode_t *Front;
    QueueNode_t *Rear;
    int Size;
}Queue_t;
/******************************************************************************/
/******************************************************************************
* Variables
*******************************************************************************/
Queue_t ReadyQueue;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**************************Timer Function Prototype****************************/
void timer0_init(timer0_cnfg* ptrtimer0);
void ov_int(TOVFIE0 Timer0_TOIE, void (*ptr_ISR)(Queue_t * pq));

/***********************Scheduler Function Prototype***************************/
void SCHEDULER_voidStartScheduler(void);
int  SCHEDULER_intCreateTask(ptr_TaskCode code,int release, int Period, char flag, void * parameter);
void SCHEDULER_voidInitScheduler(Queue_t * pq);
int  SCHEDULER_intAddTask(pStructTask_QueueENTRY  pe,Queue_t * pq);
void SCHEDULER_voidUpdateScheduler(Queue_t *pq);
void SCHEDULER_voidDispatchTasks(Queue_t *pq);
void SCHEDULER_voidServeTask(pStructTask_QueueENTRY * pe, Queue_t *pq);
void SCHEDULER_voidDeleteTask(int pos,Queue_t *pq);
void SCHEDULER_voidServeDleteTask(pStructTask_QueueENTRY *pe,Queue_t *pq);
void SCHEDULER_voidReplaceTask(int pos,pStructTask_QueueENTRY *pe,Queue_t *pq);
int  SCHEDULER_intIsQueueEmpty(Queue_t *pq);
int  SCHEDULER_intIsQueueFull(Queue_t *pq);
int  SCHEDULER_intQueueSize(Queue_t *pq);
void SCHEDULER_voidClearQueue(Queue_t *pq);
void SCHEDULER_voidTraverseQueue(Queue_t *pq, void (*PF)(pStructTask_QueueENTRY e));

#endif /*File_H_*/

/*** End of File **************************************************************/
