/*
 * Amazon FreeRTOS MQTT Echo Demo V1.2.5
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

/**
 * @file aws_mqtt_obd2pid.c
 *
 * This sample application is based on the default 'aws_demos' sample application
 * provided with the Amazon FreeRTOS distribution for CC3220SF-Launchxl.
 *
 * After establishing connection to the AWS IoT broker, the sample creates the
 * following three tasks:
 *
 * 1) CAN TX Task: Per every loop, this tasks constructs a CAN2.0 message that is
 * transmitted to the Vehicle CAN bus via the OBDII diagnostics port the neoOBD2 PRO
 * is connected to. The PIDs requested originate from the list of PIDs configured
 * by the user in the 'aws_iot_config' file.
 *
 * 2) ISM Task: This task calls the Intrepid Security Module every loop, which allows
 * exchange of vehicle network data and other processor to processor commands between
 * the main data acquisition processor and the CC320SF application processor. It is
 * critical for this task to be free from any delay (i.e: no vTaskDelay allowed in
 * the while(1) loop).
 *
 * 3) MQTT Publish Task: This task publishes the array of 132bytes of data containing
 * all 32 OBDII PID values to the connected AWS IoT broker. The topic to which the
 * data is published to is 'obd2pro/pids'
 *
 */

/* Standard includes. */
#include <aws-can-stream.h>
#include "string.h"
#include "stdio.h"


/**
 * @brief MQTT client ID.
 *
 * It must be unique per MQTT broker.
 */
#define echoCLIENT_ID          ( ( const uint8_t * ) "CANSTREAM" )

/**
 * @brief The topic that the MQTT client both subscribes and publishes to.
 */

#define CAN_PUB_TOPIC          (( const uint8_t * ) "aws/can" )
#define SUB_TOPIC         ( ( const uint8_t * ) "alexa/command" )

#define LBYTE               0x01
#define RBYTE               0x02
#define OFFBYTE             0x00

#define NETWORK_ID          0x01
/**
 * @brief Dimension of the character array buffers used to hold data (strings in
 * this case) that is published to and received from the MQTT broker (in the cloud).
 */
#define echoMAX_DATA_LENGTH    20

/**
 * @brief A block time of 0 simply means "don't block".
 */
#define echoDONT_BLOCK         ( ( TickType_t ) 0 )

#define echoMAX_DELAY        ( ( TickType_t ) 2000 )

/*-----------------------------------------------------------*/

/**
 * @brief Implements the task that connects to and then publishes messages to the
 * MQTT broker.
 *
 * Messages are published every five seconds for a minute.
 *
 * @param[in] pvParameters Parameters passed while creating the task. Unused in our
 * case.
 */
static void prvMQTTConnectAndPublishTask( void * pvParameters );

/**
 * @brief Creates an MQTT client and then connects to the MQTT broker.
 *
 * The MQTT broker end point is set by clientcredentialMQTT_BROKER_ENDPOINT.
 *
 * @return pdPASS if everything is successful, pdFAIL otherwise.
 */
static BaseType_t prvCreateClientAndConnectToBroker( void );

/**
 * @brief Publishes the next message to the echoTOPIC_NAME topic.
 *
 * This is called every five seconds to publish the next message.
 *
 * @param[in] xMessageNumber Appended to the message to make it unique.
 */
//static void prvPublishNextMessage( BaseType_t xMessageNumber );

MQTTAgentReturnCode_t prvPublishMessage( char*, char*, size_t);

/*-----------------------------------------------------------*/

/**
 * @brief The FreeRTOS message buffer that is used to send data from the callback
 * function (see prvMQTTCallback() above) to the task that echoes the data back to
 * the broker.
 */
 MessageBufferHandle_t xCommandBuffer = NULL;
 MessageBufferHandle_t xDataBuffer = NULL;

/**
 * @ brief The handle of the MQTT client object used by the MQTT echo demo.
 */
static MQTTAgentHandle_t xMQTTHandle = NULL;

