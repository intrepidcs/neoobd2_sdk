# Getting Started with neoOBD2 PRO Hardware

Thank you for purchasing neoOBD2 PRO. This guide provides the minimum level of configurations needed to setup your neoOBD2 PRO hardware for development using TI Code Composer Studio IDE and Vehicle Spy Enterprise software. 

## Prerequisites

Required Hardware:

1. [neoOBD2 PRO](https://store.intrepidcs.com/neoOBD-2-Pro-p/neoobd2-pro.htm)
2. [neoOBD2 SIM](https://store.intrepidcs.com/neoECU-CHIP-Simulator-p/neoobd2-sim.htm) (Optional)
3. [Dual USB A & USB C Cable](https://store.intrepidcs.com/productdetails_popup.asp?productcode=NEOOBD2-PRO-PROG-CABLE)
4. [12V DC Power Supply with Barrel Jack Connector](https://store.intrepidcs.com/productdetails_popup.asp?productcode=NEOVI-PS)

Required Software:

1. Vehicle Spy Enterprise

    [Vehicle Spy Enterprise](https://store.intrepidcs.com/Vehicle-Spy-p/vspy-3-ent.htm) is a single tool for diagnostics, node/ECU simulation, data acquisition, automated testing, and in-vehicle communication networks bus monitoring.
    
    For introduction, tutorials, and documentations on Vehicle Spy Enterprise, please [click here](https://cdn.intrepidcs.net/support/VehicleSpy/vehiclespyhelpdoc.html).

2. Texas Instruments Code Composer Studio IDE

## Powering Up your neoOBD2 PRO

The neoOBD2 PRO can be powered via its Male OBDII Connector or via USB Type-C Connector. 

The GND and VBATT pins on the Male OBDII Connector can be connected to a DC power source that provides 4.5V - 40V. This includes OBDII port found in a vehicle or a custom-built harness with GND on pin 4 and VBATT on pin 16 of a Female OBDII Connector. We recommend using a 3A 12V DC power supply for general use. 

While neoOBD2 PRO can also be powered via USB, we recommend powering the hardware via the Male OBDII Connector and use the USB port mainly for data connectivity.

![alt_text](../images/66-obd2pro_power_zone.PNG "Power Input & Output")

## OBDII Connectors and Pin Map

The neoOBD2 PRO features Neovi Universal Connector (NUC) boards. The boards allow OBDII pin mappings on the Male and Female OBDII connectors of the hardware to be customized so that they are compatible with the pin mapping found on vehicle OBDII port users would like to connect to.

There are two types of default NUC boards, [CAN NUC Board](https://store.intrepidcs.com/productdetails_popup.asp?productcode=OBD2-CAN-NUC-BD) and [Ethernet NUC Board](https://store.intrepidcs.com/productdetails_popup.asp?productcode=OBD2-ETH-NUC-BD). When a neoOBD2 PRO is shipped, Intrepid Control Systems will install the CAN NUC Board for you. This provides mapping for 4x CAN-FD, 1x SWCAN and 2x LIN. If you intend to use Ethernet for DoIP, contact [support](https://www.intrepidcs.com/support/) at Intrepid Control Systems for assistsance.

The CAN NUC board maps four CAN/CANFD, one SWCAN, and two LIN networks of the neoOBD2 PRO to the following pins on the OBD2 connector:

![alt_text](../images/67-obd2pro_CAN_NUC.PNG "The CAN NUC Board for neoOBD2 PRO")
    
The Ethernet NUC board maps three CAN/CANFD, one SWCAN, one LIN, and one Ethernet networks of the neoOBD2 PRO to the following pins on the OBD2 connector:

![alt_text](../images/68-obd2pro_ETHERNET_NUC.PNG "The ETHERNET NUC Board for neoOBD2 PRO")
    
## Custom Dual USB A & USB C Cable for neoOBD2 PRO

Intrepid Control Systems has designed a custom [dual USB-A to USB-C cable](https://store.intrepidcs.com/productdetails_popup.asp?productcode=NEOOBD2-PRO-PROG-CABLE) exclusively for use with neoOBD2 PRO. 

The cable provides USB 5V DC power to the neoOBD2 PRO. In addition, one leg of the USB Type A cable connects Vehicle Spy (PC) to the neoOBD2 PRO for realtime bus monitoring, loading CoreMini scripts, and configuring the neoOBD2 PRO. The other USB Type A leg connects to the onboard Texas Instruments CC3220SF JTAG debugger / UART programmer and ARM CMSIS DAPLINK debugger for nRF52832. This unique design allows the neoOBD2 PRO to be online with Vehicle Spy while you are debugging the CC3220SF WiFi MCU.

![alt_text](../images/69-obd2pro_usb_connection_map.PNG "Dual USB-A to USB-C Cable for neoOBD2 PRO")

## Install Vehicle Spy Enterprise and Configure Basic Hardware Settings

1. Run the offline installer provided with your purchase of **Vehicle Spy Enterprise**. Please [contact Intrepid Control Systems](https://www.intrepidcs.com/support/contact-support/) for a version of installer that is compatible with your neoOBD2 PRO.

2. Let's power up the neoOBD2 PRO. If you have a **neoOBD2 SIM** connect the **12V DC Power Supply** to neoOBD2 SIM via its barrel jack connector. Then, connect the neoOBD2 SIM to power the neoOBD2 PRO via the 16 pin male OBDII connector. If you do not have a neoOBD2 SIM, you can create a custom cable with a Female OBDII connector with GND on pin 4 and VBATT on pin 16. Then, supply 4.5V - 40V DC through the cable. This will provide power to the neoOBD2 PRO. If you are not able to create a custom cable, you will also be able to power the neoOBD2 PRO via USB by using the provided **Dual USB A & USB C cable**. BUt it is recommended that you power the neoOBD2 PRO via its male OBDII connector using a DC power supply. Verify that the first three status LEDs from the left to right on your neoOBD2 PRO are all blinking in orange as shown below. The orange color indicates that the neoOBD2 PRO is not connected to Vehicle Spy and both the WiFi and BLE chips are running the default bootloader.

    ![alt_text](../images/64-obd2pro_default_led.PNG "Default LED status on your neoOBD2 PRO after power up")

3. Plug in both sides of the **Dual USB A & USB C cable** to establish connection between your PC and neoOBD2 PRO. Open Vehicle Spy Enterprise. Verify Vehicle Spy Enterprise is able to detect your neoOBD2 PRO. The first LED from the left side of your neoOBD2 PRO will exhibit a blinking pattern in white color if your PC has successfully enumerated the neoOBD2 PRO.

    ![alt_text](../images/65-obd2pro_connected_to_vspy_led.PNG "LED status on your neoOBD2 PRO when connected to PC (Vehicle Spy)")

    ![alt text](../images/1-vspy_obd2pro_detect.PNG "Verify Vehicle Spy Pro is able to detect your neoOBD2 PRO")

4. Select **Setup** from the top menu and select **Hardware**. This will open the **neoVI Explorer**, a common hardware configuration tool for all hardware interfaces from Intrepid Control Systems. Click the **Connect** button to connect to your neoOBD2 PRO. This will read hardware settings from the connected neoOBD2 PRO. Verify the networks you wish to use are enabled. If any of the three available firmware versions need to be updated, click the **Manual Reflash** button and wait for the firmware update process to come to completion. Make sure to click the **Write Settings** button to commit any changes before closing the Hardware view.

    ![alt text](../images/2-vspy_obd2pro_hw_setting.PNG "Configure hardware settings using the neoVI Explorer")

5. Click the **Play** button located on the top left corner of the screen. Verify Vehicle Spy Enterprise properly transitions to **Online** state. If the neoOBD2 PRO is connected to a live CAN bus, you will be able to view all CAN message traffic from the **Messages** view. While in online state, the status LED will exhibit a blinking pattern that transitions rapidly between green and blue.

    ![alt text](../images/3-vspy_obd2pro_online.PNG "Go online in Vehicle Spy")

## Install Texas Instruments Code Composer Studio and Configure COM Ports

1. Browse to the **[TI Code Composer Studio IDE download page](http://processors.wiki.ti.com/index.php/Download_CCS)**.

2. Download the offline installer of the latest TI Code Composer Studio (the **SDK has been tested with CCS version 7.4.0**). 

3. Unzip and run the offline installer.

4. When prompted to select **Product Familes** to install, choose **SimpleLink Wi-Fi CC32xx Wireless MCUs**.

5. Accept default settings for debugging probes, and then choose **Finish**.

6. Plug in both sides of the **Dual USB A & USB C cable** to establish connection between your PC and neoOBD2 PRO. 

7. Ensure that the neoOBD2 PRO is displayed as **CC3200LP Dual Port device** under Ports (COM & LPT) in the Windows **Device Manager**.

    ![alt text](../images/6-device_manager_cc3200lpdual.PNG "Windows Device Manager showing CC3200LP Dual Port")

## Result

At this point, your neoOBD2 PRO device is configured for use with Vehicle Spy Enterprise software. During the development process, Vehicle Spy Enterprise will be **required to program the application binary into the CC3220SF Wi-Fi module and the nRF52832 BLE module**. Vehicle Spy Enterprise is also **required to configure callbacks for receive messages you want to capture from your applicationns running on the Wi-Fi and BLE chips.**

Your neoOBD2 PRO is ready for TI CCS, which provides a powerful integrated development environment for your projects and supports real time USB debugging via the built-in FTDI USB emulation in neoOBD2 PRO.

Your neoOBD2 PRO is also ready for embedded Integrated Development Environment tools for ARM to do BLE application development. The ARM MBED DAPLINK program / debug interface inside your neoOBD2 PRO allows you to do development with nRF52832 BLE SoC.

## What's Next?

Start developing Wi-Fi applications by following the step-by-step guide for **[Getting Started with Wi-Fi Development on neoOBD2 PRO](OBD2PRO_WIFI_GETTING_STARTED.md).**

Start developing BLE applications by following the step-by-step guide for **[Getting Started with BLE Development on neoOBD2 PRO](OBD2PRO_BLE_GETTING_STARTED.md).**
