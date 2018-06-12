/*
Copyright (c) 2018 Intrepid Control Systems, Inc.
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef APPLICATION_CODE_ICS_CODE_OBD2PRO_CONFIG_PARSER_H_
#define APPLICATION_CODE_ICS_CODE_OBD2PRO_CONFIG_PARSER_H_

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/* Maximum number of OBDII PIDs configurable for this sample application */
#define MAX_NUM_PIDS            (32)

/* The maximum size of the entire configuration file */
#define MAX_FILE_BUFFER_SIZE    (12*1024)

/* Configuration parameters stored in SRAM */
extern unsigned char entireFileContent[MAX_FILE_BUFFER_SIZE];
extern unsigned char pidNumLookupTable[MAX_NUM_PIDS];
extern unsigned char clientCertificate[4096];
extern unsigned char clientPrivateKey[4096];
extern unsigned char mqttBrokerEndpoint[64];
extern unsigned char thingName[64];
extern unsigned int mqttBrokerPort;
extern unsigned int greengrassDiscoveryPort;
extern unsigned char wifiSSID[64];
extern unsigned char wifiPassword[64];
extern unsigned char wifiSecurityType;

void ReadConfigFileIntoArray(void);

int CheckDuplicatePIDNumber(unsigned char pidToAdd);

int GetPIdNumbers(char* currentFilePtr);

int GetClientCertificate(char* currentFilePtr);

int GetClientPrivateKey(char* currentFilePtr);

int GetMqttBrokerEndpoint(char* currentFilePtr);

int GetThingName(char* currentFilePtr);

int GetMqttBrokerPortNumber(char* currentFilePtr);

int GetGreengrassDiscoveryPortNumber(char* currentFilePtr);

int GetWiFiSSID(char* currentFilePtr);

int GetWiFiPassword(char* currentFilePtr);

int GetWiFiSecurityType(char* currentFilePtr);

void ParseConfigFile(void);

#endif /* APPLICATION_CODE_ICS_CODE_OBD2PRO_CONFIG_PARSER_H_ */
