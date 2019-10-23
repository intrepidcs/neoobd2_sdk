pyocd erase -t nrf52 --mass-erase
pyocd flash -t nrf52 E:\\ICS\\Projects\\IoT\\SDK\\GItHub_Public\\neoobd2_sdk\\demos\\intrepid\\neoobd2_pro\\ble\\app_bl\\s132_nrf52_6.1.1_softdevice.hex
pyocd flash -t nrf52 E:\\ICS\\Projects\\IoT\\SDK\\GItHub_Public\\neoobd2_sdk\\demos\\intrepid\\neoobd2_pro\\ble\\app_bl\\nRF52832_Bootloader.hex
pyocd cmd -t nrf52 -c write32 0x10001014 0x00078000
pyocd cmd -t nrf52 -c write32 0x10001018 0x0007e000
pyocd cmd -t nrf52 -c reset
