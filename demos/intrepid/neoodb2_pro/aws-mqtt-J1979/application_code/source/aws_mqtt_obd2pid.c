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
#include <aws_mqtt_obd2pid.h>
#include "string.h"
#include "stdio.h"


/**
 * @brief MQTT client ID.
 *
 * It must be unique per MQTT broker.
 */
#define echoCLIENT_ID          ( ( const uint8_t * ) "OBD2PIDAPP" )

/**
 * @brief The topic that the MQTT client both subscribes and publishes to.
 */
#define echoTOPIC_NAME         ( ( const uint8_t * ) "obd2pro/pids" )

/**
 * @brief The string appended to messages that are echoed back to the MQTT broker.
 *
 * It is also used to detect if a received message has already been acknowledged.
 */
#define echoACK_STRING         ( ( const char * ) " ACK" )

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

static MQTTAgentReturnCode_t prvPublishOBDIIMessage( char*, char* );

/*-----------------------------------------------------------*/

/**
 * @brief The FreeRTOS message buffer that is used to send data from the callback
 * function (see prvMQTTCallback() above) to the task that echoes the data back to
 * the broker.
 */
 MessageBufferHandle_t xPIDResponseBuffer = NULL;

/**
 * @ brief The handle of the MQTT client object used by the MQTT echo demo.
 */
static MQTTAgentHandle_t xMQTTHandle = NULL;

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

