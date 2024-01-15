//Communication 1 way receiver
//firstly download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "driver/adc.h"
#include <esp_wifi.h>
#include <esp_bt.h>
#include <driver/rtc_io.h> 
#include <driver/gpio.h>

RF24 radio(21, 5);  // CE, CSN
const byte address[6] = "00001";
int wakePin = 26;
int relayPin = 22;

const int wakeupPin = 25;  // GPIO 4 for external wake-up

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(wakePin, OUTPUT);

  pinMode(wakeupPin, INPUT_PULLUP); 

  Serial.begin(9600);
  while (!Serial) {};
  Serial.println("\n\n\nONEWAY nRF24L01+ Receiver\nReceving...");
  radio.begin(21, 5);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);      //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.

  setup_rtc_gpio();  

  esp_sleep_enable_ext0_wakeup((gpio_num_t)wakeupPin, LOW);  // Configure external wake-up

  radio.startListening();             //This sets the module as receiver 
}

void loop() 
{  

  int data;
 
  if (radio.available())  //Looking for the data.
  {
    //Serial.print("radio.available():  "); Serial.println(radio.available());
    
    radio.read(&data, sizeof(data));    //Reading the data
    
    if (data == 1) 
    {
      digitalWrite(relayPin, HIGH);
      Serial.println("Battery power switched ON");
      Serial.println("ESP32 wake from Deep Sleep");
      radio.powerUp();
      Serial.println("nRF24L01 powered up");
      delay(10);
    }

    if (data == 2) 
    {
      digitalWrite(relayPin, LOW);
      Serial.println("Battery power switched OFF"); 
      Serial.println("nRF24L01 powered down");
      Serial.println("ESP32 going to Deep Sleep");
      goToDeepSleep();      
      delay(10);
    }
  }
  delay(10);
}

void setup_rtc_gpio() {
    rtc_gpio_init(GPIO_NUM_25);
    rtc_gpio_set_direction(GPIO_NUM_25, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(GPIO_NUM_25, 0);
}


void goToDeepSleep() {

  // Enable RTC peripherals for deep sleep
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  rtc_gpio_pullup_dis(GPIO_NUM_25);  
  rtc_gpio_pulldown_en(GPIO_NUM_25);

  radio.powerDown();

  esp_deep_sleep_start();
  Serial.println("Testing --Not Deep Sleeping");  //This line should not print
}
