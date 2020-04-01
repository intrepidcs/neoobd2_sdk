cd ..
cd ..
cd ..
cd ..
cd ..
cd ..
cd components/softdevice/s132/bin
copy /b /y s132_nrf52_6.1.1_softdevice.bin "../../../../examples/ble_peripheral/ble_app_template/obd2pro/s132/xworks/ble_app_template_obd2pro_s132/s132_nrf52_6.1.1_softdevice.bin"
cd ..
cd ..
cd ..
cd ..
cd examples/ble_peripheral/ble_app_template/obd2pro/s132/xworks/ble_app_template_obd2pro_s132
copy /b /y s132_nrf52_6.1.1_softdevice.bin + ble_app_template_obd2pro_s132.bin obd2pro_ble.bin