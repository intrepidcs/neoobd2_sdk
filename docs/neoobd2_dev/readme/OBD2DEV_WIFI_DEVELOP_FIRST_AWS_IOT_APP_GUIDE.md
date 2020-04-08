# Getting Started with AWS IoT Core Application for neoOBD2 DEV

This guide provides a step-by-step guide on creating, debugging, and deploying a sample ready-to-build TI CC3235SF Wi-Fi application for neoOBD2 DEV. This sample project is available in the neoOBD2 SDK. The application is an extension of the "Subscribe Publish" example application available in the Simplelink AWS IoT Plugin for CC32XX. Intrepid has modified the original example to send data elements gathered from several CAN messages to the AWS Iot Core using MQTT publish. In addition, the example receives an arbitrary data of up to 8 bytes and propgate that data out to the CAN network as a transmit CAN message.

You will learn to do the following:

* Use the CC32XX Simplelink SDK and Simplelink AWS IoT Plugin in CC3235SF to communicate with AWS IoT Core using MQTT.
* Use the Intrepid Secure Module (ISM) API in CC3235SF to transmit and receive CAN messages configured from the C Code Interface view of Vehicle Spy Enterprise.
* Publish received CAN signals in realtime to AWS IoT Core using MQTT.
* Subscribe to a topic to receive some arbitrary data up to 8 bytes and transmit that data as a CAN message.

When the sample application is properly configured and programmed into the CC3235SF Wi-Fi processor, the neoOBD2 DEV will perform the following:

* Initialize and enable the CC3235SF's Wi-Fi subsystem.
* Initialize various peripherals and the ISM API library.
* Received CAN messages are processed by the receive message event handler callback functions.
* A CAN message is transmitted on 100msec interval.
* Provision *certificate and private key* needed to connect to the AWS IoT Core.
* Use user-configured *Wi-Fi credentials* to connect to a Wi-Fi Access Point in station mode.
* Connect to the MQTT endpoint address of your AWS IoT Core account.
* Publish a payload containing the *"Vehicle Speed, Engine Speed, and Throttle Position"* data parsed from the receive message event handlers to the *obd2dev/demo/data* topic on 500msec interval.
* Subscribe to a topic containing arbitrary data upto 8 bytes that can be transmitted out as a CAN message on 100msec interval.

## Prerequisites

Required Hardware:

1. neoOBD2 DEV
2. neoOBD2 SIM (Optional / highly recommended)
3. USB-A to USB-C USB 2.0 or 3.1 Cable
4. USB-A to Micro-B USB 2.0 Cable

Required Software:

1. neoOBD2 SDK

