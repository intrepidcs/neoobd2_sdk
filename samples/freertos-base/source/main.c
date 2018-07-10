/*
 * Amazon FreeRTOS V1.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

/* Demo priorities & stack sizes. */
#include "aws_demo_config.h"
#include "aws_logging_task.h"

/* FreeRTOS Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */
#include "portmacro.h"

/* Demo files. */
#include "FreeRTOSConfig.h"
#include "aws_demo_config.h"

/* CC3220SF board file. */
#include "Board.h"

// ISM Lib includes
#include "obd2pro_wifi_cc32xx_ism.h"
#include "obd2pro_wifi_cc32xx.h"

#define mainSTACK_SIZE 2048
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    (15)

/*-----------------------------------------------------------*/

extern void Spy_EveryLoop(unsigned int);
extern void Spy_BeforeStarted(void);
extern void Spy_Started(void);
extern void Spy_Main(void);
extern void Spy_ErrorFrame(int, int, int, int);
extern void Spy_ErrorState(int, int, int, int);

/*
 * The queue send and receive tasks as described in the comments at the top of
 * this file.
 */
static void prvQueueReceiveTask(void *pvParameters);
static void prvQueueSendTask(void *pvParameters);

/*
 * The callback function assigned to the example software timer as described at
 * the top of this file.
 */
static void vExampleTimerCallback(TimerHandle_t xTimer);

/*
 * The event semaphore task as described at the top of this file.
 */
static void prvEventSemaphoreTask(void *pvParameters);

/*-----------------------------------------------------------*/

/* The queue used by the queue send and queue receive tasks. */
static QueueHandle_t xQueue = NULL;

/* The semaphore (in this case binary) that is used by the FreeRTOS tick hook
 * function and the event semaphore task.
 */
static SemaphoreHandle_t xEventSemaphore = NULL;

/* The counters used by the various examples.  The usage is described in the
 * comments at the top of this file.
 */
static volatile uint32_t ulCountOfTimerCallbackExecutions = 0;
static volatile uint32_t ulCountOfItemsReceivedOnQueue = 0;
static volatile uint32_t ulCountOfReceivedSemaphores = 0;

/*-----------------------------------------------------------*/

void ismInit()

{
	icsISM_PreInit();

	RegisterInitFunc(CM_ExtensionInit);
	RegisterMsProcessFunc(Spy_EveryLoop);
	RegisterBeforeStartedFunc(Spy_BeforeStarted);
	RegisterStartedFunc(Spy_Started);
	RegisterMainFunc(Spy_Main);
	RegisterErrorFrameFunc(Spy_ErrorFrame);
	RegisterErrorStateFunc(Spy_ErrorState);
	RegisterEveryMessageFunc(CM_EveryMessage);

	icsISM_Init();
}

/**
 * @brief Performs board and logging initializations, then starts the OS.
 *
 * Functions that require the OS to be running
 * are handled in vApplicationDaemonTaskStartupHook().
 *
 * @sa vApplicationDaemonTaskStartupHook()
 *
 * @return This function should not return.
 */
