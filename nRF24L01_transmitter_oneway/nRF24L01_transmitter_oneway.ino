//Communication 1 way transmitter
//Download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(21, 5); // CE,CSN         
const byte address[6] = "00001"; //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side. int ledPin 26;
const int ledPin = 26;
int data;
int controlRelay;

void setup() 
{
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  radio.begin(21, 5);   //Starting radio the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();  //This sets the module as transmitter
}

void loop()
{
  data = 0;
  if(data == 1)
  {    
    const char text[] = "Your Battery Switch is ON";
    radio.write(&text, sizeof(text));    //Sending the message to receiver
    radio.write(&data, sizeof(data));    //Reading the data
    delay(10);	  
  } 
  
  if(data == 0)
  {
    const char text[32] = "Your Battery Switch is OFF";
    radio.write(&text, sizeof(text));  //Sending the message to receiver radio.write(&data, sizeof(data));  //Sending the message to receiver 
    radio.write(&data, sizeof(data));    //Reading the data
    delay(10);	   
  }   	  
}