extern unsigned char pidValueArray[PUBLISH_OBD_LENGTH];
static MQTTAgentReturnCode_t prvPublishOBDIIMessage( char *cDataBuffer, char *cTopicName )
{
    MQTTAgentPublishParams_t xPublishParameters;
    MQTTAgentReturnCode_t xReturned;

    /* Check this function is not being called before the MQTT client object has
     * been created. */
    configASSERT( xMQTTHandle != NULL );

    /* Setup the publish parameters. */
    memset( &( xPublishParameters ), 0x00, sizeof( xPublishParameters ) );
    xPublishParameters.pucTopic = (const uint8_t*)cTopicName;
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) cTopicName );
    xPublishParameters.ulDataLength = ( uint32_t ) 8;
    xPublishParameters.xQoS = eMQTTQoS1;

    /* Publish the message. */
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
    unsigned char i;
    unsigned char pidTotalNum = strlen((char*)pidNumberLookup);

    msg.iID = 0x7DF;
    msg.iNetwork = 1;
    msg.iNumDataBytes = 8;
    msg.btData[0] = 0x02;
    msg.btData[1] = 0x01;
    msg.btData[3] = 0x55;
    msg.btData[4] = 0x55;
    msg.btData[5] = 0x55;
    msg.btData[6] = 0x55;
    msg.btData[7] = 0x55;

    if (pidTotalNum > MAX_NUM_PIDS)
    {
        pidTotalNum = MAX_NUM_PIDS;
    }

    while (1)
    {
        for (i = 0; i < pidTotalNum; i++)
        {
            msg.btData[2] = pidNumberLookup[i];
            GenericMessageTransmit(&msg);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
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

static void prvRunMqttPubTask(void* pvParams)
{
    (void) pvParams;
    MQTTAgentReturnCode_t xReturned;
    char cDataBuffer[ PID_BUFFER_LENGTH ] = {0};
    size_t xBytesReceived;
    configASSERT( xPIDResponseBuffer != NULL );
    char cTopicName[echoMAX_DATA_LENGTH] = {0};

    configASSERT( xMQTTHandle != NULL );

    while (1)
    {
      xBytesReceived = xMessageBufferReceive( xPIDResponseBuffer,
                                              cDataBuffer,
                                              (size_t) PUBLISH_OBD_LENGTH,
                                              portMAX_DELAY );
        /* Publish the 132-byte data containing 32 OBDII PIDs */
      if(xBytesReceived == PUBLISH_OBD_LENGTH) {
          (void ) snprintf(cTopicName, echoMAX_DATA_LENGTH, "%s/%d",(char*) echoTOPIC_NAME, (int) cDataBuffer[2]);
                  xReturned = prvPublishOBDIIMessage(cDataBuffer, cTopicName);
                  if (xReturned == eMQTTAgentSuccess)
        {
                      configPRINTF( ( "Published data '%s' on topic '%s' \r\n", cDataBuffer, cTopicName ) );

                  } else {
                      configPRINTF( ( "ERROR:  Could not publish OBD Frame \n'%x'\r\n", cDataBuffer ) );
            // MQTT publish failed. No error handler provided.
        }

      } else {
          configPRINTF( ( "ERROR:  Received 0 bytes for publish\r\n" ) );
      }
    }
}

static void prvMQTTConnectAndPublishTask( void * pvParameters )
{
    BaseType_t xReturned;
    TaskHandle_t xISMTask = NULL;
    TaskHandle_t xCANTxTask = NULL;
    TaskHandle_t xMqttPubTask = NULL;

    /* Avoid compiler warnings about unused parameters. */
    ( void ) pvParameters;

    /* Create the MQTT client object and connect it to the MQTT broker. */
    xReturned = prvCreateClientAndConnectToBroker();

    if( xReturned == pdPASS )
    {
        /* Set the LED to indicate the WiFi is online */
        ControlMainChipLEDColor(COLOR_WIFI_ONLINE);

        /* Create the CAN Transmit Task */
        xReturned = xTaskCreate( prvCANTxTask,                          /* The function that implements the demo task. */
                                 "CANTxTask",                           /* The name to assign to the task being created. */
                                 1024,                                  /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                                 NULL,                                  /* The task parameter is not being used. */
                                 tskIDLE_PRIORITY,                      /* Runs at the lowest priority. */
                                 &( xCANTxTask ) );                     /* Not storing the task's handle. */

        if( xReturned != pdPASS )
        {
            /* The task could not be created because there was insufficient FreeRTOS
             * heap available to create the task's data structures and/or stack. */
            configPRINTF( ( "CAN Tx task could not be created - out of heap space?\r\n" ) );
        }

        /* Create the IntrepidCS Security Module Task */
        xReturned = xTaskCreate( prvRunISMTask,                         /* The function that implements the demo task. */
                                 "ISMTask",                             /* The name to assign to the task being created. */
                                 3000,                                  /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                                 NULL,                                  /* The task parameter is not being used. */
                                 tskIDLE_PRIORITY,                      /* Runs at the lowest priority. */
                                 &( xISMTask ) );                       /* Not storing the task's handle. */

        if( xReturned != pdPASS )
        {
            /* The task could not be created because there was insufficient FreeRTOS
             * heap available to create the task's data structures and/or stack. */
            configPRINTF( ( "Intrepid Secure Module task could not be created - out of heap space?\r\n" ) );
        }

        /* Create the MQTT Publish Task */
        xReturned = xTaskCreate( prvRunMqttPubTask,                     /* The function that implements the demo task. */
                                 "MqttPubTask",                         /* The name to assign to the task being created. */
                                 1024,                                  /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                                 NULL,                                  /* The task parameter is not being used. */
                                 tskIDLE_PRIORITY,                      /* Runs at the lowest priority. */
                                 &( xMqttPubTask ) );                   /* Not storing the task's handle. */

        if( xReturned != pdPASS )
        {
            /* The task could not be created because there was insufficient FreeRTOS
             * heap available to create the task's data structures and/or stack. */
            configPRINTF( ( "MQTT Publish task could not be created - out of heap space?\r\n" ) );
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
    configPRINTF( ( "Creating MQTT Echo Task...\r\n" ) );

    /* Create the message buffer used to pass strings from the MQTT callback
     * function to the task that echoes the strings back to the broker.  The
     * message buffer will only ever have to hold one message as messages are only
     * published every 5 seconds.  The message buffer requires that there is space
     * for the message length, which is held in a size_t variable. */
    xPIDResponseBuffer = xMessageBufferCreate( ( size_t ) PUBLISH_OBD_LENGTH + sizeof( size_t ) );
    configASSERT( xPIDResponseBuffer );

    /* Set the LED to indicate the WiFi is offline */
    ControlMainChipLEDColor(COLOR_WIFI_OFFLINE);

    /* Create the task that publishes messages to the MQTT broker every five
     * seconds.  This task, in turn, creates the task that echoes data received
     * from the broker back to the broker. */
    ( void ) xTaskCreate( prvMQTTConnectAndPublishTask,        /* The function that implements the demo task. */
                          "MQTTEcho",                          /* The name to assign to the task being created. */
                          democonfigMQTT_ECHO_TASK_STACK_SIZE, /* The size, in WORDS (not bytes), of the stack to allocate for the task being created. */
                          NULL,                                /* The task parameter is not being used. */
                          1,   /* The priority at which the task being created will run. */
                          NULL );                              /* Not storing the task's handle. */
}
/*-----------------------------------------------------------*/
