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

// vspy generated header file
#ifndef _OBD2PRO_WIFI_CC32XX_H_
#define _OBD2PRO_WIFI_CC32XX_H_
#include "obd2pro_wifi_cc32xx_ism.h"
#include <string.h>
#include <stdint.h>

#ifndef BUILD_OBD2PRO_WIFI_CC32XX_ISM_PROJECT
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
#endif

#define CM_GETSET_SET_APP_SIGNAL                   0
#define CM_GETSET_GET_APP_SIGNAL                       1
#define CM_GETSET_SET_TMR_VALUE                        2
#define CM_GETSET_GET_TMR_VALUE                        3
#define CM_GETSET_SET_TMR_ENABLE                       4
#define CM_GETSET_GET_TMR_ENABLE                       5
#define CM_GETSET_FBLOCK_START                         6
#define CM_GETSET_FBLOCK_STOP                          7
#define CM_GETSET_FBLOCK_TRIGGER                       8
#define CM_GETSET_FBLOCK_SAVE                          9
#define CM_GETSET_FBLOCK_GET_ISRUNNING                10
#define CM_GETSET_FBLOCK_GET_ISTRIGGERED              11
#define CM_GETSET_FBLOCK_GET_NUMCOLLECTED             12
#define CM_GETSET_MSG_STATS_CLR                       13
#define CM_GETSET_DB_STATS_CLR                        14
#define CM_GETSET_TX_STATS_CLR                        15
#define CM_GETSET_NET_STATS_CLR                       16
#define CM_GETSET_NODE_STATS_CLR                      17
#define CM_GETSET_MSG_STATS_GET                       18
#define CM_GETSET_DB_STATS_GET                        19
#define CM_GETSET_TX_STATS_GET                        20
#define CM_GETSET_NET_STATS_GET                       21
#define CM_GETSET_NODE_STATS_GET                      22
#define CM_GETSET_SET_APP_SIGNAL_TEXT                 23
#define CM_GETSET_GET_APP_SIGNAL_TEXT                 24
#define CM_GETSET_DB_DLC_GET                          25
#define CM_GETSET_DB_NETWORK_GET                      26
#define CM_GETSET_DB_PERIOD_GET                       27
#define CM_GETSET_MSG_DLC_GET                         28
#define CM_GETSET_MSG_NETWORK_GET                     29
#define CM_GETSET_MSG_PERIOD_GET                      30
#define CM_GETSET_TX_DLC_GET                          31
#define CM_GETSET_TX_NETWORK_GET                      32
#define CM_GETSET_TX_PERIOD_GET                       33
#define CM_GETSET_SPY_LOCK                            34
#define CM_GETSET_SPY_UNLOCK                          35
#define CM_GETSET_DIAG_JOB_ISRUNNING                  36
#define CM_GETSET_DIAG_JOB_NumMessagesCollected       37
#define CM_GETSET_DIAG_JOB_Successful                 38
#define CM_GETSET_DIAG_JOB_ECUResponseCount           39
#define CM_GETSET_DIAG_JOB_TotalTimeAbs               40
#define CM_GETSET_DIAG_JOB_Last7FSubFunctionEx78      41
#define CM_GETSET_DIAG_JOB_7FCountEx78                42
#define CM_GETSET_DIAG_JOB_7FCountResponsePending     43
#define CM_GETSET_DIAGJOB_START                       44
#define CM_GETSET_DIAGJOB_STOP                        45
#define CM_GETSET_DIAGJOB_SAVE                        46
#define CM_GETSET_FBLOCK_ADD                          47
#define CM_GETSET_FBLOCK_FIND                         48
#define CM_GETSET_FBLOCK_POSTTRIGGER                  49
#define CM_GETSET_SET_TMR_PERIOD                      50
#define CM_GETSET_GET_TMR_TIME_TO_ELAPSE              51
#define CM_GETSET_GET_TIMENS                          52
#define CM_GETSET_SET_CAN_MODE                        53
#define CM_GETSET_SET_BTR                             54
#define CM_GETSET_STOP_MEASUREMENT                    55
#define CM_GETSET_CLEAR_TRACES                        56
#define CM_GETSET_FBLOCK_PAUSE                        57
#define CM_GETSET_FBLOCK_CONTINUE                     58
#define CM_GETSET_SYS_EXIT                            59
#define CM_GETSET_SYS_MINIMIZE                        60
#define CM_GETSET_GET_DB_NAME                         61
#define CM_GETSET_SET_LIN_WAKEUP_PARMS                62
#define CM_GETSET_SEND_LIN_WAKEUP                     63
#define CM_GETSET_SEND_LIN_SLEEP                      64
#define CM_GETSET_IL_ACTION                           65
#define CM_GETSET_SET_TXSIGNAL                        66
#define CM_GETSET_SET_APP_SIGNAL_AT                   67
#define CM_GETSET_GET_APP_SIGNAL_AT                   68
#define CM_GETSET_SET_APP_SIGNAL_TEXT_AT              69
#define CM_GETSET_GET_APP_SIGNAL_TEXT_AT              70
#define CM_GETSET_GET_NODE_NAME                       71
#define CM_GETSET_GET_NODE_TYPE                       72
#define CM_GETSET_GET_STATION_ADDR                    73
#define CM_GETSET_SET_APP_ACTIVE                      74
#define CM_GETSET_GET_SYS_CONF                        75
#define CM_GETSET_GET_REQ_STATE                       76
#define CM_GETSET_GET_SYS_BUS_REQ                     77
#define CM_GETSET_GET_SYS_FAIL_STATES                 78
#define CM_GETSET_GET_SYS_CURR_FAIL_STATES            79
#define CM_GETSET_GET_SYS_DLL_STATES                  80
#define CM_GETSET_GET_TARGET_CONF                     81
#define CM_GETSET_SET_TARGET_CONF                     82
#define CM_GETSET_GET_IS_WAKEUP_NODE                  83
#define CM_GETSET_GET_IND_ACTIVE_OTHER_BUS            84
#define CM_GETSET_REQ_NET_SHUTDOWN                    85
#define CM_GETSET_REQ_NET_ON_OTHER_BUS                86
#define CM_GETSET_REQ_NET_OFF_OTHER_BUS               87
#define CM_GETSET_TABLE_FBLOCK_ACTIVATE_SLOT		    88
#define CM_GETSET_TABLE_FBLOCK_DEACTIVATE_SLOT        89

