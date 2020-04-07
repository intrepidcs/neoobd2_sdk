/*
 * Copyright (c) 2017-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== main_freertos.c ========
 */

/* Driver configuration */
#include <ti/display/Display.h>
#include <ti/drivers/Board.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/net/wifi/simplelink.h>

#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

//#include "ti_drivers_config.h"
#include "aws_iot_config.h"
#include "network.h"

// ISM library includes
#include "obd2lc_wifi_cc32xx_ism.h"
#include "obd2lc_wifi_cc32xx.h"

// ISM library forward protos
extern void Spy_EveryLoop(unsigned int);
extern void Spy_BeforeStarted(void);
extern void Spy_Started(void);
extern void Spy_Main(void);
extern void Spy_ErrorFrame(int, int, int, int);
extern void Spy_ErrorState(int, int, int, int);

Display_Handle display;

extern void runAWSClient(void);

/*
 *  ======== checkCerts ========
 *  Utility function to check the given certificate file exists
 */
static int checkCerts(char *certName)
{
    SlFsFileInfo_t fsFileInfo;
    int status = 0;

    if (sl_FsGetInfo((const unsigned char *)certName, 0, &fsFileInfo) ==
            SL_ERROR_FS_FILE_NOT_EXISTS) {
        status = -1;
    }

    return (status);
}

/*
 * ======== ismThreadFxn ========
 */
void *ismThreadFxn(void *arg0)
{
    (void) arg0;

    while (1)//lint !e716 while1
    {
        icsISM_Main();
    }
}

/*
 *  ======== awsThreadFxn ========
 */
void *awsThreadFxn(void *arg0)
{
    SlNetCfgIpV4Args_t ipAddr;
    uint16_t           len = sizeof(ipAddr);
    uint16_t           dhcpIsOn;

    Display_printf(display, 0, 0, "Starting the AWS IoT example application\n");

    /* Wait for an IP address, initialize the socket layer and get the time */
    Network_startup();

    /* Retrieve & print the IP address */
    sl_NetCfgGet(SL_NETCFG_IPV4_STA_ADDR_MODE, &dhcpIsOn, &len,
            (unsigned char *)&ipAddr);
    Display_printf(display, 0, 0,
            "CC32XX has connected to AP and acquired an IP address.\n");
    Display_printf(display, 0, 0, "IP Address: %ld.%ld.%ld.%ld\n",
            SL_IPV4_BYTE(ipAddr.Ip, 3), SL_IPV4_BYTE(ipAddr.Ip, 2),
            SL_IPV4_BYTE(ipAddr.Ip, 1), SL_IPV4_BYTE(ipAddr.Ip, 0));

    /* Check the Certificate Files */
    if (checkCerts(AWS_IOT_ROOT_CA_FILENAME) < 0) {
        Display_printf(display, 0, 0, "Certificate file %s does not exist",
                AWS_IOT_ROOT_CA_FILENAME);
    }

    if (checkCerts(AWS_IOT_CERTIFICATE_FILENAME) < 0) {
        Display_printf(display, 0, 0, "Certificate file %s does not exist",
                AWS_IOT_CERTIFICATE_FILENAME);
    }

    if (checkCerts(AWS_IOT_PRIVATE_KEY_FILENAME) < 0) {
        Display_printf(display, 0, 0, "Certificate file %s does not exist",
                AWS_IOT_PRIVATE_KEY_FILENAME);
    }

    runAWSClient();

    return (NULL);
}

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    pthread_attr_t pthreadAttrs;
    pthread_t slThread;
    pthread_t awsThread;
    pthread_t ismThread;
    int status;

    Board_init();
    GPIO_init();
    SPI_init();
    Display_init();
    Network_init();
	
	/* Initialize the ISM library*/
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

    /* Configure the LED and button pins */
#if 0
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
#endif

    /* Open the Display for output */
    display = Display_open(Display_Type_UART, NULL);
    if (display == NULL) {
        /* Failed to open the Display driver */
        while (1);
    }

    /* Create the sl_Task thread */
    pthread_attr_init(&pthreadAttrs);

    status = pthread_attr_setstacksize(&pthreadAttrs, 2048);
    if (status != 0) {
        /* Error setting stack size */
        while (1);
    }

    status = pthread_create(&slThread, &pthreadAttrs, sl_Task, NULL);
    if (status != 0) {
        /* Failed to create sl_Task thread */
        while (1);
    }

    /* Create the ISM thread */
    status = pthread_attr_setstacksize(&pthreadAttrs, 16478);
    if (status != 0) {
        /* Error setting stack size */
        while (1);
    }

    status = pthread_create(&ismThread, &pthreadAttrs, ismThreadFxn, NULL);
    if (status != 0) {
        /* Failed to create ISM thread */
        while (1);
    }

    /* Create the AWS thread */
    status = pthread_attr_setstacksize(&pthreadAttrs, 4096);
    if (status != 0) {
        /* Error setting stack size */
        while (1);
    }

    status = pthread_create(&awsThread, &pthreadAttrs, awsThreadFxn, NULL);
    if (status != 0) {
        /* Failed to create AWS thread */
        while (1);
    }

    pthread_attr_destroy(&pthreadAttrs);

    /*  To enable low power mode, uncomment the following line.
     *  Please be aware that your JTAG connection will be
     *  dropped when entering low power mode. You must reset the
     *  board in order to re-establish your JTAG connection.
     */
    /* Power_enablePolicy(); */

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}

/*
 *  ======== vApplicationMallocFailedHook ========
 *
 *! \brief Application defined malloc failed hook
 *!
 *! \param  none
 *!
 *! \return none
 *!
 */
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1);
}

/*
 *  ======== vApplicationStackOverflowHook ========
 *
 *! \brief Application defined stack overflow hook
 *!
 *! \param  none
 *!
 *! \return none
 *!
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    /* Handle FreeRTOS Stack Overflow */
    while(1);
}
