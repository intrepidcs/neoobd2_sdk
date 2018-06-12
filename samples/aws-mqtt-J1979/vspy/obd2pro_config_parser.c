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

#include "obd2pro_config_parser.h"
#include "simplelink.h"

unsigned char entireFileContent[MAX_FILE_BUFFER_SIZE] = {0};
unsigned char pidNumLookupTable[MAX_NUM_PIDS] = {0};
unsigned char clientCertificate[4096] = {0};
unsigned char clientPrivateKey[4096] = {0};
unsigned char mqttBrokerEndpoint[64] = {0};
unsigned char thingName[64] = {0};
unsigned int mqttBrokerPort = 0;
unsigned int greengrassDiscoveryPort = 0;
unsigned char wifiSSID[64] = {0};
unsigned char wifiPassword[64] = {0};
unsigned char wifiSecurityType = {0};

void ReadConfigFileIntoArray(void)
{
    SlFsFileInfo_t fileInfo;
    long handle = sl_FsOpen("aws_iot_config", SL_FS_READ, NULL);
    if (handle >= 0)
    {
        _i16 ret = sl_FsGetInfo("aws_iot_config", NULL, &fileInfo);

        memset(entireFileContent, 0, MAX_FILE_BUFFER_SIZE);
        if (ret >= 0)
        {
            sl_FsRead(handle, 0, (unsigned char*)entireFileContent, fileInfo.Len);
        }
    }
}

int CheckDuplicatePIDNumber(unsigned char pidToAdd)
{
    unsigned int i;
    unsigned char hasDuplicate = 0;
    for (i = 0; i < MAX_NUM_PIDS; i++)
    {
        if (pidNumLookupTable[i] == pidToAdd)
        {
            hasDuplicate = 1;
            break;
        }
    }

    return (hasDuplicate ? 1 : 0);
}

int GetPIdNumbers(char* currentFilePtr)
{
    char pidNumberScratch[4] = { 0 };
    unsigned char numPIDsSearched = 0;
    unsigned char numPIDsFound = 0;
    unsigned int i = 0;
    unsigned char pidToAdd = 0;

    // seek until '{' is found
    while (*currentFilePtr++ != '{') { ; }
    // skip spaces
    while (*currentFilePtr == ' ' ||
        *currentFilePtr == '\n' ||
        *currentFilePtr == '\t' ||
        *currentFilePtr == '\r')
    {
        currentFilePtr++;
    }
    // get PID numbers until we reach the end
    while (numPIDsSearched < 32)
    {
        // get the next PID number
        while (*currentFilePtr != ',' && *currentFilePtr != '}')
        {
            // skip spaces, new lines, and tabs
            if (*currentFilePtr != ' ' && *currentFilePtr != '\r' && *currentFilePtr != '\n' && *currentFilePtr != '\t')
            {
                pidNumberScratch[i++] = *currentFilePtr;
            }
            currentFilePtr++;
        }
        // check duplicate
        pidToAdd = atoi(pidNumberScratch);
        if (!CheckDuplicatePIDNumber(pidToAdd))
        {
            // save the PID number found
            pidNumLookupTable[numPIDsFound] = pidToAdd;
            memset(pidNumberScratch, 0, sizeof(pidNumberScratch));
            // increment PID found count
            numPIDsFound++;
        }
        // skip spaces
        while (*currentFilePtr == ' ') { currentFilePtr++; }
        // reset PID number char count
        i = 0;
        // Increment PID searched count
        numPIDsSearched++;
        // check if we reached the end
        if (*currentFilePtr == '}')
        {
            break;
        }
        // Go to next char
        currentFilePtr++;
    }

    return numPIDsFound;
}

int GetClientCertificate(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the certificate
    while (*currentFilePtr != ';')
    {
        // until the end of a line until a '\\' is found
        while (*currentFilePtr != '\\')
        {
            clientCertificate[i++] = *currentFilePtr;
            currentFilePtr++;
        }
        // skip until start of next line
        while (*currentFilePtr++ != '"') { ; }
        // check the end ';'
        if (*currentFilePtr == ';')
        {
            clientCertificate[i++] = '\n';
            break;
        }
        clientCertificate[i++] = '\n';
        while (*currentFilePtr++ != '"') { ; }
    }

    return 1;
}

int GetClientPrivateKey(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the certificate
    while (*currentFilePtr != ';')
    {
        // until the end of a line until a '\\' is found
        while (*currentFilePtr != '\\')
        {
            clientPrivateKey[i++] = *currentFilePtr;
            currentFilePtr++;
        }
        // skip until start of next line
        while (*currentFilePtr++ != '"') { ; }
        // check the end ';'
        if (*currentFilePtr == ';')
        {
            clientPrivateKey[i++] = '\n';
            break;
        }
        clientPrivateKey[i++] = '\n';
        while (*currentFilePtr++ != '"') { ; }
    }

    return 1;
}

