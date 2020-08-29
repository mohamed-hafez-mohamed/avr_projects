/*******************************************************************************
* Title                 :   DRIVER 
* Filename              :   DRIVER_program.c
* Author                :   Mohamed Hafez
* Origin Date           :   10/8/2020
* Version               :   1.0.0
* Compiler              :   TODO: COMPILER GOES HERE
* Target                :   TODO: MCU GOES HERE
* Notes                 :   None 
*
*****************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author          Description 
*  04/01/15   1.0.0   Mohamed Hafez   Initial Release.
*
*******************************************************************************/
/** @file DRIVER_program.c
 *  @brief This is the source file for TODO: WHAT DO I DO? 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>	
#include <avr/interrupt.h>
#include "common.h"
#include "platform_PCfg.h"
#include "GPIO.h"
#include "SCHEDULER_interface.h"
#include "SCHEDULER_private.h"
#include "SCHEDULER_config.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
extern Queue_t ReadyQueue;
timer0_cnfg mytimer = {PRESCALING_CLK1024, CTC, Toggle_on_com};
static void  (*pfunc_ovi)(Queue_t * pq);

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************Timer Functions********************************/

void timer0_init(timer0_cnfg* ptrtimer0)
{
	pin_dirc(T0,PIN_INPUT);
	ACCESS_REG_8BIT((TIMER0BASE + TIMER0_OFFSET))    = CLEAR_REGISTER;                 //clear TCNT0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))  = CLEAR_REGISTER;                 //clear TCCR0 REG
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_clkSelect << CS00);
	ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET)) |= (ptrtimer0->Timer0_COM       << COM00);
	switch(ptrtimer0->Timer0_mode)
	{
		case Normal :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		break;
		case PWM_phase_correct :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
		case CTC :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   &= ~(SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
		case Fast_PWM :
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM01);
		   ACCESS_REG_8BIT((TIMER0BASE + CONTROL0_OFFSET))   |=  (SET << WGM00);
		   pin_dirc(OC0,PIN_OUTPUT);
		break;
	}
}

void ov_int(TOVFIE0 Timer0_TOIE, void (*ptr_ISR)(Queue_t * pq))
{
	if(Timer0_TOIE == TOIE0_enable)
	{
		ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) |= (SET << TOIE0);
	}
	if(Timer0_TOIE == TOIE0_disable)
	{
		ACCESS_REG_8BIT((TIMER0BASE + MASK_OFFSET)) &= ~(SET << TOIE0);
	}
	pfunc_ovi = ptr_ISR;
}

ISR(TIMER0_OVF_vect)
{
	sei();
	(*pfunc_ovi)(&ReadyQueue);
}

/*****************************Scheduler Functions*******************************/
void SCHEDULER_voidStartScheduler(void)
{
	sei();
}

void SCHEDULER_voidInitScheduler(Queue_t *pq)
{
    pq->Front = NULL;
    pq->Rear  = NULL;
    pq->Size  = 0;
	timer0_init(&mytimer);
	ov_int(TOIE0_enable, &SCHEDULER_voidUpdateScheduler);
}

int SCHEDULER_intAddTask(pStructTask_QueueENTRY  pe,Queue_t * pq)
{
   QueueNode_t  * pn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if(! pn)
    {
      return 0;
    }
    else
    {
      pn->entry = pe;
      pn->next  = NULL;
      if(!pq->Rear)
      {
          pq->Front = pn;
      }
      else
      {
          pq->Rear->next = pn;
      }
      pq->Rear = pn;
      pq->Size++;
      return 1;
    }
}

int SCHEDULER_intCreateTask(ptr_TaskCode code,int release, int Period, char flag, void * parameter)
{
    pStructTask_QueueENTRY Task = (pStructTask_QueueENTRY)malloc(sizeof(Task_t));
    Task->p_TaskCode   = code;
    Task->ReleaseTime  = release;
    Task->Period       = Period;
    Task->Runme_f      = flag;
    Task->Parameter    = parameter;
    SCHEDULER_intAddTask(Task, &ReadyQueue);
}

