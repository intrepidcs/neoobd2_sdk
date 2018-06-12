// vspy generated implementation file
#include "vspy.h"
#include "stdarg.h"

void * g_uiHandle = NULL;
unsigned char g_bUseExtendedIdBit = 0;
long g_lStartDelay = 0;

#define MIN_VSPY_H_VERSION     1

int getStartDelay()
{
    return g_lStartDelay;
}

void setStartDelay(int delay)
{
    if ((delay < 0) || (delay > 99999))
    {
        Printf("setStartDelay was passed an invalid value: %d\n", delay);
        delay = 0;
    }
    g_lStartDelay = delay;
}

int CM_GetVSPY_C_H_Version()
{
    return MIN_VSPY_H_VERSION;
}

void SetUseExtendedIdBit()
{
    g_bUseExtendedIdBit = 1;
}

int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize)
{
    int nLen;
    wchar_t *pWideBuffer = malloc(iBufferSize * sizeof(wchar_t));
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    if (CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pWideBuffer, iBufferSize))
    {
        nLen = WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), NULL, 0, NULL, NULL);
        WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), pName, nLen, NULL, NULL);
        pName[nLen] = 0;
        free(pWideBuffer);
        return 1;
    }
    free(pWideBuffer);
    return 0;
}

int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)
{
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    return CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pName, iBufferSize);
}

int SpyViewGetCount()
{
    int temp = 0;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWCOUNT, 0, &temp);
    return temp;
}

int SpyViewGetType(void* pView)
{
    stGetViewTypeArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWTYPE, 0, &args);
    return args.OutType;
}

void* SpyViewGetHandle(int index){

    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWHANDLE, index, &temp);
    return temp;
}

void SpyViewShow(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEW, 0, pView);
}

void SpyViewHide(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_HIDEVIEW, 0, pView);
}

int SpyViewIsVisible(void* pView)
{
    stGetViewIsVisibleArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWISVISIBLE, 0, &args);
    return args.OutVisible;
}

void* SpyViewShowByType(int type)
{
    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEWBYTYPE, type, &temp);
    return temp;
}

void* SpyViewGetProcAddress(void* pView, const char* szProcName)
{
    stGetViewProcAddressArgs args;
    args.InForm = pView;
    args.InFunctionName = szProcName;
    args.OutFunctionPtr = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWPROCADDRESS, 0, &args);
    return args.OutFunctionPtr;
}

double AS_Get(int index)
{
    double dTemp;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL, index, &dTemp);
    return dTemp;
}

void AS_Set(int index, double dValue)
{
    double dTemp = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL, index, &dTemp);
}

struct AppSigValue
{
    int nOffset;
    double dValue;
};

double AS_GetAt(int index, int element)
{
    struct AppSigValue sVal;
    if (element == 0)
        return AS_Get(index);
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_AT, index, &sVal);
    return sVal.dValue;
}

void AS_SetAt(int index, int element, double dValue)
{
    struct AppSigValue sVal;
    if (element == 0)
    {
        AS_Set(index, dValue);
        return;
    }
    sVal.dValue = dValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_AT, index, &sVal);
}

int AS_GetText(int nIndex, void * szValue, int nLength)
{
    wchar_t szTemp[1024];
    int nLen = nLength;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, nIndex, szTemp);
    if (nLen <= 0)
        nLen = min(WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), NULL, 0, NULL, NULL), 1023);
    if (wcsncmp(szTemp, L"#0x", 3) == 0)  // Binary
    {
        wchar_t szByte[] = L"00";
        int nByte;
        nLen = ((int)wcslen(szTemp) - 3) / 2;
        for (nByte = 0; nByte < nLen; ++nByte)
        {
            szByte[0] = szTemp[3 + nByte * 2];
            szByte[1] = szTemp[4 + nByte * 2];
            *((BYTE *)szValue + nByte) = (BYTE)wcstol(szByte, NULL, 16);
        }
        return nLen;
    }
    WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), (char *)szValue, nLen, NULL, NULL);
    *((char *)szValue + nLen) = 0;
    return (int)strlen(szValue);
}

int AS_SetText(int nIndex, void * szValue, int nLength)
{
    BOOL bIsBinary = 0;
    wchar_t szTemp[1024];
    int nLen = nLength;
    if (nLen <= 0)
        nLen = min(MultiByteToWideChar(0, 0, (char *)szValue, (int)strlen(szValue), NULL, 0), 1023);
    else
    {
        int nByte;
        wcscpy_s(szTemp, 4, L"#0x");
        for (nByte = 0; nByte < nLength; ++nByte)
        {
            if ((*((BYTE *)szValue) + nByte) < 32)
                bIsBinary = 1;
            swprintf(szTemp + (nByte * 2) + 3, _countof(szTemp) - (nByte * 2) - 3, L"%02x",
                     (*((BYTE *)szValue) + nByte));
        }
    }
    if (bIsBinary)
    {
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return nLength;
    }
    else
    {
        MultiByteToWideChar(0, 0, szValue, (int)strlen(szValue), szTemp, nLen);
        szTemp[nLen] = 0;
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return (int)strlen(szValue);
    }
}

int AS_GetTextW(int index, wchar_t * szValue)
{
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, index, szValue);
    return (int)wcslen(szValue);
}

struct AppSigTextValue
{
    int nOffset;
    wchar_t *szValue;
};

int AS_GetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int AS_SetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int CanNetworksInUse[] = {
    0,  //HS_CAN
    1,  //MS_CAN
};

int Spy_NetworksInUse()
{
    return _countof(CanNetworksInUse);
}

int Spy_TranslateNetwork(int nNetworkOffset)
{
    if ((nNetworkOffset <= 1) || (nNetworkOffset > Spy_NetworksInUse()))
        return CanNetworksInUse[0] + 1;
    else
        return CanNetworksInUse[nNetworkOffset - 1] + 1;
}
int Spy_UntranslateNetwork(int nNetwork)
{
    int can;
    for (can = 0; can < Spy_NetworksInUse(); ++can)
    {
        if (CanNetworksInUse[can] + 1 == nNetwork)
            return can + 1;
    }
    return 1;
}

int Spy_LINIndex(int iNetwork)
{
    if (iNetwork == NET_LIN2)
        return 2;
    else if (iNetwork == NET_LIN3)
        return 3;
    else if (iNetwork == NET_LIN4)
        return 4;
    else if (iNetwork == NET_LIN2__VNET_A_)
        return 2;
    else if (iNetwork == NET_LIN3__VNET_A_)
        return 3;
    else if (iNetwork == NET_LIN4__VNET_A_)
        return 4;
    else if (iNetwork == NET_LIN2__VNET_B_)
        return 2;
    else if (iNetwork == NET_LIN3__VNET_B_)
        return 3;
    else if (iNetwork == NET_LIN4__VNET_B_)
        return 4;
    else
        return 1;
}

