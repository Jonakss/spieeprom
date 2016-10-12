//#include <iostream>
//
//void print_binary(int n) {
//    if (n == 0 || n ==1)
//        std::cout << n;
//    else {
//        print_binary(n >> 1);
//        std::cout << (n & 0x1);
//    }
//}
//
//char* a(){
//  long add = 0, capacity = 524287, lastAdd=16, j=0;
//  j = lastAdd - add;
//  char data[j];
//
//  for(long i=0; i<=j; i++){
//    data[i] = 'a';
//  }
//
//  return data;
//}
//
//int main(void){
//  char* data = a();
//
//  std::cout << sizeof(data) << '\n';
//
//  for(long i=0; i<=sizeof(data); i++){
//    std::cout << data[i] << '\n';
//  }
//
//  return 0;
//}
