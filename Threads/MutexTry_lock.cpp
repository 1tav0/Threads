// Topic: std::mutex::try_lock on c++11
// 1. try_lock() tries to lock the mutex object. Returns immediately, on success lock acquistion returns true else returns false.
// 2. if try_lock is not able to lock the mutex, then it doesnt get blocked thats why it is called non-blocking
// 3. If try_lock is called again by te same thread which owns the mutex, the behavior is undefined
// it is a deadlock situation with undefined behavior. (if you want to be able to lock the same mutex by the same thread more than once then go for recursive_mutex)

//total try_lock()
// 1. std::try_lock()
// 2. std::mutex::try_lock()
// 3. std::shared_lock::try_lock()
// 4. std::timed_mutex::try_lock()
// 5. std::unique_lock::try_lock()
// 6. std::shared_mutex::try_lock()
// 7. std::recursive_mutex::try_lock()
// 8. std::shared_timed_mutex::try_lock()
// 9. std::recursive_timed_mutex::try_lock()


#include <iostream>
#include <thread>
#include <mutex>
using namespace std::chrono_literals;
int counter = 0;

std::mutex counterMutex;
void printCounter(){
  for (int i = 0; i < 100000; ++i){
    if(counterMutex.try_lock()){
      ++counter;
      // std::this_thread::sleep_for(500ms);
      counterMutex.unlock();
    }
  }
}

// void printCounter(){
//   for (int i = 0; i < 1000; ++i){
//     counterMutex.lock();
//     ++counter;
//     std::cout << "counter is: " << counter << std::endl;
//     counterMutex.unlock();
//   }
// }

int main(){
  std::thread t1(printCounter);
  std::thread t2(printCounter);

  t1.join();
  t2.join();

  //note we should be able to output 200000 but we dont instead we get different values everytime
  //this is bc when either thread races to get to the critical section, once they get there they lock that section, & starts processing the data, then it may be processing without having realeased the lock so when thread 2 comes in at i=0 it may be locked still so we skip that iteration and try with another one and this can go on for various iterations of i therefore when thread 2 finally accesses the critical section after release from the first thread, i isnt exactly starting from 0 hence the iteration starts from an unexpected number and then the counter keeps incrementing from that iteration hence the unexpected random value for counter
  //this behavior of trying for each iteration is due to try_lock 
  //to avoid it we can simply use the lock() and unlock()
  std::cout << "counter is: " << counter << std::endl;
  return 0;
}