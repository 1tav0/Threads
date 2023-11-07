#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

//i & 1: This performs a bitwise AND operation between the binary representation of i and the binary number 1. Since the binary representation of 1 is 0001, the result of this operation is 0 if the least significant bit of i is 0 (indicating an even number) and 1 if the least significant bit is 1 (indicating an odd number).
void findEven(ull start, ull end){
  for (ull i = start; i <= end; ++i){
    if((i&1)==0){
      evenSum += i;
    }
  }
}
//(i & 1) == 0: This condition checks whether the result of the bitwise AND operation is equal to 0. If it's equal to 0, it means that the least significant bit of i is 0, which indicates that i is an even number.
void findOdd(ull start, ull end){
  for (ull i = start; i <= end; ++i){
    if((i&1)==1){
      oddSum += i;
    }
  }
}

int main(){
  ull start = 0;
  ull end = 1900000000;

  auto startTime = high_resolution_clock::now();

  findOdd(start, end);
  findEven(start, end);

  auto stopTime = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stopTime - startTime);

  cout << "oddsum: " << oddSum << endl;
  cout << "EvenSum: " << evenSum << endl;

  cout << "Secs: " << duration.count() / 1000000 << endl;

  return 0;
}
