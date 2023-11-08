//Mutex in c++ Threading | why use mutex | what is a race condition and how to solve it? | What is a critical section?

//Mutex: aka Mutual Exclusion

//Race condition: 
//1. Race condition is a situation where two or more threads/process happen to change a common data at the same time
//2. If there is a race conditon then we have to protect it and the protected section is called critical section/region

// Mutex
// 1. Mutex is used to avoid race condition
// 2. We use lock(), unlock() on mutex to avoid race conditon
//  mutex carMutex; //create the mutex object
//  unique_lock<mutex> carLock(carMutex);
//  carLock.unlock();
//  lock_guard<mutex> carLock(carMutex);

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
using namespace std::chrono_literals;
int myAmount = 0;

std::mutex moneyMutex;
void addMoney(int x){
  moneyMutex.lock();
  myAmount += x; //critical region/section for the race condition
  std::this_thread::sleep_for(1000ms);
  std::cout << myAmount << std::endl;
  moneyMutex.unlock();
}

void driveCar(std::string name){
  moneyMutex.lock();
  std::cout << name << " is driving" << std::endl;
  std::this_thread::sleep_for(1000ms);
  std::cout << name << " is done driving" << std::endl;
  moneyMutex.unlock();
}

int main(){
  // std::thread t1(driveCar,"tavo");
  // std::thread t2(driveCar, "bob");

  std::thread t3(addMoney, 1);
  std::thread t4(addMoney, 2);
  // t1.join();
  // t2.join();
  t3.join();
  t4.join();

  return 0;
}