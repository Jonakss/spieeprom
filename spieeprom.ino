#include <SPI.h>

const char WP = 49;
const char HOLD = 48;
const char CS = 31;

//MX25L4005A-12G
const long capacity = 524288; // in chars -> 4MB (512KB) // 0x000000 - 0x07FFFF
const long blockSize = 65536; // 64K
const long sectorSize = 4096; // 4K

const char WREN = 0x06;       // Write enable
const char WRDI = 0x04;       // Write disable
const char RDID = 0x9F;       // Read identification
const char RDSR = 0x05;       // Read status register
const char WRSR = 0x01;       // Write status register
const char READ = 0x03;       // Read data
const char FREAD = 0x0B;      // Fast read data
const char SECTORE = 0x20;    // Sector erease
const char BE = 0xD8;         // 52 Or D8
const char CE = 0x60;         // 60 Or C7
const char PP = 0x02;         // Page program
const char DP = 0xB9;         // Deep power down
const char RDP = 0xAB;        // Release from Deep power down
const char RES = 0xAB;        // Read electronic ID
const char REMS = 0x90;       // Read Electronic Manofacturer & device ID

int inBlock(long add){
  int b=0;
  long i=blockSize;
  
  while((add >= i) && (i<capacity)){
    b+=1;
    i+=blockSize;
  }

  return b;
}

int inSector(long add){
  int s=0;
  long i=sectorSize;
  
  while((add >= i) && (i<capacity)){
      s+=1;
      i+=sectorSize;
  }

  return s;
}

void writeEnable(){
  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);

  SPI.transfer(WREN);

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);

//  Serial.println("Write protection enabled");
}

void writeDisable(){
  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);

  SPI.transfer(WRDI);

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);
  
//  Serial.println("Write protection disabled");
}

int readIdentification(){
  byte mId, mType, dId;

  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);

  SPI.transfer(RDID);
  mId = SPI.transfer(0x00);
  mType= SPI.transfer(0x00);
  dId= SPI.transfer(0x00);

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);

  Serial.println("RDID:");
  Serial.print("Manufacturer ID:\t");
  Serial.print(mId, HEX);
  Serial.print("\tMemory type:\t");
  Serial.print(mType, HEX);
  Serial.print("\tDevice ID:\t");
  Serial.println(dId, HEX);
  Serial.println();

  return 0;
}

byte readStatusRegister(){
  byte statusRegister;

  digitalWrite(CS, LOW);
  digitalWrite(HOLD, HIGH);
  
  SPI.transfer(RDSR);
  statusRegister = SPI.transfer(0x00);
  
  digitalWrite(HOLD, LOW);
  digitalWrite(CS, HIGH);

  Serial.print("Status Register:\t");
  Serial.println(statusRegister, BIN);

  return statusRegister;
}

boolean writeStatusRegister(byte statusRegister){
  Serial.print("\n Status register to write: \t");
  Serial.println(statusRegister, BIN);
  
  writeEnable();
  
  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);
  
  SPI.transfer(WRSR);
  SPI.transfer(statusRegister);

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);

  writeDisable();
//  if(readStatusRegister() == statusRegister){
//    Serial.print("Writed Status Register:\t");
//    Serial.println(statusRegister, BIN);
//    return true;
//  }else{
//    Serial.println("Error not the same Status Register after writing!");
//    return false;
//  }
  return true;
}

byte readData(long add){
byte data;

digitalWrite(CS, LOW);

SPI.transfer(READ);
SPI.transfer(add >> 16);
SPI.transfer(add >> 8 & 0x00ff);
SPI.transfer(add & 0x0000ff);
data = SPI.transfer(0x00);

digitalWrite(CS, LOW);

Serial.print("Data in ");
Serial.print(add, HEX);
Serial.print(" addres memory:\t");
Serial.println(data, HEX);

return data;
} // End readData

