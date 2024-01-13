# OneWay_nRF24L01_Battery_Switch
ESP32 DEVKIT V1 nRF24L01+ Transciever and Receiver --Remote Battery Switch

Transmitter\Receiver code to use two, nRF24L01 to remotely switch battery on or off for a low demand, 
video live stream.  Goal is to add external wake-up for a deep sleeping, ESP32.  Web camera consumes 10,000 mAH 
every 24 hours; switching battery on/off by webserver input for the nRF24L01; should extend battery power between batter 
charges. 

1/13/2024  Files currently are a work in progress; only supporting turning a LED on and off.

SPI pin connections for ESP32 DEVKIT V! board:

MOSI   23
MISO   19
SCK    18
CE     21
CSN     5
IRQ    nc
VCC
GND

