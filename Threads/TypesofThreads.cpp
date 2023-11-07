#include <iostream>
#include <thread>
using namespace std::chrono_literals;

//Type 1 Function Pointer
/*
void function(int x){
  while(x --> 0){
    std::cout << x << std::endl;
    std::this_thread::sleep_for(1000ms);
  }
}
int main(){
  std::thread t1(function, 10);
  t1.join();

  return 0;
}
*/
//Type 2 Lambda Function
/*
int main(){
  // we can directly inject lambda at thread creation time
  std::thread t1([](int x)
  {
    while(x-->0)
    {
      std::cout << x << std::endl;
      std::this_thread::sleep_for(500ms);
    }
  }, 10);
  t1.join();

  return 0;
}
*/
//Type 3 Functor (Function object)
/*
class Base{
  public:
    void operator()(int x){
      while(x-->0){
        std::cout << x << std::endl;
      }
    }
};

int main(){
    std::thread t((Base()), 10);
    t.join();

    return 0;
}
*/
//Type 4 Non-Static member function
/*
class Base{
  public:
    void run(int x){
      while(x-->0){
        std::cout << x << std::endl;
      }
    }
};

int main(){
  Base b;
  //we need b bc like normal class call we need to create an object to be able to call the function inside of the class
  std::thread t(&Base::run, &b, 10);
  t.join();

  return 0;
}
*/
//Type 4 Static member function
class Base{
  public:
    static void run(int x){
      while(x-->0){
        std::cout << x << std::endl;
      }
    }
};

int main(){
  //dont need to create an object with a static member function class
  std::thread t(&Base::run, 10);
  t.join();

  return 0;
}
