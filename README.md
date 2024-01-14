# OneWay_nRF24L01_Battery_Switch
ESP32 DEVKIT V1 nRF24L01+ Transciever and Receiver --Remote Battery Switch

Added external wake-up for a Deep Sleeping, ESP32.  n24L01 Transmitter\Receiver code using two, nRF24L01 to remotely switch battery on or off for a low demand, 
video live stream.    Web camera consumes 10,000 mAH every 24 hours; switching battery on/off by webserver, URL Request over the nRF24L01 should extend battery between battery 
charges. 

1/14/2024  Files have been updated; supporting switching battery on/off, putting the ESP32 into Deep Sleep, and waking ESP32 from Deep Sleep; using external 0, RTC_GPIO pin.

SPI-ESP32 --pin connections for ESP32 DEVKIT V1 board:

MOSI   23
MISO   19
SCK    18
CE     21
CSN     5
IRQ    nc
VCC
GND

