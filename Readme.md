# neoOBD2 SDK

Today, it is easy to find IoT platforms that allow individuals and enterprises to quickly build IoT applications for various use cases. Building an Automotive IoT application however, is not a trivial task. While the IoT platforms provide myriad of services that can run computations, make data available to other apps, perform analytics, and many more, it can be challenging to get the data you want from the vehicle to begin with. There are plenty of OBDII devices in the market, but most of them are programmed to provide only a fixed number of parameters to the user and therefore does not offer the freedom to access the complete dataset available on your vehicle's in-vehicle networks.

The neoOBD2 family of products are designed to give your WiFi / BLE applications easy and complete access to all the data available on the supported vehicle networks; CAN/CANFD, LIN, and Ethernet. With built-in support for popular IoT platforms like the AWS IoT Core and AWS Greengrass, the neoOBD2 makes it easy to create IoT solutions for Automotive applications. The device provides programmable WiFi and BLE modules based on ARM Cortex M4. For each module type, a precompiled static library called Intrepid Security Module (ISM) is provided which can be used by your applications to receive and transmit low-level raw messages (i.e: full CAN/CANFD, LIN, and Ethernet frames) so that you can access high-level signals (i.e: vehicle speed, engine temp, pedal position) that are embedded within the messages.

The list of neoOBD2 devices supported by the SDK are as follows:

* [neoOBD2 PRO](https://www.intrepidcs.com/products/vehicle-network-adapters/neoobd-2-pro/)
* [neoOBD2 DEV](https://www.intrepidcs.com/products/vehicle-network-adapters/neoobd-2-lc/) (New!) - Development kit for the [neoOBD2 LC](https://www.intrepidcs.com/products/vehicle-network-adapters/neoobd-2-lc/).

## Getting Started

The neoOBD2 SDK is based on [Amazon FreeRTOS](https://aws.amazon.com/documentation/freertos/), [CC32XX Simplelink SDK from Texas Instruments](http://www.ti.com/tool/download/SIMPLELINK-CC32XX-SDK), and [nRF52 SDK from Nordic Semiconductor](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK). These three dependencies are already provided with this source package, they are not needed to be installed separately. We are working on adding support for other IoT platforms such as IBM Watson, Google Cloud, and Microsoft Azure.

* neoOBD2 PRO

	* **Please complete the hardware setup guide before you begin development to ensure your neoOBD2 PRO is configured correctly** - please [click here](docs/neoobd2_pro/readme/OBD2PRO_HW_SETUP_GUIDE.md).

	* For guide on getting started with CC3220SF Wi-Fi application development using the SDK for neoOBD2 PRO - please [click here](docs/neoobd2_pro/readme/OBD2PRO_WIFI_GETTING_STARTED.md).

	* For guide on getting started with nRF52832 BLE application development using the SDK for neoOBD2 PRO - please [click here](docs/neoobd2_pro/readme/OBD2PRO_BLE_GETTING_STARTED.md).

* neoOBD2 DEV

	* **Please complete the hardware setup guide before you begin development to ensure your neoOBD2 DEV is configured correctly** - please [click here](docs/neoobd2_dev/readme/OBD2DEV_HW_SETUP_GUIDE.md).
	
	* For guide on getting started with CC3235SF Wi-Fi application development using the SDK for neoOBD2 DEV - please [click here](docs/neoobd2_dev/readme/OBD2DEV_WIFI_GETING_STARTED.md).
	
	* For guide on getting started with nRF52840 BLE application development using the SDK for neoOBD2 DEV - please [click here](docs/neoobd2_dev/readme/OBD2DEV_BLE_GETTING_STARTED.md).

## SDK Compatibility by Vehicle Spy Versions

The v901_maintenance branch is compatible with the latest release version of Vehicle Spy, available for download at - [click here](https://www.intrepidcs.com/main/updates).

The master branch contains new features and fixes in development for future release. A beta version of the upcoming Vehicle Spy is available upon request that is compatible with the master branch of SDK. Please send your inquiry to icssupport@intrepidcs.com.

* Master - Vehicle Spy Beta Version 3.9.3.XXX

* v902_maintenance - Vehicle Spy Release Versions 3.9.2.XXX

* v901_maintenance - Vehicle Spy Release Versions 3.9.1.27+

* v900_maintenance - Vehicle Spy Release Version 3.9.0.79+

* v803_maintenance - Vehicle Spy Release Version 3.8.3.104+

## License

This project is licensed under the BSD License - see the [LICENSE.md](LICENSE.md) file for details