2. Vehicle Spy Enterprise

    [Vehicle Spy Enterprise](https://store.intrepidcs.com/Vehicle-Spy-p/vspy-3-ent.htm) is a single tool for diagnostics, node/ECU simulation, data acquisition, automated testing, and in-vehicle communication networks bus monitoring.
    
    For introduction, tutorials, and documentations on Vehicle Spy Enterprise, please [click here](https://cdn.intrepidcs.net/support/VehicleSpy/vehiclespyhelpdoc.html).

3. TI Code Composer Studio (CCS) IDE - download [here](http://www.ti.com/tool/download/CCSTUDIO)

4. TI Uniflash Utility - download [here](http://www.ti.com/tool/UNIFLASH)

5. TI Simplelink CC32XX Plugin for AWS IoT Core - download [here](http://www.ti.com/tool/download/SIMPLELINK-CC32XX-PLUGIN-FOR-AWSIOT)

Other requirements:

1. AWS IoT account with access to the AWS IoT console - [create one here](https://aws.amazon.com)

## Import, Build, and Run the AWS CC32XX Plugin for AWS IoT Core

First, let's import, build, and run the *subscribe_publish_sample_CC3235SF_LAUNCHXL_freertos_ccs* project provided in the plugin.

1. Download and install the following software. 

	- [TI Code Composer Studio (CCS) IDE](http://www.ti.com/tool/download/CCSTUDIO)
	- [TI Uniflash](http://www.ti.com/tool/UNIFLASH)
	- [AWS CC32XX Plugin for AWS IoT Core](http://www.ti.com/tool/download/SIMPLELINK-CC32XX-PLUGIN-FOR-AWSIOT).

2. Navigate to the install directory of the plugin and locate the **AWS_Quick_Start_Guide.html** under <install_path>/docs/aws. Open the guide.

3. You may jump to the **Hardware Setup** section. You will notice the **Jumper Settings** section describes the sense-on-power scheme. The SOP pins 0 - 2 on the neoOBD2 DEV is indicated below. 

	![alt text](../images/17-obd2dev_cc32xx_sop_pins.PNG "CC32XX SOP Pins on neoOBD2 DEV")
	
	For debugging in CCS and programming using the TI Uniflash software, you can use the onboard XDS110 USB-JTAG probe. Simply plug-in a Type-A to Micro-B USB cable to the correct Micro USB port that points to the CC3235SF on the neoOBD2. If you flip the board, the USB port is labeled as **WiFi Debug Port**.
	
	![alt text](../images/3-obd2dev-usb-map.PNG "XDS110 USB-JTAG USB port")

4. Follow the rest of the guide exactly as shown. Make sure to follow the **Example Pre-Build Steps** section of the guide to properly configure the certificates and the Wi-Fi credentials in the **aws_iot_config.h**.

Once you have completed the above steps, you should be able to build and debug your project on the neoOBD2 DEV to establish MQTT pub/sub between the CC3235SF and your AWS IoT Core endpoint. 

Next, we will work on adding the auto-generated C codes from Vehicle Spy's **C Code Interface** tool and the **ISM API library** to expand the sample application to access the CAN network simultaneously while communicating with AWS IoT Core.

## Importing auto-generated ISM codes from Vehicle Spy Enterprise

The **ISM library (obd2lc_wifi_cc32xx_ism.a)** and a set of **auto-generated ISM source files (obd2lc_wifi_cc32xx.c, obd2lc_wifi_cc32xx.h, and SpyCCode.c) from Vehicle Spy Enterprise** are the software components that grant the code running on CC3235SF transmit and receive access to data over the vehicle networks supported by neoOBD2 DEV.

Please complete this section to learn how to generate and import the above files into the project as they are essential parts of Wi-Fi application development process using the neoOBD2 DEV.

1. Open Vehicle Spy Enterprise. Go to the **Scripting and Automation** menu and select **C Code Interface.** 

2. Click **Add Project...** button and select **New Project...**

3. Click the **Create embedded projects for Intrepid Security Module (ISM) devices** checkbox to inflate additional view.

	![alt text](../images/18-obd2dev_new_wifi_ccif_proj.PNG "Vehicle Spy create new CCIF Project")

4. Select **neoOBD2 LC WiFi CC32XX** from the list of available ISM targets and add it to the selected ISM targets list. Click **OK** button to generate ISM source files. Note that Visual Studio will open if you have Visual Studio installed on your PC.

5. Let's add the three CAN messages that will each hold a 2-byte CAN signal; vehicle speed, engine speed, and throttle position. Go to the **Messages Editor** and add three messages under the **Receive** tab as follows.

	![alt text](../images/29-obd2dev_add_rx_msgs.PNG "Create RX Messages")
	
6. Create event handlers for the three CAN messages. Go to **C Code Interface** and click the **Edit** button to open the **C Code Module Setup** view. navigate to the **Message Events** tab where you will see the three receive messages that were created in the previous step. Double click to add all of them to the list box on the right.

	Navigate to the **Event Handler Code** tab. Click the **Copy** button to copy the generated code stub to the Windows clip board. Click the **OK** button to exit the **C Code Module Setup** view.

	Once you are back to the **C Code Interface** view, click the **Update Support Files** button.

	**IMPORTANT:** Before proceeding further, save the Vehicle Spy Enterprise project (.vs3) by going to **File** on top menu and selecting **Save**. The saved .vs3 project will be used later to program the completed application into the CC3235SF in neoOBD2 DEV.

7. Now that the auto-generates source files have been updated, We will flash the CoreMini binary down to the main CPU on neoOBD2 DEV. The CoreMini is a critical component, it will filter the received CAN messages and forward the three messages of interest to the appropriate receive message event handlers.

	Connect the neoOBD2 DEV to your PC via the USB Type-C cable. In Vehicle Spy, go to **Tools -> CoreMini Console**. Wait for the **CoreMini Executable Generator** view to appear. Click the **Send** button to program the CoreMini binary. Confirm you have successfully programmed the CoreMini binary by verifying the **Success** message.
	
	![alt text](../images/40-obd2dev_coremini_flash.PNG "Flash CoreMini executable")

8. Go back to the **C Code Interface view**. Click the **Folder** button which will open up a file explorer in the root directory of the generated C Code Project. 

	![alt text](../images/19-obd2dev_ccif_proj_folder.PNG "Open the create CCIF Project Root Directory")
	
9. Open the **SpyCCode.c** file in a text editor and paste the **Event Handler Code** stub that you copied from step 6.

	![alt text](../images/30-obd2dev_add_rx_msg_handlers.PNG "Paste the code stub into SpyCCode.c")

10. Copy the **SpyCCode.c** file and add it into the CCS project directory.

	![alt text](../images/20-obd2dev_overwrite_spyccode.PNG "Integrate ISM source codes into CCS project")
	
11. Go back to the file explorer. Open the **ProjectName_neoOBD2LC_WIFI_CC32XX** folder. Copy **obd2lc_wifi_cc32xx.c** and **obd2lc_wifi_cc32xx.h** files and paste them into the CCS project directory.

	![alt text](../images/21-obd2dev_overwrite_lcfiles.PNG "Integrate ISM source codes into CCS project")

12. Open project properties in CCS and verify the **BUILD_OBD2LC_WIFI_CC32XX_ISM_PROJECT** is defined in **Predefined Symobls** list.

	![alt text](../images/22-obd2dev_preprocessor.PNG "Add preprocessor macro for Wi-Fi project")

13. We need to add a few more ISM API source files. Navigate to path <neoobd2sdk_path>\demos\intrepid\neoobd2_dev\wifi\ismlib. Copy all files and paste them into the CCS project directory.

	![alt text](../images/23-obd2dev_additional_ismlib.PNG "Add additional ISM API files")
	
14. Open project properties in CCS and go to **File Search Path** under **ARM Linker**. Add **obd2lc_wifi_cc32xx_ism.a** in the first list box. Add **${workspace_loc:/${ProjName}}** in the second box. Make sure **Reread libraries** option is checked.

	![alt text](../images/24-obd2dev_link_ismlib.PNG "Linker settings for ISM API library")

15. Build the CCS project and verify the project builds successfully.

	The ISM API glue codes and library are now all integrated into the project, but they are not actually being executed as we have not added any codes that exercise the library. Next, we will add codes to enable vehicle network communication. This will allow you to receive and transmit CAN messages from the project. Furthermore, we will add codes to forward the CAN data to AWS IoT Core and transmit data received from AWS IoT Core in a CAN message.
	
## Add Codes to Facilitate CAN Rx and Tx with AWS IoT Core

1. From the project explorer, open the **aws_iot.syscfg** file. From the menu window that pops up, delete the following peripherals.
	- SPI
	- DMA
	- GPIO

	These peripherals are already in use by the ISM API library (obd2lc_wifi_cc32xx_ism.a). If you attempt to compile with the above peripherals defined in the **aws_iot.syscfg** file, the compiler will throw an error saying some of the functions are re-defined. 

	First, choose SPI from the list and click the **Remove All** button. You will notice DMA automatically removed when SPI is removed. Then, choose GPIO from the list and click the **Removal All** button.

	Verify that only the following are enabled from the **TI Driver** list.
	- Display
	- Power
	- RTOS
	- UART

	***Please note that the following peripherals are used by the ISM API library (obd2lc_wifi_cc32xx_ism.a), and are not available for your application.***
	- GSPI
	- Timer0
	- GPIO (*GPIOs are not available for user applications*)

2. Let's start making some code changes. 

	First, add the following includes and extern forward protos.
	
	![alt text](../images/31-obd2dev_main_freertos_includes.PNG "Add ISM API includes and forward protos")

	Next, go to the main() function in **main_freertos.c**. Comment out or delete the GPIO calls.

	![alt text](../images/26-obd2dev_remove_main_calls.PNG "Remove GPIO calls from main()")
	
	Declare a new thread instance for the ISM process, and add the ISM initialization codes.
	
	![alt text](../images/33-obd2dev_main_freertos_ism_create.PNG "Add ISM init code")
	
	Finally implement the function that shall be executed in the ISM thread.
	
	![alt text](../images/34-obd2dev_main_freertos_ism_thread.PNG "Implement ISM thread function")

3. Next, go to **networks.c** and remove the GPIO calls.

	Remove GPIO calls from network_startup():
	
	![alt text](../images/27-obd2dev_remove_network_calls.PNG "Remove GPIO calls from network_startup()")
	
	Remove GPIO calls from initWiFi():
	
	![alt text](../images/28-obd2dev_remove_network_calls.PNG "Remove GPIO calls from initWiFi()")

5. Let's implement the Receive Message Event Handlers in **SpyCCode.c**.

	First, open **obd2lc_wifi_cc32xx.h** and define the global object that will store the vehicle data points contained in the payload of the received messages.
	
	```
	typedef struct _stVehicleData
	{
	    union {
		uint16_t speed;
		uint8_t speedBytes[2];
	    };

	    union {
		uint16_t rpm;
		uint8_t rpmBytes[2];
	    };

	    union {
		uint16_t throttle;
		uint8_t throttleBytes[2];
	    };
	} stVehicleData;
	```
	
	Then, declare the vehicle data object and the 8-byte buffer to store the CAN Tx data from the server as follows.
	
	```
	// TODO: add global variables here
	stVehicleData obVehicleData;
	uint8_t canTxData[8];
	```
	
	For every CAN message that is associated with each of the event handlers, the ISM process will auto-magically invoke the matching handler. We will assume the signals are occupying the first two bytes of each corresponding CAN messages. We store the received signal data into our global object.
	
	```
	void SpyMsg_MG_RPM_Msg_HS_CAN(MG_RPM_Msg_HS_CAN * pMG_RPM_Msg_HS_CAN)
	{
		// store the vehicle speed occupying the first two bytes of the received CAN message
		obVehicleData.speedBytes[0] = pMG_RPM_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.speedBytes[1] = pMG_RPM_Msg_HS_CAN->MessageData.btData[0];	
	}

	void SpyMsg_MG_Speed_Msg_HS_CAN(MG_Speed_Msg_HS_CAN * pMG_Speed_Msg_HS_CAN)
	{
		// store the engine speed occupying the first two bytes of the received CAN message
		obVehicleData.rpmBytes[0] = pMG_Speed_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.rpmBytes[1] = pMG_Speed_Msg_HS_CAN->MessageData.btData[0];		
	}

	void SpyMsg_MG_Throttle_Msg_HS_CAN(MG_Throttle_Msg_HS_CAN * pMG_Throttle_Msg_HS_CAN)
	{
		// store the throttle position occupying the first two bytes of the received CAN message
		obVehicleData.throttleBytes[0] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.throttleBytes[1] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[0];
	}
	```

	A good way to check if the event handlers are actually receiving the correct CAN message is by implementing the following logic to re-transmit or gateway the received message as another message.

	``` 
	#define ENABLE_GATEWAY_TEST (1)
	
	void SpyMsg_MG_RPM_Msg_HS_CAN(MG_RPM_Msg_HS_CAN * pMG_RPM_Msg_HS_CAN)
	{
		// store the vehicle speed occupying the first two bytes of the received CAN message
		obVehicleData.speedBytes[0] = pMG_RPM_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.speedBytes[1] = pMG_RPM_Msg_HS_CAN->MessageData.btData[0];	
	
	#if ENABLE_GATEWAY_TEST
		GenericMessage msg = { 0 };
		msg.iID = pMG_RPM_Msg_HS_CAN->MessageData.iID + 1;
		msg.iNetwork = pMG_RPM_Msg_HS_CAN->MessageData.iNetwork;
		msg.iNumDataBytes = pMG_RPM_Msg_HS_CAN->MessageData.iNumDataBytes;
		memcpy(msg.btData, pMG_RPM_Msg_HS_CAN->MessageData.btData, pMG_RPM_Msg_HS_CAN->MessageData.iNumDataBytes);
		GenericMessageTransmit(&msg);
	#endif
	}

	void SpyMsg_MG_Speed_Msg_HS_CAN(MG_Speed_Msg_HS_CAN * pMG_Speed_Msg_HS_CAN)
	{
		// store the engine speed occupying the first two bytes of the received CAN message
		obVehicleData.rpmBytes[0] = pMG_Speed_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.rpmBytes[1] = pMG_Speed_Msg_HS_CAN->MessageData.btData[0];	
	
	#if ENABLE_GATEWAY_TEST
		GenericMessage msg = { 0 };
		msg.iID = pMG_Speed_Msg_HS_CAN->MessageData.iID + 2;
		msg.iNetwork = pMG_Speed_Msg_HS_CAN->MessageData.iNetwork;
		msg.iNumDataBytes = pMG_Speed_Msg_HS_CAN->MessageData.iNumDataBytes;
		memcpy(msg.btData, pMG_Speed_Msg_HS_CAN->MessageData.btData, pMG_Speed_Msg_HS_CAN->MessageData.iNumDataBytes);
		GenericMessageTransmit(&msg);
	#endif
	}

	void SpyMsg_MG_Throttle_Msg_HS_CAN(MG_Throttle_Msg_HS_CAN * pMG_Throttle_Msg_HS_CAN)
	{
		// store the throttle position occupying the first two bytes of the received CAN message
		obVehicleData.throttleBytes[0] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[1];
		obVehicleData.throttleBytes[1] = pMG_Throttle_Msg_HS_CAN->MessageData.btData[0];
	
	#if ENABLE_GATEWAY_TEST
		GenericMessage msg = { 0 };
		msg.iID = pMG_Throttle_Msg_HS_CAN->MessageData.iID + 3;
		msg.iNetwork = pMG_Throttle_Msg_HS_CAN->MessageData.iNetwork;
		msg.iNumDataBytes = pMG_Throttle_Msg_HS_CAN->MessageData.iNumDataBytes;
		memcpy(msg.btData, pMG_Throttle_Msg_HS_CAN->MessageData.btData, pMG_Throttle_Msg_HS_CAN->MessageData.iNumDataBytes);
		GenericMessageTransmit(&msg);
	#endif
	}
	```
	
	Finally, go to **Spy_Everyloop()** function and implement it as follows. This function is automatically executed by the ISM process on every 1ms interval. We will setup a CAN message to be transmitted every 100ms using the 8-byte data received from the server via the MQTT topic **sdkTest/cantx**.
	
	```
	void Spy_EveryLoop(unsigned int uiCurrentTime)
	{
		static int cnt;
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
	```
	
5. All that remains to be extended is the **subscribe_publish_sample.c**. Open the file and include the **obd2lc_wifi_cc32xx.h**. Declare the **stVehicleData** object and the **canTxData** buffer as an extern so that they are visible. Change the **subscribe_callback_handler()** as follows:
	
	```
	extern stVehicleData obVehicleData;
	extern uint8_t canTxData[8];

	static void iot_subscribe_callback_handler(AWS_IoT_Client *pClient,
		char *topicName, uint16_t topicNameLen,
		IoT_Publish_Message_Params *params, void *pData)
	{
	    IOT_UNUSED(pData);
	    IOT_UNUSED(pClient);
	    IOT_INFO("Subscribe callback");
	    IOT_INFO("%.*s\t%.*s",topicNameLen, topicName, (int)params->payloadLen,
		    (char *)params->payload);

	    // Copy the MQTT payload into canTxData array so it can be
	    // transmitted as a CAN message from Spy_EveryLoop() in SpyCCode.c
	    memcpy(canTxData, params->payload, sizeof(canTxData));
	}

	```
	
	Go to the **runAWSClient()** function. Create two variables to store the subscribe topic name and the topic name length. We will set the subscribe topic name to **sdkTest/cantx**.
	
	![alt text](../images/36-obd2dev_pubsub_changes.PNG "Create separate topic for subscribe")
	
	Replace the existing topic name and length parameters in the **aws_iot_mqtt_subscribe()** call.
	
	![alt text](../images/37-obd2dev_pubsub_changes.PNG "Create separate topic for subscribe")
	
	Finally, replace the places where the **cPayload** is constructed using sprintf as follows.
	
	```
	sprintf(cPayload, "%s : %d, %s : %d, %s : %d ", "Speed", obVehicleData.speed, "RPM", obVehicleData.rpm, "Throttle", obVehicleData.throttle);
	```
	
	![alt text](../images/39-obd2dev_pubsub_payload_adj.PNG "Replace code that constructs the MQTT payload")
	
6. All done! Build the project to verify the project builds successfully. 

	For your reference, all source, header, and libraries from this section are placed in the <neoobd2_sdk>\demos\intrepid\neoobd2_dev\wifi\aws_subscribe_publish_sample directory in the neoOBD2 SDK. If you are having difficulty getting the project up and running, simply copy everything in the directory and paste them into the CCS project.

	![alt text](../images/38-obd2dev_pubsub_ref_files.PNG "Reference source, header, and libs")
	
## Running your Application in Debug Mode

Let's run your application in debug and confirm the sample application is running properly.
	
## Programming the Application into neoOBD2 DEV

Once your Wi-Fi program is ready to be deployed in neoOBD2 DEV, you can use Vehicle Spy to do so.

## What's Next?

Now that you are able to import, debug, and program a sample project: 

