// vspy generated header file
#ifndef VSPY_GENERATED_HEADER
#define VSPY_GENERATED_HEADER
#include "windows.h"
#include "string.h"
#include <stdio.h>
extern void * g_uiHandle;
typedef unsigned __int64 uint64;

#define printf Printf
int Printf(const char *szInMsg, ...);
int PrintfW(const wchar_t *szInMsg, ...);
int WriteLine(const char *szInMsg, ...);
int WriteLineW(const wchar_t *szInMsg, ...);
void DisplayLastError(LPCWSTR lpszFunction);

typedef void (* RS232OnError_fdef)(DWORD port, DWORD errorFlags);
typedef void (* RS232OnRxTx_fdef)(DWORD port, BYTE buffer[], DWORD dwSize);

DWORD ICS_RS232Open(DWORD port);
DWORD ICS_RS232Close(DWORD port);
DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout);
DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity);
DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar);
DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state);
WORD ICS_RS232WriteByte(DWORD port, DWORD data);
WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size);
void ICS_RS232CloseAllPorts();

typedef void	(__stdcall *lpOut32)(short, short);
typedef short	(__stdcall *lpInp32)(short);
typedef BOOL	(__stdcall *lpIsInpOutDriverOpen)(void);
void LoadInpOut();
void UnloadInpout();

#define J1939Priority(id)                   ((unsigned long)((id >> 26) & 0x7))
#define J1939PGN(id)                        ((unsigned long)((id >> 8) & 0x3FFFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define J1939ExtDataPage(id)                ((unsigned char)((id >> 25) & 0x1))
#define J1939DataPage(id)                   ((unsigned char)((id >> 24) & 0x1))
#define J1939PduFormat(id)                  ((unsigned char)((id >> 16) & 0xFF))
#define J1939PduSpecific(id)                ((unsigned char)((id >> 8) & 0xFF))
#define J1939SourceAddress(id)              ((unsigned char)(id & 0xFF))
#define J1939DestinationAddress(id)         ((unsigned char)(J1939PduFormat(id) < 240) ? ((id >> 8) & 0xFF) : 0)

#define SetJ1939Priority(id, prio)          (id = (prio << 26) | (id & 0x7FFFFFF))
#define SetJ1939PGN(id, pgn)                (id = (pgn << 8) | (id & 0xFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define SetJ1939ExtDataPage(id, edp)        (id = (edp << 25) | (id & 0x1DFFFFFF))
#define SetJ1939DataPage(id, dp)            (id = (dp << 24) | (id & 0x1EFFFFFF))
#define SetJ1939PduFormat(id, pf)           (id = (pf << 16) | (id & 0x1F00FFFF))
#define SetJ1939PduSpecific(id, ps)         (id = (ps << 8) | (id & 0x1FFF00FF))
#define SetJ1939SourceAddress(id, sa)       (id = sa | (id & 0x1FFFFF00))
#define SetJ1939DestinationAddress(id, da)  SetJ1939PduSpecific(id, da)

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength);
int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength);

#define CM_CALLBACKTYPE_APP_SIGNAL                     0
#define CM_CALLBACKTYPE_MESSAGE                        1
#define CM_CALLBACKTYPE_TIMER                          2
#define CM_CALLBACKTYPE_MESSAGE_MG                     3
#define CM_CALLBACKTYPE_MESSAGE_TX                     4
#define CM_CALLBACKTYPE_BEFORE_MESSAGE_TX   5

#define CM_GETSET_SET_APP_SIGNAL                       0
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
#define CM_GETSET_TABLE_FBLOCK_DEACTIVATE_SLOT		89

#define CM_OSEK_GET_TXID                             501
#define CM_OSEK_SET_TXID                             502
#define CM_OSEK_GET_RXID                             503
#define CM_OSEK_SET_RXID                             504
#define CM_OSEK_GET_USEFC                            505
#define CM_OSEK_SET_USEFC                            506
#define CM_OSEK_SET_0PADDING                         507
#define CM_OSEK_GET_USEEXTID                         508
#define CM_OSEK_SET_USEEXTID                         509
#define CM_OSEK_GET_BS                               510
#define CM_OSEK_SET_BS                               511
#define CM_OSEK_GET_STMIN                            512
#define CM_OSEK_SET_STMIN                            513
#define CM_OSEK_GET_EVAL1FC                          514
#define CM_OSEK_SET_EVAL1FC                          515
#define CM_OSEK_GET_TIMEOUTAR                        516
#define CM_OSEK_SET_TIMEOUTAR                        517
#define CM_OSEK_GET_TIMEOUTAS                        518
#define CM_OSEK_SET_TIMEOUTAS                        519
#define CM_OSEK_GET_TIMEOUTBR                        520
#define CM_OSEK_SET_TIMEOUTBR                        521
#define CM_OSEK_GET_TIMEOUTBS                        522
#define CM_OSEK_SET_TIMEOUTBS                        523
#define CM_OSEK_GET_TIMEOUTCR                        524
#define CM_OSEK_SET_TIMEOUTCR                        525
#define CM_OSEK_GET_1FCBS                            526
#define CM_OSEK_SET_1FCBS                            527
#define CM_OSEK_SET_FIXEDST                          528
#define CM_OSEK_GET_0PATTERN                         529
#define CM_OSEK_SET_0PATTERN                         530
#define CM_OSEK_GET_STARTSN                          531
#define CM_OSEK_SET_STARTSN                          532
#define CM_OSEK_GET_IDFROMADR                        533
#define CM_OSEK_SET_IDFROMADR                        534
#define CM_OSEK_GET_ADRFROMID                        535
#define CM_OSEK_SET_ADRFROMID                        536
#define CM_OSEK_GET_TPBASEADR                        537
#define CM_OSEK_SET_TPBASEADR                        538
#define CM_OSEK_GET_MAXMSGLEN                        539
#define CM_OSEK_SET_MAXMSGLEN                        540
#define CM_OSEK_SET_FCDELAY                          541
#define CM_OSEK_SET_WFTMAX                           542
#define CM_OSEK_GET_DATAREQ                          543
#define CM_OSEK_GET_RXDATA                           544
#define CM_OSEK_GET_SRCADR                           545
#define CM_OSEK_GET_NMSTATUS                         546
#define CM_OSEK_SET_NMSTATUS                         547
#define CM_OSEK_GET_NMCONFIG                         548
#define CM_AUTOSAR_SET_STATUS                        549
#define CM_OSEK_SET_ADDRMODE                         550
#define CM_OSEK_GET_ADDRMODE                         551
#define CM_OSEK_SET_DLCMODE                          552
#define CM_OSEK_SET_CAN                              553
#define CM_OSEK_GET_TGTADR                           554
#define CM_OSEK_SET_TGTADR                           555
#define CM_OSEK_GET_TXMODE                           556
#define CM_OSEK_SET_TXMODE                           557
#define CM_OSEK_SET_MINSTMIN                         558
#define CM_OSEK_GET_ECUNUM                           559
#define CM_OSEK_SET_ECUNUM                           560
#define CM_OSEK_GET_LOFCTADR                         561
#define CM_OSEK_SET_LOFCTADR                         562
#define CM_OSEK_GET_HIFCTADR                         563
#define CM_OSEK_SET_HIFCTADR                         564
#define CM_OSEK_GET_MSGCOUNT                         565
#define CM_OSEK_SET_MSGCOUNT                         566
#define CM_OSEK_GET_TXPRIO                           567
#define CM_OSEK_SET_TXPRIO                           568
#define CM_OSEK_GET_FFPRIO                           569
#define CM_OSEK_SET_FFPRIO                           570
#define CM_OSEK_GET_FCPRIO                           571
#define CM_OSEK_SET_FCPRIO                           572
#define CM_OSEK_GET_USEALLAE                         573
#define CM_OSEK_SET_USEALLAE                         574
#define CM_OSEK_GET_TXTOTHRESHOLD                    575
#define CM_OSEK_SET_TXTOTHRESHOLD                    576
#define CM_OSEK_GET_RECENTAE                         577
#define CM_OSEK_SET_MAXCFBURST                       578
#define CM_OSEK_GET_ADREXT                           579
#define CM_OSEK_SET_ADREXT                           580
#define CM_OSEK_CONNECTREQ                           581
#define CM_OSEK_GET_CAN                              582
#define CM_OSEK_GET_0PADDING                         583
#define CM_OSEK_GET_FIXED_DLC                        584
#define CM_GET_VIEWCOUNT						   	   600
#define CM_GET_VIEWHANDLE					   	   	   601
#define CM_GET_VIEWTYPE							   602
#define CM_GET_VIEWPROCADDRESS					   603
#define CM_SET_SHOWVIEW							   604
#define CM_SET_HIDEVIEW							   605
#define CM_GET_VIEWISVISIBLE					   	   606
#define CM_SET_SHOWVIEWBYTYPE			               607

