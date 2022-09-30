#include <Servo.h>
#include <Ethernet.h>
#include <Ethernet.Udp.>
#include <SPI.h>

byte mac[] ={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; //assign mac value
IPAddress ip(192, 168, 1); //ip address
unsinged int localPort = 2000;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; 
String data;
EhternetUDP Udp;
int packetSize; //vairable to store packet size

Servo upperExtender;
Servo lowerExtender;
Servo screwDriver;
Servo claw;
Servo swivel;
Servo hoist;
void setup() {
  Serial.begin(9600);
  Ethernet.begin( mac , ip):
  Udp.begin(localPort);
  upperExtender.attach(22);
  lowerExtender.attach(23):
  hoist.attach(25);
  screwdriver.attach(11);
  claw.attach(28);
  swivel.attach(12);

}

void loop() {
  packetSize= Udp.parsePacket();
  if (packetSize>0){
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    String data(packetBuffer);

    if (data == "ArmCommand_upperExtender"){
      upperExtender.writeMicroseconds(2000);
    }
    else if (data == "ArmCommand_lowerExtender"){
      lowerExtender.writeMicroseconds(2000);
    }
    else if (data == "ArmCommand_hoist"){
      hoist.writeMicroseconds(2000);
    }
    else if (data =="ArmCommand_claw"){
      hoist.writeMicroseconds(2000);
    }
    else if (data== "ArmCommand_screwDriver"){
      screwDriver.writeMicroseconds(2000);
    }
    else if (data == "ArmCommand_swivel"){
      swivel.writeMicroseconds(2000);
    }
  }

}