void SCHEDULER_voidUpdateScheduler(Queue_t *pq)
{
    QueueNode_t *pn;
    for(pn = pq -> Front;pn;pn = pn -> next)
    {
        /*!<Check if there is a task at this location*/
        if(pn->entry->p_TaskCode)
        {
            if(pn->entry->ReleaseTime == 0)
            {
                /*!<The task is ready to run*/
               pn->entry->Runme_f += 1;
               if(pn->entry->Period)
               {
                    /*!<Schedule periodic tasks to run again*/
                    pn->entry->ReleaseTime = pn->entry->Period;
               }
            }
            else
            {
                /*!<Not yet ready to run: just decrement the delay*/
                pn->entry->ReleaseTime -= 1;
            }
        }
    }
}

/*!<Dispatch function*/
void SCHEDULER_voidDispatchTasks(Queue_t *pq)
{
    static QueueNode_t *pn;
    int position = 0;
    for(pn = pq -> Front;pn;pn = pn -> next)
    {
        if(pn->entry->Runme_f > 0)
        {
            pn->entry->p_TaskCode(pn->entry->Parameter);        /*!<Run the task */
            pn->entry->Runme_f -= 1;                            /*!<Reset / reduce RunMe flag */
            /*!<Periodic tasks will automatically run again*/
            /*!<if this is a 'one shot' task, remove it from the array*/
            if(pn->entry->Period == 0)
            {
                /*!<The task is ready to run*/
                SCHEDULER_voidDeleteTask(position,pq);
            }
        }
        position++;
    }
    /*!<Report system status*/
    //SCH_Report_Status();
    /*!<The scheduler enters idle mode at this point*/
    //SCH_Go_To_Sleep();
}

void SCHEDULER_voidServeTask(pStructTask_QueueENTRY * pe, Queue_t * pq)
{
    QueueNode_t * pn = pq->Front;
    *pe = pn->entry;
    if(!pq->Front)
    {
        pq->Rear = NULL;
    }
}

void SCHEDULER_voidServeDleteTask(pStructTask_QueueENTRY * pe, Queue_t * pq)
{
    QueueNode_t *pn = pq->Front;
    *pe = pn->entry;
    pq->Front = pn->next;

    pn->entry->Period       = 0;
    pn->entry->Runme_f      = 0;
    pn->entry->ReleaseTime = 0;
    free(pn->entry);
    free(pn);
    if(!pq->Front)
    {
        pq->Rear = NULL;
    }
    pq->Size--;
}

void SCHEDULER_voidDeleteTask(int pos,Queue_t * pq)
{
    int i;
    QueueNode_t * temp;
    QueueNode_t * q;
    if(pos == 0)
    {
        temp = pq->Front->next;
        pq->Front->entry->Period      = 0;
        pq->Front->entry->Runme_f     = 0;
        pq->Front->entry->ReleaseTime = 0;
        free(pq->Front->entry);
        free(pq->Front);
        pq->Front = temp;
    }
    else
    {
       for(q = pq->Front,i = 0;i < pos - 1;i++)
       {
           q = q->next;
       }
       temp = q->next->next;
       q->next->entry->Period      = 0;
       q->next->entry->Runme_f     = 0;
       q->next->entry->ReleaseTime = 0;
       free(q->next->entry);
       free(q->next);
       q->next = temp;
    }
    pq->Size--;
}

void SCHEDULER_voidReplaceTask(int pos, pStructTask_QueueENTRY * pe, Queue_t * pq)
{
    int i;
    QueueNode_t * q;
    if(pos == 0)
    {
        pq->Front->entry = *pe;
    }
    else
    {
        for(q = pq->Front, i = 0;i < pos;i++)
       {
           q = q->next;
       }
       q->entry = *pe;
    }

}

int  SCHEDULER_intIsQueueEmpty(Queue_t * pq)
{
    return !pq->Size;
}

int  SCHEDULER_intIsQueueFull(Queue_t * pq)
{
    return 0;
}

int  SCHEDULER_intQueueSize(Queue_t * pq)
{
    return pq->Size;
}

void SCHEDULER_voidClearQueue(Queue_t * pq)
{
    while(pq->Front)
    {
        pq->Rear = pq->Front->next;
        free(pq -> Front);
        pq->Front = pq->Rear;
    }
    pq->Size = 0;
}

void SCHEDULER_voidTraverseQueue(Queue_t * pq, void (*PF)(pStructTask_QueueENTRY e))
{
    QueueNode_t *pn;
    for(pn = pq -> Front;pn;pn = pn -> next)
    {
        (*PF)(pn -> entry);
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/