int main(void)
{
	TimerHandle_t xExampleSoftwareTimer = NULL;

	UART_Handle xtUartHndl;

	/* Configure the system ready to run the demo.  The clock configuration
	   can be done here if it was not done before main() was called. */
	/* Call board init functions. */
	Board_initGeneral();

	Board_initGPIO();
	Board_initSPI(); /* AN:  Is the SPI actually used? */

    /* Initialize GPIO to enable UART0 as UART Terminal */
    GPIO_write(CC_UART_EN, 1);
    GPIO_write(WIFI_INT, 1);
    GPIO_write(CC_LED0, 1);

	ismInit();

    /* Configure the UART. */
    xtUartHndl = InitTerm();
    UART_control(xtUartHndl, UART_CMD_RXDISABLE, NULL);

    /* Start logging task. */
    xLoggingTaskInitialize( democonfigTASKSTACKSIZE,
    tskIDLE_PRIORITY,
                           mainLOGGING_MESSAGE_QUEUE_LENGTH);

	/* Create the queue used by the queue send and queue receive tasks. */
	xQueue = xQueueCreate(
		/* The number of items the queue can hold. */
		democonfigQUEUE_LENGTH,
		/* The size of each item the queue holds. */
		sizeof( uint32_t ));

	/* Create the semaphore used by the FreeRTOS tick hook function and the
	   event semaphore task.  NOTE: A semaphore is used for example purposes,
	   using a direct to task notification will be faster! */
	xEventSemaphore = xSemaphoreCreateBinary();

	/* Create the queue receive task as described in the comments at the top
	   of this file. */
	xTaskCreate(
		/* The function that implements the task. */
		prvQueueReceiveTask,
		/* Text name for the task, just to help debugging. */
		(char *) "Rx",
		/* The size (in words) of the stack that should be created
		   for the task. */
		mainSTACK_SIZE,
		/* A parameter that can be passed into the task.  Not used
		   in this simple demo. */
		NULL,
		/* The priority to assign to the task.  tskIDLE_PRIORITY
		   (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
		   is the highest priority. */
		democonfigQUEUE_RECEIVE_TASK_PRIORITY,
		/* Used to obtain a handle to the created task.  Not used in
		   this simple demo, so set to NULL. */
		NULL);

	/* Create the queue send task in exactly the same way.  Again, this is
	   described in the comments at the top of the file. */
	xTaskCreate(prvQueueSendTask, (char *) "TX",
	            mainSTACK_SIZE,
	            NULL, democonfigQUEUE_SEND_TASK_PRIORITY,
	            NULL);

	/* Create the task that is synchronised with an interrupt using the
	   xEventSemaphore semaphore. */
	xTaskCreate(prvEventSemaphoreTask, (char *) "Sem",
	            mainSTACK_SIZE,
	            NULL, democonfigEVENT_SEMAPHORE_TASK_PRIORITY,
	            NULL);

	/* Create the software timer as described in the comments at the top of
	   this file. */
	xExampleSoftwareTimer = xTimerCreate(
		/* A text name, purely to help debugging. */
		(const char *) "LEDTimer",
		/* The timer period, in this case 1000ms (1s). */
		democonfigSOFTWARE_TIMER_PERIOD_MS,
		/* This is a periodic timer, so xAutoReload is set to pdTRUE. */
		pdTRUE,
		/* The ID is not used, so can be set to anything. */
		(void *) 0,
		/* The callback function that switches the LED off. */
		vExampleTimerCallback);

	/* Start the created timer.  A block time of zero is used as the timer
	   command queue cannot possibly be full here (this is the first timer to
	   be created, and it is not yet running). */
	xTimerStart(xExampleSoftwareTimer, 0);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	   will never be reached.  If the following line does execute, then there was
	   insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	   to be created.  See the memory management section on the FreeRTOS web site
	   for more details.  */
	for (;; )
	{
		;
	}
}
/*-----------------------------------------------------------*/

static void vExampleTimerCallback(TimerHandle_t xTimer)
{
	/* The timer has expired.  Count the number of times this happens.  The
	   timer that calls this function is an auto re-load timer, so it will
	   execute periodically. */
	ulCountOfTimerCallbackExecutions++;
	configPRINTF(("Timer expired %d times\r\n", (int) ulCountOfTimerCallbackExecutions));
}
/*-----------------------------------------------------------*/

