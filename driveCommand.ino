#include <Servo.h>
#include <Ethernet.h>
#include <Ethernet.Udp.>
#include <SPI.h>


Servo leftWheel1;
Servo rightWheel1;
Servo leftWheel2;
Servo rightWheel2;
Servo leftWheel3;
Servo rightWheel3;

byte mac[] ={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; //assign mac value
IPAddress ip(192, 168, 1); //ip address
unsinged int localPort = 2000;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; 
String data;
EhternetUDP Udp;
int packetSize; //vairable to store packet size

void setup()
{
  Serial.begin(9600);
  Ethernet.begin( mac , ip):
  Udp.begin(localPort);
  leftWheel1.attach(11);
  leftWheel2.attach(12);
  leftWheel3.attach(24);
  rightWheel1.attach(25);
  rightWheel2.attach(28);
  rightWheel3.attach(29);
  
}

void loop()
{
  packetSize = Udp.parsePacket();

  if(packetSize>0){
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    String data(packetBuffer);
    //set the left wheels on max speed
    if (data == "DriveCommand_leftWheel1_leftWheel2_leftWheel3"){
      leftWheel1.writeMicroseconds(2000);
      leftWheel2.writeMicroseconds(2000);
      leftWheel3.writeMicroseconds(2000);
    }
    else if (data == "DriveCommand_rightWheel1_rightWhee2_rightWheel3"){
      rightWheel1.writeMicroseconds(2000);
      rightWheel2.writeMicroseconds(2000);
      rightWheel3.writeMicroseconds(2000);
      leftWheel1.writeMicroseconds(1500);
      leftWheel2.writeMicroseconds(1500);
      leftWheel3.writeMicroseconds(1500);
    }
    else if (data == "DriveCommand_leftWheel1_rightWheel1_leftWheel2_rightWheel2_leftWheel3_rightWheel3_forward"){
      rightWheel1.writeMicroseconds(2000);
      rightWheel2.writeMicroseconds(2000);
      rightWheel3.writeMicroseconds(2000);
      leftWheel1.writeMicroseconds(2000);
      leftWheel2.writeMicroseconds(2000);
      leftWheel3.writeMicroseconds(2000);
    }
    else if (data == "DriveCommand_leftWheel1_rightWheel1_leftWheel2_rightWheel2_leftWheel3_rightWheel3_backward"){
      rightWheel1.writeMicroseconds(0);
      rightWheel2.writeMicroseconds(0);
      rightWheel3.writeMicroseconds(0);
      leftWheel1.writeMicroseconds(0);
      leftWheel2.writeMicroseconds(0);
      leftWheel3.writeMicroseconds(0)
    }
  }
}
