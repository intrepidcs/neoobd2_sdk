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
    int iID;
    int iBitField;
    iID = pM->iID;
    iBitField = pM->iBitField;
    if (isExtId(iID))
    {
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }

    return CM_TransmitMessage(pM->iNetwork, iID, pM->iNumDataBytes, iBitField, pM->btData);
}

int GenericLongMessageTransmit(GenericLongMessage * pM)
{
    int iID;
    int iBitField;
    iID = pM->iID;
    iBitField = pM->iBitField;
    if (isExtId(iID))
    {
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }

    return CM_TransmitMessage(pM->iNetwork, iID, pM->iNumDataBytes, iBitField, pM->btData);
}

int CANFDMessageTransmit(GenericLongMessage * pM, uint8_t bBRS)
{
    int iID;
    int iBitField;
    iID = pM->iID;
    iBitField = pM->iBitField;
    if (isExtId(iID))
    {
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }
    iBitField |= ATTR_CANFD_FRAME;
    if (bBRS)
    {
        iBitField |= ATTR_CANFD_BRS;
    }

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

int ControlMainChipLEDColor(unsigned int ledColor)
{
    sfifoISMChipLEDControl stData = { 0 };
    if (CM_SendCommandToMainChip == 0)
        return 0;
    stData.red = (ledColor & 0x00ff0000) >> 16;
    stData.green = (ledColor & 0x0000ff00) >> 8;
    stData.blue = ledColor & 0x000000ff;
    return CM_SendCommandToMainChip(ISM_CMD_CTRL_LED_COLOR, sizeof(sfifoISMChipLEDControl), &stData);
}

void CM_MG_Message_HS_CAN_1_HS_CAN()
{
    MG_Message_HS_CAN_1_HS_CAN stMyStruct;
    MG_Message_HS_CAN_1_HS_CAN_Init(&stMyStruct);
    SpyMsg_MG_Message_HS_CAN_1_HS_CAN(&stMyStruct);
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
int (* CM_SendCommandToMainChip)(unsigned int iCommand, unsigned int iDataSizeBytes, const void* btData);

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
    CM_SendCommandToMainChip = (int (*)(unsigned int, unsigned int, const void*))pCb->pSendCommandToMainChip;

    map_init(icsISM_GetAppSignalMap(), cb_app_signal_nodes, sizeof(cb_app_signal_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageMap(), cb_message_nodes, sizeof(cb_message_nodes)/sizeof(node_t));
    map_init(icsISM_GetTimerMap(), cb_timer_nodes, sizeof(cb_timer_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageMgMap(), cb_message_mg_nodes, sizeof(cb_message_mg_nodes)/sizeof(node_t));
    map_init(icsISM_GetMessageTxMap(), cb_message_tx_nodes, sizeof(cb_message_tx_nodes)/sizeof(node_t));
    map_init(icsISM_GetBeforeMessageTxMap(), cb_before_message_tx_nodes, sizeof(cb_before_message_tx_nodes)/sizeof(node_t));

    CM_RegisterCallback(CM_CALLBACKTYPE_MESSAGE_MG, MG_Message_HS_CAN_1_HS_CAN_Index,CM_MG_Message_HS_CAN_1_HS_CAN);
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

int MG_Message_HS_CAN_1_HS_CAN_Index = 0;

void MG_Message_HS_CAN_1_HS_CAN_Init(MG_Message_HS_CAN_1_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(1, 
    MG_Message_HS_CAN_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_Message_HS_CAN_1_HS_CAN_Transmit(MG_Message_HS_CAN_1_HS_CAN * pMsg)
{
    return CM_TxFromSignals(1, MG_Message_HS_CAN_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_Message_HS_CAN_1_HS_CAN_Transmit_raw(MG_Message_HS_CAN_1_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(1, MG_Message_HS_CAN_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