// network index variables - identify networks in vspy
int NET_HS_CAN = 0;
void NET_HS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN,0);
}
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN,p_NetworkStats);
}
int NET_MS_CAN = 1;
void NET_MS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN,0);
}
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN,p_NetworkStats);
}
int NET_SW_CAN = 2;
void NET_SW_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN,0);
}
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN,p_NetworkStats);
}
int NET_J1850_VPW = 3;
void NET_J1850_VPW_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW,0);
}
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW,p_NetworkStats);
}
int NET_ISO9141_KW2K = 4;
void NET_ISO9141_KW2K_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K,0);
}
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K,p_NetworkStats);
}
int NET_LSFT_CAN = 5;
void NET_LSFT_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN,0);
}
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN,p_NetworkStats);
}
int NET_J1850_PWM = 6;
void NET_J1850_PWM_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_PWM,0);
}
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_PWM,p_NetworkStats);
}
int NET_J1708 = 7;
void NET_J1708_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708,0);
}
void NET_J1708_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708,p_NetworkStats);
}
int NET_neoVI = 8;
void NET_neoVI_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI,0);
}
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI,p_NetworkStats);
}
int NET_HS_CAN2 = 9;
void NET_HS_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2,0);
}
void NET_HS_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2,p_NetworkStats);
}
int NET_HS_CAN3 = 10;
void NET_HS_CAN3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3,0);
}
void NET_HS_CAN3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3,p_NetworkStats);
}
int NET_LIN2 = 11;
void NET_LIN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2,0);
}
void NET_LIN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2,p_NetworkStats);
}
int NET_LIN3 = 12;
void NET_LIN3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3,0);
}
void NET_LIN3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3,p_NetworkStats);
}
int NET_LIN4 = 13;
void NET_LIN4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4,0);
}
void NET_LIN4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4,p_NetworkStats);
}
int NET_CGI = 14;
void NET_CGI_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI,0);
}
void NET_CGI_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI,p_NetworkStats);
}
int NET_LIN = 15;
void NET_LIN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN,0);
}
void NET_LIN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN,p_NetworkStats);
}
int NET_ISO9141_KW2K_2 = 16;
void NET_ISO9141_KW2K_2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2,0);
}
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2,p_NetworkStats);
}
int NET_ISO9141_KW2K_3 = 17;
void NET_ISO9141_KW2K_3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3,0);
}
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3,p_NetworkStats);
}
int NET_ISO9141_KW2K_4 = 18;
void NET_ISO9141_KW2K_4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4,0);
}
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4,p_NetworkStats);
}
int NET_HS_CAN4 = 19;
void NET_HS_CAN4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4,0);
}
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4,p_NetworkStats);
}
int NET_HS_CAN5 = 20;
void NET_HS_CAN5_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5,0);
}
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5,p_NetworkStats);
}
int NET_UART = 21;
void NET_UART_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART,0);
}
void NET_UART_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART,p_NetworkStats);
}
int NET_UART2 = 22;
void NET_UART2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART2,0);
}
void NET_UART2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART2,p_NetworkStats);
}
int NET_LIN5 = 23;
void NET_LIN5_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5,0);
}
void NET_LIN5_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5,p_NetworkStats);
}
int NET_MOST__VNET_A_ = 24;
void NET_MOST__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MOST__VNET_A_,0);
}
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MOST__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1A__VNET_A_ = 25;
void NET_FlexRay1A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1A__VNET_A_,0);
}
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1B__VNET_A_ = 26;
void NET_FlexRay1B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1B__VNET_A_,0);
}
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1B__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2A__VNET_A_ = 27;
void NET_FlexRay2A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2A__VNET_A_,0);
}
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2B__VNET_A_ = 28;
void NET_FlexRay2B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2B__VNET_A_,0);
}
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2B__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN__VNET_A_ = 29;
void NET_HS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN__VNET_A_,0);
}
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN__VNET_A_,p_NetworkStats);
}
int NET_MS_CAN__VNET_A_ = 30;
void NET_MS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN__VNET_A_,0);
}
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN__VNET_A_,p_NetworkStats);
}
int NET_SW_CAN__VNET_A_ = 31;
void NET_SW_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN__VNET_A_,0);
}
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1850_VPW__VNET_A_ = 32;
void NET_J1850_VPW__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW__VNET_A_,0);
}
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW__VNET_A_,p_NetworkStats);
}
int NET_LSFT_CAN__VNET_A_ = 33;
void NET_LSFT_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN__VNET_A_,0);
}
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1708__VNET_A_ = 34;
void NET_J1708__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708__VNET_A_,0);
}
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708__VNET_A_,p_NetworkStats);
}
int NET_neoVI__VNET_A_ = 35;
void NET_neoVI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI__VNET_A_,0);
}
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN2__VNET_A_ = 36;
void NET_HS_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__VNET_A_,0);
}
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN3__VNET_A_ = 37;
void NET_HS_CAN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__VNET_A_,0);
}
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__VNET_A_,p_NetworkStats);
}
int NET_LIN__VNET_A_ = 38;
void NET_LIN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN__VNET_A_,0);
}
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN__VNET_A_,p_NetworkStats);
}
int NET_LIN2__VNET_A_ = 39;
void NET_LIN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__VNET_A_,0);
}
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__VNET_A_,p_NetworkStats);
}
int NET_LIN3__VNET_A_ = 40;
void NET_LIN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__VNET_A_,0);
}
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__VNET_A_,p_NetworkStats);
}
int NET_LIN4__VNET_A_ = 41;
void NET_LIN4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__VNET_A_,0);
}
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__VNET_A_,p_NetworkStats);
}
int NET_CGI__VNET_A_ = 42;
void NET_CGI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__VNET_A_,0);
}
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K__VNET_A_ = 43;
void NET_ISO9141_KW2K__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K__VNET_A_,0);
}
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_2__VNET_A_ = 44;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2__VNET_A_,0);
}
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_3__VNET_A_ = 45;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3__VNET_A_,0);
}
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_4__VNET_A_ = 46;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4__VNET_A_,0);
}
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN__VNET_B_ = 47;
void NET_HS_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN__VNET_B_,0);
}
void NET_HS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN__VNET_B_,p_NetworkStats);
}
int NET_MS_CAN__VNET_B_ = 48;
void NET_MS_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN__VNET_B_,0);
}
void NET_MS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN__VNET_B_,p_NetworkStats);
}
int NET_SW_CAN__VNET_B_ = 49;
void NET_SW_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN__VNET_B_,0);
}
void NET_SW_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN__VNET_B_,p_NetworkStats);
}
int NET_J1850_VPW__VNET_B_ = 50;
void NET_J1850_VPW__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW__VNET_B_,0);
}
void NET_J1850_VPW__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW__VNET_B_,p_NetworkStats);
}
int NET_LSFT_CAN__VNET_B_ = 51;
void NET_LSFT_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN__VNET_B_,0);
}
void NET_LSFT_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN__VNET_B_,p_NetworkStats);
}
int NET_J1708__VNET_B_ = 52;
void NET_J1708__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708__VNET_B_,0);
}
void NET_J1708__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708__VNET_B_,p_NetworkStats);
}
int NET_neoVI__VNET_B_ = 53;
void NET_neoVI__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI__VNET_B_,0);
}
void NET_neoVI__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN2__VNET_B_ = 54;
void NET_HS_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__VNET_B_,0);
}
void NET_HS_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN3__VNET_B_ = 55;
void NET_HS_CAN3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__VNET_B_,0);
}
void NET_HS_CAN3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__VNET_B_,p_NetworkStats);
}
int NET_LIN__VNET_B_ = 56;
void NET_LIN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN__VNET_B_,0);
}
void NET_LIN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN__VNET_B_,p_NetworkStats);
}
int NET_LIN2__VNET_B_ = 57;
void NET_LIN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__VNET_B_,0);
}
void NET_LIN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__VNET_B_,p_NetworkStats);
}
int NET_LIN3__VNET_B_ = 58;
void NET_LIN3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__VNET_B_,0);
}
void NET_LIN3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__VNET_B_,p_NetworkStats);
}
int NET_LIN4__VNET_B_ = 59;
void NET_LIN4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__VNET_B_,0);
}
void NET_LIN4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__VNET_B_,p_NetworkStats);
}
int NET_CGI__VNET_B_ = 60;
void NET_CGI__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__VNET_B_,0);
}
void NET_CGI__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K__VNET_B_ = 61;
void NET_ISO9141_KW2K__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K__VNET_B_,0);
}
void NET_ISO9141_KW2K__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_2__VNET_B_ = 62;
void NET_ISO9141_KW2K_2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2__VNET_B_,0);
}
void NET_ISO9141_KW2K_2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_3__VNET_B_ = 63;
void NET_ISO9141_KW2K_3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3__VNET_B_,0);
}
void NET_ISO9141_KW2K_3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_4__VNET_B_ = 64;
void NET_ISO9141_KW2K_4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4__VNET_B_,0);
}
void NET_ISO9141_KW2K_4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN4__VNET_A_ = 65;
void NET_HS_CAN4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4__VNET_A_,0);
}
void NET_HS_CAN4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN5__VNET_A_ = 66;
void NET_HS_CAN5__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5__VNET_A_,0);
}
void NET_HS_CAN5__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5__VNET_A_,p_NetworkStats);
}
int NET_LIN5__VNET_A_ = 67;
void NET_LIN5__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5__VNET_A_,0);
}
void NET_LIN5__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN4__VNET_B_ = 68;
void NET_HS_CAN4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4__VNET_B_,0);
}
void NET_HS_CAN4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN5__VNET_B_ = 69;
void NET_HS_CAN5__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5__VNET_B_,0);
}
void NET_HS_CAN5__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5__VNET_B_,p_NetworkStats);
}
int NET_LIN5__VNET_B_ = 70;
void NET_LIN5__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5__VNET_B_,0);
}
void NET_LIN5__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5__VNET_B_,p_NetworkStats);
}
int NET_Ethernet_DAQ = 71;
void NET_Ethernet_DAQ_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet_DAQ,0);
}
void NET_Ethernet_DAQ_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet_DAQ,p_NetworkStats);
}
int NET_Ethernet = 72;
void NET_Ethernet_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet,0);
}
void NET_Ethernet_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet,p_NetworkStats);
}
int NET_MOST__VNET_B_ = 73;
void NET_MOST__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MOST__VNET_B_,0);
}
void NET_MOST__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MOST__VNET_B_,p_NetworkStats);
}
int NET_FlexRay1A__VNET_B_ = 74;
void NET_FlexRay1A__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1A__VNET_B_,0);
}
void NET_FlexRay1A__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1A__VNET_B_,p_NetworkStats);
}
int NET_FlexRay1B__VNET_B_ = 75;
void NET_FlexRay1B__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1B__VNET_B_,0);
}
void NET_FlexRay1B__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1B__VNET_B_,p_NetworkStats);
}
int NET_FlexRay2A__VNET_B_ = 76;
void NET_FlexRay2A__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2A__VNET_B_,0);
}
void NET_FlexRay2A__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2A__VNET_B_,p_NetworkStats);
}
int NET_FlexRay2B__VNET_B_ = 77;
void NET_FlexRay2B__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2B__VNET_B_,0);
}
void NET_FlexRay2B__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2B__VNET_B_,p_NetworkStats);
}
int NET_SW_CAN2 = 78;
void NET_SW_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2,0);
}
void NET_SW_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2,p_NetworkStats);
}
int NET_SW_CAN2__VNET_A_ = 79;
void NET_SW_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2__VNET_A_,0);
}
void NET_SW_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2__VNET_A_,p_NetworkStats);
}
int NET_SW_CAN2__VNET_B_ = 80;
void NET_SW_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2__VNET_B_,0);
}
void NET_SW_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2__VNET_B_,p_NetworkStats);
}
int NET_FSA = 81;
void NET_FSA_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FSA,0);
}
void NET_FSA_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FSA,p_NetworkStats);
}
int NET_TCP = 82;
void NET_TCP_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_TCP,0);
}
void NET_TCP_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_TCP,p_NetworkStats);
}
int NET_HS_CAN6 = 83;
void NET_HS_CAN6_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6,0);
}
void NET_HS_CAN6_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6,p_NetworkStats);
}
int NET_HS_CAN7 = 84;
void NET_HS_CAN7_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7,0);
}
void NET_HS_CAN7_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7,p_NetworkStats);
}
int NET_LIN6 = 85;
void NET_LIN6_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6,0);
}
void NET_LIN6_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6,p_NetworkStats);
}
int NET_LSFT_CAN2 = 86;
void NET_LSFT_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2,0);
}
void NET_LSFT_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2,p_NetworkStats);
}
int NET_OP__BR__ETH01 = 87;
void NET_OP__BR__ETH01_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH01,0);
}
void NET_OP__BR__ETH01_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH01,p_NetworkStats);
}
int NET_OP__BR__ETH02 = 88;
void NET_OP__BR__ETH02_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH02,0);
}
void NET_OP__BR__ETH02_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH02,p_NetworkStats);
}
int NET_OP__BR__ETH03 = 89;
void NET_OP__BR__ETH03_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH03,0);
}
void NET_OP__BR__ETH03_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH03,p_NetworkStats);
}
int NET_OP__BR__ETH04 = 90;
void NET_OP__BR__ETH04_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH04,0);
}
void NET_OP__BR__ETH04_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH04,p_NetworkStats);
}
int NET_OP__BR__ETH05 = 91;
void NET_OP__BR__ETH05_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH05,0);
}
void NET_OP__BR__ETH05_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH05,p_NetworkStats);
}
int NET_OP__BR__ETH06 = 92;
void NET_OP__BR__ETH06_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH06,0);
}
void NET_OP__BR__ETH06_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH06,p_NetworkStats);
}
int NET_OP__BR__ETH07 = 93;
void NET_OP__BR__ETH07_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH07,0);
}
void NET_OP__BR__ETH07_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH07,p_NetworkStats);
}
int NET_OP__BR__ETH08 = 94;
void NET_OP__BR__ETH08_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH08,0);
}
void NET_OP__BR__ETH08_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH08,p_NetworkStats);
}
int NET_OP__BR__ETH09 = 95;
void NET_OP__BR__ETH09_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH09,0);
}
void NET_OP__BR__ETH09_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH09,p_NetworkStats);
}
int NET_OP__BR__ETH10 = 96;
void NET_OP__BR__ETH10_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH10,0);
}
void NET_OP__BR__ETH10_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH10,p_NetworkStats);
}
int NET_OP__BR__ETH11 = 97;
void NET_OP__BR__ETH11_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH11,0);
}
void NET_OP__BR__ETH11_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH11,p_NetworkStats);
}
int NET_OP__BR__ETH12 = 98;
void NET_OP__BR__ETH12_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH12,0);
}
void NET_OP__BR__ETH12_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH12,p_NetworkStats);
}
int NET_FlexRay = 99;
void NET_FlexRay_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay,0);
}
void NET_FlexRay_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay,p_NetworkStats);
}
int NET_FlexRay2 = 100;
void NET_FlexRay2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2,0);
}
void NET_FlexRay2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2,p_NetworkStats);
}
int NET_LIN6__VNET_A_ = 101;
void NET_LIN6__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6__VNET_A_,0);
}
void NET_LIN6__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6__VNET_A_,p_NetworkStats);
}
int NET_LIN6__VNET_B_ = 102;
void NET_LIN6__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6__VNET_B_,0);
}
void NET_LIN6__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN6__VNET_A_ = 103;
void NET_HS_CAN6__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6__VNET_A_,0);
}
void NET_HS_CAN6__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN6__VNET_B_ = 104;
void NET_HS_CAN6__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6__VNET_B_,0);
}
void NET_HS_CAN6__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN7__VNET_A_ = 105;
void NET_HS_CAN7__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7__VNET_A_,0);
}
void NET_HS_CAN7__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN7__VNET_B_ = 106;
void NET_HS_CAN7__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7__VNET_B_,0);
}
void NET_HS_CAN7__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7__VNET_B_,p_NetworkStats);
}
int NET_LSFT_CAN2__VNET_A_ = 107;
void NET_LSFT_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2__VNET_A_,0);
}
void NET_LSFT_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2__VNET_A_,p_NetworkStats);
}
int NET_LSFT_CAN2__VNET_B_ = 108;
void NET_LSFT_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2__VNET_B_,0);
}
void NET_LSFT_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2__VNET_B_,p_NetworkStats);
}
int NET_Ethernet__VNET_A_ = 109;
void NET_Ethernet__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet__VNET_A_,0);
}
void NET_Ethernet__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet__VNET_A_,p_NetworkStats);
}
int NET_Ethernet__VNET_B_ = 110;
void NET_Ethernet__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet__VNET_B_,0);
}
void NET_Ethernet__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet__VNET_B_,p_NetworkStats);
}

