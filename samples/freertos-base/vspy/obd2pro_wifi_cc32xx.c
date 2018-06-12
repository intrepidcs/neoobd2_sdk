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

// vspy generated implementation file
#include "obd2pro_wifi_cc32xx.h"
#include "obd2pro_wifi_cc32xx_ism.h"

unsigned char g_bUseExtendedIdBit = 0;
unsigned int g_startDelay = 0;

unsigned int getStartDelay(void)
{
    return g_startDelay;
}
void setStartDelay(unsigned int delay)
{
    if (delay > 99999)
        delay = 0;
    g_startDelay = delay;
}

void SetUseExtendedIdBit(void)
{
    g_bUseExtendedIdBit = 1;
}

double AS_Get(int index)
{
    double value;
    CM_GetSetValue(CM_GETSET_GET_APP_SIGNAL, index, &value);
    return value;
}

void AS_Set(int index, double value)
{
    CM_GetSetValue(CM_GETSET_SET_APP_SIGNAL, index, &value);
}

struct AppSigValue
{
    int offset;
    double value;
};

double AS_GetAt(int index, int element)
{
    struct AppSigValue sVal;
    if (element == 0)
        return AS_Get(index);
    sVal.offset = element;
    CM_GetSetValue(CM_GETSET_GET_APP_SIGNAL_AT, index, &sVal);
    return sVal.value;
}

void AS_SetAt(int index, int element, double value)
{
    struct AppSigValue sVal;
    if (element == 0)
        AS_Set(index, value);
    else
    {
        sVal.value = value;
        sVal.offset = element;
        CM_GetSetValue(CM_GETSET_SET_APP_SIGNAL_AT, index, &sVal);
    }
}

int GenericMessageTransmit(GenericMessage * pM)
{
    return CM_TransmitMessage(pM->iNetwork, pM->iID, pM->iNumDataBytes, pM->iBitField, pM->btData);
}

int GenericLongMessageTransmit(GenericLongMessage * pM)
{
    return CM_TransmitMessage(pM->iNetwork, pM->iID, pM->iNumDataBytes, pM->iBitField, pM->btData);
}

int CANFDMessageTransmit(GenericLongMessage * pM, uint8_t bBRS)
{
    int iID;
    int iBitField;
    iID = pM->iID;
    iBitField = pM->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }
    iBitField |= ATTR_CANFD_FRAME;
    if (bBRS)
        iBitField |= ATTR_CANFD_BRS;

    return CM_TransmitMessage(pM->iNetwork, iID, pM->iNumDataBytes, iBitField, pM->btData);
}

void SpySetTxSignal(unsigned int msgIndex, unsigned int signalIndex, double value)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = signalIndex;
    txSetSignal.iType = 0;
    txSetSignal.v.dValue = value;
    CM_GetSetValue(CM_GETSET_SET_TXSIGNAL, msgIndex, &txSetSignal);
}

void SpySetTxSignalRaw(unsigned int msgIndex, unsigned int signalIndex, uint64_t value)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = signalIndex;
    txSetSignal.iType = 1;
    txSetSignal.v.nValue = value;
    CM_GetSetValue(CM_GETSET_SET_TXSIGNAL, msgIndex, &txSetSignal);
}

void SpySetTxEvent(unsigned int msgIndex)
{
    TxSetSignal txSetSignal;
    txSetSignal.iType = 2;
    CM_GetSetValue(CM_GETSET_SET_TXSIGNAL, msgIndex, &txSetSignal);
}
void SpyAppSig_CallAllHandlers()
{
}


node_t cb_app_signal_nodes[1];
node_t cb_message_nodes[1];
node_t cb_timer_nodes[1];
node_t cb_message_mg_nodes[1];
node_t cb_message_tx_nodes[1];
node_t cb_before_message_tx_nodes[1];

void (*CM_RegisterCallback)(unsigned short type, unsigned short index, void * ptr);
void (*CM_GetSetValue)(unsigned short type, unsigned short index, void * value);
int (*CM_TransmitMessage)(int netId, int msgId, int msgLen, int bitfield, const unsigned char * data);
int (*CM_GetSignalValue_)(unsigned short msgType, unsigned short msgIndex, unsigned short signalIndex, void * value);
int (*CM_TxFromSignals)(unsigned short msgType, unsigned short msgIndex, unsigned char * bytes, int msgLen, int netId, void * signalValues, int signalCnt);
int (*CM_TxFromRawSignals)(unsigned short msgType, unsigned short msgIndex, unsigned char * bytes, int msgLen, int netId, void * signalValues, int signalCnt);
int (*CM_MessageGenericInit)(   unsigned short msgType, unsigned short msgIndex, void * pStats, int * pNetId, int * pNumBytes, int numBytesMax, int * pPeriod, int * pID,
                                int * pBitField, unsigned char * pData, double * pSignals, int signalMaxCnt,
                                int * pSignalMaxCnt, uint64_t * pTimeStampNs,unsigned int * pTimeStampMs);