static uint8_t commandByte = 0x00;

/*-----------------------------------------------------------*/

static BaseType_t prvCreateClientAndConnectToBroker( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn = pdFAIL;
    MQTTAgentConnectParams_t xConnectParameters =
    {
        0,                                    /* The URL of the MQTT broker to connect to. */
        democonfigMQTT_AGENT_CONNECT_FLAGS,   /* Connection flags. */
        pdFALSE,                              /* Deprecated. */
        0,                                    /* Port number on which the MQTT broker is listening. Can be overridden by ALPN connection flag. */
        echoCLIENT_ID,                        /* Client Identifier of the MQTT client. It should be unique per broker. */
        0,                                    /* The length of the client Id, filled in later as not const. */
        pdFALSE,                              /* Deprecated. */
        NULL,                                 /* User data supplied to the callback. Can be NULL. */
        NULL,                                 /* Callback used to report various events. Can be NULL. */
        NULL,                                 /* Certificate used for secure connection. Can be NULL. */
        0                                     /* Size of certificate used for secure connection. */
    };

    xConnectParameters.pcURL = clientcredentialMQTT_BROKER_ENDPOINT;
    xConnectParameters.usPort = clientcredentialMQTT_BROKER_PORT;

    /* Check this function has not already been executed. */
    configASSERT( xMQTTHandle == NULL );

    /* The MQTT client object must be created before it can be used.  The
     * maximum number of MQTT client objects that can exist simultaneously
     * is set by mqttconfigMAX_BROKERS. */
    xReturned = MQTT_AGENT_Create( &xMQTTHandle );

    if( xReturned == eMQTTAgentSuccess )
    {
        /* Fill in the MQTTAgentConnectParams_t member that is not const,
         * and therefore could not be set in the initializer (where
         * xConnectParameters is declared in this function). */
        xConnectParameters.usClientIdLength = ( uint16_t ) strlen( ( const char * ) echoCLIENT_ID );

        /* Connect to the broker. */
        configPRINTF( ( "MQTT echo attempting to connect to %s.\r\n", clientcredentialMQTT_BROKER_ENDPOINT ) );
        xReturned = MQTT_AGENT_Connect( xMQTTHandle,
                                        &xConnectParameters,
                                        democonfigMQTT_ECHO_TLS_NEGOTIATION_TIMEOUT );

        if( xReturned != eMQTTAgentSuccess )
        {
            /* Could not connect, so delete the MQTT client. */
            ( void ) MQTT_AGENT_Delete( xMQTTHandle );
            configPRINTF( ( "ERROR:  MQTT echo failed to connect.\r\n" ) );
        }
        else
        {
            configPRINTF( ( "MQTT echo connected.\r\n" ) );
            xReturn = pdPASS;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/
static MQTTBool_t prvMQTTCallback( void * pvUserData,
                                   const MQTTPublishData_t * const pxPublishParameters )
{
    char cBuffer[ echoMAX_DATA_LENGTH ];
    uint32_t ulBytesToCopy = ( echoMAX_DATA_LENGTH - 1 ); /* Bytes to copy initialized to ensure it fits in the buffer. One place is left for NULL terminator. */

    /* Remove warnings about the unused parameters. */
    ( void ) pvUserData;

    /* Don't expect the callback to be invoked for any other topics. */
    configASSERT( ( size_t ) ( pxPublishParameters->usTopicLength ) == strlen( ( const char * ) SUB_TOPIC ) );
    configASSERT( memcmp( pxPublishParameters->pucTopic, SUB_TOPIC, ( size_t ) ( pxPublishParameters->usTopicLength ) ) == 0 );

    /* THe ulBytesToCopy has already been initialized to ensure it does not copy
     * more bytes than will fit in the buffer.  Now check it does not copy more
     * bytes than are available. */
    if( pxPublishParameters->ulDataLength < ulBytesToCopy )
    {
        ulBytesToCopy = pxPublishParameters->ulDataLength;
    }

    /* Set the buffer to zero and copy the data into the buffer to ensure
     * there is a NULL terminator and the buffer can be accessed as a
     * string. */
    memset( cBuffer, 0x00, sizeof( cBuffer ) );
    memcpy( cBuffer, pxPublishParameters->pvData, ( size_t ) ulBytesToCopy );

    ( void ) xMessageBufferSend( xCommandBuffer, cBuffer, ( size_t ) ulBytesToCopy + ( size_t ) 1, echoDONT_BLOCK );

    /* The data was copied into the FreeRTOS message buffer, so the buffer
     * containing the data is no longer required.  Returning eMQTTFalse tells the
     * MQTT agent that the ownership of the buffer containing the message lies with
     * the agent and it is responsible for freeing the buffer. */
    return eMQTTFalse;
}

 MQTTAgentReturnCode_t prvPublishMessage( char *cDataBuffer, char *cTopicName, size_t len )
{
    MQTTAgentPublishParams_t xPublishParameters;
    MQTTAgentReturnCode_t xReturned;

    /* Check this function is not being called before the MQTT client object has
     * been created. */
    configASSERT( xMQTTHandle != NULL );

    memset( &( xPublishParameters ), 0x00, sizeof( xPublishParameters ) );
    xPublishParameters.pucTopic = (const uint8_t*)cTopicName;
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) cTopicName );
    xPublishParameters.ulDataLength = ( uint32_t ) len;
    xPublishParameters.xQoS = eMQTTQoS1;

    xReturned = MQTT_AGENT_Publish( xMQTTHandle,
                                    &( xPublishParameters ),
                                    democonfigMQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "Echo successfully published '%s'\r\n", cDataBuffer ) );
    }
    else
    {
        configPRINTF( ( "ERROR:  Echo failed to publish '%s'\r\n", cDataBuffer ) );
    }

    /* Remove compiler warnings in case configPRINTF() is not defined. */
    return xReturned;
}

