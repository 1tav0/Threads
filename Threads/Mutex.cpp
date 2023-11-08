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

int myAmount = 0;

std::mutex moneyMutex;
void addMoney(){
  //moneyMutex.lock();
  ++myAmount; //critical region/section for the race condition
  //moneyMutex.unlock();
}

int main(){
  std::thread t1(addMoney);
  std::thread t2(addMoney);

  t1.join();
  t2.join();

  std::cout << myAmount << std::endl;

  return 0;
}