int GenericMessageTransmit(GenericMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int GenericLongMessageTransmit(GenericLongMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }
    iBitField |= ATTR_CANFD_FRAME;
    if (bBRS)
        iBitField |= ATTR_CANFD_BRS;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 0;
    txSetSignal.dValue = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 1;
    txSetSignal.nValue = nValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxEvent(unsigned int iMessageIndex)
{
    TxSetSignal txSetSignal;
    txSetSignal.iType = 2;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength)
{
    return CM_TextAPI(g_uiHandle,wcCommand,wcResponse,iResponseMaxLength);
}

int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength)
{
    int iCount;
    int iResult;
    wchar_t wcCommand[1024];
    wchar_t wcResponse[1024];
    iCount = MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), NULL, 0);
    MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), wcCommand, iCount);
    wcCommand[iCount] = 0;
    iResult = CM_TextAPI(g_uiHandle, wcCommand, wcResponse, 1024);
    iCount = WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), NULL, 0, NULL, NULL);
    WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), szResponse, iCount, NULL, NULL);
    szResponse[iCount] = 0;
    return iResult;
}

#define MAX_PRINT_BUF_SIZE 1024

int OutputChars(const char *szMsg, int nLen)
{
    wchar_t *pWideBuffer;
    int iCount = MultiByteToWideChar(0, 0, szMsg, nLen, NULL, 0);
    pWideBuffer = malloc((iCount + 1) * sizeof(wchar_t));
    MultiByteToWideChar(0, 0, szMsg, nLen, pWideBuffer, iCount);
    pWideBuffer[iCount] = 0;
    CM_OutputWindow(g_uiHandle, pWideBuffer, 0x0000, 0);
    free(pWideBuffer);
    return iCount;
}

int Printf(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int PrintfW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters;
}

int WriteLine(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    strcat_s(szMsg, MAX_PRINT_BUF_SIZE, "\n");
    ++iNumCharacters;
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int WriteLineW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    wcscat_s(szMsg, MAX_PRINT_BUF_SIZE, L"\n");
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters + 1;
}

// Retrieve the system error message for the last error code
void DisplayLastError(LPCWSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &lpMsgBuf, 0, NULL );

    // Display the error message
    if (lpszFunction)
        PrintfW(L"%ls failed with error %d: %ls\n", lpszFunction, dw, lpMsgBuf);
    else
        PrintfW(L"Error %d: %ls\n", dw, lpMsgBuf);

    LocalFree(lpMsgBuf);
}

#define ICS_MAX_RS232_PORT 255
HANDLE hSerialPorts[ICS_MAX_RS232_PORT] = { INVALID_HANDLE_VALUE };

RS232OnRxTx_fdef fptr_ICS_RS232OnSend = NULL;
RS232OnRxTx_fdef fptr_ICS_RS232OnReceive = NULL;
RS232OnError_fdef fptr_ICS_RS232OnError = NULL;

DWORD ICS_RS232Open(DWORD port)
{
    wchar_t szPort[20];
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Open was passed an invalid port number: %d\n", port);
        return 0;
    }
    wsprintf(szPort, TEXT("\\\\.\\COM%d"), port);
    hSerialPorts[port - 1] = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
        return 1;
    else
    {
        DisplayLastError(TEXT("ICS_RS232Open"));
        return 0;
    }
}