/*-----------------------------------------------------------*/

static void prvCANTxTask(void* pvParams)
{
    (void) pvParams;
    GenericMessage msg = {0};
    unsigned char pidTotalNum = strlen((char*)pidNumberLookup);

    msg.iID = 0x600;
    msg.iNetwork = NETWORK_ID;
    msg.iNumDataBytes = 8;
    //msg.btData[0] = 0x00;
    msg.btData[1] = 0x00;
    msg.btData[2] = 0x00;
    msg.btData[3] = 0xc8;
    msg.btData[4] = 0x00;
    msg.btData[5] = 0x2c;
    msg.btData[6] = 0x00;
    msg.btData[7] = 0x00;

    while (1)
    {
        msg.btData[0] = (commandByte);
        GenericMessageTransmit(&msg);
        vTaskDelay(pdMS_TO_TICKS(400));
        msg.btData[0] = OFFBYTE;
        GenericMessageTransmit(&msg);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

/*-----------------------------------------------------------*/

static void prvRunISMTask(void* pvParams)
{
    (void) pvParams;

    while (1)
    {
        icsISM_Main();
    }
}


/*-----------------------------------------------------------*/

static BaseType_t prvSubscribe( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn;
    MQTTAgentSubscribeParams_t xSubscribeParams;

    xSubscribeParams.pucTopic = SUB_TOPIC;
    xSubscribeParams.pvPublishCallbackContext = NULL;
    xSubscribeParams.pxPublishCallback = prvMQTTCallback;
    xSubscribeParams.usTopicLength = ( uint16_t ) strlen( ( const char * ) SUB_TOPIC );
    xSubscribeParams.xQoS = eMQTTQoS1;

    /* Subscribe to the topic. */
    xReturned = MQTT_AGENT_Subscribe( xMQTTHandle,
                                      &xSubscribeParams,
                                      democonfigMQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "MQTT Echo demo subscribed to %s\r\n", SUB_TOPIC ) );
        xReturn = pdPASS;
    }
    else
    {
        configPRINTF( ( "ERROR:  MQTT Echo demo could not subscribe to %s\r\n", SUB_TOPIC ) );
        xReturn = pdFAIL;
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static void prvEchoCANTask(void* pvParams)
{
    (void) pvParams;
    MQTTAgentReturnCode_t xReturned;
    char cDataBuffer[echoMAX_DATA_LENGTH] = {0};
    size_t xBytesReceived;

    configASSERT( xDataBuffer != NULL );

    while (1)
    {

        xBytesReceived = xMessageBufferReceive(xDataBuffer, cDataBuffer,
                                               STREAM_DATA_LENGTH,
                                               portMAX_DELAY);
        if (xBytesReceived > 0)
        {
            xReturned = prvPublishMessage(cDataBuffer, (char*)CAN_PUB_TOPIC, xBytesReceived );

            if (xReturned != eMQTTAgentSuccess){
                configPRINTF(( "Published on CAN topic failed \r\n" ));
            }
        } else {
                configPRINTF(( "ERROR:  Received 0 bytes for  CAN publish\r\n" ));
        }
    }
}
/*-----------------------------------------------------------*/

static void prvMQTTConnectAndPublishTask( void * pvParameters )
{
    BaseType_t xReturned;
    TaskHandle_t xMqttPubTask = NULL;

    /* Avoid compiler warnings about unused parameters. */
    ( void ) pvParameters;

    /* Create the MQTT client object and connect it to the MQTT broker. */
    xReturned = prvCreateClientAndConnectToBroker();

    if( xReturned == pdPASS )
    {
        /* Set the LED to indicate the WiFi is online */
        ControlMainChipLEDColor(COLOR_WIFI_ONLINE);

        /* Subscribe to the echo topic. */
        xReturned = prvSubscribe();

        if( xReturned == pdPASS )
        {
        /* Create the MQTT Publish Task */
           xReturned = xTaskCreate( prvEchoCANTask,         /* The function that implements the demo task. */
                         "CANEcho",                         /* The name to assign to the task being created. */
                         1024,                              /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                         NULL,                              /* The task parameter is not being used. */
                         tskIDLE_PRIORITY,                  /* Runs at the lowest priority. */
                         &( xMqttPubTask ) );               /* Not storing the task's handle. */

            if( xReturned != pdPASS )
            {
                /* The task could not be created because there was insufficient FreeRTOS
                 * heap available to create the task's data structures and/or stack. */
                configPRINTF( ( "CAN Echo task could not be created - out of heap space?\r\n" ) );
            }
        } else {
            configPRINTF( ( "ERROR:  MQTT Echo demo could not subscribe to %s\r\n", SUB_TOPIC ) );
        }
    }
    else
    {
        configPRINTF( ( "MQTT echo test could not connect to broker.\r\n" ) );
    }

    if( xReturned == pdPASS )
    {
        while(1)
        {
            vTaskDelay( pdMS_TO_TICKS( 5000UL ) );
        }
    }
}
/*-----------------------------------------------------------*/

void vStartMQTTEchoDemo( void )
{
    //TaskHandle_t xISMTask = NULL;
    configPRINTF( ( "Creating MQTT Echo Task...\r\n" ) );

    xDataBuffer = xMessageBufferCreate( (size_t) STREAM_DATA_LENGTH + sizeof( size_t ) );

    configASSERT( xCommandBuffer );
    ControlMainChipLEDColor(COLOR_WIFI_OFFLINE);
    ( void ) xTaskCreate( prvMQTTConnectAndPublishTask,
                          "MQTTEcho",
                          democonfigMQTT_ECHO_TASK_STACK_SIZE,
                          NULL,
                          1,
                          NULL );

    (void) xTaskCreate(prvRunISMTask,
                       "ISM",
                       democonfigISM_TASK_STACK_SIZE,
                       NULL,
                       democonfigISM_TASK_PRIORITY,
                       NULL);
}
/*-----------------------------------------------------------*/