// Send this struct to CM_GET_VIEWPROCADDRESS
typedef struct _stGetViewProcAddressArgs
{
	void* InForm;
	const char* InFunctionName;
	void* OutFunctionPtr;
} stGetViewProcAddressArgs;

// Send this struct to CM_GET_VIEWTYPE
typedef struct _stGetViewTypeArgs
{
	void* InForm;
	int OutType;
} stGetViewTypeArgs;

// Send this struct to CM_GET_VIEWISVISIBLE
typedef struct _stGetViewIsVisibleArgs
{
	void* InForm;
	int OutVisible;
} stGetViewIsVisibleArgs;

// Typedefs for function pointers returned by CM_GET_VIEWPROCADDRESS
typedef int(_stdcall* VideoFrameReview_GetMaxCamCount)(void* pForm);
typedef int(_stdcall* VideoFrameReview_CamIsVisible)(void* pForm, int camIndex);
typedef void(_stdcall* VideoFrameReview_AddRect)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int color, int thickness);
typedef void(_stdcall* VideoFrameReview_ClearRects)(void* pForm, int camIndex);
typedef int(_stdcall* VideoFrameReview_AddText)(void* pForm, int cam, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void(_stdcall* VideoFrameReview_UpdateText)(void* pForm, int cam, int index, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void(_stdcall* VideoFrameReview_ClearTexts)(void* pForm, int cam);
typedef int(_stdcall* VideoFrameReview_AddBitmap)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible, const wchar_t* imagePath);
typedef void(_stdcall* VideoFrameReview_UpdateBitmap)(void* pForm, int cam, int index, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible);
typedef void(_stdcall* VideoFrameReview_ClearBitmaps)(void* pForm, int cam);

#define ATTR_LIN_TX_SENDSLAVE                       0x10
#define ATTR_LIN_TX_CLASSIC_CHECKSUM                0x20
#define ATTR_LIN_TX_SEND_BREAK_ONLY                 0x40
#define ATTR_LIN_TX_SEND_HDR_ONLY                   0x80
#define ATTR_ACTIVE_INIT                            0x10
#define ATTR_CAN_29BIT_ID_FRAME                     0x20
#define ATTR_CAN_REMOTE_FRAME                       0x40
#define ATTR_CAN_TX_HIGH_VOLTAGE                    0x80
#define ATTR_ALL_RX_TRANSMIT                           1
#define ATTR_ALL_RX_ERROR                              2
#define ATTR_LIN_RX_MASTER_TX                      0x100
#define ATTR_LIN_RX_SLAVE_TX                       0x200
#define ATTR_CANFD_FRAME                          0x1000
#define ATTR_CANFD_ESI                            0x2000
#define ATTR_CANFD_BRS                            0x4000

// Spy_ErrorState iErrorBitfield flags
#define CAN_ERROR_STATUS_ACTIVE                   0x0000
#define CAN_ERROR_STATUS_TXRX_WARNING             0x0001  // EWARN: Transmitter or Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_RX_WARNING               0x0002  // RXWAR: Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_TX_WARNING               0x0004  // TXWAR: Transmitter in Error State Warning bit
#define CAN_ERROR_STATUS_RX_PASSIVE               0x0008  // RXBP: Receiver in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_PASSIVE               0x0010  // TXBP: Transmitter in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_BUS_OFF               0x0020  // TXBO: Transmitter in Error State Bus Off bit

#define SPY_CTL_PROP_ENABLE                       1
#define SPY_CTL_PROP_SET_BACKGROUND               2
#define SPY_CTL_PROP_SET_FOREGROUND               3
#define SPY_CTL_PROP_SET_CAPTION                  4
#define SPY_CTL_PROP_SET_LEFT                     5
#define SPY_CTL_PROP_SET_TOP                      6
#define SPY_CTL_PROP_SET_WIDTH                    7
#define SPY_CTL_PROP_SET_HEIGHT                   8
#define SPY_CTL_PROP_SET_TRANSPARENT              9
#define SPY_CTL_PROP_SET_FONT_NAME               10
#define SPY_CTL_PROP_SET_FONT_SIZE               11

struct stCallBackPointers
{
    void * pRegisterCallBack;
    void * pGetSetValueCallBack;
    void * pTransmitMessageCallBack;
    void * pOutputWindowCallBack;
    void * pTextAPICallBack;
    void * pGetSignalValue;
    void * pDecodeSignalValue;
    void * pTransmitMessagesFromSignalValues;
    void * pFindIndexForObjectFromNameCallBack;
    void * pShowPanelCallBack;
    void * pMessageGenericInit;
    void * pGetEcuCount;
    void * pGetMemoryBlockCount;
    void * pGetMemoryBlockInfo;
    void * pGetMemoryBlockData;
    void * pSetMemoryBlockData;
    void * pMessageRawInit;
    void * pSignalPhysicalToRaw;
    void * pTransmitMessagesFromRawSignalValues;
    void * pGetMessageName;
    void * pSetControlProp;
    void * pUpdateMessageSignalsFromBytes;
    void * pUpdateBytesFromSignals;
    void * pUpdateBytesFromRawSignals;
};
extern void (* CM_RegisterCallback) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
extern void (* CM_GetSetValue) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
extern int  (* CM_TextAPI) (void * uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
extern int  (* CM_OutputWindow) (void * uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
extern int  (* CM_TransmitMessage) (void * uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
extern int  (* CM_GetSignalValue) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
extern int  (* CM_TxFromSignals) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_TxFromRawSignals) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_UpdateMessageSignalsFromBytes) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromRawSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_FindIndexForObjectFromName) (void * uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
extern int  (* CM_GetMessageName) (void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
extern int  (* CM_ShowPanel) (void * uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
extern int  (* CM_SetControlProperty) (void * uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
extern int  (* CM_MessageGenericInit) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
                       int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
                       int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
                       int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
extern int  (* CM_MessageRawInit) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
extern uint64 (* CM_SignalPhysicalToRaw) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned short iSignalIndex, double dPhysicalValue);
extern int  (* CM_GetEcuCount) (void * uiHandle);
extern int  (* CM_GetMemoryBlockCount) (void * uiHandle, int ecu);
extern int  (* CM_GetMemoryBlockInfo) (void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
extern int  (* CM_GetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
extern int  (* CM_SetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

#define CAN_ID_EXTENDED_BIT   0x80000000
#define isStdId(id) ((id & CAN_ID_EXTENDED_BIT) == 0)
#define isExtId(id) ((id & CAN_ID_EXTENDED_BIT) == CAN_ID_EXTENDED_BIT)
#define mkExtId(id) (id | CAN_ID_EXTENDED_BIT)
#define mkStdId(id) (id & (~CAN_ID_EXTENDED_BIT))
#define valOfId(id) ((long)id)
void SetUseExtendedIdBit();

#define GMLAN_SOURCE_MASK 0xff
#define GMLAN_PID_MASK    0xffff
#define GMLAND_PID_SHIFT  8
#define GMLAN_PRIO_MASK   0x07
#define GMLAND_PRIO_SHIFT 26
#define gmlanSetSourceId(id, source) (id |= (source & GMLAN_SOURCE_MASK))
#define gmlanSetPid(id, pid) (id |= ((pid & GMLAN_PID_MASK) << GMLAND_PID_SHIFT))
#define gmlanSetPrio(id, prio) (id |= ((prio & GMLAN_PRIO_MASK) << GMLAND_PRIO_SHIFT))
#define gmlanGetSourceId(id) (id & GMLAN_SOURCE_MASK)
#define gmlanGetPid(id) ((id >> GMLAND_PID_SHIFT) & GMLAN_PID_MASK)
#define gmlanGetPrio(id) ((id >> GMLAND_PRIO_SHIFT) & GMLAN_PRIO_MASK)
#define gmlanId(id, source) (id | (source & GMLAN_SOURCE_MASK))

int getStartDelay();
void setStartDelay(int delay);

void SpyShowPanel(char * pWindowName, char * pPanelName);
void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName);
void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue);
void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue);
void Spy_Lock();
void Spy_Unlock();
int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize);
int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
double AS_Get(int index);
void AS_Set(int index, double dValue);
double AS_GetAt(int index, int element);
void AS_SetAt(int index, int element, double dValue);
int AS_GetText(int nIndex, void * szValue, int nLength);
int AS_SetText(int nIndex, void * szValue, int nLength);
int AS_GetTextW(int index, wchar_t * szValue);
void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue);
void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue);
void SpySetTxEvent(unsigned int iMessageIndex);
int AS_GetTextAtW(int index, int element, wchar_t * szValue);
int AS_SetTextAtW(int index, int element, wchar_t * szValue);
int SpyViewGetCount();
void* SpyViewGetHandle(int index);
int SpyViewGetType(void* pView);
void SpyViewShow(void* pView);
void SpyViewHide(void* pView);
int SpyViewIsVisible(void* pView);
void* SpyViewShowByType(int type);
void* SpyViewGetProcAddress(void* pView, const char* szProcName);

typedef struct {
    unsigned int iSignal;    /// signal to set
    unsigned int iType;      /// 0 physical, 1 raw
    union {
        double dValue;           /// value 
        __int64 nValue;
    };
} TxSetSignal;

// Network Statistics
typedef struct {
    unsigned int iCount;  /// count of messages on network
    unsigned int iRate; /// messages per second
    double dPercentUse; /// current bus utilization 
    unsigned int iMaxRate;    /// maximum messages per second
    double dMaxPercentUse;   /// maximum bus utilization
    unsigned int iErrorCount;   /// number of errors on a network
    unsigned int iTxCount;       /// number of messages transmitted on a network
    unsigned int iErrorRate; /// errors per second
    unsigned int iTxRate;        /// transmissions per second
    unsigned int iTxBufferFill;  /// current network buffer fill level
    unsigned int iCANTxErrCount;  /// transmit CAN errors
    unsigned int iCANRxErrCount;  /// receive CAN errors
} NetworkStats; 
int Spy_TranslateNetwork(int nNetworkOffset);
int Spy_UntranslateNetwork(int nNetwork);
int Spy_NetworksInUse();
int Spy_LINIndex(int iNetwork);

// network index variables - identify networks in vspy
extern int NET_HS_CAN;
void NET_HS_CAN_ClearStats();
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN;
void NET_MS_CAN_ClearStats();
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN;
void NET_SW_CAN_ClearStats();
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW;
void NET_J1850_VPW_ClearStats();
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K;
void NET_ISO9141_KW2K_ClearStats();
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN;
void NET_LSFT_CAN_ClearStats();
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_PWM;
void NET_J1850_PWM_ClearStats();
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708;
void NET_J1708_ClearStats();
void NET_J1708_GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI;
void NET_neoVI_ClearStats();
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2;
void NET_HS_CAN2_ClearStats();
void NET_HS_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3;
void NET_HS_CAN3_ClearStats();
void NET_HS_CAN3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2;
void NET_LIN2_ClearStats();
void NET_LIN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3;
void NET_LIN3_ClearStats();
void NET_LIN3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4;
void NET_LIN4_ClearStats();
void NET_LIN4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI;
void NET_CGI_ClearStats();
void NET_CGI_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN;
void NET_LIN_ClearStats();
void NET_LIN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2;
void NET_ISO9141_KW2K_2_ClearStats();
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3;
void NET_ISO9141_KW2K_3_ClearStats();
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4;
void NET_ISO9141_KW2K_4_ClearStats();
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4;
void NET_HS_CAN4_ClearStats();
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5;
void NET_HS_CAN5_ClearStats();
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART;
void NET_UART_ClearStats();
void NET_UART_GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART2;
void NET_UART2_ClearStats();
void NET_UART2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5;
void NET_LIN5_ClearStats();
void NET_LIN5_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MOST__VNET_A_;
void NET_MOST__VNET_A__ClearStats();
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1A__VNET_A_;
void NET_FlexRay1A__VNET_A__ClearStats();
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1B__VNET_A_;
void NET_FlexRay1B__VNET_A__ClearStats();
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2A__VNET_A_;
void NET_FlexRay2A__VNET_A__ClearStats();
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2B__VNET_A_;
void NET_FlexRay2B__VNET_A__ClearStats();
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN__VNET_A_;
void NET_HS_CAN__VNET_A__ClearStats();
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN__VNET_A_;
void NET_MS_CAN__VNET_A__ClearStats();
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN__VNET_A_;
void NET_SW_CAN__VNET_A__ClearStats();
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW__VNET_A_;
void NET_J1850_VPW__VNET_A__ClearStats();
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN__VNET_A_;
void NET_LSFT_CAN__VNET_A__ClearStats();
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708__VNET_A_;
void NET_J1708__VNET_A__ClearStats();
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI__VNET_A_;
void NET_neoVI__VNET_A__ClearStats();
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__VNET_A_;
void NET_HS_CAN2__VNET_A__ClearStats();
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__VNET_A_;
void NET_HS_CAN3__VNET_A__ClearStats();
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN__VNET_A_;
void NET_LIN__VNET_A__ClearStats();
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__VNET_A_;
void NET_LIN2__VNET_A__ClearStats();
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__VNET_A_;
void NET_LIN3__VNET_A__ClearStats();
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__VNET_A_;
void NET_LIN4__VNET_A__ClearStats();
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__VNET_A_;
void NET_CGI__VNET_A__ClearStats();
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K__VNET_A_;
void NET_ISO9141_KW2K__VNET_A__ClearStats();
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2__VNET_A_;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats();
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3__VNET_A_;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats();
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4__VNET_A_;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats();
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN__VNET_B_;
void NET_HS_CAN__VNET_B__ClearStats();
void NET_HS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN__VNET_B_;
void NET_MS_CAN__VNET_B__ClearStats();
void NET_MS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN__VNET_B_;
void NET_SW_CAN__VNET_B__ClearStats();
void NET_SW_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW__VNET_B_;
void NET_J1850_VPW__VNET_B__ClearStats();
void NET_J1850_VPW__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN__VNET_B_;
void NET_LSFT_CAN__VNET_B__ClearStats();
void NET_LSFT_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708__VNET_B_;
void NET_J1708__VNET_B__ClearStats();
void NET_J1708__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI__VNET_B_;
void NET_neoVI__VNET_B__ClearStats();
void NET_neoVI__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__VNET_B_;
void NET_HS_CAN2__VNET_B__ClearStats();
void NET_HS_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__VNET_B_;
void NET_HS_CAN3__VNET_B__ClearStats();
void NET_HS_CAN3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN__VNET_B_;
void NET_LIN__VNET_B__ClearStats();
void NET_LIN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__VNET_B_;
void NET_LIN2__VNET_B__ClearStats();
void NET_LIN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__VNET_B_;
void NET_LIN3__VNET_B__ClearStats();
void NET_LIN3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__VNET_B_;
void NET_LIN4__VNET_B__ClearStats();
void NET_LIN4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__VNET_B_;
void NET_CGI__VNET_B__ClearStats();
void NET_CGI__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K__VNET_B_;
void NET_ISO9141_KW2K__VNET_B__ClearStats();
void NET_ISO9141_KW2K__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2__VNET_B_;
void NET_ISO9141_KW2K_2__VNET_B__ClearStats();
void NET_ISO9141_KW2K_2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3__VNET_B_;
void NET_ISO9141_KW2K_3__VNET_B__ClearStats();
void NET_ISO9141_KW2K_3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4__VNET_B_;
void NET_ISO9141_KW2K_4__VNET_B__ClearStats();
void NET_ISO9141_KW2K_4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4__VNET_A_;
void NET_HS_CAN4__VNET_A__ClearStats();
void NET_HS_CAN4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5__VNET_A_;
void NET_HS_CAN5__VNET_A__ClearStats();
void NET_HS_CAN5__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5__VNET_A_;
void NET_LIN5__VNET_A__ClearStats();
void NET_LIN5__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4__VNET_B_;
void NET_HS_CAN4__VNET_B__ClearStats();
void NET_HS_CAN4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5__VNET_B_;
void NET_HS_CAN5__VNET_B__ClearStats();
void NET_HS_CAN5__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5__VNET_B_;
void NET_LIN5__VNET_B__ClearStats();
void NET_LIN5__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet_DAQ;
void NET_Ethernet_DAQ_ClearStats();
void NET_Ethernet_DAQ_GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet;
void NET_Ethernet_ClearStats();
void NET_Ethernet_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MOST__VNET_B_;
void NET_MOST__VNET_B__ClearStats();
void NET_MOST__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1A__VNET_B_;
void NET_FlexRay1A__VNET_B__ClearStats();
void NET_FlexRay1A__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1B__VNET_B_;
void NET_FlexRay1B__VNET_B__ClearStats();
void NET_FlexRay1B__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2A__VNET_B_;
void NET_FlexRay2A__VNET_B__ClearStats();
void NET_FlexRay2A__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2B__VNET_B_;
void NET_FlexRay2B__VNET_B__ClearStats();
void NET_FlexRay2B__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2;
void NET_SW_CAN2_ClearStats();
void NET_SW_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2__VNET_A_;
void NET_SW_CAN2__VNET_A__ClearStats();
void NET_SW_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2__VNET_B_;
void NET_SW_CAN2__VNET_B__ClearStats();
void NET_SW_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FSA;
void NET_FSA_ClearStats();
void NET_FSA_GetStats(NetworkStats * p_NetworkStats);
extern int NET_TCP;
void NET_TCP_ClearStats();
void NET_TCP_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6;
void NET_HS_CAN6_ClearStats();
void NET_HS_CAN6_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7;
void NET_HS_CAN7_ClearStats();
void NET_HS_CAN7_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6;
void NET_LIN6_ClearStats();
void NET_LIN6_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2;
void NET_LSFT_CAN2_ClearStats();
void NET_LSFT_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH01;
void NET_OP__BR__ETH01_ClearStats();
void NET_OP__BR__ETH01_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH02;
void NET_OP__BR__ETH02_ClearStats();
void NET_OP__BR__ETH02_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH03;
void NET_OP__BR__ETH03_ClearStats();
void NET_OP__BR__ETH03_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH04;
void NET_OP__BR__ETH04_ClearStats();
void NET_OP__BR__ETH04_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH05;
void NET_OP__BR__ETH05_ClearStats();
void NET_OP__BR__ETH05_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH06;
void NET_OP__BR__ETH06_ClearStats();
void NET_OP__BR__ETH06_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH07;
void NET_OP__BR__ETH07_ClearStats();
void NET_OP__BR__ETH07_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH08;
void NET_OP__BR__ETH08_ClearStats();
void NET_OP__BR__ETH08_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH09;
void NET_OP__BR__ETH09_ClearStats();
void NET_OP__BR__ETH09_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH10;
void NET_OP__BR__ETH10_ClearStats();
void NET_OP__BR__ETH10_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH11;
void NET_OP__BR__ETH11_ClearStats();
void NET_OP__BR__ETH11_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH12;
void NET_OP__BR__ETH12_ClearStats();
void NET_OP__BR__ETH12_GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay;
void NET_FlexRay_ClearStats();
void NET_FlexRay_GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2;
void NET_FlexRay2_ClearStats();
void NET_FlexRay2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6__VNET_A_;
void NET_LIN6__VNET_A__ClearStats();
void NET_LIN6__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6__VNET_B_;
void NET_LIN6__VNET_B__ClearStats();
void NET_LIN6__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6__VNET_A_;
void NET_HS_CAN6__VNET_A__ClearStats();
void NET_HS_CAN6__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6__VNET_B_;
void NET_HS_CAN6__VNET_B__ClearStats();
void NET_HS_CAN6__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7__VNET_A_;
void NET_HS_CAN7__VNET_A__ClearStats();
void NET_HS_CAN7__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7__VNET_B_;
void NET_HS_CAN7__VNET_B__ClearStats();
void NET_HS_CAN7__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2__VNET_A_;
void NET_LSFT_CAN2__VNET_A__ClearStats();
void NET_LSFT_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2__VNET_B_;
void NET_LSFT_CAN2__VNET_B__ClearStats();
void NET_LSFT_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet__VNET_A_;
void NET_Ethernet__VNET_A__ClearStats();
void NET_Ethernet__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet__VNET_B_;
void NET_Ethernet__VNET_B__ClearStats();
void NET_Ethernet__VNET_B__GetStats(NetworkStats * p_NetworkStats);

void SpyAppSig_CallAllHandlers();

// Application Signals

// Messages

typedef struct {
    unsigned char btPresent;  /// indicates message rxed at least once
    unsigned char  btPresentToggle; /// toggle every message rx
    unsigned char         btMultiFrameComplete; /// indicates frame is complete 
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
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[16]; /// Message data bytes
    unsigned char btInitialData[16]; /// Data bytes after initialization
} GenericMessage;

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[4096]; /// Message data bytes
    unsigned char btInitialData[4096]; /// Data bytes after initialization
} GenericLongMessage;