DWORD ICS_RS232Close(DWORD port)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Close was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSerialPorts[port - 1]);
        hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
        return 1;
    }
    else
    {
        PrintfW(L"ICS_RS232Close port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232ConfigTimeout was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
		{
            DCB newComState = comState;

            newComState.BaudRate = baudrate;
            newComState.ByteSize = (BYTE)numberOfDataBits;
            newComState.StopBits = (BYTE)numberOfStopBits;
            newComState.Parity = (BYTE)parity;

            if (SetCommState(hSerialPorts[port - 1], &newComState))
            {
                // Add CommTimeout
                COMMTIMEOUTS commTimeout;
                GetCommTimeouts(hSerialPorts[port - 1], &commTimeout);

                commTimeout.ReadIntervalTimeout = 0;
                commTimeout.ReadTotalTimeoutMultiplier = 0;
                commTimeout.ReadTotalTimeoutConstant = timeout;
                commTimeout.WriteTotalTimeoutMultiplier = 0;
                commTimeout.WriteTotalTimeoutConstant = timeout;

                SetCommTimeouts(hSerialPorts[port - 1], &commTimeout);
                return 1;
            }
            else
            {
                DisplayLastError(TEXT("ICS_RS232Config"));
                hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                return 0;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Config"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE; 
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Config port number %d was not opened\n", port); 
        return 0;
    }
}

DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity)
{
    return ICS_RS232ConfigTimeout(port, baudrate, numberOfDataBits, numberOfStopBits, parity, 10);
}

DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232SetHandshake was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
        {
            if (handshake == 128) // Software handshake
            {
                comState.fRtsControl = RTS_CONTROL_HANDSHAKE;
                comState.XonLim = (WORD)XonLimit;
                comState.XoffLim = (WORD)XoffLimit;
                comState.XonChar = (char)XonChar;
                comState.XoffChar = (char)XoffChar;
                if (SetCommState(hSerialPorts[port - 1], &comState))
                    return 1;
                else
                {
                    DisplayLastError(TEXT("RS232SetHandshake"));
                    hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                    return 0;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232SetHandshake"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232SetHandshake port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state)
{
    return 0;
}

DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Send was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesWritten = 0;
        if (WriteFile(hSerialPorts[port - 1], buffer, size, &dwBytesWritten, NULL))
        {
            if (fptr_ICS_RS232OnSend)
                fptr_ICS_RS232OnSend(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Send"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x1);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Send port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Receive was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesRead = 0;
        if (ReadFile(hSerialPorts[port - 1], buffer, size, &dwBytesRead, NULL))
        {
            if (dwBytesRead < size)
                buffer[dwBytesRead] = 0;
            if (fptr_ICS_RS232OnReceive)
                fptr_ICS_RS232OnReceive(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Receive"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x2);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Receive port number %d was not opened\n", port);
        return 0;
    }
}

WORD ICS_RS232WriteByte(DWORD port, DWORD data)
{
    return (WORD)ICS_RS232Send(port, (LPBYTE)&data, 1);
}

WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size)
{
    return (WORD)ICS_RS232Send(port, buffer, size);
}

void ICS_RS232CloseAllPorts()
{
    int nPort;
    for (nPort = 0; nPort < ICS_MAX_RS232_PORT; ++nPort)
    {
        if (hSerialPorts[nPort] != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hSerialPorts[nPort]);
            hSerialPorts[nPort] = INVALID_HANDLE_VALUE;
        }
    }
    UnloadInpout();
}

HINSTANCE hInpOutDll = NULL;
char bIOErrorDisp = 0;
lpOut32 gfpOut32 = NULL;
lpInp32 gfpInp32 = NULL;
lpIsInpOutDriverOpen gfpIsInpOutDriverOpen = NULL;

void LoadInpOut()
{
    if (hInpOutDll == NULL)
    {
        char szPath[MAX_PATH];
        char *pLastSlash;
        GetModuleFileNameA(NULL, szPath, sizeof(szPath));
        pLastSlash = strrchr(szPath, '\\');
        if (pLastSlash)
            *(pLastSlash + 1) = 0;
        strcat_s(szPath, MAX_PATH, "inpout32.DLL");
        hInpOutDll = LoadLibraryA(szPath);
    }
    if (hInpOutDll == NULL)
    {
        if (bIOErrorDisp == 0)
        {
            PrintfW(L"InpOut32.DLL is not installed!");
            bIOErrorDisp = 1;
        }
    }
    else if (gfpIsInpOutDriverOpen == NULL)
    {
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
    }
}

void UnloadInpout()
{
    if (hInpOutDll)
    {
        gfpOut32 = NULL;
        gfpInp32 = NULL;
        gfpIsInpOutDriverOpen = NULL;
        FreeLibrary(hInpOutDll);
    }
}

void __stdcall CM_MG_OBDII_RESP_HS_CAN()
{
    MG_OBDII_RESP_HS_CAN stMyStruct;
    MG_OBDII_RESP_HS_CAN_Init(&stMyStruct);
    SpyMsg_MG_OBDII_RESP_HS_CAN(&stMyStruct);
}

void SpyAppSig_CallAllHandlers()
{
}

void (* CM_RegisterCallback) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
void (* CM_GetSetValue) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
int (* CM_TextAPI) (void * uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
int (* CM_FindIndexForObjectFromName) (void * uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
int (* CM_GetMessageName) (void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
int (* CM_ShowPanel) (void * uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
int (* CM_SetControlProperty) (void * uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
int (* CM_OutputWindow) (void * uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
int (* CM_TransmitMessage) (void * uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
int (* CM_GetSignalValue) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
int (* CM_TxFromSignals) (void * uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_TxFromRawSignals) (void * uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_MessageGenericInit) (void * uiHandle, unsigned short iMessageType,
					   unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
					   int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
					   int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
					   int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
int (* CM_MessageRawInit) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
uint64 (* CM_SignalPhysicalToRaw) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue);
int (* CM_UpdateMessageSignalsFromBytes) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromRawSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_GetEcuCount) (void * uiHandle);
int (* CM_GetMemoryBlockCount) (void * uiHandle, int ecu);
int (* CM_GetMemoryBlockInfo) (void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
int (* CM_GetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
int (* CM_SetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

void __stdcall CM_ExtensionInit(void * uiHandle, struct stCallBackPointers  * p_stCallBackPointers)
{
    g_uiHandle = uiHandle;
    // setup the callback function to communicate to the CoreMini
    CM_RegisterCallback = (void ( *)(void *, unsigned short, unsigned short, void *)) p_stCallBackPointers->pRegisterCallBack;
    CM_GetSetValue = (void ( *)(void * , unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSetValueCallBack; 
    CM_TextAPI = (int ( *)(void *, wchar_t *, wchar_t *, int)) p_stCallBackPointers->pTextAPICallBack;
    CM_FindIndexForObjectFromName = (int ( *)(void *, int, wchar_t *, int *)) p_stCallBackPointers->pFindIndexForObjectFromNameCallBack;
    CM_GetMessageName = (int ( *)(void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)) p_stCallBackPointers->pGetMessageName;
    CM_ShowPanel = (int ( *)(void *, wchar_t *, wchar_t *)) p_stCallBackPointers->pShowPanelCallBack;
    CM_SetControlProperty = (int ( *)(void *, wchar_t *, wchar_t *, int, void *)) p_stCallBackPointers->pSetControlProp;
    CM_OutputWindow = (int ( *)(void *, wchar_t *, int, int)) p_stCallBackPointers->pOutputWindowCallBack;
    CM_TransmitMessage = (int (* )(void *, int, int, int, int, unsigned char *)) p_stCallBackPointers->pTransmitMessageCallBack  ;
    CM_GetSignalValue = (int (* )(void *, unsigned short, unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSignalValue;
    CM_TxFromSignals = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromSignalValues; 
    CM_TxFromRawSignals = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromRawSignalValues;
    CM_MessageGenericInit = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, void *p_MessageStats, int *p_iNetworkID,
                    int *p_iNumDataBytes, int  p_iNumDataMax, int *p_iPeriodMs, int *p_iID,
                    int *p_iBitField, unsigned char *p_btData, double *p_dSignals, int dSignalMaxCount,
                    int *p_iActualSignalMaxCount, __int64 *p_iTimeStampNanoSecondsHW, unsigned int *p_iTimeStampMillisecondsOS)) p_stCallBackPointers->pMessageGenericInit; 
    CM_MessageRawInit = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount)) p_stCallBackPointers->pMessageRawInit;
    CM_SignalPhysicalToRaw = (uint64 (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue)) p_stCallBackPointers->pSignalPhysicalToRaw;
    CM_UpdateMessageSignalsFromBytes = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateMessageSignalsFromBytes;
    CM_UpdateBytesFromSignals = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromSignals;
    CM_UpdateBytesFromRawSignals = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromRawSignals;
    CM_GetEcuCount = (int (* )(void * uiHandle)) p_stCallBackPointers->pGetEcuCount;
    CM_GetMemoryBlockCount = (int (* )(void * uiHandle, int ecu)) p_stCallBackPointers->pGetMemoryBlockCount;
    CM_GetMemoryBlockInfo = (int (* )(void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size)) p_stCallBackPointers->pGetMemoryBlockInfo;
    CM_GetMemoryBlockData = (int (* )(void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pGetMemoryBlockData;
    CM_SetMemoryBlockData = (int (* )(void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pSetMemoryBlockData;
    // fix up the index variables by searching for the names
    // network indexes
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN",&NET_HS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN",&NET_MS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN",&NET_SW_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW",&NET_J1850_VPW);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K",&NET_ISO9141_KW2K);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN",&NET_LSFT_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 PWM",&NET_J1850_PWM);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708",&NET_J1708);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI",&NET_neoVI);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2",&NET_HS_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3",&NET_HS_CAN3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2",&NET_LIN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3",&NET_LIN3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4",&NET_LIN4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI",&NET_CGI);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN",&NET_LIN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2",&NET_ISO9141_KW2K_2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3",&NET_ISO9141_KW2K_3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4",&NET_ISO9141_KW2K_4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4",&NET_HS_CAN4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5",&NET_HS_CAN5);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART",&NET_UART);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART2",&NET_UART2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5",&NET_LIN5);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MOST (VNET A)",&NET_MOST__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1A (VNET A)",&NET_FlexRay1A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1B (VNET A)",&NET_FlexRay1B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2A (VNET A)",&NET_FlexRay2A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2B (VNET A)",&NET_FlexRay2B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN (VNET A)",&NET_HS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN (VNET A)",&NET_MS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN (VNET A)",&NET_SW_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW (VNET A)",&NET_J1850_VPW__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN (VNET A)",&NET_LSFT_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708 (VNET A)",&NET_J1708__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI (VNET A)",&NET_neoVI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (VNET A)",&NET_HS_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (VNET A)",&NET_HS_CAN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN (VNET A)",&NET_LIN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (VNET A)",&NET_LIN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (VNET A)",&NET_LIN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (VNET A)",&NET_LIN4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (VNET A)",&NET_CGI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K (VNET A)",&NET_ISO9141_KW2K__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2 (VNET A)",&NET_ISO9141_KW2K_2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3 (VNET A)",&NET_ISO9141_KW2K_3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4 (VNET A)",&NET_ISO9141_KW2K_4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN (VNET B)",&NET_HS_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN (VNET B)",&NET_MS_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN (VNET B)",&NET_SW_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW (VNET B)",&NET_J1850_VPW__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN (VNET B)",&NET_LSFT_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708 (VNET B)",&NET_J1708__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI (VNET B)",&NET_neoVI__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (VNET B)",&NET_HS_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (VNET B)",&NET_HS_CAN3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN (VNET B)",&NET_LIN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (VNET B)",&NET_LIN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (VNET B)",&NET_LIN3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (VNET B)",&NET_LIN4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (VNET B)",&NET_CGI__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K (VNET B)",&NET_ISO9141_KW2K__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2 (VNET B)",&NET_ISO9141_KW2K_2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3 (VNET B)",&NET_ISO9141_KW2K_3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4 (VNET B)",&NET_ISO9141_KW2K_4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4 (VNET A)",&NET_HS_CAN4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5 (VNET A)",&NET_HS_CAN5__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5 (VNET A)",&NET_LIN5__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4 (VNET B)",&NET_HS_CAN4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5 (VNET B)",&NET_HS_CAN5__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5 (VNET B)",&NET_LIN5__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet DAQ",&NET_Ethernet_DAQ);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet",&NET_Ethernet);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MOST (VNET B)",&NET_MOST__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1A (VNET B)",&NET_FlexRay1A__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1B (VNET B)",&NET_FlexRay1B__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2A (VNET B)",&NET_FlexRay2A__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2B (VNET B)",&NET_FlexRay2B__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2",&NET_SW_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2 (VNET A)",&NET_SW_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2 (VNET B)",&NET_SW_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FSA",&NET_FSA);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"TCP",&NET_TCP);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6",&NET_HS_CAN6);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7",&NET_HS_CAN7);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6",&NET_LIN6);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2",&NET_LSFT_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH01",&NET_OP__BR__ETH01);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH02",&NET_OP__BR__ETH02);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH03",&NET_OP__BR__ETH03);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH04",&NET_OP__BR__ETH04);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH05",&NET_OP__BR__ETH05);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH06",&NET_OP__BR__ETH06);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH07",&NET_OP__BR__ETH07);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH08",&NET_OP__BR__ETH08);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH09",&NET_OP__BR__ETH09);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH10",&NET_OP__BR__ETH10);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH11",&NET_OP__BR__ETH11);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH12",&NET_OP__BR__ETH12);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay",&NET_FlexRay);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2",&NET_FlexRay2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6 (VNET A)",&NET_LIN6__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6 (VNET B)",&NET_LIN6__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6 (VNET A)",&NET_HS_CAN6__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6 (VNET B)",&NET_HS_CAN6__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7 (VNET A)",&NET_HS_CAN7__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7 (VNET B)",&NET_HS_CAN7__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2 (VNET A)",&NET_LSFT_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2 (VNET B)",&NET_LSFT_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet (VNET A)",&NET_Ethernet__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet (VNET B)",&NET_Ethernet__VNET_B_);

    // database indexes
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_neoVI",&DB_Report_Message_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__PWM__neoVI",&DB_Report_Message__PWM__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__VCAN_RF__neoVI",&DB_Report_Message__VCAN_RF__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__neoVI_Fire2__neoVI",&DB_Report_Message__neoVI_Fire2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Latitude__neoVI",&DB_Report_Message__GPS_Latitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Longitude__neoVI",&DB_Report_Message__GPS_Longitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Flags__neoVI",&DB_Report_Message__GPS_Flags__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Altitude__neoVI",&DB_Report_Message__GPS_Altitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Speed_Bearing__neoVI",&DB_Report_Message__GPS_Speed_Bearing__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Accuracy__neoVI",&DB_Report_Message__GPS_Accuracy__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Time__neoVI",&DB_Report_Message__GPS_Time__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Sectors__neoVI",&DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Signals__neoVI",&DB_Report_Message__WirelessneoVI_Signals__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI",&DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_Message_Data_Lost_neoVI",&DB_neoVI_Logger_Message_Data_Lost_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI",&DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_woke_up_neoVI",&DB_neoVI_Logger_woke_up_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_1_Analog_Card__neoVI",&DB_Report_Message_1_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_2_Analog_Card__neoVI",&DB_Report_Message_2_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_3_Analog_Card__neoVI",&DB_Report_Message_3_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_4_Analog_Card__neoVI",&DB_Report_Message_4_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Time_Resync_neoVI",&DB_Time_Resync_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_Clock_Edge_neoVI",&DB_VNET_Clock_Edge_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Stats_neoVI",&DB_VNET_A_Stats_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Reboot_neoVI",&DB_VNET_A_Reboot_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Went_To_Sleep_neoVI",&DB_neoVI_Went_To_Sleep_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Device_subsystem_restarted__neoVI",&DB_Device_subsystem_restarted__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Ethernet_DAQ_Report_neoVI",&DB_Ethernet_DAQ_Report_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Status_Update_neoVI",&DB_neoVI_Status_Update_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Scc_Status_neoVI",&DB_Scc_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM_Inputs__neoVI",&DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM1__neoVI",&DB_Report_Message__Analog_Card_PWM1__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM2__neoVI",&DB_Report_Message__Analog_Card_PWM2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM3__neoVI",&DB_Report_Message__Analog_Card_PWM3__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM4__neoVI",&DB_Report_Message__Analog_Card_PWM4__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM5__neoVI",&DB_Report_Message__Analog_Card_PWM5__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM6__neoVI",&DB_Report_Message__Analog_Card_PWM6__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM7__neoVI",&DB_Report_Message__Analog_Card_PWM7__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM8__neoVI",&DB_Report_Message__Analog_Card_PWM8__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_neoVI",&DB_neoVI_Device_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_2_neoVI",&DB_neoVI_Device_Status_2_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trace_Logger_Status_neoVI",&DB_Trace_Logger_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trigger_neoVI",&DB_Trigger_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Ethernet_Status_neoVI",&DB_Ethernet_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OP__BR__Ethernet___Link_status_changed_neoVI",&DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_FIRE2_Report_Message_PWM_IN_1__neoVI",&DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_FIRE2_Report_Message_PWM_IN_2__neoVI",&DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Hardware_Latency_Test_neoVI",&DB_Hardware_Latency_Test_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_MIC_neoVI",&DB_neoVI_MIC_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_neoVI_db49",&DB_neoVI_Device_Status_neoVI_db49_Index);

    // messages indexes
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_OBDII_RESP_HS_CAN",&MG_OBDII_RESP_HS_CAN_Index);

    // tx messages indexes

    // function block indexes

    // diagnostic job indexes

    // app signals indexes

    CM_RegisterCallback( g_uiHandle,CM_CALLBACKTYPE_MESSAGE_MG, MG_OBDII_RESP_HS_CAN_Index,CM_MG_OBDII_RESP_HS_CAN);
}
void __stdcall CM_EveryMessage(int iNetwork, int iID, __int64 iTimeStampNanoSecondsHW, unsigned int iTimeStampMillisecondsOS,
									  int iNumDataBytes, int iBitField, unsigned char *p_btData)
{
    GenericMessage stMsg = {0};
    stMsg.iNetwork = iNetwork;
    stMsg.iID = iID;
    stMsg.iNumDataBytes = iNumDataBytes;
    if (stMsg.iNumDataBytes > sizeof(stMsg.btData))
        stMsg.iNumDataBytes = sizeof(stMsg.btData);
    stMsg.iBitField = iBitField;
    stMsg.iTimeStampMillisecondsOS = iTimeStampMillisecondsOS;
    stMsg.iTimeStampNanoSecondsHW = iTimeStampNanoSecondsHW;
    if (g_bUseExtendedIdBit && (stMsg.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        stMsg.iID = mkExtId(stMsg.iID);
    memcpy(stMsg.btData, p_btData, stMsg.iNumDataBytes);
    Spy_EveryMessage(&stMsg);

    if ((stMsg.iBitField & ATTR_CANFD_FRAME) || (stMsg.iNumDataBytes < iNumDataBytes))
    {
        GenericLongMessage stLongMsg = {0};
        stLongMsg.iNetwork = stMsg.iNetwork;
        stLongMsg.iID = stMsg.iID;
        stLongMsg.iNumDataBytes = iNumDataBytes;
        if (stLongMsg.iNumDataBytes > sizeof(stLongMsg.btData))
            stLongMsg.iNumDataBytes = sizeof(stLongMsg.btData);
        stLongMsg.iBitField = stMsg.iBitField;
        stLongMsg.iTimeStampMillisecondsOS = stMsg.iTimeStampMillisecondsOS;
        stLongMsg.iTimeStampNanoSecondsHW = stMsg.iTimeStampNanoSecondsHW;
        memcpy(stLongMsg.btData, p_btData, stLongMsg.iNumDataBytes);
        Spy_EveryLongMessage(&stLongMsg);
    }
}

void Spy_Lock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_LOCK,0,0);
}
void Spy_Unlock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_UNLOCK,0,0);
}