#define ATTR_ACTIVE_INIT                        0x10
#define ATTR_CAN_29BIT_ID_FRAME                     0x20
#define ATTR_CAN_REMOTE_FRAME                       0x40
#define ATTR_CAN_TX_HIGH_VOLTAGE                    0x80

#define ATTR_CANFD_FRAME                      0x1000
#define ATTR_CANFD_ESI                            0x2000
#define ATTR_CANFD_BRS                            0x4000

void CM_ExtensionInit(const struct stCallBackPointers *);
void CM_EveryMessage(int,int,uint64_t,unsigned int,int,int,const unsigned char *);

#define CAN_ID_EXTENDED_BIT   0x80000000
#define isStdId(id) ((id & CAN_ID_EXTENDED_BIT) == 0)
#define isExtId(id) ((id & CAN_ID_EXTENDED_BIT) == CAN_ID_EXTENDED_BIT)
#define mkExtId(id) (id | CAN_ID_EXTENDED_BIT)
#define mkStdId(id) (id & (~CAN_ID_EXTENDED_BIT))
void SetUseExtendedIdBit(void);

unsigned int getStartDelay(void);
void setStartDelay(unsigned int delay);

double AS_Get(int index);
void AS_Set(int index, double value);
double AS_GetAt(int index, int element);
void AS_SetAt(int index, int element, double value);
void SpySetTxSignal(unsigned int msgIndex, unsigned int signalIndex, double value);
void SpySetTxSignalRaw(unsigned int msgIndex, unsigned int signalIndex, uint64_t value);
void SpySetTxEvent(unsigned int msgIndex);