int GetMqttBrokerEndpoint(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the mqtt broker endpoint name
    while (*currentFilePtr != ';')
    {
        if (*currentFilePtr != '"')
            mqttBrokerEndpoint[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;

    return 1;
}

int GetThingName(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the thing name
    while (*currentFilePtr != '"')
    {
        thingName[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;

    return 1;
}

int GetMqttBrokerPortNumber(char* currentFilePtr)
{
    unsigned int i = 0;
    char mqttBrokerPortNumberScratch[8] = { 0 };

    // seek until no space is found
    while (*currentFilePtr++ != ' ') { ; }
    // get the port number
    while (*currentFilePtr != ' ' && *currentFilePtr != '\n')
    {
        mqttBrokerPortNumberScratch[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;
    mqttBrokerPort = atoi(mqttBrokerPortNumberScratch);
    return 1;
}

int GetGreengrassDiscoveryPortNumber(char* currentFilePtr)
{
    unsigned int i = 0;
    char greengrassPortNumberScratch[8] = { 0 };

    // seek until no space is found
    while (*currentFilePtr++ != ' ') { ; }
    // get the port number
    while (*currentFilePtr != ' ' && *currentFilePtr != '\n')
    {
        greengrassPortNumberScratch[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;
    greengrassDiscoveryPort = atoi(greengrassPortNumberScratch);
    return 1;
}

int GetWiFiSSID(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the thing name
    while (*currentFilePtr != '"')
    {
        wifiSSID[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;

    return 1;
}

int GetWiFiPassword(char* currentFilePtr)
{
    unsigned int i = 0;

    // seek until '"' is found
    while (*currentFilePtr++ != '"') { ; }
    // get the thing name
    while (*currentFilePtr != '"')
    {
        wifiPassword[i++] = *currentFilePtr;
        currentFilePtr++;
    } currentFilePtr++;

    return 1;
}

int GetWiFiSecurityType(char* currentFilePtr)
{
    wifiSecurityType = 0; // default to open
    if (strstr(currentFilePtr, "WEP"))
    {
        wifiSecurityType = 1;
    }
    else if (strstr(currentFilePtr, "WPA"))
    {
        wifiSecurityType = 2;
    }
    return 1;
}

void ParseConfigFile(void)
{
    // 1. Read the entire file into array
    ReadConfigFileIntoArray();

    // 2. Parse the needed parameters
    // 2-1. Get the PIDs
    char* currentFilePtr = 0;
    currentFilePtr = strstr((const char*)entireFileContent, "pidNumberLookup");
    if (currentFilePtr)
    {
        GetPIdNumbers(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-2. clientcredentialCLIENT_CERTIFICATE_PEM
    currentFilePtr = strstr(currentFilePtr, "clientcredentialCLIENT_CERTIFICATE_PEM");
    if (currentFilePtr)
    {
        GetClientCertificate(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-3. clientcredentialCLIENT_PRIVATE_KEY_PEM
    currentFilePtr = strstr(currentFilePtr, "clientcredentialCLIENT_PRIVATE_KEY_PEM");
    if (currentFilePtr)
    {
        GetClientPrivateKey(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-4. clientcredentialMQTT_BROKER_ENDPOINT
    currentFilePtr = strstr(currentFilePtr, "clientcredentialMQTT_BROKER_ENDPOINT");
    if (currentFilePtr)
    {
        GetMqttBrokerEndpoint(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-5. clientcredentialIOT_THING_NAME
    currentFilePtr = strstr(currentFilePtr, "clientcredentialIOT_THING_NAME");
    if (currentFilePtr)
    {
        GetThingName(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-6. clientcredentialMQTT_BROKER_PORT
    currentFilePtr = strstr(currentFilePtr, "clientcredentialMQTT_BROKER_PORT");
    if (currentFilePtr)
    {
        GetMqttBrokerPortNumber(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-7. clientcredentialGREENGRASS_DISCOVERY_PORT
    currentFilePtr = strstr(currentFilePtr, "clientcredentialGREENGRASS_DISCOVERY_PORT");
    if (currentFilePtr)
    {
        GetGreengrassDiscoveryPortNumber(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-8. clientcredentialWIFI_SSID
    currentFilePtr = strstr(currentFilePtr, "clientcredentialWIFI_SSID");
    if (currentFilePtr)
    {
        GetWiFiSSID(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-9. clientcredentialWIFI_PASSWORD
    currentFilePtr = strstr(currentFilePtr, "clientcredentialWIFI_PASSWORD");
    if (currentFilePtr)
    {
        GetWiFiPassword(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }

    // 2-10. clientcredentialWIFI_SECURITY
    currentFilePtr = strstr(currentFilePtr, "clientcredentialWIFI_SECURITY");
    if (currentFilePtr)
    {
        GetWiFiSecurityType(currentFilePtr);
    }
    else
    {
        while (1) { ; }
    }
}