void Spy_EveryMessage(GenericMessage * p_Msg);
void Spy_EveryLongMessage(GenericLongMessage * p_Msg);
int GenericMessageTransmit(GenericMessage * p_Msg);
int GenericLongMessageTransmit(GenericLongMessage * p_Msg);
int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS);
extern int MG_OBDII_RESP_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} MG_OBDII_RESP_HS_CAN;


void MG_OBDII_RESP_HS_CAN_Init(MG_OBDII_RESP_HS_CAN * pMsg);
int MG_OBDII_RESP_HS_CAN_Transmit(MG_OBDII_RESP_HS_CAN * pMsg);
int MG_OBDII_RESP_HS_CAN_Transmit_raw(MG_OBDII_RESP_HS_CAN * pMsg);
#define MG_OBDII_RESP_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_OBDII_RESP_HS_CAN_Index, 0)
extern int DB_Report_Message_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC3_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC3_AIN_raw;
    double MISC4_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC4_AIN_raw;
    double MISC5_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC5_AIN_raw;
    double MISC6_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC6_AIN_raw;
    double MISC1; /// Min: 0 Max: 1 Units: 
    BYTE MISC1_raw;
    double MISC2; /// Min: 0 Max: 1 Units: 
    BYTE MISC2_raw;
    double MISC3; /// Min: 0 Max: 1 Units: 
    BYTE MISC3_raw;
    double MISC4; /// Min: 0 Max: 1 Units: 
    BYTE MISC4_raw;
    double MISC5; /// Min: 0 Max: 1 Units: 
    BYTE MISC5_raw;
    double MISC6; /// Min: 0 Max: 1 Units: 
    BYTE MISC6_raw;
    double LED1; /// Min: 0 Max: 1 Units: 
    BYTE LED1_raw;
    double LED2; /// Min: 0 Max: 1 Units: 
    BYTE LED2_raw;
    double LIN1; /// Min: 0 Max: 1 Units: 
    BYTE LIN1_raw;
    double LIN2; /// Min: 0 Max: 1 Units: 
    BYTE LIN2_raw;
} DB_Report_Message_neoVI;