static void prvQueueSendTask(void *pvParameters)
{
	TickType_t xNextWakeTime;
	const uint32_t ulValueToSend = 100UL;

	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for (;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		   The block time is specified in ticks, the constant used converts ticks
		   to ms.  The task will not consume any CPU time while it is in the
		   Blocked state. */
		vTaskDelayUntil(&xNextWakeTime, democonfigQUEUE_SEND_PERIOD_MS);

		/* Send to the queue - causing the queue receive task to unblock and
		   increment its counter.  0 is used as the block time so the sending
		   operation will not block - it shouldn't need to block as the queue
		   should always be empty at this point in the code. */
		xQueueSend(xQueue, &ulValueToSend, 0);
	}
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask(void *pvParameters)
{
	uint32_t ulReceivedValue;

	for (;; )
	{
		/* Wait until something arrives in the queue - this task will block
		   indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		   FreeRTOSConfig.h. */
		xQueueReceive(xQueue, &ulReceivedValue, portMAX_DELAY);

		/*  To get here something must have been received from the queue, but
		   is it the expected value?  If it is, increment the counter. */
		if (ulReceivedValue == 100UL)
		{
			/* Count the number of items that have been received correctly. */
			ulCountOfItemsReceivedOnQueue++;
			configPRINTF(("Queue rx's count %d \r\n", (int) ulCountOfItemsReceivedOnQueue));
		}
	}
}
/*-----------------------------------------------------------*/

static void prvEventSemaphoreTask(void *pvParameters)
{
	for (;; )
	{
		/* Block until the semaphore is 'given'.  NOTE:
		   A semaphore is used for example purposes.  In a real application it might
		   be preferable to use a direct to task notification, which will be faster
		   and use less RAM. */
		if ((xSemaphoreTake(xEventSemaphore, portMAX_DELAY)) == pdTRUE)
		{
			/* Count the number of times the semaphore is received. */
			ulCountOfReceivedSemaphores++;
            configPRINTF(("Received semaphores' count %d \r\n", (int ) ulCountOfReceivedSemaphores));
		}
		else
		{
			configPRINTF(("ERROR: Semaphore take failed \r\n"));

		}

	}
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	static uint32_t ulCount = 0;

	/* The RTOS tick hook function is enabled by setting configUSE_TICK_HOOK to
	   1 in FreeRTOSConfig.h.

	   "Give" the semaphore on every 500th tick interrupt. */
	ulCount++;
	if (ulCount >= 1000UL)
	{
		/* This function is called from an interrupt context (the RTOS tick
		   interrupt),    so only ISR safe API functions can be used (those that end
		   in "FromISR()".

		   xHigherPriorityTaskWoken was initialised to pdFALSE, and will be set to
		   pdTRUE by xSemaphoreGiveFromISR() if giving the semaphore unblocked a
		   task that has equal or higher priority than the interrupted task.
		   NOTE: A semaphore is used for example purposes.  In a real application it
		   might be preferable to use a direct to task notification,
		   which will be faster and use less RAM. */
		xSemaphoreGiveFromISR(xEventSemaphore, &xHigherPriorityTaskWoken);
		ulCount = 0UL;
	}

	/* If xHigherPriorityTaskWoken is pdTRUE then a context switch should
	   normally be performed before leaving the interrupt (because during the
	   execution of the interrupt a task of equal or higher priority than the
	   running task was unblocked).  The syntax required to context switch from
	   an interrupt is port dependent, so check the documentation of the port you
	   are using.

	   In this case, the function is running in the context of the tick interrupt,
	   which will automatically check for the higher priority task to run anyway,
	   so no further action is required. */
}
/*-----------------------------------------------------------*/

/**
 * @brief Warn user if pvPortMalloc fails.
 *
 * Called if a call to pvPortMalloc() fails because there is insufficient
 * free memory available in the FreeRTOS heap.  pvPortMalloc() is called
 * internally by FreeRTOS API functions that create tasks, queues, software
 * timers, and semaphores.  The size of the FreeRTOS heap is set by the
 * configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
 *
 */
void vApplicationMallocFailedHook()
{
	configPRINTF(("ERROR: Malloc failed to allocate memory\r\n"));
}

/*-----------------------------------------------------------*/

/**
 * @brief Loop forever if stack overflow is detected.
 *
 * If configCHECK_FOR_STACK_OVERFLOW is set to 1,
 * this hook provides a location for applications to
 * define a response to a stack overflow.
 *
 * Use this hook to help identify that a stack overflow
 * has occurred.
 *
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName)
{
	portDISABLE_INTERRUPTS()
	;

	/* Loop forever */
	for (;; )
		;
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	   FreeRTOSConfig.h.

	   This function is called on each cycle of the idle task.  In this case it
	   does nothing useful, other than report the amount of FreeRTOS heap that
	   remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if (xFreeStackSpace > 100)
	{
		/* By now, the kernel has allocated everything it is going to, so
		   if there is a lot of heap remaining unallocated then
		   the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		   reduced accordingly. */
	}
}
/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t ** ppxIdleTaskTCBBuffer,
                                   StackType_t ** ppxIdleTaskStackBuffer,
                                   uint32_t * pulIdleTaskStackSize)
{
	/* If the buffers to be provided to the Idle task are declared inside this
	 * function then they must be declared static - otherwise they will be allocated on
	 * the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle
	 * task's state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t ** ppxTimerTaskTCBBuffer,
                                    StackType_t ** ppxTimerTaskStackBuffer,
                                    uint32_t * pulTimerTaskStackSize)
{
	/* If the buffers to be provided to the Timer task are declared inside this
	 * function then they must be declared static - otherwise they will be allocated on
	 * the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	 * task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*-----------------------------------------------------------*/
