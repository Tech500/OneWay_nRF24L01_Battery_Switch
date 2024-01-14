//Communication 1 way transmitter
//Download library https://github.com/nRF24/RF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(21, 5); // CE,CSN         
const byte address[6] = "00001"; //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side. int ledPin 26;
int controlRelay;



void setup() 
{
  
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("\n\n\nONEWAY nRF24L01+ Transmitter\nSending...");
  radio.begin(21, 5);   //Starting radio the Wireless communication
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();  //This sets the module as transmitter
}

void loop()
{

  char text1[32] = "";   //Saving the incoming data
  char text2[32] = "";  //Saving the incoming data
  char text3[32] = "";  //Saving the incoming data
  char text4[32] = "";  //Saving the incoming data  
  
  int data;
  data = 3;
  
  if(data == 1)
  { 
    const char text1[] = "Your Battery Switch is ON";
    radio.write(&text1, sizeof(text1));  //Sending the message to receiver
    radio.write(&data, sizeof(data));  //Reading the data
    Serial.println(text1);
    delay(200);    
  } 
  
  if(data == 2)
  {
    const char text2[] = "Your Battery Switch is OFF";
    radio.write(&text2, sizeof(text2));  //Sending the message to receiver
    radio.write(&data, sizeof(data));  //Reading the data
    Serial.println(text2);
    delay(200);    
  }   

  if(data == 3)
  {
    const char text3[] = "ESP32 Going to Sleep";
    radio.write(&text3, sizeof(text3));  //Sending the message to receiver
    radio.write(&data, sizeof(data));  //Reading the data
    Serial.println(text3);
    delay(200);   
  }
 
  if(data == 4)
  {
    for(int x = 1;x< 6;x++){  
      const char text4[] = "ESP32 Waking from Sleep";
      radio.write(&text4, sizeof(text4));  //Sending the message to receiver
      radio.write(&data, sizeof(data));  //Reading the data
      Serial.println(text4);
      delay(200);
    }    
  }
  delay(10);	
  while(data){};
}
