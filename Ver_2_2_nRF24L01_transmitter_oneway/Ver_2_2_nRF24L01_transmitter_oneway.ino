//Communication 1 way transmitter
//Download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(21, 5); // CE,CSN         
const byte address[6] = "00001"; //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side. int ledPin 26;

void setup() 
{
  
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("\n\n\nONEWAY nRF24L01+ Transmitter\nSending...");
  radio.begin(21, 5);   //Starting radio the Wireless communication
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
}

void loop()
{ 
  radio.stopListening();  //This sets the module as transmitter
  
  int data = 2;  //Change to 1, 2, 3, 4 to select option -- will be variable "control"
  
  if(data == 1)
  { 
    radio.write(&data, sizeof(data));  //Reading the data
    Serial.println("Your Battery Switch is ON");
    delay(10);  
  } 
  
  if(data == 2)
  {
    radio.write(&data, sizeof(data));  //Reading the data
    Serial.println("Battery power switched OFF"); 
    Serial.println("nRF24L01 powered down");
    Serial.println("ESP32 going to Deep Sleep");
    delay(10);    
  }   

  delay(10);
} 
