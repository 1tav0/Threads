//join() detach() and joinable() in c++11

//1.Once a thread is started we wait for this thread to finish by calling join() function on thread object to join it with the main thread
//2. Double join will result in program termination
//3. If needed we should check thread is joinable before joining

// detach()
// 1. This is used to detach newly created thread from the parent thread
// 2. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and double detach() will result in program termination
// 3. If we have detached thread and main funcition is returning then the detached thread execution is suspended

//Either join() or detach() should be called on thread object, otherwise during thread object's destructor it will terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.

#include <iostream>
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

void run(int count){
  while(count --> 0)
    std::cout << count << " Hello World" << std::endl;
  std::this_thread::sleep_for(3000ms);
  std::cout << "Thread is finished" << std::endl;
}

int main(){
  std::thread t1(run, 10);
  std::cout << "main" << std::endl;
  //detach this thread from the main thread means it wont be waiting for the thread to finsih 
  t1.detach();
  //to avoid double detach
  if(t1.joinable()){
    t1.detach();
  }
  std::cout << "main after" << std::endl;

  return 0;
}