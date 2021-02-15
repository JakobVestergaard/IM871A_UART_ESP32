#include <Arduino.h>

#define RXD2 16 // Black
#define TXD2 17 // Red

// LINKMODE C1A
// write(port.to_bytes([IM871A_SERIAL_SOF, DEVMGMT_ID, DEVMGMT_MSG_SET_CONFIG_REQ, 0x03, TEMP_MEM, 0x2, Mode]))


#define IM871A_SERIAL_SOF 0xA5
#define DEVMGMT_ID 0x01
#define TEMP_MEM 0x00
#define DEVMGMT_MSG_PING_REQ 0x01
#define DEVMGMT_MSG_PING_RSP 0x02
#define DEVMGMT_MSG_SET_CONFIG_REQ 0x03
#define DEVMGMT_MSG_SET_CONFIG_RSP 0x04
#define DEVMGMT_MSG_RESET_REQ 0x07
#define DEVMGMT_MSG_RESET_RSP 0x08

void linkmodeC1a();
void resetModule();
void pingModule();

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(57600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

  linkmodeC1a();
  //resetModule();
  delay(1000);
  //pingModule();
}

void loop() {
  Serial.println(char(Serial2.read()));
  delay(1000);
  }

void linkmodeC1a(){
  // LINKMODE C1A
  // write(port.to_bytes([IM871A_SERIAL_SOF, DEVMGMT_ID, DEVMGMT_MSG_SET_CONFIG_REQ, 0x03, TEMP_MEM, 0x2, Mode]))




  Serial2.print(byte(IM871A_SERIAL_SOF));
  Serial2.print(byte(DEVMGMT_ID));
  Serial2.print(byte(DEVMGMT_MSG_SET_CONFIG_REQ));
  Serial2.print(byte(0x03));
  Serial2.print(byte(TEMP_MEM));
  Serial2.print(byte(0x2));
  Serial2.print(byte(0xa));
  Serial2.flush();
}

void resetModule(){
  // self.IM871.write([IM871A_SERIAL_SOF, DEVMGMT_ID, DEVMGMT_MSG_RESET_REQ, 0x00])
  Serial2.print(byte(IM871A_SERIAL_SOF));
  Serial2.print(byte(DEVMGMT_ID));
  Serial2.print(byte(DEVMGMT_MSG_RESET_REQ));
  Serial2.print(byte(0x00));
  Serial2.flush();

}

void pingModule(){
  // self.IM871.write(port.to_bytes([IM871A_SERIAL_SOF, DEVMGMT_ID, DEVMGMT_MSG_PING_REQ, 0x0]))



  Serial2.print(byte(IM871A_SERIAL_SOF));
  Serial2.print(byte(DEVMGMT_ID));
  Serial2.print(byte(DEVMGMT_MSG_PING_REQ));
  Serial2.print(byte(0x0));
  Serial2.flush();

  int incomingData;
  for (int i = 0; i < 500; i++){
    incomingData = Serial2.read();
    Serial.print("Incoming data: \"");
    Serial.print(incomingData);
    Serial.println("\"");

  }
}

