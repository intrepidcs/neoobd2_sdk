/*
 * Copyright (c) 2015-2017, Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// stdlib includes
#include <stdint.h>
#include <stddef.h>

#include "Board.h"

// ISM Lib includes
#include "obd2pro_wifi_cc32xx_ism.h"
#include "obd2pro_wifi_cc32xx.h"

extern void Spy_EveryLoop(unsigned int);
extern void Spy_BeforeStarted(void);
extern void Spy_Started(void);
extern void Spy_Main(void);
extern void Spy_ErrorFrame(int, int, int, int);
extern void Spy_ErrorState(int, int, int, int);

void *mainThread(void* arg0)
{
    icsISM_PreInit();

    /* Here is where we link up the user code to the static lib */
    RegisterInitFunc(CM_ExtensionInit);
    RegisterMsProcessFunc(Spy_EveryLoop);
    RegisterBeforeStartedFunc(Spy_BeforeStarted);
    RegisterStartedFunc(Spy_Started);
    RegisterMainFunc(Spy_Main);
    RegisterErrorFrameFunc(Spy_ErrorFrame);
    RegisterErrorStateFunc(Spy_ErrorState);
    RegisterEveryMessageFunc(CM_EveryMessage);

    icsISM_Init();

    while (1)//lint !e716 while1
    {
        icsISM_Main();
    }

    return 0; //lint !e527
}
