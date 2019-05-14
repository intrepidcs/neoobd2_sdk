# Getting Started with neoOBD2 PRO Hardware

This guide provides the minimum level of configurations needed to setup your neoOBD2 PRO hardware for development using Segger Embedded Studio and Vehicle Spy Professional software. 

## Prerequisites

Required Hardware:

1. neoOBD2 PRO
2. Dual USB A & USB C Cable

Required Software:

1. Vehicle Spy Professional

    [Vehicle Spy Professional](http://store.intrepidcs.com/Vehicle-Spy-p/vspy-3-pro.htm) is a single tool for diagnostics, node/ECU simulation, data acquisition, automated testing, and in-vehicle communication networks bus monitoring.
    
    For introduction, tutorials, and documentations on Vehicle Spy Professional, please [click here](https://cdn.intrepidcs.net/support/VehicleSpy/vehiclespyhelpdoc.html).

2. Segger Embedded Studio
	
## Install Vehicle Spy Professional and Configure Basic Hardware Settings

1. Run the offline installer provided with your purchase of **Vehicle Spy Professional**. Please [contact Intrepid Control Systems](https://www.intrepidcs.com/support/contact-support/) for a version of installer that is compatible with your neoOBD2 PRO.

2. Plug in both sides of the **Dual USB A & USB C cable** to establish connection between your PC and neoOBD2 PRO. This will power up the neoOBD2 PRO. Verify that the status LED on neoOBD2 PRO is blinking in orange color.

3. Open Vehicle Spy Professional. Verify Vehicle Spy Professional is able to detect your neoOBD2 PRO. The status LED on neoOBD2 PRO will exhibit a blinking pattern in white color if your PC has successfully enumerated the neoOBD2 PRO.

    ![alt text](../images/1-vspy_obd2pro_detect.PNG "Verify Vehicle Spy Pro is able to detect your neoOBD2 PRO")

4. Select **Setup** from the top menu and select **Hardware**. This will open the **neoVI Explorer**, a common hardware configuration tool for all hardware interfaces from Intrepid Control Systems. Click the **Connect** button to connect to your neoOBD2 PRO. This will read hardware settings from the connected neoOBD2 PRO. Verify the networks you wish to use are enabled. If any of the three available firmware versions need to be updated, click the **Manual Reflash** button and wait for the firmware update process to come to completion. Make sure to click the **Write Settings** button to commit any changes before closing the Hardware view.

    ![alt text](../images/2-vspy_obd2pro_hw_setting.PNG "Configure hardware settings using the neoVI Explorer")

5. Click the **Play** button located on the top left corner of the screen. Verify Vehicle Spy Professional properly transitions to **Online** state. If the neoOBD2 PRO is connected to a live CAN bus, you will be able to view all CAN message traffic from the **Messages** view. While in online state, the status LED will exhibit a blinking pattern that transitions rapidly between green and blue.

    ![alt text](../images/3-vspy_obd2pro_online.PNG "Go online in Vehicle Spy")

## Result

At this point, your neoOBD2 PRO device is configured for use with Vehicle Spy Professional software. During the development process, Vehicle Spy Professional will be **required to program the application binary into the nRF52 BLE module**. Vehicle Spy Professional is also **required to configure callbacks for receive messages you want to capture from your application.**

Your neoOBD2 PRO is also ready for Segger Embedded Studio, which provides a powerful integrated development environment for your projects and supports real time USB debugging via **JLink (dev board and special cable!)**.

## What's Next?

Start developing BLE applications by following the step-by-step guide for **[Getting Started with BLE Development on neoOBD2 PRO](OBD2PRO_BLE_GETTING_STARTED.md).**
