#include <SPI.h>

const byte WP = 49;
const byte HOLD = 48;
const byte CS = 53;

//MX25L4005A-12G
//const int capacity = 4194304; // in bytes -> 4MB

const byte WREN = 0x06;   // Write enable
const byte WRDI = 0x04;   // Write disable
const byte RDID = 0x9F;   // Read identification
const byte RDSR = 0x05;   // Read status register
const byte WRSR = 0x01;   // Write status register
const byte READ = 0x03;   // Read data
const byte FREAD = 0x0B;  // Fast read data
const byte SECTORE = 0x20;// Sector erease
const byte BE = 0x52;     // Or D8
const byte CE = 0x60;     // Or C7
const byte PP = 0x02;     // Page program
const byte DP = 0xB9;     // Deep power down
const byte RDP = 0xAB;    // Release from Deep power down
const byte RES = 0xAB;    // Read electronic ID
const byte REMS = 0x90;   // Read Electronic Manofacturer & device ID

void writeEnable(){
  digitalWrite(CS, LOW);

  SPI.transfer(WREN);

  digitalWrite(CS, HIGH);

  Serial.println("Write protection enabled");
}

void writeDisable(){
  digitalWrite(CS, LOW);

  SPI.transfer(WRDI);

  digitalWrite(CS, HIGH);

  Serial.println("Write protection disabled");
}

int readIdentification(){
  int mId, mType, dId;
  
  digitalWrite(CS, LOW);
  
  SPI.transfer(RDID);
  mId = SPI.transfer(0x00);
  mType= SPI.transfer(0x00);
  dId= SPI.transfer(0x00);

  digitalWrite(CS, HIGH);

  Serial.println("RDID:");
  Serial.print("Manufacturer ID:\t");
  Serial.print(mId, HEX);
  Serial.print("\tMemory type:\t");
  Serial.print(mType, HEX);
  Serial.print("\tDevice ID:\t");
  Serial.println(dId, HEX);
  Serial.println();
}

byte readStatusRegister(){
  byte statusRegister;

  digitalWrite(CS, LOW);

  SPI.transfer(RDSR);
  statusRegister = SPI.trasnfer(0x00);

  digitalWrite(CS, HIGH);

  Serial.print("Status Register:\t");
  Serial.println(statusRegister);
  
  return statusRegister
}

//void readData(byte add){
//
// SPI.transfer(READ);
//
//}
//
//void readData(byte add, int lastAdd){
// 
// SPI.transfer(READ);
//}

void setup() {
  Serial.begin(9600);

  //SPI.setDataMode(SPI_MODE3);
  SPI.begin();
  
  pinMode(HOLD, OUTPUT); // Hold
  pinMode(WP, OUTPUT); // Write protection
  pinMode(CS, OUTPUT); // CS

  
  readIdentification();
}

void loop() {
}