void readData(long add, long lastAdd){ // if lastAdd < 0, the whole memory will be readed

if(add >= capacity){
  add = lastAdd = capacity - 1;
}else{
  if(add < 0) add = 0;

  if(lastAdd >= capacity) lastAdd = capacity - 1;
  else if(lastAdd < add) lastAdd = add;
  else if(lastAdd < 0) lastAdd = capacity - 1;
}

long delta = lastAdd-add;
//byte data[delta];

digitalWrite(HOLD, HIGH);
digitalWrite(CS, LOW);

SPI.transfer(READ);
SPI.transfer(add >> 16);
SPI.transfer(add >> 8 & 0x00ff);
SPI.transfer(add & 0x0000ff);

for(long i=0; i<=delta; i++){
  //data[i] = SPI.transfer(0x00);
  Serial.print(SPI.transfer(0x00), HEX);
  Serial.print("\t");
  if ((i%10)==0)
    Serial.print("\n");
}

digitalWrite(CS, HIGH);
digitalWrite(HOLD, LOW);

Serial.println();
//return data;
} // End readData 

void fastReadData(long add, long lastAdd){

if(add >= capacity){
  add = lastAdd = capacity - 1;
}else{
  if(add < 0) add = 0;

  if(lastAdd >= capacity) lastAdd = capacity - 1;
  else if(lastAdd < add) lastAdd = add;
  else if(lastAdd < 0) lastAdd = capacity - 1;
}

long delta = lastAdd-add;
//byte data[delta];

digitalWrite(HOLD, HIGH);
digitalWrite(CS, LOW);

SPI.transfer(FREAD);
SPI.transfer(add >> 16);
SPI.transfer(add >> 8 & 0x00ff);
SPI.transfer(add & 0x0000ff);
SPI.transfer(0xFF); // Or maybe 0xFF

for(long i=0; i<=delta; i++){
  //data[i] = SPI.transfer(0x00);
  Serial.print(SPI.transfer(0x00), HEX);  
  Serial.print("\t");
  if ((i%10)==0)
    Serial.print("\n");
}

digitalWrite(CS, HIGH);
digitalWrite(HOLD, LOW);

Serial.println();

//return data;
} // End fastReadData

//// TODO: readSectorData
//// TODO: readBlockData

void sectorErase(long add){
  writeEnable();

  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);
  
  //TODO: Check the statusRegister for Protected areas

  SPI.transfer(SECTORE);
  SPI.transfer(add >> 16);
  SPI.transfer(add >> 8 & 0x00ff);
  SPI.transfer(add & 0x0000ff);

  //TODO: Check sector after erease
  //inSector(add);

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);

  do{
    delay(1);
  }while((readStatusRegister() & 0b00000001) != 0);
}

void blockErase(long add){
  writeEnable();
  
  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);

  //TODO: Check the statusRegister for Protected areas

  SPI.transfer(BE);
  SPI.transfer(add >> 16);
  SPI.transfer(add >> 8 & 0x00ff);
  SPI.transfer(add & 0x0000ff);

  //TODO: Check block after erease, Se puede saber el bloque por los 2 primeros digitos del hexadecimal de la memoria 0x02f000 -> bloque 2

  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);
  
  do{
    delay(1);
  }while((readStatusRegister() & 0b00000001) != 0);
}

void chipErase(){
  writeEnable();
  digitalWrite(CS, LOW);

  //TODO: Check the statusRegister for Protected areas

  SPI.transfer(BE);

  //TODO: Check chip after erease

  digitalWrite(CS, HIGH);

  writeDisable();
}

void pageProgram(long add){
  writeEnable();
readStatusRegister();
  digitalWrite(HOLD, HIGH);
  digitalWrite(CS, LOW);

  SPI.transfer(PP);
  SPI.transfer(add >> 16);
  SPI.transfer(add >> 8 & 0x00ff);
  SPI.transfer(add & 0x0000ff);
  SPI.transfer(0xC2);

 
  digitalWrite(CS, HIGH);
  digitalWrite(HOLD, LOW);
  
  do{
    delay(1);
  }while((readStatusRegister() & 0b00000001) != 0);
}

void setup() {  
  Serial.begin(9600);

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  //SPI.setDataMode(SPI_MODE3);

  pinMode(HOLD, OUTPUT); // Hold
  pinMode(WP, OUTPUT); // Write protection
  pinMode(CS, OUTPUT); // CS

  readIdentification();
  
//  readStatusRegister();
//  writeStatusRegister(0b00011100);
//  readStatusRegister();

//  readData(0x000000,0x0000ff);
//  readStatusRegister();
//  sectorErase(0x000000);
//  readData(0x000000,0x0000ff);

  readData(0x00ff00);
  pageProgram(0x00ff00);
  readData(0x00ff00);
}

void loop() {
  
}
