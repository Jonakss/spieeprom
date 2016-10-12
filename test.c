#include <iostream>

struct int24{
    unsigned int data : 24;
};

void print_binary(int n) {
    if (n == 0 || n ==1)
        std::cout << n;
    else {
        print_binary(n >> 1);
        std::cout << (n & 0x1);
    }
}

int main(void){
  long add = 0, capacity = 524287, lastAdd=4, j=0;
  j = lastAdd - add;
  std::cout << j << '\n';
  char data[j];

  for(long i=0; i<=j; i++){
    data[i] = 'a';
  }

  for(long i=0; i<=j; i++){
    std::cout << data[i] << '\n';
  }

  return 0;
}