void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg);
#define DB_Report_Message_neoVI_MISC3_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message_neoVI_LED1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 10, dPhysicalValue);
#define DB_Report_Message_neoVI_LED2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 11, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 12, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 13, dPhysicalValue);
#define DB_Report_Message_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_neoVI_Index, 0)
extern int DB_Report_Message__PWM__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM_In_1; /// Min: 0 Max: 4294967295 Units: 
    DWORD PWM_In_1_raw;
} DB_Report_Message__PWM__neoVI;


void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg);
#define DB_Report_Message__PWM__neoVI_PWM_In_1_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__PWM__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__PWM__neoVI_Index, 0)
extern int DB_Report_Message__VCAN_RF__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC1_AIN; /// Min: 0 Max: 41.55477149999999 Units: V
    WORD MISC1_AIN_raw;
    double MISC_1; /// Min: 0 Max: 1 Units: 
    BYTE MISC_1_raw;
    double MISC_2; /// Min: 0 Max: 1 Units: 
    BYTE MISC_2_raw;
    double MISC_3; /// Min: 0 Max: 1 Units: 
    BYTE MISC_3_raw;
    double MISC_4; /// Min: 0 Max: 1 Units: 
    BYTE MISC_4_raw;
    double Vehicle_Battery_Voltage; /// Min: 0 Max: 43.18778320312499 Units: V
    WORD Vehicle_Battery_Voltage_raw;
    double Temperature; /// Min: -215 Max: 114.677734375 Units: C
    WORD Temperature_raw;
    double Hardware_Revision; /// Min: 3 Max: 10.9921875 Units: 
    WORD Hardware_Revision_raw;
    double RTC_Battery_Measure_Enabled; /// Min: 0 Max: 1 Units: 
    BYTE RTC_Battery_Measure_Enabled_raw;
    double RTC_Battery_Voltage; /// Min: 0 Max: 3.29677734375 Units: V
    WORD RTC_Battery_Voltage_raw;
} DB_Report_Message__VCAN_RF__neoVI;


