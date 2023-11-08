// Topic: std::try_lock() c++11
// 1 .tries to lock all the lockable objects passed in it one by one in given order
// SYNTAX: std::try_lock(m1,m2,m3,m4...,mn);
// 2. On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock
// 3. If it fails to lock any of the mutex then it will release all the mutex it locked before
// 4. If a call to try_lock results in an exception, unlock is called for any locked objects before rethrowing
// Notes: m.try_lock() tries to lock that one object
// std::try_lock(m1,m2,m3...) has multiple objects that can be tried to lock at the same time
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

int X = 0, Y = 0;
std::mutex m1, m2;
// 1. Threads t1 and t2 run concurrently. They increment X and Y, respectively, by locking and unlocking m1 and m2. The order in which t1 and t2 lock and unlock m1 and m2 may vary. For example, t1 might lock m1, unlock m1, and then t2 might lock m2 and unlock m2, or the order could be different.

void incrementXY(int &XorY, std::mutex &m, const char *desc)
{
  for (int i = 0; i < 5; ++i)
  {
    m.lock();
    ++XorY;
    std::cout << desc << " is " << XorY << std::endl;
    m.unlock();
    std::this_thread::sleep_for(1000ms);
  }
}
// 2. Meanwhile, t3 runs concurrently with t1 and t2. It's calling std::try_lock(m1, m2) to attempt to lock both m1 and m2 simultaneously. If either m1 or m2 is locked by t1 or t2 at this point, std::try_lock will not succeed in locking both, and lockResult will not be set to -1. The try_lock function won't block; it will return immediately.
// 3. If std::try_lock fails to lock both m1 and m2, t3 continues without entering the critical section, and it doesn't consume X and Y because at least one of the mutexes is already locked by either t1 or t2.
// 4. The key advantage of using std::try_lock is that it prevents potential deadlocks because it doesn't block. If t3 attempted to lock m1 and m2 using regular locking methods (lock), it would wait indefinitely if one of the mutexes was already locked by another thread. With try_lock, t3 can continue to run even if it can't lock both mutexes immediately.
void consumeXY()
{
  int timer = 5;
  int sum = 0;
  while (true)
  {
    //If std::try_lock successfully locks both m1 and m2, it proceeds to the next step, indicating that no other thread has currently locked these mutexes.
    //To safely manipulate both X and Y concurrently, you use std::try_lock to ensure that both m1 and m2 can be locked simultaneously. If std::try_lock succeeds in locking both mutexes at the same time, it means that the thread has exclusive access to both X and Y, and you can safely manipulate them without any risk of data race or inconsistency.
    int lockResult = std::try_lock(m1, m2);
    if (lockResult == -1)
    {
      if (X != 0 && Y != 0)
      {
        --timer;
        sum += X + Y;
        X = 0;
        Y = 0;
        std::cout << "x plus y " << sum << std::endl;
        std::this_thread::sleep_for(2000ms);
      }
      m1.unlock();
      m2.unlock();
      if (timer == 0)
        break;
    }
  }
}
//In summary, std::try_lock allows t3 to check if both m1 and m2 can be locked simultaneously without blocking, and it only enters the critical section when it successfully locks both mutexes. The order in which t1, t2, and t3 lock and unlock the mutexes can vary, and try_lock doesn't rely on a specific order of execution.
int main()
{
  std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X");
  std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y");
  std::thread t3(consumeXY);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}