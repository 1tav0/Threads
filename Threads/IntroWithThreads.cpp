#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end){
  for (ull i = start; i <= end; ++i){
    if((i&1)==0){
      evenSum += i;
    }
  }
}

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

  std::thread t1(findEven, start, end);
  std::thread t2(findOdd, start, end);
  //to join these thread to the main thread without this it means the main thread may finish and the thread may not be threfore there wont be any way of getting the result from these threads
  t1.join();
  t2.join();

  auto stopTime = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stopTime - startTime);

  cout << "oddsum: " << oddSum << endl;
  cout << "EvenSum: " << evenSum << endl;

  cout << "Secs: " << duration.count() / 1000000 << endl;
  
  return 0;
}