void SpyShowPanel(char * pWindowName, char * pPanelName)
{
    wchar_t szWideWindowName[1024];
    wchar_t szWidePanelName[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), NULL, 0);
    MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), szWideWindowName, iCount);
    szWideWindowName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    // call the api
    CM_ShowPanel(g_uiHandle,szWideWindowName,szWidePanelName);
}

void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName)
{
    CM_ShowPanel(g_uiHandle,pWindowName,pPanelName);
}

void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue)
{
    wchar_t szWidePanelName[1024];
    wchar_t szWideControlTag[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), NULL, 0);
    MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), szWideControlTag, iCount);
    szWideControlTag[iCount] = 0;
    if (SPY_CTL_PROP_SET_CAPTION == prop)
    {
        wchar_t szWideValue[1024];
        iCount = MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), NULL, 0);
        MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), szWideValue, iCount);
        szWideValue[iCount] = 0;
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, szWideValue);
    }
    else // call the api
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, pValue);
}

void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue)
{
    CM_SetControlProperty(g_uiHandle, pPanelName, pControlTag, prop, pValue);
}

int MG_OBDII_RESP_HS_CAN_Index = 0;

void MG_OBDII_RESP_HS_CAN_Init(MG_OBDII_RESP_HS_CAN * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_OBDII_RESP_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int MG_OBDII_RESP_HS_CAN_Transmit(MG_OBDII_RESP_HS_CAN * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 1, MG_OBDII_RESP_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int MG_OBDII_RESP_HS_CAN_Transmit_raw(MG_OBDII_RESP_HS_CAN * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 1, MG_OBDII_RESP_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Report_Message_neoVI_Index = 0;

void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC3_AIN = dValues[0];
    pMsg->MISC4_AIN = dValues[1];
    pMsg->MISC5_AIN = dValues[2];
    pMsg->MISC6_AIN = dValues[3];
    pMsg->MISC1 = dValues[4];
    pMsg->MISC2 = dValues[5];
    pMsg->MISC3 = dValues[6];
    pMsg->MISC4 = dValues[7];
    pMsg->MISC5 = dValues[8];
    pMsg->MISC6 = dValues[9];
    pMsg->LED1 = dValues[10];
    pMsg->LED2 = dValues[11];
    pMsg->LIN1 = dValues[12];
    pMsg->LIN2 = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->MISC3_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC4_AIN_raw = (WORD)nRawValues[1];
    pMsg->MISC5_AIN_raw = (WORD)nRawValues[2];
    pMsg->MISC6_AIN_raw = (WORD)nRawValues[3];
    pMsg->MISC1_raw = (BYTE)nRawValues[4];
    pMsg->MISC2_raw = (BYTE)nRawValues[5];
    pMsg->MISC3_raw = (BYTE)nRawValues[6];
    pMsg->MISC4_raw = (BYTE)nRawValues[7];
    pMsg->MISC5_raw = (BYTE)nRawValues[8];
    pMsg->MISC6_raw = (BYTE)nRawValues[9];
    pMsg->LED1_raw = (BYTE)nRawValues[10];
    pMsg->LED2_raw = (BYTE)nRawValues[11];
    pMsg->LIN1_raw = (BYTE)nRawValues[12];
    pMsg->LIN2_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_neoVI_LoadSignalValuesArray(DB_Report_Message_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC3_AIN;
    dArray[1] = pMsg->MISC4_AIN;
    dArray[2] = pMsg->MISC5_AIN;
    dArray[3] = pMsg->MISC6_AIN;
    dArray[4] = pMsg->MISC1;
    dArray[5] = pMsg->MISC2;
    dArray[6] = pMsg->MISC3;
    dArray[7] = pMsg->MISC4;
    dArray[8] = pMsg->MISC5;
    dArray[9] = pMsg->MISC6;
    dArray[10] = pMsg->LED1;
    dArray[11] = pMsg->LED2;
    dArray[12] = pMsg->LIN1;
    dArray[13] = pMsg->LIN2;
}

void DB_Report_Message_neoVI_LoadRawSignalValuesArray(DB_Report_Message_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC3_AIN_raw;
    nRawValues[1] = pMsg->MISC4_AIN_raw;
    nRawValues[2] = pMsg->MISC5_AIN_raw;
    nRawValues[3] = pMsg->MISC6_AIN_raw;
    nRawValues[4] = pMsg->MISC1_raw;
    nRawValues[5] = pMsg->MISC2_raw;
    nRawValues[6] = pMsg->MISC3_raw;
    nRawValues[7] = pMsg->MISC4_raw;
    nRawValues[8] = pMsg->MISC5_raw;
    nRawValues[9] = pMsg->MISC6_raw;
    nRawValues[10] = pMsg->LED1_raw;
    nRawValues[11] = pMsg->LED2_raw;
    nRawValues[12] = pMsg->LIN1_raw;
    nRawValues[13] = pMsg->LIN2_raw;
}

int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__PWM__neoVI_Index = 1;

void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__PWM__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM_In_1 = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->PWM_In_1_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM_In_1;
}

void DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM_In_1_raw;
}

int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__VCAN_RF__neoVI_Index = 2;

void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__VCAN_RF__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC1_AIN = dValues[0];
    pMsg->MISC_1 = dValues[1];
    pMsg->MISC_2 = dValues[2];
    pMsg->MISC_3 = dValues[3];
    pMsg->MISC_4 = dValues[4];
    pMsg->Vehicle_Battery_Voltage = dValues[5];
    pMsg->Temperature = dValues[6];
    pMsg->Hardware_Revision = dValues[7];
    pMsg->RTC_Battery_Measure_Enabled = dValues[8];
    pMsg->RTC_Battery_Voltage = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->MISC1_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC_1_raw = (BYTE)nRawValues[1];
    pMsg->MISC_2_raw = (BYTE)nRawValues[2];
    pMsg->MISC_3_raw = (BYTE)nRawValues[3];
    pMsg->MISC_4_raw = (BYTE)nRawValues[4];
    pMsg->Vehicle_Battery_Voltage_raw = (WORD)nRawValues[5];
    pMsg->Temperature_raw = (WORD)nRawValues[6];
    pMsg->Hardware_Revision_raw = (WORD)nRawValues[7];
    pMsg->RTC_Battery_Measure_Enabled_raw = (BYTE)nRawValues[8];
    pMsg->RTC_Battery_Voltage_raw = (WORD)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC1_AIN;
    dArray[1] = pMsg->MISC_1;
    dArray[2] = pMsg->MISC_2;
    dArray[3] = pMsg->MISC_3;
    dArray[4] = pMsg->MISC_4;
    dArray[5] = pMsg->Vehicle_Battery_Voltage;
    dArray[6] = pMsg->Temperature;
    dArray[7] = pMsg->Hardware_Revision;
    dArray[8] = pMsg->RTC_Battery_Measure_Enabled;
    dArray[9] = pMsg->RTC_Battery_Voltage;
}

void DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC1_AIN_raw;
    nRawValues[1] = pMsg->MISC_1_raw;
    nRawValues[2] = pMsg->MISC_2_raw;
    nRawValues[3] = pMsg->MISC_3_raw;
    nRawValues[4] = pMsg->MISC_4_raw;
    nRawValues[5] = pMsg->Vehicle_Battery_Voltage_raw;
    nRawValues[6] = pMsg->Temperature_raw;
    nRawValues[7] = pMsg->Hardware_Revision_raw;
    nRawValues[8] = pMsg->RTC_Battery_Measure_Enabled_raw;
    nRawValues[9] = pMsg->RTC_Battery_Voltage_raw;
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__neoVI_Fire2__neoVI_Index = 3;

