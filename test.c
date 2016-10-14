//#include <iostream>
//
//const long capacity = 524288; // in chars -> 4MB (512KB) // 0x000000 - 0x07FFFF
//const long blockSize = 65536; // 64K
//const long sectorSize = 4096; // 4K
//
//void print_binary(int n) {
//    if (n == 0 || n ==1)
//        std::cout << n;
//    else {
//        print_binary(n >> 1);
//        std::cout << (n & 0x1);
//    }
//  }
//
//int inBlock(long add){
//  int b=0;
//  long i=blockSize;
//  
//  while((i<capacity)){
//    if(add < i){
//      i=capacity;
//    }else{
//      b+=1;
//      i+=blockSize;
//    }
//  }
//
//  return b;
//}
//int inSector(long add){
//  int s=0;
//  long i=sectorSize;
//  
//  while((add >= i) && (i<capacity)){
//      s+=1;
//      i+=sectorSize;
//  }
//
//  return s;
//}
//
//int main(void){
//  int b = inBlock(0x060000);
//  std::cout << b;
//  
//  return 0;
//}