void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
#define DB_Report_Message__VCAN_RF__neoVI_MISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Vehicle_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Hardware_Revision_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Measure_Enabled_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__VCAN_RF__neoVI_Index, 0)
extern int DB_Report_Message__neoVI_Fire2__neoVI_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RTC_Battery; /// Min: 0 Max: 0 Units: V
    uint64 RTC_Battery_raw;
    double Temperature; /// Min: 0 Max: 0 Units: C
    uint64 Temperature_raw;
    double Vehicle_Battery; /// Min: 0 Max: 0 Units: V
    uint64 Vehicle_Battery_raw;
    double EMISC1_AIN; /// Min: 0 Max: 665.51513385 Units: V
    WORD EMISC1_AIN_raw;
    double EMISC2_AIN; /// Min: 0 Max: 665.51513385 Units: V
    WORD EMISC2_AIN_raw;
    double EMISC1_DIN; /// Min: 0 Max: 1 Units: 
    BYTE EMISC1_DIN_raw;
    double EMISC2_DIN; /// Min: 0 Max: 1 Units: 
    BYTE EMISC2_DIN_raw;
    double MISC5_DIN; /// Min: 0 Max: 1 Units: 
    BYTE MISC5_DIN_raw;
    double MISC6_DIN; /// Min: 0 Max: 1 Units: 
    BYTE MISC6_DIN_raw;
    double LED1; /// Min: 0 Max: 1 Units: 
    BYTE LED1_raw;
    double LED2; /// Min: 0 Max: 1 Units: 
    BYTE LED2_raw;
} DB_Report_Message__neoVI_Fire2__neoVI;


