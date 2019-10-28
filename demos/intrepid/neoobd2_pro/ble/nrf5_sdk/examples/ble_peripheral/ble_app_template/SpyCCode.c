////////////////////////////////////////
// Spy C Code Implementation
////////////////////////////////////////
#if defined(BUILD_VSPY_DLL_PROJECT)
#include "vspy.h"
#elif defined(BUILD_OBD2PRO_BLE_NRF52_ISM_PROJECT)
#include "obd2pro_ble_nrf52.h"
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
	static int cnt = 0;

	if (!(++cnt % 100))
	{
		GenericMessage msg = {0};
		msg.iID = 0x111;
		msg.iNetwork = 1;
		msg.iNumDataBytes = 8;
		msg.btData[0] = 0xAA;
		msg.btData[7] = 0xBB;
		GenericMessageTransmit(&msg);
	}
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
#if defined(BUILD_VSPY_DLL_PROJECT)
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
