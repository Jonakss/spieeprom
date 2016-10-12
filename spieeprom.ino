#include <SPI.h>

const char WP = 49;
const char HOLD = 48;
const char CS = 53;

//MX25L4005A-12G
const long capacity = 524288; // in chars -> 4MB (512KB) // 0x000000 - 0x07FFFF

const char WREN = 0x06;   // Write enable
const char WRDI = 0x04;   // Write disable
const char RDID = 0x9F;   // Read identification
const char RDSR = 0x05;   // Read status register
const char WRSR = 0x01;   // Write status register
const char READ = 0x03;   // Read data
const char FREAD = 0x0B;  // Fast read data
const char SECTORE = 0x20;// Sector erease
const char BE = 0x52;     // Or D8
const char CE = 0x60;     // Or C7
const char PP = 0x02;     // Page program
const char DP = 0xB9;     // Deep power down
const char RDP = 0xAB;    // Release from Deep power down
const char RES = 0xAB;    // Read electronic ID
const char REMS = 0x90;   // Read Electronic Manofacturer & device ID

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

char readStatusRegister(){
  char statusRegister;

  digitalWrite(CS, LOW);

  SPI.transfer(RDSR);
  statusRegister = SPI.transfer(0x00);

  digitalWrite(CS, HIGH);

  Serial.print("Status Register:\t");
  Serial.println(statusRegister);

  return statusRegister;
}

boolean writeStatusRegister(char statusRegister){
  digitalWrite(CS, LOW);

  SPI.transfer(WRSR);
  SPI.transfer(statusRegister);

  digitalWrite(CS, HIGH);

  if(readStatusRegister() == statusRegister){
    Serial.print("Writed Status Register:\t");
    Serial.println(statusRegister, BIN);
    return true;
  }else{
    Serial.print("Error not the same Status Register after writing!");
    return false;
  }
}

char readData(long add){
char data;

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
}

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
//char data[delta];

digitalWrite(CS, LOW);

SPI.transfer(READ);
SPI.transfer(add >> 16);
SPI.transfer(add >> 8 & 0x00ff);
SPI.transfer(add & 0x0000ff);

for(long i=0; i<=delta; i++){
  //data[i] = SPI.transfer(0x00);
  Serial.print(SPI.transfer(0x00));
}

digitalWrite(CS, HIGH);

Serial.println();
//return data;
}

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
//char data[delta];

digitalWrite(CS, LOW);

SPI.transfer(READ);
SPI.transfer(add >> 16);
SPI.transfer(add >> 8 & 0x00ff);
SPI.transfer(add & 0x0000ff);
SPI.transfer(0x00); // Or maybe 0xFF

for(long i=0; i<=delta; i++){
  //data[i] = SPI.transfer(0x00);
  Serial.print(SPI.transfer(0x00));
}

digitalWrite(CS, HIGH);

Serial.println();

//return data;
}

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
