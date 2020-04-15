////////////////////////////////////////
// Spy C Code Implementation
////////////////////////////////////////
#if defined(BUILD_VSPY_DLL_PROJECT)
#include "vspy.h"
#elif defined(BUILD_OBD2LC_WIFI_CC32XX_ISM_PROJECT)
#include "obd2lc_wifi_cc32xx.h"
#endif

// module variables

// TODO: add global variables here
stVehicleData obVehicleData;
uint8_t canTxData[8];

// TODO: add event handlers here
void SpyMsg_MG_RPM_Msg_HS_CAN(MG_RPM_Msg_HS_CAN * pMG_RPM_Msg_HS_CAN)
{
    obVehicleData.speedBytes[0] = pMG_RPM_Msg_HS_CAN->MessageData.btData[1];
    obVehicleData.speedBytes[1] = pMG_RPM_Msg_HS_CAN->MessageData.btData[0];

	GenericMessage msg = { 0 };
	msg.iID = pMG_RPM_Msg_HS_CAN->MessageData.iID + 1;
	msg.iNetwork = pMG_RPM_Msg_HS_CAN->MessageData.iNetwork;
	msg.iNumDataBytes = pMG_RPM_Msg_HS_CAN->MessageData.iNumDataBytes;
	memcpy(msg.btData, pMG_RPM_Msg_HS_CAN->MessageData.btData, pMG_RPM_Msg_HS_CAN->MessageData.iNumDataBytes);
	GenericMessageTransmit(&msg);
}

void SpyMsg_MG_Speed_Msg_HS_CAN(MG_Speed_Msg_HS_CAN * pMG_Speed_Msg_HS_CAN)
{
    obVehicleData.rpmBytes[0] = pMG_Speed_Msg_HS_CAN->MessageData.btData[1];
    obVehicleData.rpmBytes[1] = pMG_Speed_Msg_HS_CAN->MessageData.btData[0];

	GenericMessage msg = { 0 };
	msg.iID = pMG_Speed_Msg_HS_CAN->MessageData.iID + 2;
	msg.iNetwork = pMG_Speed_Msg_HS_CAN->MessageData.iNetwork;
	msg.iNumDataBytes = pMG_Speed_Msg_HS_CAN->MessageData.iNumDataBytes;
	memcpy(msg.btData, pMG_Speed_Msg_HS_CAN->MessageData.btData, pMG_Speed_Msg_HS_CAN->MessageData.iNumDataBytes);
	GenericMessageTransmit(&msg);
}

void SpyMsg_MG_Throttle_Msg_HS_CAN(MG_Throttle_Msg_HS_CAN * pMG_Throttle_Msg_HS_CAN)
{
    obVehicleData.throttleBytes[0] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[1];
    obVehicleData.throttleBytes[1] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[0];

	GenericMessage msg = { 0 };
	msg.iID = pMG_Throttle_Msg_HS_CAN->MessageData.iID + 3;
	msg.iNetwork = pMG_Throttle_Msg_HS_CAN->MessageData.iNetwork;
	msg.iNumDataBytes = pMG_Throttle_Msg_HS_CAN->MessageData.iNumDataBytes;
	memcpy(msg.btData, pMG_Throttle_Msg_HS_CAN->MessageData.btData, pMG_Throttle_Msg_HS_CAN->MessageData.iNumDataBytes);
	GenericMessageTransmit(&msg);
}

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
    static int cnt;

    /* The Spy_EverLoop() function is executed by the ISM process
    *  on 1ms interval. Setup a CAN message to be transmitted every
    *  100msec using a simple counter.
    *  Up to 8bytes of MQTT payload is copied into the canTxData
    *  buffer from the MQTT subscribe handler as defined in the
    *  subscribe_publish_sample.c.
    */
    if ( !(++cnt % 100) )
    {
        GenericMessage msg = {0};
        msg.iID = 0x777;
        msg.iNetwork = 1;
        msg.iNumDataBytes = 8;
        memcpy(msg.btData, canTxData, msg.iNumDataBytes);
        GenericMessageTransmit(&msg);
    }
}

#ifdef BUILD_VSPY_DLL_PROJECT
int Spy_EveryMessage_BeforeTx(GenericMessage * p_Msg, int index)
{
	return 0; // Send your message here and return 1 if you need to
}

int Spy_EveryLongMessage_BeforeTx(GenericLongMessage * p_Msg, int index)
{
	return 0; // Send your message here and return 1 if you need to
}

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
#elif defined(BUILD_NEODEVICE_STM32F415_ISM_PROJECT)
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
#elif defined(BUILD_OBD2LC_WIFI_CC32XX_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time OBD2LC WiFi CC32XX ISM is run
}
#elif defined(BUILD_OBD2LC_BLE_NRF52_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time OBD2LC BLE nRF52 ISM is run
}
#elif defined(BUILD_NEODEVICE_STM32F301_ISM_PROJECT)
void Spy_Main()
{
	// TODO: Add code here to run every time NEODEVICE STM32F301 ISM is run
}
#endif