int (*CM_MessageRawInit)(unsigned short msgType, unsigned short msgIndex, uint64_t * signals, int signalMaxCnt, int * actualSignalMaxCnt);
uint64_t (*CM_SignalPhysicalToRaw)(unsigned short iType, unsigned short msgIndex, unsigned short signalIndex, double value);
int (* CM_UpdateMessageSignalsFromBytes)(unsigned short iType, unsigned short msgIndex, unsigned char * bytes, int numBytes);
int (* CM_UpdateBytesFromSignals)(unsigned short iType, unsigned short msgIndex, double * pSignals, int signalMaxCnt, unsigned char * bytes, int numBytes);
int (* CM_UpdateBytesFromRawSignals)(unsigned short iType, unsigned short msgIndex, uint64_t * pSignals, int signalMaxCnt, unsigned char * bytes, int numBytes);

void CM_ExtensionInit(const struct stCallBackPointers * pCb)
{
    /* Setup the callback functions */
    CM_RegisterCallback = (void(*)(uint16_t,uint16_t,void*))pCb->pRegisterCallBack;
    CM_GetSetValue = (void(*)(unsigned short, unsigned short, void *))pCb->pGetSetValueCallBack;
    CM_TransmitMessage = (int(*)(int,int,int,int,const unsigned char*))pCb->pTransmitMessageCallBack;
    CM_GetSignalValue_ = (int (*)(unsigned short, unsigned short, unsigned short, void*))pCb->pGetSignalValue;
    CM_TxFromSignals = (int (*)(unsigned short, unsigned short, unsigned char * , int, int, void *, int))pCb->pTransmitMessagesFromSignalValues;
    CM_TxFromRawSignals = (int (*)(unsigned short, unsigned short, unsigned char * , int, int, void *, int))pCb->pTransmitMessagesFromRawSignalValues;
    CM_MessageGenericInit = (int (*)(   unsigned short, unsigned short, void *, int *, int *, int, int *, int *,
                                        int *, unsigned char *, double *, int,
                                        int *, uint64_t *, unsigned int *))pCb->pMessageGenericInit;
    CM_MessageRawInit = (int (*)(unsigned short, unsigned short, uint64_t *, int, int *))pCb->pMessageRawInit;
    CM_SignalPhysicalToRaw = (uint64_t (*)(unsigned short, unsigned short, unsigned short, double))pCb->pSignalPhysicalToRaw;
    CM_UpdateMessageSignalsFromBytes = (int (*)(unsigned short, unsigned short, unsigned char *, int))pCb->pUpdateMessageSignalsFromBytes;
    CM_UpdateBytesFromSignals = (int (*)(unsigned short, unsigned short, double *, int, unsigned char *, int))pCb->pUpdateBytesFromSignals;
    CM_UpdateBytesFromRawSignals = (int (*)(unsigned short, unsigned short, uint64_t *, int, unsigned char *,int))pCb->pUpdateBytesFromRawSignals;

    map_init(icsISM_GetAppSignalMap(), cb_app_signal_nodes, sizeof(cb_app_signal_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageMap(), cb_message_nodes, sizeof(cb_message_nodes)/sizeof(node_t));
    map_init(icsISM_GetTimerMap(), cb_timer_nodes, sizeof(cb_timer_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageMgMap(), cb_message_mg_nodes, sizeof(cb_message_mg_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageTxMap(), cb_message_tx_nodes, sizeof(cb_message_tx_nodes)/sizeof(node_t));
    map_init(icsISM_GetBeforeMessageTxMap(), cb_before_message_tx_nodes, sizeof(cb_before_message_tx_nodes)/sizeof(node_t));

}

void CM_EveryMessage(int iNetwork, int iID, uint64_t iTimeNanoseconds, unsigned int iTimeMilliseconds, int iNumDataBytes, int iBitField, const unsigned char * p_btData)
{
    GenericMessage stMsg = {0};
    GenericLongMessage stLongMsg = {0};
    stMsg.iNetwork = iNetwork;
    stMsg.iID = iID;
    stMsg.iNumDataBytes = iNumDataBytes;
    if (stMsg.iNumDataBytes > sizeof(stMsg.btData))
        stMsg.iNumDataBytes = sizeof(stMsg.btData);
    stMsg.iBitField = iBitField;
    stMsg.iTimeStampMillisecondsOS = iTimeMilliseconds;
    stMsg.iTimeStampNanoSecondsHW = iTimeNanoseconds;
    if (g_bUseExtendedIdBit && (stMsg.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        stMsg.iID = mkExtId(stMsg.iID);
    memcpy(stMsg.btData, p_btData, stMsg.iNumDataBytes);
    Spy_EveryMessage(&stMsg);

    if ((stMsg.iBitField & ATTR_CANFD_FRAME) || (stMsg.iNumDataBytes < iNumDataBytes))
    {
        stLongMsg.iNetwork = iNetwork;
        stLongMsg.iID = stMsg.iID;
        stLongMsg.iNumDataBytes = iNumDataBytes;
        if (iNumDataBytes > sizeof(stLongMsg.btData))
            iNumDataBytes = sizeof(stLongMsg.btData);
        stLongMsg.iBitField = iBitField;
        stLongMsg.iTimeStampMillisecondsOS = iTimeMilliseconds;
        stLongMsg.iTimeStampNanoSecondsHW = iTimeNanoseconds;
        memcpy(stLongMsg.btData, p_btData, stLongMsg.iNumDataBytes);
        Spy_EveryLongMessage(&stLongMsg);
    }
}

