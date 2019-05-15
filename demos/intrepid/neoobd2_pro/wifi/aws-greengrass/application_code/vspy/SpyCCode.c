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

////////////////////////////////////////
// Spy C Code Implementation
////////////////////////////////////////
#ifdef BUILD_VSPY_DLL_PROJECT
#include "vspy.h"
#elif defined(BUILD_OBD2PRO_WIFI_CC32XX_ISM_PROJECT)
#include "obd2pro_wifi_cc32xx.h"
#endif

// module variables

// TODO: add global variables here

// TODO: add event handlers here

void Spy_EveryMessage(GenericMessage * p_Msg)
{
	// TODO: add something you want to do for every message
}

void Spy_EveryLongMessage(GenericLongMessage * p_Msg)
{
	// TODO: add something you want to do for every long message
}

void Spy_EveryLoop(unsigned int uiCurrentTime)
{
	// TODO: add something you want to do every millisecond
}

#ifdef BUILD_VSPY_DLL_PROJECT
void Spy_EveryGUILoop()
{
	// TODO: write code to interact with the vehicle spy gui (this is called on the GUI thread)
}
#endif

void Spy_ErrorState(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
}

void Spy_ErrorFrame(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
}

void Spy_Stopped()
{

	// TODO: add stopped code
}

void Spy_KeyPress(int iKey, int iCTRLPressed, int iALTPressed)
{
	// TODO: add key handler code
}

void Spy_Started()
{
	// TODO: add started code
}

void Spy_BeforeStarted()
{
	// TODO: add before started code
}
#ifdef BUILD_VSPY_DLL_PROJECT
void Spy_Main()
{
	// TODO: Add code here to run every time Spy is run
	do 
	{
			// delay for one second
			Sleep(1000);
			// write to the output window
			Printf("Another Second happened\n");
			
	} while (1);
}
#elif defined(BUILD_FIRE2_STM32_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time FIRE2 STM32 ISM is run
}
#elif defined(BUILD_OBD2PRO_WIFI_CC32XX_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time OBD2PRO WiFi CC32XX ISM is run
}
#elif defined(BUILD_FIRE2_BLE_NRF51_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time FIRE2 BLE nRF51 ISM is run
}
#elif defined(BUILD_OBD2PRO_BLE_NRF52_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time OBD2PRO BLE nRF52 ISM is run
}
#elif defined(BUILD_VALUECAN4_STM32_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time VALUECAN4 STM32 ISM is run
}
#endif