void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dValues[11] = {0.0};
    uint64 nRawValues[11] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__neoVI_Fire2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 11, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RTC_Battery = dValues[0];
    pMsg->Temperature = dValues[1];
    pMsg->Vehicle_Battery = dValues[2];
    pMsg->EMISC1_AIN = dValues[3];
    pMsg->EMISC2_AIN = dValues[4];
    pMsg->EMISC1_DIN = dValues[5];
    pMsg->EMISC2_DIN = dValues[6];
    pMsg->MISC5_DIN = dValues[7];
    pMsg->MISC6_DIN = dValues[8];
    pMsg->LED1 = dValues[9];
    pMsg->LED2 = dValues[10];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 11, &iActualSignalMaxCount);
    pMsg->RTC_Battery_raw = (uint64)nRawValues[0];
    pMsg->Temperature_raw = (uint64)nRawValues[1];
    pMsg->Vehicle_Battery_raw = (uint64)nRawValues[2];
    pMsg->EMISC1_AIN_raw = (WORD)nRawValues[3];
    pMsg->EMISC2_AIN_raw = (WORD)nRawValues[4];
    pMsg->EMISC1_DIN_raw = (BYTE)nRawValues[5];
    pMsg->EMISC2_DIN_raw = (BYTE)nRawValues[6];
    pMsg->MISC5_DIN_raw = (BYTE)nRawValues[7];
    pMsg->MISC6_DIN_raw = (BYTE)nRawValues[8];
    pMsg->LED1_raw = (BYTE)nRawValues[9];
    pMsg->LED2_raw = (BYTE)nRawValues[10];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->RTC_Battery;
    dArray[1] = pMsg->Temperature;
    dArray[2] = pMsg->Vehicle_Battery;
    dArray[3] = pMsg->EMISC1_AIN;
    dArray[4] = pMsg->EMISC2_AIN;
    dArray[5] = pMsg->EMISC1_DIN;
    dArray[6] = pMsg->EMISC2_DIN;
    dArray[7] = pMsg->MISC5_DIN;
    dArray[8] = pMsg->MISC6_DIN;
    dArray[9] = pMsg->LED1;
    dArray[10] = pMsg->LED2;
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RTC_Battery_raw;
    nRawValues[1] = pMsg->Temperature_raw;
    nRawValues[2] = pMsg->Vehicle_Battery_raw;
    nRawValues[3] = pMsg->EMISC1_AIN_raw;
    nRawValues[4] = pMsg->EMISC2_AIN_raw;
    nRawValues[5] = pMsg->EMISC1_DIN_raw;
    nRawValues[6] = pMsg->EMISC2_DIN_raw;
    nRawValues[7] = pMsg->MISC5_DIN_raw;
    nRawValues[8] = pMsg->MISC6_DIN_raw;
    nRawValues[9] = pMsg->LED1_raw;
    nRawValues[10] = pMsg->LED2_raw;
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[11];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 11);
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[11];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 11);
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[11];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, dArray, 11, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[11];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 11, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Latitude__neoVI_Index = 4;

void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Latitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Latitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Latitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Latitude;
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Latitude_raw;
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Longitude__neoVI_Index = 5;

void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Longitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Longitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Longitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Longitude;
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Longitude_raw;
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Flags__neoVI_Index = 6;

void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Flags__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Update_Count = dValues[0];
    pMsg->GPS_Date_Available = dValues[1];
    pMsg->GPS_Time_Available = dValues[2];
    pMsg->GPS_Accuracy_Available = dValues[3];
    pMsg->GPS_Bearing_Available = dValues[4];
    pMsg->GPS_Speed_Available = dValues[5];
    pMsg->GPS_Altitude_Available = dValues[6];
    pMsg->GPS_Lat_Lon_Available = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->Update_Count_raw = (BYTE)nRawValues[0];
    pMsg->GPS_Date_Available_raw = (BYTE)nRawValues[1];
    pMsg->GPS_Time_Available_raw = (BYTE)nRawValues[2];
    pMsg->GPS_Accuracy_Available_raw = (BYTE)nRawValues[3];
    pMsg->GPS_Bearing_Available_raw = (BYTE)nRawValues[4];
    pMsg->GPS_Speed_Available_raw = (BYTE)nRawValues[5];
    pMsg->GPS_Altitude_Available_raw = (BYTE)nRawValues[6];
    pMsg->GPS_Lat_Lon_Available_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Update_Count;
    dArray[1] = pMsg->GPS_Date_Available;
    dArray[2] = pMsg->GPS_Time_Available;
    dArray[3] = pMsg->GPS_Accuracy_Available;
    dArray[4] = pMsg->GPS_Bearing_Available;
    dArray[5] = pMsg->GPS_Speed_Available;
    dArray[6] = pMsg->GPS_Altitude_Available;
    dArray[7] = pMsg->GPS_Lat_Lon_Available;
}

void DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Update_Count_raw;
    nRawValues[1] = pMsg->GPS_Date_Available_raw;
    nRawValues[2] = pMsg->GPS_Time_Available_raw;
    nRawValues[3] = pMsg->GPS_Accuracy_Available_raw;
    nRawValues[4] = pMsg->GPS_Bearing_Available_raw;
    nRawValues[5] = pMsg->GPS_Speed_Available_raw;
    nRawValues[6] = pMsg->GPS_Altitude_Available_raw;
    nRawValues[7] = pMsg->GPS_Lat_Lon_Available_raw;
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Altitude__neoVI_Index = 7;

void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Altitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Altitude_Ellipse = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Altitude_Ellipse_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Altitude_Ellipse;
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Altitude_Ellipse_raw;
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index = 8;

void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Speed = dValues[0];
    pMsg->Bearing = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Speed_raw = (DWORD)nRawValues[0];
    pMsg->Bearing_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Speed;
    dArray[1] = pMsg->Bearing;
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Speed_raw;
    nRawValues[1] = pMsg->Bearing_raw;
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Accuracy__neoVI_Index = 9;

void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Accuracy__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Accuracy = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Accuracy_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Accuracy;
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Accuracy_raw;
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Time__neoVI_Index = 10;

void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Time__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index = 11;

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviStartSector = dValues[0];
    pMsg->WiviEndSector = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->WiviStartSector_raw = (DWORD)nRawValues[0];
    pMsg->WiviEndSector_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviStartSector;
    dArray[1] = pMsg->WiviEndSector;
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviStartSector_raw;
    nRawValues[1] = pMsg->WiviEndSector_raw;
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index = 12;

void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviJob = dValues[0];
    pMsg->WiviApkResponse = dValues[1];
    pMsg->WiviDataTransferMediumChoice = dValues[2];
    pMsg->WiviApkResponseTo = dValues[3];
    pMsg->WiviReserved0 = dValues[4];
    pMsg->WiviReserved1 = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->WiviJob_raw = (BYTE)nRawValues[0];
    pMsg->WiviApkResponse_raw = (BYTE)nRawValues[1];
    pMsg->WiviDataTransferMediumChoice_raw = (BYTE)nRawValues[2];
    pMsg->WiviApkResponseTo_raw = (BYTE)nRawValues[3];
    pMsg->WiviReserved0_raw = (BYTE)nRawValues[4];
    pMsg->WiviReserved1_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviJob;
    dArray[1] = pMsg->WiviApkResponse;
    dArray[2] = pMsg->WiviDataTransferMediumChoice;
    dArray[3] = pMsg->WiviApkResponseTo;
    dArray[4] = pMsg->WiviReserved0;
    dArray[5] = pMsg->WiviReserved1;
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviJob_raw;
    nRawValues[1] = pMsg->WiviApkResponse_raw;
    nRawValues[2] = pMsg->WiviDataTransferMediumChoice_raw;
    nRawValues[3] = pMsg->WiviApkResponseTo_raw;
    nRawValues[4] = pMsg->WiviReserved0_raw;
    nRawValues[5] = pMsg->WiviReserved1_raw;
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index = 13;

void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index = 14;

void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index = 15;

void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_woke_up_neoVI_Index = 16;

void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_woke_up_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SleepFlags = dValues[0];
    pMsg->WakeupFlags = dValues[1];
    pMsg->WakeUpSms = dValues[2];
    pMsg->WakeupSlaveA = dValues[3];
    pMsg->WakeupSlaveB = dValues[4];
    pMsg->WakeupMainVnet = dValues[5];
    pMsg->WakeupUsb = dValues[6];
    pMsg->PowerBoot = dValues[7];
    pMsg->LowVbatSleep = dValues[8];
    pMsg->NoCmSleep = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->SleepFlags_raw = (WORD)nRawValues[0];
    pMsg->WakeupFlags_raw = (WORD)nRawValues[1];
    pMsg->WakeUpSms_raw = (BYTE)nRawValues[2];
    pMsg->WakeupSlaveA_raw = (BYTE)nRawValues[3];
    pMsg->WakeupSlaveB_raw = (BYTE)nRawValues[4];
    pMsg->WakeupMainVnet_raw = (BYTE)nRawValues[5];
    pMsg->WakeupUsb_raw = (BYTE)nRawValues[6];
    pMsg->PowerBoot_raw = (BYTE)nRawValues[7];
    pMsg->LowVbatSleep_raw = (BYTE)nRawValues[8];
    pMsg->NoCmSleep_raw = (BYTE)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->SleepFlags;
    dArray[1] = pMsg->WakeupFlags;
    dArray[2] = pMsg->WakeUpSms;
    dArray[3] = pMsg->WakeupSlaveA;
    dArray[4] = pMsg->WakeupSlaveB;
    dArray[5] = pMsg->WakeupMainVnet;
    dArray[6] = pMsg->WakeupUsb;
    dArray[7] = pMsg->PowerBoot;
    dArray[8] = pMsg->LowVbatSleep;
    dArray[9] = pMsg->NoCmSleep;
}

void DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SleepFlags_raw;
    nRawValues[1] = pMsg->WakeupFlags_raw;
    nRawValues[2] = pMsg->WakeUpSms_raw;
    nRawValues[3] = pMsg->WakeupSlaveA_raw;
    nRawValues[4] = pMsg->WakeupSlaveB_raw;
    nRawValues[5] = pMsg->WakeupMainVnet_raw;
    nRawValues[6] = pMsg->WakeupUsb_raw;
    nRawValues[7] = pMsg->PowerBoot_raw;
    nRawValues[8] = pMsg->LowVbatSleep_raw;
    nRawValues[9] = pMsg->NoCmSleep_raw;
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_1_Analog_Card__neoVI_Index = 17;

