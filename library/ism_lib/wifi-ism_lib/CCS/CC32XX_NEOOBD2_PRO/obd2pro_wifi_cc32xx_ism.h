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

#ifndef OBD2PRO_CC32XX_ISM_H_
#define OBD2PRO_CC32XX_ISM_H_

#include "types.h"

void icsISM_PreInit(void);
void icsISM_Init(void);
void icsISM_Main(void);

struct stCallBackPointers
{
    void* pRegisterCallBack;
    void* pGetSetValueCallBack;
    void* pTransmitMessageCallBack;
    void* pOutputWindowCallBack;
    void* pTextAPICallBack;
    void* pGetSignalValue;
    void* pDecodeSignalValue;
    void* pTransmitMessagesFromSignalValues;
    void* pFindIndexForObjectFromNameCallBack;
    void* pShowPanelCallBack;
    void* pMessageGenericInit;
    void* pGetEcuCount;
    void* pGetMemoryBlockCount;
    void* pGetMemoryBlockInfo;
    void* pGetMemoryBlockData;
    void* pSetMemoryBlockData;
    void* pMessageRawInit;
    void* pSignalPhysicalToRaw;
    void* pTransmitMessagesFromRawSignalValues;
    void* pGetMessageName;
    void* pSetControlProp;
    void* pUpdateMessageSignalsFromBytes;
    void* pUpdateBytesFromSignals;
    void* pUpdateBytesFromRawSignals;
};

// map - exposed methods
typedef struct node_t
{
    uint16_t k;
    unsigned int v;
    struct node_t* left;
    struct node_t* right;
} node_t;

typedef struct _map_t
{
    unsigned int numNodes;
    unsigned int maxNodes;
    node_t* pool;
    /* BTree root will always sit at pool[0] */
} map_t;

void map_init(map_t* m, void* p, unsigned int maxNodes);
const node_t* map_lookup(const map_t* m, uint16_t key);
unsigned int map_insert(map_t* m, uint16_t key, unsigned int val);

// ccif_callback
#define CM_CALLBACKTYPE_APP_SIGNAL 0
#define CM_CALLBACKTYPE_MESSAGE 1
#define CM_CALLBACKTYPE_TIMER 2
#define CM_CALLBACKTYPE_MESSAGE_MG 3
#define CM_CALLBACKTYPE_MESSAGE_TX 4
#define CM_CALLBACKTYPE_BEFORE_MESSAGE_TX 5

map_t* icsISM_GetAppSignalMap(void);
map_t* icsISM_GetMessageMap(void);
map_t* icsISM_GetTimerMap(void);
map_t* icsISM_GetMessageTxMap(void);
map_t* icsISM_GetMessageMgMap(void);
map_t* icsISM_GetBeforeMessageTxMap(void);

typedef void (*initFunc_t)(const struct stCallBackPointers*);
typedef void (*msProcessFunc_t)(unsigned int);
typedef void (*beforeStartedCallback_t)(void);
typedef void (*startedCallback_t)(void);
typedef void (*stoppedCallback_t)(void);
typedef void (*mainProcessFunc_t)(void);
typedef void (*errorFrameCallback_t)(int, int, int, int);
typedef void (*errorStateCallback_t)(int, int, int, int);
typedef void (*everyMessageCallback_t)(int, int, uint64_t, unsigned int, int, int, const unsigned char*);

typedef int (*beforeTxCallback_t)(void*);
typedef void (*messageMgCallback_t)(void*);

extern initFunc_t ICSCoreMiniExtensionInit;
extern msProcessFunc_t ICSCoreMiniExtensionProcessMs;
extern beforeStartedCallback_t ICSCoreMiniExtensionBeforeStarted;
extern startedCallback_t ICSCoreMiniExtensionStarted;
extern stoppedCallback_t ICSCoreMiniExtensionStopped;
extern mainProcessFunc_t ICSCoreMiniExtensionMain;
extern errorFrameCallback_t ICSCoreMiniExtensionErrorFrame;
extern errorStateCallback_t ICSCoreMiniExtensionErrorState;
extern everyMessageCallback_t ICSCoreMiniExtensionEveryMessage;

void CCIF_RegisterCallback(unsigned short dataType, unsigned short index, void* pFunction);

unsigned int RegisterInitFunc(initFunc_t f);
unsigned int RegisterMsProcessFunc(msProcessFunc_t f);
unsigned int RegisterBeforeStartedFunc(beforeStartedCallback_t f);
unsigned int RegisterStartedFunc(startedCallback_t f);
unsigned int RegisterStoppedFunc(stoppedCallback_t f);
unsigned int RegisterMainFunc(mainProcessFunc_t f);
unsigned int RegisterErrorFrameFunc(errorFrameCallback_t f);
unsigned int RegisterErrorStateFunc(errorStateCallback_t f);
unsigned int RegisterEveryMessageFunc(everyMessageCallback_t f);


// AES

#define AES_CBC (0)
#define AES_ECB (1)

/** \fn int AES_Decrypt(void* data, void* key, void* iv, uint8_t keyLen, uint16_t dataLen, uint8_t algo)
    \brief Perform in-place AES decryption using Electronic Codebook (ECB) or Cipher Block Chaining (CBC) modes.
    \param data Pointer to the ciphertext. Plaintext will filled in-place.
    \param key Pointer to the decryption key.
    \param iv Pointer to the initialization vector for CBC mode operation.
    \param keyLen Number of bytes in the key. Valid values are 16, 24, or 32.
    \param dataLen Number of bytes of data.
    \param algo The algorithm to use: ALGO_AES_CBC, or ALGO_AES_ECB.
    \return 0 on success, nonzero on failure
 */
int AES_Decrypt(void* data, const void* key, const void* iv, uint8_t keyLen, uint16_t dataLen, uint8_t algo);

/** \fn int AES_Encrypt(void* data, void* key, void* iv, uint8_t keyLen, uint16_t dataLen, uint8_t algo)
    \brief Perform in-place AES Encryption using Electronic Codebook (ECB) or Cipher Block Chaining (CBC) modes.
    \param data Pointer to the plaintext. Ciphertext will filled in-place.
    \param key Pointer to the encryption key.
    \param iv Pointer to the initialization vector for CBC mode operation.
    \param keyLen Number of bytes in the key. Valid values are 16, 24, or 32.
    \param dataLen Number of bytes of data.
    \param algo The algorithm to use: ALGO_AES_CBC, or ALGO_AES_ECB.
    \return 0 on success, nonzero on failure
 */
int AES_Encrypt(void* data, const void* key, const void* iv, uint8_t keyLen, uint16_t dataLen, uint8_t algo);

#endif /* OBD2PRO_WIFI_CC32XX_ISM_H_ */