void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
#define DB_Report_Message__neoVI_Fire2__neoVI_RTC_Battery_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Vehicle_Battery_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC2_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC1_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC2_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC5_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC6_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_LED1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_LED2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 10, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Latitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Latitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Latitude_raw;
} DB_Report_Message__GPS_Latitude__neoVI;


void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Latitude__neoVI_Latitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Latitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Latitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Longitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Longitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Longitude_raw;
} DB_Report_Message__GPS_Longitude__neoVI;


void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Longitude__neoVI_Longitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Longitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Longitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Flags__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Update_Count; /// Min: 0 Max: 255 Units: 
    BYTE Update_Count_raw;
    double GPS_Date_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Date_Available_raw;
    double GPS_Time_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Time_Available_raw;
    double GPS_Accuracy_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Accuracy_Available_raw;
    double GPS_Bearing_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Bearing_Available_raw;
    double GPS_Speed_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Speed_Available_raw;
    double GPS_Altitude_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Altitude_Available_raw;
    double GPS_Lat_Lon_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Lat_Lon_Available_raw;
} DB_Report_Message__GPS_Flags__neoVI;


void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
#define DB_Report_Message__GPS_Flags__neoVI_Update_Count_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Date_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Time_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Accuracy_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Bearing_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Speed_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Altitude_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Lat_Lon_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Flags__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Altitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Altitude_Ellipse; /// Min: 0 Max: 0 Units: meters
    uint64 Altitude_Ellipse_raw;
} DB_Report_Message__GPS_Altitude__neoVI;


void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Altitude__neoVI_Altitude_Ellipse_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Altitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Altitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Speed; /// Min: 0 Max: 0 Units: m/s
    DWORD Speed_raw;
    double Bearing; /// Min: 0 Max: 0 Units: degrees
    DWORD Bearing_raw;
} DB_Report_Message__GPS_Speed_Bearing__neoVI;


void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Speed_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Bearing_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Accuracy__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Accuracy; /// Min: 0 Max: 0 Units: meters
    DWORD Accuracy_raw;
} DB_Report_Message__GPS_Accuracy__neoVI;


void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
#define DB_Report_Message__GPS_Accuracy__neoVI_Accuracy_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Accuracy__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Time__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: ms since 1/1/1970
    uint64 Timestamp_raw;
} DB_Report_Message__GPS_Time__neoVI;


void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
#define DB_Report_Message__GPS_Time__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Time__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Time__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviStartSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviStartSector_raw;
    double WiviEndSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviEndSector_raw;
} DB_Report_Message__WirelessneoVI_Sectors__neoVI;


void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviStartSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviEndSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviJob; /// Min: -128 Max: 127 Units: 
    BYTE WiviJob_raw;
    double WiviApkResponse; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponse_raw;
    double WiviDataTransferMediumChoice; /// Min: -128 Max: 127 Units: 
    BYTE WiviDataTransferMediumChoice_raw;
    double WiviApkResponseTo; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponseTo_raw;
    double WiviReserved0; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved0_raw;
    double WiviReserved1; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved1_raw;
} DB_Report_Message__WirelessneoVI_Signals__neoVI;


void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviJob_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponse_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviDataTransferMediumChoice_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponseTo_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved0_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0)
extern int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI;


void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
#define DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, 0)
extern int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_Message_Data_Lost_neoVI;


void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
#define DB_neoVI_Logger_Message_Data_Lost_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, 0)
extern int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI;


void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
#define DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, 0)
extern int DB_neoVI_Logger_woke_up_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SleepFlags; /// Min: 0 Max: 65535 Units: 
    WORD SleepFlags_raw;
    double WakeupFlags; /// Min: 0 Max: 65535 Units: 
    WORD WakeupFlags_raw;
    double WakeUpSms; /// Min: 0 Max: 1 Units: 
    BYTE WakeUpSms_raw;
    double WakeupSlaveA; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveA_raw;
    double WakeupSlaveB; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveB_raw;
    double WakeupMainVnet; /// Min: 0 Max: 1 Units: 
    BYTE WakeupMainVnet_raw;
    double WakeupUsb; /// Min: 0 Max: 1 Units: 
    BYTE WakeupUsb_raw;
    double PowerBoot; /// Min: 0 Max: 1 Units: 
    BYTE PowerBoot_raw;
    double LowVbatSleep; /// Min: 0 Max: 1 Units: 
    BYTE LowVbatSleep_raw;
    double NoCmSleep; /// Min: 0 Max: 1 Units: 
    BYTE NoCmSleep_raw;
} DB_neoVI_Logger_woke_up_neoVI;


void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
#define DB_neoVI_Logger_woke_up_neoVI_SleepFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeUpSms_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 4, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupMainVnet_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 5, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupUsb_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 6, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_PowerBoot_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 7, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_LowVbatSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 8, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_NoCmSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 9, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_woke_up_neoVI_Index, 0)
extern int DB_Report_Message_1_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_A; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_A_raw;
    double Channel_B; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_B_raw;
    double Channel_1_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_1_Differential__raw;
    double Channel_2_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_2_Differential__raw;
} DB_Report_Message_1_Analog_Card__neoVI;


void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_A_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_B_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_1_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_2_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_1_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_2_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_3_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_3_Differential__raw;
    double Channel_4_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_4_Differential__raw;
    double Channel_5_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_5_Differential__raw;
    double Channel_6_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_6_Differential__raw;
} DB_Report_Message_2_Analog_Card__neoVI;


void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_3_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_4_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_5_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_6_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_2_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_3_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_7_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_7_Differential__raw;
} DB_Report_Message_3_Analog_Card__neoVI;


void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_3_Analog_Card__neoVI_Channel_7_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_3_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_3_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_4_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 Timestamp_raw;
} DB_Report_Message_4_Analog_Card__neoVI;


void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_4_Analog_Card__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_4_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_4_Analog_Card__neoVI_Index, 0)
extern int DB_Time_Resync_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: -0 Max: 0 Units: ms
    uint64 Timestamp_raw;
} DB_Time_Resync_neoVI;


void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg);
#define DB_Time_Resync_neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, 0, dPhysicalValue);
#define DB_Time_Resync_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Time_Resync_neoVI_Index, 0)
extern int DB_VNET_Clock_Edge_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_Clock_Edge_neoVI;


void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg);
#define DB_VNET_Clock_Edge_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_Clock_Edge_neoVI_Index, 0)
extern int DB_VNET_A_Stats_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double msgTotal; /// Min: 0 Max: 65535 Units: 
    WORD msgTotal_raw;
    double rxSize; /// Min: 0 Max: 255 Units: 
    BYTE rxSize_raw;
    double scCnt; /// Min: 0 Max: 255 Units: 
    BYTE scCnt_raw;
    double yields; /// Min: 0 Max: 65535 Units: 
    WORD yields_raw;
    double bytesRead; /// Min: 0 Max: 65535 Units: 
    WORD bytesRead_raw;
} DB_VNET_A_Stats_neoVI;


