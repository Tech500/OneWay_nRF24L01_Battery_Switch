//communication 1 way receiver
//firstly download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(21, 5); // CE, CSN
const byte address[6] = "00001";
int relayPin = 26;
int controlRelay;
int data = controlRelay;  

void setup() {
pinMode(relayPin, OUTPUT);
Serial.begin(9600);
radio.begin(21, 5);
radio.openReadingPipe(0,address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);  //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();  //This sets the module as receiver
}

void loop()
{
  
  for(int x= 1; x< 10000;x++);
  
  if (radio.available())  //Looking for the data.
  {
    char text[32] = "";  //Saving the incoming data
    radio.read(&text, sizeof(text));  //Reading the data
    radio.read(&data, sizeof(data));    //Reading the data
    Serial.print("data:  "); Serial.println(data);
    if(data == 1)
    {
      digitalWrite(relayPin, data);
      Serial.println(text);
    }
    
    if(data ==  0)
    {
      digitalWrite(relayPin, data);
      Serial.println(text);
    }    
  }
  delay(50);
}