typedef struct {
    unsigned int iSignal;    /// signal to set
    unsigned int iType;      /// 0 physical, 1 raw
    union {
        double dValue;           /// value 
        uint64_t nValue;
    } v;
} TxSetSignal;
void SpyAppSig_CallAllHandlers();

// Application Signals

// Timers

// Messages

typedef struct {
    unsigned char btPresent;  /// indicates message rxed at least once
    unsigned char btPresentToggle; /// toggle every message rx
    unsigned char btMultiFrameComplete; /// indicates frame is complete 
    double dUpdateRateRel;    /// periodic update rate
    double dUpdateRateAbs ;   /// absolute update rate
    int iPerSecond;   /// number of messages per second
    int iCount;       /// number of messages rxed
    int iChangeCount; /// count of everytime the message changes
    double dStartTime;        /// time between two first messages
    double dMsgMinTime;       /// min time between two messages
    double dMaxTime;          /// max time between two messages
    double dMeanTime;         /// average time between two messages
} MessageStats;

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    uint64_t iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[16]; /// Message data bytes
    unsigned char btInitialData[16]; /// Data bytes after initialization
} GenericMessage;

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    uint64_t iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[4096]; /// Message data bytes
    unsigned char btInitialData[4096]; /// Data bytes after initialization
} GenericLongMessage;

extern void (*CM_RegisterCallback)(unsigned short type, unsigned short index, void * ptr);
extern void (*CM_GetSetValue)(unsigned short type, unsigned short index, void * value);
extern int (*CM_TransmitMessage)(int netId, int msgId, int msgLen, int bitfield, const unsigned char * data);
extern int (*CM_GetSignalValue)(unsigned short msgType, unsigned short msgIndex, unsigned short signalIndex, void * value);
extern int (*CM_TxFromSignals)(unsigned short msgType, unsigned short msgIndex, unsigned char * bytes, int msgLen, int netId, void * signalValues, int signalCnt);
extern int (*CM_TxFromRawSignals)(unsigned short msgType, unsigned short msgIndex, unsigned char * bytes, int msgLen, int netId, void * signalValues, int signalCnt);
extern int (*CM_MessageGenericInit)(unsigned short msgType, unsigned short msgIndex, void * pStats, int * pNetId, int * pNumBytes, int numBytesMax, int * pPeriod, int * pID,
                                    int * pBitField, unsigned char * pData, double * pSignals, int signalMaxCnt,
                                    int * pSignalMaxCnt, uint64_t * pTimeStampNs,unsigned int * pTimeStampMs);
extern int (*CM_MessageRawInit)(unsigned short msgType, unsigned short msgIndex, uint64_t * signals, int signalMaxCnt, int * actualSignalMaxCnt);
extern uint64_t (*CM_SignalPhysicalToRaw)(unsigned short iType, unsigned short msgIndex, unsigned short signalIndex, double value);
extern int (* CM_UpdateMessageSignalsFromBytes)(unsigned short iType, unsigned short msgIndex, unsigned char * bytes, int numBytes);
extern int (* CM_UpdateBytesFromSignals)(unsigned short iType, unsigned short msgIndex, double * pSignals, int signalMaxCnt, unsigned char * bytes, int numBytes);
extern int (* CM_UpdateBytesFromRawSignals)(unsigned short iType, unsigned short msgIndex, uint64_t * pSignals, int signalMaxCnt, unsigned char * bytes, int numBytes);

void Spy_EveryMessage(GenericMessage * p_Msg);
void Spy_EveryLongMessage(GenericLongMessage * p_Msg);
int GenericMessageTransmit(GenericMessage * p_Msg);
int GenericLongMessageTransmit(GenericLongMessage * p_Msg);
int CANFDMessageTransmit(GenericLongMessage * p_Msg, uint8_t bBRS);


#endif // VSPY_GENERATED_HEADER