void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg);
#define DB_VNET_A_Stats_neoVI_msgTotal_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 0, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_rxSize_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 1, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_scCnt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 2, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_yields_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 3, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_bytesRead_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 4, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Stats_neoVI_Index, 0)
extern int DB_VNET_A_Reboot_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_A_Reboot_neoVI;


void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg);
#define DB_VNET_A_Reboot_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Reboot_neoVI_Index, 0)
extern int DB_neoVI_Went_To_Sleep_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Went_To_Sleep_neoVI;


void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
#define DB_neoVI_Went_To_Sleep_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Went_To_Sleep_neoVI_Index, 0)
extern int DB_Device_subsystem_restarted__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_Device_subsystem_restarted__neoVI;


void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg);
#define DB_Device_subsystem_restarted__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Device_subsystem_restarted__neoVI_Index, 0)
extern int DB_Ethernet_DAQ_Report_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Recording; /// Min: 0 Max: 1 Units: 
    BYTE Recording_raw;
    double FPGA_Alive; /// Min: 0 Max: 1 Units: 
    BYTE FPGA_Alive_raw;
    double Bad_Chip; /// Min: 0 Max: 1 Units: 
    BYTE Bad_Chip_raw;
    double Raw_MAC_Mode; /// Min: 0 Max: 1 Units: 
    BYTE Raw_MAC_Mode_raw;
    double IPv4_Filter; /// Min: 0 Max: 1 Units: 
    BYTE IPv4_Filter_raw;
    double RxOverflow; /// Min: 0 Max: 1 Units: 
    BYTE RxOverflow_raw;
    double CmdBusy; /// Min: 0 Max: 1 Units: 
    BYTE CmdBusy_raw;
    double LogTO; /// Min: 0 Max: 1 Units: 
    BYTE LogTO_raw;
    double SockActivityTO; /// Min: 0 Max: 1 Units: 
    BYTE SockActivityTO_raw;
    double FPGAComTO; /// Min: 0 Max: 255 Units: 
    BYTE FPGAComTO_raw;
    double SockConfigTO; /// Min: 0 Max: 255 Units: 
    BYTE SockConfigTO_raw;
    double SockDiscon; /// Min: 0 Max: 255 Units: 
    BYTE SockDiscon_raw;
    double WcfSM; /// Min: 0 Max: 255 Units: 
    BYTE WcfSM_raw;
    double TxMsgsPending; /// Min: 0 Max: 255 Units: 
    BYTE TxMsgsPending_raw;
} DB_Ethernet_DAQ_Report_neoVI;


void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
#define DB_Ethernet_DAQ_Report_neoVI_Recording_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 0, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGA_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 1, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Bad_Chip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 2, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Raw_MAC_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 3, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_IPv4_Filter_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 4, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_RxOverflow_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 5, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_CmdBusy_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 6, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_LogTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 7, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockActivityTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 8, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGAComTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 9, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockConfigTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 10, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockDiscon_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 11, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_WcfSM_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 12, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_TxMsgsPending_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 13, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Ethernet_DAQ_Report_neoVI_Index, 0)
extern int DB_neoVI_Status_Update_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Type; /// Min: 0 Max: 255 Units: 
    BYTE Type_raw;
    double ChangeCount; /// Min: 0 Max: 255 Units: 
    BYTE ChangeCount_raw;
} DB_neoVI_Status_Update_neoVI;


void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg);
#define DB_neoVI_Status_Update_neoVI_Type_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ChangeCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Status_Update_neoVI_Index, 0)
extern int DB_Scc_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double FvA; /// Min: 0 Max: 1 Units: 
    BYTE FvA_raw;
    double ScA; /// Min: 0 Max: 1 Units: 
    BYTE ScA_raw;
    double Atv; /// Min: 0 Max: 1 Units: 
    BYTE Atv_raw;
    double sip; /// Min: 0 Max: 1 Units: 
    BYTE sip_raw;
    double pt; /// Min: 0 Max: 4294967295 Units: 
    DWORD pt_raw;
    double Req; /// Min: 0 Max: 255 Units: 
    BYTE Req_raw;
} DB_Scc_Status_neoVI;


void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg);
#define DB_Scc_Status_neoVI_FvA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Scc_Status_neoVI_ScA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Scc_Status_neoVI_Atv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Scc_Status_neoVI_sip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Scc_Status_neoVI_pt_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Scc_Status_neoVI_Req_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Scc_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Scc_Status_neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM1_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM1_IN_raw;
    double PWM2_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM2_IN_raw;
    double PWM3_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM3_IN_raw;
    double PWM4_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM4_IN_raw;
    double PWM5_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM5_IN_raw;
    double PWM6_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM6_IN_raw;
    double PWM7_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM7_IN_raw;
    double PWM8_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM8_IN_raw;
} DB_Report_Message__Analog_Card_PWM_Inputs__neoVI;


void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM1_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM2_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM3_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM4_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM5_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM6_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM7_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM8_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM1__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM1__neoVI;


void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM2__neoVI;


void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM3__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM3__neoVI;


void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM4__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM4__neoVI;


void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM5__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM5__neoVI;


void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM6__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM6__neoVI;


void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM7__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM7__neoVI;


void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM8__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM8__neoVI;


void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0)
extern int DB_neoVI_Device_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double HID_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD HID_Temperature__C__raw;
    double HID_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD HID_Bus_Voltage__V__raw;
    double VNET_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD VNET_Temperature__C__raw;
    double VNET_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD VNET_Bus_Voltage__V__raw;
} DB_neoVI_Device_Status_neoVI;


void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg);
#define DB_neoVI_Device_Status_neoVI_HID_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_HID_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_neoVI_Index, 0)
extern int DB_neoVI_Device_Status_2_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Disk_Space_Avail__WiVI__KB; /// Min: 0 Max: 4294967295 Units: KB
    DWORD Disk_Space_Avail__WiVI__KB_raw;
    double Power_Supply_Voltage; /// Min: 0 Max: 255.99609375 Units: V
    WORD Power_Supply_Voltage_raw;
    double Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD Temperature__C__raw;
} DB_neoVI_Device_Status_2_neoVI;


void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
#define DB_neoVI_Device_Status_2_neoVI_Disk_Space_Avail__WiVI__KB_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Power_Supply_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_2_neoVI_Index, 0)
extern int DB_Trace_Logger_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double State; /// Min: 0 Max: 8 Units: 
    BYTE State_raw;
    double Debug_Level; /// Min: 0 Max: 3 Units: 
    BYTE Debug_Level_raw;
    double IP_MSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_MSB__raw;
    double IP; /// Min: 0 Max: 255 Units: 
    BYTE IP_raw;
    double IP_sig4; /// Min: 0 Max: 255 Units: 
    BYTE IP_sig4_raw;
    double IP_LSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_LSB__raw;
    double Port; /// Min: 0 Max: 65535 Units: 
    WORD Port_raw;
} DB_Trace_Logger_Status_neoVI;

