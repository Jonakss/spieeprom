#include <SPI.h>


const byte WP = 49;
const byte HOLD = 48;

//MX25L4005A-12G
const int capacity = 4194304; // in bytes -> 4MB

const byte WREN = 0x06;   // Write enable
const byte WRID = 0x04;   // Write disable
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

void read(byte add){
 SPI.transfer(READ);
}

void setup() {
  Serial.begin(9600);

  pinMode(48, OUTPUT); // Hold
  pinMode(49, OUTPUT); // Write protection

  SPI.setDataMode(SPI_MODE3);
}

void loop() {
  

}
