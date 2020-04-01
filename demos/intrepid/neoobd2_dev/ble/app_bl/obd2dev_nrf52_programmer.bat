pyocd erase -t nrf52840 --mass-erase
pyocd flash -t nrf52840 C:\\ICS\\Projects\\IoT\\SDK\\GitHub_Public\\neoobd2_sdk\\demos\\intrepid\\neoobd2_dev\\ble\\app_bl\\s140_nrf52_6.1.1_softdevice.hex
pyocd flash -t nrf52840 C:\\ICS\\Projects\\IoT\\SDK\\GitHub_Public\\neoobd2_sdk\\demos\\intrepid\\neoobd2_dev\\ble\\app_bl\\nRF52840_Bootloader.hex
pyocd cmd -t nrf52840 -c write32 0x10001014 0x000F0000
pyocd cmd -t nrf52840 -c write32 0x10001018 0x000FE000
pyocd cmd -t nrf52840 -c reset
