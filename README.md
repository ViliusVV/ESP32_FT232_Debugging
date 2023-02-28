## Debug ESP32 using FT232 chip/adapter using platformIO

Set FT232H usb driver to winUsb in Zadig
In `.platformio\packages\tool-openocd-esp32\share\openocd\scripts\interface\ftdi\esp32_devkitj_v1.cfg`
Replace `ftdi_vid_pid line` to `ftdi_vid_pid 0x0403 0x6014`

#### Connecting
* FT232->  ESP32
* AD0  ->  13
* AD1  ->  12
* AD2  ->  15
* AD3  ->  14 
* GND  ->   GND
