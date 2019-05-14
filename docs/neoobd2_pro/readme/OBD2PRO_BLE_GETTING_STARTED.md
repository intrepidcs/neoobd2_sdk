# Getting Started with BLE Development on neoOBD2 PRO

**Before proceeding further, please make sure you have completed the neoOBD2 PRO Hardware setup guide** - [click here](OBD2PRO_HW_SETUP_GUIDE_BLE.md).


## Overview of the Development Process
The following diagram gives a high-level view of the process for developing BLE applications for the neoOBD2 PRO

![alt text](../images/neoOBD2_BLE_Development_Process.PNG "Overview")

## Required Hardware:

1. neoOBD2 PRO
2. Dual USB A & USB C cable
	
## Required Software:

### neoOBD2 SDK

   The neoOBD2 SDK is a collection of precompiled static libraries from Intrepid Control Systems and third-party SDKs such as Amazon FreeRTOS, TI CC3220 SDK, and Nordic nRF5 SDK that allow embedded developers to create IoT applications with full access to vehicle networks supported by compatible neoOBD2 family of adaptors including CAN/CANFD, LIN, and Ethernet.
    
   The SDK comes with ready to build sample projects that leverage the Intrepid Security Module (ISM) library, [TI CC3220 SDK](http://www.ti.com/tool/simplelink-cc3220-sdk), and [Amazon FreeRTOS](https://aws.amazon.com/freertos/) with connectivity support for [AWS IoT Core](https://aws.amazon.com/iot-core/) and [AWS Greengrass](https://aws.amazon.com/greengrass/).

### Microsoft Visual Studio

   The C Code Interface feature in Vehicle Spy Professional generates a Visual Studio project containing source and header files that already integrate the ISM libraries for neoOBD2 PRO. Developers can take the generated C codes along with the ISM library and import them into their CC3220SF and nRF52 projects to add the ability to access vehicle networks supported by neoOBD2 PRO.

   [Microsoft Visual Studio](https://www.visualstudio.com/downloads/) Community, Professional, or Enterprise edition is required. Microsoft Visual Studio version 2010 or higher is required.

### Intrepid Security Module (ISM) Toolchain

   The Intrepid Security Module (ISM) is a precompiled static library for compatible embedded microprocessors in Intrepid vehicle network adaptors, which allow the applications running on the microprocessors to access vehicle network data. For neoOBD2 PRO, these microprocessors include the the ARM Cortex M4 application processors in the TI CC3220SF Wi-Fi and Nordic nRF52832 BLE modules. The library allows CAN/CANFD, LIN, and Ethernet messages to be easily constructed from code and transmitted on a live bus with a single API function call. The library also allows you to setup callbacks in code for vehicle network messages you want to capture. This can be done by configuring those messages in Vehicle Spy Professional using the C Code Interface.

   The Intrepid Security Module (ISM) Toolchain is a collection of software tools and third-party SDKs that allow you to build embedded applications for ISM-compatible microprocessors. The toolchain is consisted of ARM GCC toolchain, GNU Make tool, and ISM Builder tool which are capable of generating GNU Makefiles to build embedded binaries. For neoOBD2 PRO, the code runs on the ARM Cortex-M4 v7EM processor within Nordic nRF52832 BLE module. The tool chain also comes with vendor Board Support Packages and SDK files needed to build applications.

   The ISM tool chain is tightly integrated into Vehicle Spy to provide a convenient way to generate a base, skeleton project in Visual Studio with source and header stubs that already integrates the ISM library. Developers can import the ISM library along with the generated source and header files into their nRF52 BLE projects to access vehicle networks supported by neoOBD2 PRO.

   The embedded C Code Interface projects in Visual Studio do not support debugging. Therefore, a full fledged embedded IDE is desired for an enhanced development and debugging experience. When developing BLE applications for the Nordic nRF52 BLE module, the Segger Embedded Studio IDE is a popular and recommended choice. Full USB debugging for nRF52 is supported for neoOBD2 PRO from the Segger IDE. All BLE sample projects provided by the SDK can easily be imported into the Segger IDE. Step by step details on developing, building, and deploying projects using the Segger IDE and Vehicle Spy Professional is provided with the SDK.

### Vehicle Spy Professional 

Please complete installation & configuration using the [hardware setup guide](OBD2PRO_HW_SETUP_GUIDE_BLE.md)

   [Vehicle Spy Professional](http://store.intrepidcs.com/Vehicle-Spy-p/vspy-3-pro.htm) is a single tool for diagnostics, node/ECU simulation, data acquisition, automated testing, and in-vehicle communication networks bus monitoring.
    
   For introduction, tutorials, and documentations on Vehicle Spy Professional, please [click here](https://cdn.intrepidcs.net/support/VehicleSpy/vehiclespyhelpdoc.html).

### Segger Embedded Studio

Segger Embedded Studio is an Integrated Development Environment (IDE) that is free to use with Nordic nRF52 BLE projects.

Details on this integrated development enivronment from Segger can ve found [here](https://www.segger.com/downloads/embedded-studio).

The basic installation steps are:
1. Browse to the **[Segger Embedded Studio IDE download page](https://www.segger.com/downloads/embedded-studio)**.
2. Download the Embedded Studio for ARM, Windows, 64-bit. 
3. Run the installer. Ensure that "Install J-Link Device Drivers" is selected in the Additional Components Dialog. 

### Install neoOBD2 SDK

Using git, clone the neoOBD2 SDK from [GitHub](https://github.com/intrepidcs/neoobd2_sdk).

### Install Microsoft Visual Studio

[Microsoft Visual Studio](https://www.visualstudio.com/downloads) Community, Professional, or Enterprise editions are supported. Microsoft Visual Studio version 2010 or higher is required.

### Install Intrepid Security Module (ISM) Toolchain for BLE

1. Open Vehicle Spy Professional. Select **Scripting and Automation** from the top menu and select **C Code Interface**. 

2. Click the **Add Project** button and select **New Project...**. Click the **Create embedded projects for Intrepid Security Module (ISM) devices** check box to inflate additional options. The **ISM Toolchain Path** will automatically point to the ISM folder at the working directory of Vehicle Spy Professional. This must be configured as \<drive>:\IntrepidCS\Vehicle Spy 3\ISM. \<drive> is the drive where Vehicle Spy Professional is installed.

![alt text](../images/7-vspy_new_ccif_proj.PNG "Add new C Code Interface Project for ISM")

3. Select **neoOBD2 PRO BLE nRF52** from the list of **Available ISM Targets**. Click the **OK** button to save and close the view. If you have Microsoft Visual Studio installed, Vehicle Spy will automatically open the generated project in Visual Studio.

![alt text](../images/8-vspy_new_ccif_proj_BLE.PNG "Add new BLE C Code Interface Project for ISM")

4. Go back to the **C Code Interface** view. From the top menu, click the **Edit** button to open the **C Code Module Setup** view. Navigate to the **ISM Settings** view and click the **Install…** button to open the **ISM Toolchain Downloader**. 

![alt text](../images/9-vspy_ccif_ismsettings.PNG "ISM Toolchain Downloader")

5. **IMPORTANT: YOU MUST set the installation path of the ISM Toolchain to \<drive>:\IntrepidCS\Vehicle Spy 3\ISM.** \<drive> is the drive where Vehicle Spy Professional is installed. This is required because \<drive>:\IntrepidCS\Vehicle Spy 3 is considered as a safe area in your PC for Vehicle Spy to access various resources. To do this, click the **Find Existing Installation** button and navigate to the path. Then perform one of the following:

* **If you do not have the ISM folder** under \<drive>:\IntrepidCS\Vehicle Spy 3, that signifies that ISM Toolchain has never been installed on your PC. If this is the case, keep the path set at \<drive>:\IntrepidCS\Vehicle Spy 3 and click the **Download/Update** button to begin the installation process. When the installation process is completed, you will see that the **ISM folder** is created. Next, select the **OBD2PRO_BLE_nRF52** from the populated list of targets and click the **Download/Update Selected Targets** button located on the bottom of the view. Doing so will download the support files needed to build BLE applications - the download process can take a few minutes to complete.

![alt text](../images/11-vspy_ccif_ism_grabber_folder_not_exists.PNG "ISM Toolchain does not exist")

* **If you have the ISM folder** under \<drive>:\IntrepidCS\Vehicle Spy 3, that signifies that ISM Toolchain has already been installed on your PC. If this is the case, navigate inside the ISM folder and click the **Select Folder** button to exit the view. Then a list of **Additional Targets** will be populated. Select the **OBD2PRO_BLE_NRF52** from the list and click the **Download/Update Selected Targets** button located on the bottom of the view. Doing so will update the support files needed to build Wi-Fi applications - the download process can take a few minutes to complete.

![alt text](../images/10-vspy_ccif_ism_grabber_folder_exists.PNG "ISM Toolchain exists")

![alt text](../images/12-vspy_ccif_ism_grabber_folder_not_exists_download.PNG "Download/Update ISM Toolchain")

## Results

By completing this guide and the [Hardware Setup Guide](OBD2PRO_HW_SETUP_GUIDE.md) for neoOBD2 PRO, you are ready to start developing ARM Cortex M4F applications for the nRF5 BLE module on neoOBD2 PRO that leverage ISM library.

## What's Next?

Please use this step-by-step guide to start building your first BLE application for neoOBD2 PRO. The guide walks through an Amazon FreeRTOS sample project provided with the SDK that transmits a classical CAN 2.0 message and processes a response messagee - **[Getting Started with your first BLE Application for neoOBD2 PRO](OBD2PRO_DEVELOP_FIRST_BLE_APP_GUIDE.md)**
