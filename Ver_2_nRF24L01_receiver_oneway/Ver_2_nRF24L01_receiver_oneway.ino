//communication 1 way receiver
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
int batteryPin = 22;
int controlRelay;
int data = controlRelay;

const int wakeupPin = 25;  // GPIO 4 for external wake-up

void setup() {
  pinMode(batteryPin, OUTPUT);
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

  char text1[32] = "";   //Saving the incoming data
  char text2[32] = "";  //Saving the incoming data
  char text3[32] = "";  //Saving the incoming data
  char text4[32] = "";  //Saving the incoming data  
  
  int data;
  int text;

  data = text;

  if (radio.available())  //Looking for the data.
  {
    Serial.print("radio.available():  "); Serial.println(radio.available());
    
    radio.read(&data, sizeof(data));    //Reading the data
    
    //Serial.print("data:  "); Serial.println(data);
   
    if (data == 1) 
    {
      radio.read(&text1, sizeof(text1));    //Reading the data
      digitalWrite(batteryPin, HIGH);
      Serial.println("Battery power switched ON");
      delay(10);
    }

    if (data== 2) 
    {
      radio.read(&text2, sizeof(text2));    //Reading the data
      digitalWrite(batteryPin, LOW);
      Serial.println("Battery power switched OFF");
      delay(10);
    }

    if (data== 3) 
    {
      radio.read(&text3, sizeof(text3));    //Reading the data
      Serial.println(text3);
      Serial.println("Going to Sleep");
      goToDeepSleep();
    }

    if (data == 4) 
    {
      radio.read(&text4, sizeof(text4));    //Reading the data
      digitalWrite(wakeupPin, LOW);
      Serial.println(text4);
      delay(10);
      Serial.println("ESP32 waked from deep sleep");
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

  Serial.println("Gets here 2");

  /*
  btStop();
  adc_power_off();
  esp_wifi_stop();
  esp_bt_controller_disable();
  */

  // Enable RTC peripherals for deep sleep
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  rtc_gpio_pullup_dis(GPIO_NUM_25);  // Correct argument
  rtc_gpio_pulldown_en(GPIO_NUM_25);

  Serial.println("Going to sleep");
  esp_deep_sleep_start();
}