void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_1_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_A = dValues[0];
    pMsg->Channel_B = dValues[1];
    pMsg->Channel_1_Differential_ = dValues[2];
    pMsg->Channel_2_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_A_raw = (WORD)nRawValues[0];
    pMsg->Channel_B_raw = (WORD)nRawValues[1];
    pMsg->Channel_1_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_2_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_A;
    dArray[1] = pMsg->Channel_B;
    dArray[2] = pMsg->Channel_1_Differential_;
    dArray[3] = pMsg->Channel_2_Differential_;
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_A_raw;
    nRawValues[1] = pMsg->Channel_B_raw;
    nRawValues[2] = pMsg->Channel_1_Differential__raw;
    nRawValues[3] = pMsg->Channel_2_Differential__raw;
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_2_Analog_Card__neoVI_Index = 18;

void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_2_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_3_Differential_ = dValues[0];
    pMsg->Channel_4_Differential_ = dValues[1];
    pMsg->Channel_5_Differential_ = dValues[2];
    pMsg->Channel_6_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_3_Differential__raw = (WORD)nRawValues[0];
    pMsg->Channel_4_Differential__raw = (WORD)nRawValues[1];
    pMsg->Channel_5_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_6_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_3_Differential_;
    dArray[1] = pMsg->Channel_4_Differential_;
    dArray[2] = pMsg->Channel_5_Differential_;
    dArray[3] = pMsg->Channel_6_Differential_;
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_3_Differential__raw;
    nRawValues[1] = pMsg->Channel_4_Differential__raw;
    nRawValues[2] = pMsg->Channel_5_Differential__raw;
    nRawValues[3] = pMsg->Channel_6_Differential__raw;
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_3_Analog_Card__neoVI_Index = 19;

void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_3_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_7_Differential_ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Channel_7_Differential__raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_7_Differential_;
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_7_Differential__raw;
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_4_Analog_Card__neoVI_Index = 20;

void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_4_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Time_Resync_neoVI_Index = 21;

void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Time_Resync_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Time_Resync_neoVI_LoadSignalValuesArray(DB_Time_Resync_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Time_Resync_neoVI_LoadRawSignalValuesArray(DB_Time_Resync_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VNET_Clock_Edge_neoVI_Index = 22;

void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_Clock_Edge_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_VNET_A_Stats_neoVI_Index = 23;

void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Stats_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->msgTotal = dValues[0];
    pMsg->rxSize = dValues[1];
    pMsg->scCnt = dValues[2];
    pMsg->yields = dValues[3];
    pMsg->bytesRead = dValues[4];
    CM_MessageRawInit(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->msgTotal_raw = (WORD)nRawValues[0];
    pMsg->rxSize_raw = (BYTE)nRawValues[1];
    pMsg->scCnt_raw = (BYTE)nRawValues[2];
    pMsg->yields_raw = (WORD)nRawValues[3];
    pMsg->bytesRead_raw = (WORD)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->msgTotal;
    dArray[1] = pMsg->rxSize;
    dArray[2] = pMsg->scCnt;
    dArray[3] = pMsg->yields;
    dArray[4] = pMsg->bytesRead;
}

void DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->msgTotal_raw;
    nRawValues[1] = pMsg->rxSize_raw;
    nRawValues[2] = pMsg->scCnt_raw;
    nRawValues[3] = pMsg->yields_raw;
    nRawValues[4] = pMsg->bytesRead_raw;
}

int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VNET_A_Reboot_neoVI_Index = 24;

void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Reboot_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Went_To_Sleep_neoVI_Index = 25;

void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Went_To_Sleep_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Device_subsystem_restarted__neoVI_Index = 26;

void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Device_subsystem_restarted__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Ethernet_DAQ_Report_neoVI_Index = 27;

void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Ethernet_DAQ_Report_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Recording = dValues[0];
    pMsg->FPGA_Alive = dValues[1];
    pMsg->Bad_Chip = dValues[2];
    pMsg->Raw_MAC_Mode = dValues[3];
    pMsg->IPv4_Filter = dValues[4];
    pMsg->RxOverflow = dValues[5];
    pMsg->CmdBusy = dValues[6];
    pMsg->LogTO = dValues[7];
    pMsg->SockActivityTO = dValues[8];
    pMsg->FPGAComTO = dValues[9];
    pMsg->SockConfigTO = dValues[10];
    pMsg->SockDiscon = dValues[11];
    pMsg->WcfSM = dValues[12];
    pMsg->TxMsgsPending = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->Recording_raw = (BYTE)nRawValues[0];
    pMsg->FPGA_Alive_raw = (BYTE)nRawValues[1];
    pMsg->Bad_Chip_raw = (BYTE)nRawValues[2];
    pMsg->Raw_MAC_Mode_raw = (BYTE)nRawValues[3];
    pMsg->IPv4_Filter_raw = (BYTE)nRawValues[4];
    pMsg->RxOverflow_raw = (BYTE)nRawValues[5];
    pMsg->CmdBusy_raw = (BYTE)nRawValues[6];
    pMsg->LogTO_raw = (BYTE)nRawValues[7];
    pMsg->SockActivityTO_raw = (BYTE)nRawValues[8];
    pMsg->FPGAComTO_raw = (BYTE)nRawValues[9];
    pMsg->SockConfigTO_raw = (BYTE)nRawValues[10];
    pMsg->SockDiscon_raw = (BYTE)nRawValues[11];
    pMsg->WcfSM_raw = (BYTE)nRawValues[12];
    pMsg->TxMsgsPending_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Recording;
    dArray[1] = pMsg->FPGA_Alive;
    dArray[2] = pMsg->Bad_Chip;
    dArray[3] = pMsg->Raw_MAC_Mode;
    dArray[4] = pMsg->IPv4_Filter;
    dArray[5] = pMsg->RxOverflow;
    dArray[6] = pMsg->CmdBusy;
    dArray[7] = pMsg->LogTO;
    dArray[8] = pMsg->SockActivityTO;
    dArray[9] = pMsg->FPGAComTO;
    dArray[10] = pMsg->SockConfigTO;
    dArray[11] = pMsg->SockDiscon;
    dArray[12] = pMsg->WcfSM;
    dArray[13] = pMsg->TxMsgsPending;
}

void DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Recording_raw;
    nRawValues[1] = pMsg->FPGA_Alive_raw;
    nRawValues[2] = pMsg->Bad_Chip_raw;
    nRawValues[3] = pMsg->Raw_MAC_Mode_raw;
    nRawValues[4] = pMsg->IPv4_Filter_raw;
    nRawValues[5] = pMsg->RxOverflow_raw;
    nRawValues[6] = pMsg->CmdBusy_raw;
    nRawValues[7] = pMsg->LogTO_raw;
    nRawValues[8] = pMsg->SockActivityTO_raw;
    nRawValues[9] = pMsg->FPGAComTO_raw;
    nRawValues[10] = pMsg->SockConfigTO_raw;
    nRawValues[11] = pMsg->SockDiscon_raw;
    nRawValues[12] = pMsg->WcfSM_raw;
    nRawValues[13] = pMsg->TxMsgsPending_raw;
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Status_Update_neoVI_Index = 28;

void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Status_Update_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Type = dValues[0];
    pMsg->ChangeCount = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Type_raw = (BYTE)nRawValues[0];
    pMsg->ChangeCount_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Type;
    dArray[1] = pMsg->ChangeCount;
}

void DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Type_raw;
    nRawValues[1] = pMsg->ChangeCount_raw;
}

int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Scc_Status_neoVI_Index = 29;

void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Scc_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->FvA = dValues[0];
    pMsg->ScA = dValues[1];
    pMsg->Atv = dValues[2];
    pMsg->sip = dValues[3];
    pMsg->pt = dValues[4];
    pMsg->Req = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->FvA_raw = (BYTE)nRawValues[0];
    pMsg->ScA_raw = (BYTE)nRawValues[1];
    pMsg->Atv_raw = (BYTE)nRawValues[2];
    pMsg->sip_raw = (BYTE)nRawValues[3];
    pMsg->pt_raw = (DWORD)nRawValues[4];
    pMsg->Req_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Scc_Status_neoVI_LoadSignalValuesArray(DB_Scc_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->FvA;
    dArray[1] = pMsg->ScA;
    dArray[2] = pMsg->Atv;
    dArray[3] = pMsg->sip;
    dArray[4] = pMsg->pt;
    dArray[5] = pMsg->Req;
}

void DB_Scc_Status_neoVI_LoadRawSignalValuesArray(DB_Scc_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->FvA_raw;
    nRawValues[1] = pMsg->ScA_raw;
    nRawValues[2] = pMsg->Atv_raw;
    nRawValues[3] = pMsg->sip_raw;
    nRawValues[4] = pMsg->pt_raw;
    nRawValues[5] = pMsg->Req_raw;
}

int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index = 30;

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM1_IN = dValues[0];
    pMsg->PWM2_IN = dValues[1];
    pMsg->PWM3_IN = dValues[2];
    pMsg->PWM4_IN = dValues[3];
    pMsg->PWM5_IN = dValues[4];
    pMsg->PWM6_IN = dValues[5];
    pMsg->PWM7_IN = dValues[6];
    pMsg->PWM8_IN = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->PWM1_IN_raw = (BYTE)nRawValues[0];
    pMsg->PWM2_IN_raw = (BYTE)nRawValues[1];
    pMsg->PWM3_IN_raw = (BYTE)nRawValues[2];
    pMsg->PWM4_IN_raw = (BYTE)nRawValues[3];
    pMsg->PWM5_IN_raw = (BYTE)nRawValues[4];
    pMsg->PWM6_IN_raw = (BYTE)nRawValues[5];
    pMsg->PWM7_IN_raw = (BYTE)nRawValues[6];
    pMsg->PWM8_IN_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM1_IN;
    dArray[1] = pMsg->PWM2_IN;
    dArray[2] = pMsg->PWM3_IN;
    dArray[3] = pMsg->PWM4_IN;
    dArray[4] = pMsg->PWM5_IN;
    dArray[5] = pMsg->PWM6_IN;
    dArray[6] = pMsg->PWM7_IN;
    dArray[7] = pMsg->PWM8_IN;
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM1_IN_raw;
    nRawValues[1] = pMsg->PWM2_IN_raw;
    nRawValues[2] = pMsg->PWM3_IN_raw;
    nRawValues[3] = pMsg->PWM4_IN_raw;
    nRawValues[4] = pMsg->PWM5_IN_raw;
    nRawValues[5] = pMsg->PWM6_IN_raw;
    nRawValues[6] = pMsg->PWM7_IN_raw;
    nRawValues[7] = pMsg->PWM8_IN_raw;
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM1__neoVI_Index = 31;

void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM1__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM2__neoVI_Index = 32;

void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM3__neoVI_Index = 33;

void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM3__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM4__neoVI_Index = 34;

void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM4__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM5__neoVI_Index = 35;

void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM5__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM6__neoVI_Index = 36;

void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM6__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM7__neoVI_Index = 37;

void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM7__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM8__neoVI_Index = 38;

void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM8__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Device_Status_neoVI_Index = 39;