#pragma warning(disable : 4005)
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Direct_Connect 1
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connecting 2
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Reconnecting 3
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connected 4
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Set_Debug_Level 5
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closing 6
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closed 7
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Timestamp 8
#pragma warning(default : 4005)

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg);
#define DB_Trace_Logger_Status_neoVI_State_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Debug_Level_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_MSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_sig4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_LSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Port_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 6, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trace_Logger_Status_neoVI_Index, 0)
extern int DB_Trigger_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Logger_triggered; /// Min: 0 Max: 2 Units: 
    BYTE Logger_triggered_raw;
    double Pre_trigger_size; /// Min: 0 Max: 4294967295 Units: 
    DWORD Pre_trigger_size_raw;
    double Collection_index; /// Min: 0 Max: 255 Units: 
    BYTE Collection_index_raw;
} DB_Trigger_neoVI;

#pragma warning(disable : 4005)
#define DB_Trigger_neoVI_$_Logger_triggered_$$_NO_TRG 0
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_msg_ 1
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_ms_ 2
#pragma warning(default : 4005)

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg);
#define DB_Trigger_neoVI_Logger_triggered_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 0, dPhysicalValue);
#define DB_Trigger_neoVI_Pre_trigger_size_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 1, dPhysicalValue);
#define DB_Trigger_neoVI_Collection_index_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 2, dPhysicalValue);
#define DB_Trigger_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trigger_neoVI_Index, 0)
extern int DB_Ethernet_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Link_Status; /// Min: 0 Max: 1 Units: 
    BYTE Link_Status_raw;
    double Link_Speed; /// Min: 0 Max: 2 Units: 
    BYTE Link_Speed_raw;
    double Link_Duplex; /// Min: 0 Max: 1 Units: 
    BYTE Link_Duplex_raw;
} DB_Ethernet_Status_neoVI;

#pragma warning(disable : 4005)
#define DB_Ethernet_Status_neoVI_$_Link_Status_$$_Link_Down 0
#define DB_Ethernet_Status_neoVI_$_Link_Status_$$_Link_Up 1
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_10Mbps 0
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_100Mbps 1
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_1000Mbps 2
#define DB_Ethernet_Status_neoVI_$_Link_Duplex_$$_Half_Duplex 0
#define DB_Ethernet_Status_neoVI_$_Link_Duplex_$$_Full_Duplex 1
#pragma warning(default : 4005)

void DB_Ethernet_Status_neoVI_Init(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_Transmit(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_Transmit_raw(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_UpdateBytesFromSignals(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_Status_neoVI * pMsg);
#define DB_Ethernet_Status_neoVI_Link_Status_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_Link_Speed_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_Link_Duplex_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Ethernet_Status_neoVI_Index, 0)
extern int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Network; /// Min: 0 Max: 11 Units: 
    BYTE Network_raw;
    double Link_Status; /// Min: 0 Max: 1 Units: 
    BYTE Link_Status_raw;
} DB_OP__BR__Ethernet___Link_status_changed_neoVI;

#pragma warning(disable : 4005)
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH1 0
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH2 1
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH3 2
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH4 3
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$________________OP_ETH5 4
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH6 5
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH7 6
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH8 7
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$________________OP_ETH9 8
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH10 9
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH11 10
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH12 11
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Link_Status_$$_Down 0
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Link_Status_$$_Up 1
#pragma warning(default : 4005)

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit_raw(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromRawSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_Network_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 0, dPhysicalValue);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_Link_Status_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 1, dPhysicalValue);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 0)
extern int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Period; /// Min: 0 Max: 4294967295 Units: us
    DWORD Period_raw;
    double Pulse_Width; /// Min: 0 Max: 4294967295 Units: us
    DWORD Pulse_Width_raw;
} DB_FIRE2_Report_Message_PWM_IN_1__neoVI;


void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Period_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 0, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Pulse_Width_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 1, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 0)
extern int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Period; /// Min: 0 Max: 4294967295 Units: us
    DWORD Period_raw;
    double Pulse_Width; /// Min: 0 Max: 4294967295 Units: us
    DWORD Pulse_Width_raw;
} DB_FIRE2_Report_Message_PWM_IN_2__neoVI;


void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Period_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 0, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Pulse_Width_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 1, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 0)
extern int DB_Hardware_Latency_Test_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Latency__us_; /// Min: 0 Max: 18446744073709551615 Units: us
    uint64 Latency__us__raw;
} DB_Hardware_Latency_Test_neoVI;


void DB_Hardware_Latency_Test_neoVI_Init(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_Transmit(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_Transmit_raw(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromSignals(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromRawSignals(DB_Hardware_Latency_Test_neoVI * pMsg);
#define DB_Hardware_Latency_Test_neoVI_Latency__us__PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, 0, dPhysicalValue);
#define DB_Hardware_Latency_Test_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Hardware_Latency_Test_neoVI_Index, 0)
extern int DB_neoVI_MIC_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Button_Pressed; /// Min: 0 Max: 1 Units: 
    BYTE Button_Pressed_raw;
} DB_neoVI_MIC_neoVI;


void DB_neoVI_MIC_neoVI_Init(DB_neoVI_MIC_neoVI * pMsg);
int DB_neoVI_MIC_neoVI_Transmit(DB_neoVI_MIC_neoVI * pMsg);
int DB_neoVI_MIC_neoVI_Transmit_raw(DB_neoVI_MIC_neoVI * pMsg);
int DB_neoVI_MIC_neoVI_UpdateBytesFromSignals(DB_neoVI_MIC_neoVI * pMsg);
int DB_neoVI_MIC_neoVI_UpdateBytesFromRawSignals(DB_neoVI_MIC_neoVI * pMsg);
#define DB_neoVI_MIC_neoVI_Button_Pressed_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_MIC_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_MIC_neoVI_Index, 0)
extern int DB_neoVI_Device_Status_neoVI_db49_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Bus_Voltage__V_; /// Min: 0 Max: 0 Units: V
    DWORD Bus_Voltage__V__raw;
    double HID_Temperature__C_; /// Min: 0 Max: 0 Units: deg C
    DWORD HID_Temperature__C__raw;
    double MCHIP_Temperature__C_; /// Min: 0 Max: 0 Units: deg C
    DWORD MCHIP_Temperature__C__raw;
    double ZCHIP_Temperature__C_; /// Min: 0 Max: 0 Units: deg C
    DWORD ZCHIP_Temperature__C__raw;
} DB_neoVI_Device_Status_neoVI_db49;


void DB_neoVI_Device_Status_neoVI_db49_Init(DB_neoVI_Device_Status_neoVI_db49 * pMsg);
int DB_neoVI_Device_Status_neoVI_db49_Transmit(DB_neoVI_Device_Status_neoVI_db49 * pMsg);
int DB_neoVI_Device_Status_neoVI_db49_Transmit_raw(DB_neoVI_Device_Status_neoVI_db49 * pMsg);
int DB_neoVI_Device_Status_neoVI_db49_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI_db49 * pMsg);
int DB_neoVI_Device_Status_neoVI_db49_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI_db49 * pMsg);
#define DB_neoVI_Device_Status_neoVI_db49_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_db49_HID_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_db49_MCHIP_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_db49_ZCHIP_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, 3, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_db49_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_neoVI_db49_Index, 0)
void SpyMsg_MG_OBDII_RESP_HS_CAN(MG_OBDII_RESP_HS_CAN * pMG_OBDII_RESP_HS_CAN);

#endif // VSPY_GENERATED_HEADER
