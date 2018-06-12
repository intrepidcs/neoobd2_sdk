/*
 * Amazon FreeRTOS V1.2.5
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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
 
 /*
 * Copyright (c) 2018 Intrepid Control Systems, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Debug setup instructions:
 * 1) Open the debug configuration dialog.
 * 2) Go to the target tab.
 * 3) Ensure that check box 'Reset target on a connect' is selected.
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* EDIT THIS FILE:
 * Wifi SSID, password & security settings,
 * AWS endpoint, certificate, private key & thing name. */
#include "aws_clientcredential.h"

/* Demo priorities & stack sizes. */
#include "aws_demo_config.h"

/* FreeRTOS header files. */
#include "FreeRTOS.h"
#include "task.h"

/* WiFi Interface files. */
#include "aws_wifi.h"

/* Demo files. */
#include "aws_logging_task.h"
#include "aws_demo_runner.h"
#include "aws_system_init.h"
#include "aws_dev_mode_key_provisioning.h"

/* CC3220SF board file. */
#include "Board.h"

/* Intrepid Control Systems library */
#include "obd2pro_wifi_cc32xx.h"
#include "obd2pro_wifi_cc32xx_ism.h"
#include "obd2pro_config_parser.h"

extern void Spy_EveryLoop(unsigned int);
extern void Spy_BeforeStarted(void);
extern void Spy_Started(void);
extern void Spy_Main(void);
extern void Spy_ErrorFrame(int, int, int, int);
extern void Spy_ErrorState(int, int, int, int);

#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 15 )

void vApplicationDaemonTaskStartupHook( void );

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
int main( void )
{
    /* Call board init functions. */
    Board_initGeneral();

    /* Start logging task. */
    xLoggingTaskInitialize( democonfigTASKSTACKSIZE,
                            tskIDLE_PRIORITY,
                            mainLOGGING_MESSAGE_QUEUE_LENGTH );

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    return( 0 );
}

/*-----------------------------------------------------------*/

/**
 * @brief Initializes the IntrepidCS Security Module, which provides
 * receive & transmit access to Vehicle Network data supported by
 * neoOBD2 PRO (CAN/CANFD, SWCAN, LIN, and Ethernet)
 */
void vInitISMLib( void )
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
 * @brief Completes board, Wifi, and AWS system initializations
 * and creates the test runner task.
 *
 * This task is run when configUSE_DAEMON_TASK_STARTUP_HOOK = 1.
 */
void vApplicationDaemonTaskStartupHook( void )
{
    UART_Handle xtUartHndl;
    WIFINetworkParams_t xNetworkParams;

    Board_initGPIO();
    Board_initSPI(); /* AN:  Is the SPI actually used? */

    /* Configure the UART. */
    xtUartHndl = InitTerm();
    UART_control( xtUartHndl, UART_CMD_RXDISABLE, NULL );

    /* Initialize WiFi module, start simple link device. */
    WIFI_On();

    /* Parse the application configuration file. */
    ParseConfigFile();
    clientcredentialMQTT_BROKER_ENDPOINT = (char*)&mqttBrokerEndpoint[0];
    clientcredentialMQTT_BROKER_PORT = mqttBrokerPort;
    clientcredentialGREENGRASS_DISCOVERY_PORT = greengrassDiscoveryPort;
    clientcredentialWIFI_SSID = (char*)&wifiSSID[0];
    clientcredentialWIFI_PASSWORD = (char*)&wifiPassword[0];
    clientcredentialWIFI_SECURITY = wifiSecurityType;
    clientcredentialCLIENT_CERTIFICATE_PEM = (char*)&clientCertificate[0];
    clientcredentialCLIENT_PRIVATE_KEY_PEM = (char*)&clientPrivateKey[0];
    clientcredentialCLIENT_CERTIFICATE_LENGTH = strlen((char*)clientCertificate) + 1;
    clientcredentialCLIENT_PRIVATE_KEY_LENGTH = strlen((char*)clientPrivateKey) + 1;


    /* A simple example to demonstrate key and certificate provisioning in
     * flash using PKCS#11 interface. This should be replaced
     * by production ready key provisioning mechanism. */
    vDevModeKeyProvisioning();

    /* Initialize the AWS library system. */
    BaseType_t xResult = SYSTEM_Init();
    configASSERT( xResult == pdPASS );

    /* Initialize Network params. */
    xNetworkParams.pcSSID = clientcredentialWIFI_SSID;
    xNetworkParams.ucSSIDLength = strlen ( clientcredentialWIFI_SSID );
    xNetworkParams.pcPassword = clientcredentialWIFI_PASSWORD;
    xNetworkParams.ucPasswordLength = strlen( clientcredentialWIFI_PASSWORD );
    xNetworkParams.xSecurity = (WIFISecurity_t)clientcredentialWIFI_SECURITY;

    /* Connect to WIFI. */
    WIFI_ConnectAP( &xNetworkParams );

    /* Initialize IntrepidCS Library. */
    vInitISMLib();

    /* Start the application tasks. */
    DEMO_RUNNER_RunDemos();
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
    configPRINTF( ( "ERROR: Malloc failed to allocate memory\r\n" ) );
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
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
    portDISABLE_INTERRUPTS();

    /* Loop forever */
    for( ; ; );
}

/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

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
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

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

/**
 * @brief Socket event handler function.
 *
 * TI SimpleLink driver expects this function to be defined to notify
 * various socket events. The actual socket event handler funtion is
 * defined by the secure sockets layer in the file lib\secure_sockets\
 * portable\ti\cc3220_launchpad\aws_secure_sockets.c. If the user chooses
 * not to download secure sockets library, this weak definition ensures
 * that there are no linker errors.
 *
 * @param  pSlSockEvent Pointer to a structure containing the socket event
 * and the relevant data.
 *
 * @see SlSockEvent_t.
 */
void portWEAK_SYMBOL SimpleLinkSockEventHandler( void )
{
    configPRINTF( ( "Call of stub socket event handler.\r\n" ) );
}