void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->HID_Temperature__C_ = dValues[0];
    pMsg->HID_Bus_Voltage__V_ = dValues[1];
    pMsg->VNET_Temperature__C_ = dValues[2];
    pMsg->VNET_Bus_Voltage__V_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->HID_Temperature__C__raw = (WORD)nRawValues[0];
    pMsg->HID_Bus_Voltage__V__raw = (WORD)nRawValues[1];
    pMsg->VNET_Temperature__C__raw = (WORD)nRawValues[2];
    pMsg->VNET_Bus_Voltage__V__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->HID_Temperature__C_;
    dArray[1] = pMsg->HID_Bus_Voltage__V_;
    dArray[2] = pMsg->VNET_Temperature__C_;
    dArray[3] = pMsg->VNET_Bus_Voltage__V_;
}

void DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->HID_Temperature__C__raw;
    nRawValues[1] = pMsg->HID_Bus_Voltage__V__raw;
    nRawValues[2] = pMsg->VNET_Temperature__C__raw;
    nRawValues[3] = pMsg->VNET_Bus_Voltage__V__raw;
}

int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Device_Status_2_neoVI_Index = 40;

void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_2_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Disk_Space_Avail__WiVI__KB = dValues[0];
    pMsg->Power_Supply_Voltage = dValues[1];
    pMsg->Temperature__C_ = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Disk_Space_Avail__WiVI__KB_raw = (DWORD)nRawValues[0];
    pMsg->Power_Supply_Voltage_raw = (WORD)nRawValues[1];
    pMsg->Temperature__C__raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Disk_Space_Avail__WiVI__KB;
    dArray[1] = pMsg->Power_Supply_Voltage;
    dArray[2] = pMsg->Temperature__C_;
}

void DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Disk_Space_Avail__WiVI__KB_raw;
    nRawValues[1] = pMsg->Power_Supply_Voltage_raw;
    nRawValues[2] = pMsg->Temperature__C__raw;
}

int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Trace_Logger_Status_neoVI_Index = 41;

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trace_Logger_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->State = dValues[0];
    pMsg->Debug_Level = dValues[1];
    pMsg->IP_MSB_ = dValues[2];
    pMsg->IP = dValues[3];
    pMsg->IP_sig4 = dValues[4];
    pMsg->IP_LSB_ = dValues[5];
    pMsg->Port = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->State_raw = (BYTE)nRawValues[0];
    pMsg->Debug_Level_raw = (BYTE)nRawValues[1];
    pMsg->IP_MSB__raw = (BYTE)nRawValues[2];
    pMsg->IP_raw = (BYTE)nRawValues[3];
    pMsg->IP_sig4_raw = (BYTE)nRawValues[4];
    pMsg->IP_LSB__raw = (BYTE)nRawValues[5];
    pMsg->Port_raw = (WORD)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->State;
    dArray[1] = pMsg->Debug_Level;
    dArray[2] = pMsg->IP_MSB_;
    dArray[3] = pMsg->IP;
    dArray[4] = pMsg->IP_sig4;
    dArray[5] = pMsg->IP_LSB_;
    dArray[6] = pMsg->Port;
}

void DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->State_raw;
    nRawValues[1] = pMsg->Debug_Level_raw;
    nRawValues[2] = pMsg->IP_MSB__raw;
    nRawValues[3] = pMsg->IP_raw;
    nRawValues[4] = pMsg->IP_sig4_raw;
    nRawValues[5] = pMsg->IP_LSB__raw;
    nRawValues[6] = pMsg->Port_raw;
}

int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Trigger_neoVI_Index = 42;

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trigger_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Logger_triggered = dValues[0];
    pMsg->Pre_trigger_size = dValues[1];
    pMsg->Collection_index = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Logger_triggered_raw = (BYTE)nRawValues[0];
    pMsg->Pre_trigger_size_raw = (DWORD)nRawValues[1];
    pMsg->Collection_index_raw = (BYTE)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trigger_neoVI_LoadSignalValuesArray(DB_Trigger_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Logger_triggered;
    dArray[1] = pMsg->Pre_trigger_size;
    dArray[2] = pMsg->Collection_index;
}

void DB_Trigger_neoVI_LoadRawSignalValuesArray(DB_Trigger_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Logger_triggered_raw;
    nRawValues[1] = pMsg->Pre_trigger_size_raw;
    nRawValues[2] = pMsg->Collection_index_raw;
}

int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Ethernet_Status_neoVI_Index = 43;

void DB_Ethernet_Status_neoVI_Init(DB_Ethernet_Status_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Ethernet_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Link_Status = dValues[0];
    pMsg->Link_Speed = dValues[1];
    pMsg->Link_Duplex = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Link_Status_raw = (BYTE)nRawValues[0];
    pMsg->Link_Speed_raw = (BYTE)nRawValues[1];
    pMsg->Link_Duplex_raw = (BYTE)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Ethernet_Status_neoVI_LoadSignalValuesArray(DB_Ethernet_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Link_Status;
    dArray[1] = pMsg->Link_Speed;
    dArray[2] = pMsg->Link_Duplex;
}

void DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(DB_Ethernet_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Link_Status_raw;
    nRawValues[1] = pMsg->Link_Speed_raw;
    nRawValues[2] = pMsg->Link_Duplex_raw;
}

int DB_Ethernet_Status_neoVI_Transmit(DB_Ethernet_Status_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_Status_neoVI_Init(pMsg);
    }

    DB_Ethernet_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_Ethernet_Status_neoVI_Transmit_raw(DB_Ethernet_Status_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_Status_neoVI_Init(pMsg);
    }

    DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_Ethernet_Status_neoVI_UpdateBytesFromSignals(DB_Ethernet_Status_neoVI * pMsg)
{
    double dArray[3];

    DB_Ethernet_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Ethernet_Status_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_Status_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index = 44;

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Network = dValues[0];
    pMsg->Link_Status = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Network_raw = (BYTE)nRawValues[0];
    pMsg->Link_Status_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Network;
    dArray[1] = pMsg->Link_Status;
}

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Network_raw;
    nRawValues[1] = pMsg->Link_Status_raw;
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(pMsg);
    }

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit_raw(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(pMsg);
    }

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dArray[2];

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromRawSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index = 45;

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Period = dValues[0];
    pMsg->Pulse_Width = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Period_raw = (DWORD)nRawValues[0];
    pMsg->Pulse_Width_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Period;
    dArray[1] = pMsg->Pulse_Width;
}

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Period_raw;
    nRawValues[1] = pMsg->Pulse_Width_raw;
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dArray[2];

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index = 46;

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Period = dValues[0];
    pMsg->Pulse_Width = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Period_raw = (DWORD)nRawValues[0];
    pMsg->Pulse_Width_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Period;
    dArray[1] = pMsg->Pulse_Width;
}

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Period_raw;
    nRawValues[1] = pMsg->Pulse_Width_raw;
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dArray[2];

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Hardware_Latency_Test_neoVI_Index = 47;

void DB_Hardware_Latency_Test_neoVI_Init(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Hardware_Latency_Test_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Latency__us_ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Latency__us__raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(DB_Hardware_Latency_Test_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Latency__us_;
}

void DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(DB_Hardware_Latency_Test_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Latency__us__raw;
}

int DB_Hardware_Latency_Test_neoVI_Transmit(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Hardware_Latency_Test_neoVI_Init(pMsg);
    }

    DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Hardware_Latency_Test_neoVI_Transmit_raw(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Hardware_Latency_Test_neoVI_Init(pMsg);
    }

    DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromSignals(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dArray[1];

    DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromRawSignals(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_MIC_neoVI_Index = 48;

void DB_neoVI_MIC_neoVI_Init(DB_neoVI_MIC_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_MIC_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Button_Pressed = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Button_Pressed_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_MIC_neoVI_LoadSignalValuesArray(DB_neoVI_MIC_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Button_Pressed;
}

void DB_neoVI_MIC_neoVI_LoadRawSignalValuesArray(DB_neoVI_MIC_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Button_Pressed_raw;
}

int DB_neoVI_MIC_neoVI_Transmit(DB_neoVI_MIC_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_MIC_neoVI_Init(pMsg);
    }

    DB_neoVI_MIC_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_neoVI_MIC_neoVI_Transmit_raw(DB_neoVI_MIC_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_MIC_neoVI_Init(pMsg);
    }

    DB_neoVI_MIC_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_neoVI_MIC_neoVI_UpdateBytesFromSignals(DB_neoVI_MIC_neoVI * pMsg)
{
    double dArray[1];

    DB_neoVI_MIC_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_MIC_neoVI_UpdateBytesFromRawSignals(DB_neoVI_MIC_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_neoVI_MIC_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_MIC_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Device_Status_neoVI_db49_Index = 49;

void DB_neoVI_Device_Status_neoVI_db49_Init(DB_neoVI_Device_Status_neoVI_db49 * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_neoVI_db49_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Bus_Voltage__V_ = dValues[0];
    pMsg->HID_Temperature__C_ = dValues[1];
    pMsg->MCHIP_Temperature__C_ = dValues[2];
    pMsg->ZCHIP_Temperature__C_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Bus_Voltage__V__raw = (DWORD)nRawValues[0];
    pMsg->HID_Temperature__C__raw = (DWORD)nRawValues[1];
    pMsg->MCHIP_Temperature__C__raw = (DWORD)nRawValues[2];
    pMsg->ZCHIP_Temperature__C__raw = (DWORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_neoVI_db49_LoadSignalValuesArray(DB_neoVI_Device_Status_neoVI_db49 * pMsg, double *dArray)
{
    dArray[0] = pMsg->Bus_Voltage__V_;
    dArray[1] = pMsg->HID_Temperature__C_;
    dArray[2] = pMsg->MCHIP_Temperature__C_;
    dArray[3] = pMsg->ZCHIP_Temperature__C_;
}

void DB_neoVI_Device_Status_neoVI_db49_LoadRawSignalValuesArray(DB_neoVI_Device_Status_neoVI_db49 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Bus_Voltage__V__raw;
    nRawValues[1] = pMsg->HID_Temperature__C__raw;
    nRawValues[2] = pMsg->MCHIP_Temperature__C__raw;
    nRawValues[3] = pMsg->ZCHIP_Temperature__C__raw;
}

int DB_neoVI_Device_Status_neoVI_db49_Transmit(DB_neoVI_Device_Status_neoVI_db49 * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_db49_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_db49_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_neoVI_Device_Status_neoVI_db49_Transmit_raw(DB_neoVI_Device_Status_neoVI_db49 * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_db49_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_db49_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_neoVI_Device_Status_neoVI_db49_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI_db49 * pMsg)
{
    double dArray[4];

    DB_neoVI_Device_Status_neoVI_db49_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Device_Status_neoVI_db49_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI_db49 * pMsg)
{
    uint64 nRawValues[4];

    DB_neoVI_Device_Status_neoVI_db49_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_db49_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

