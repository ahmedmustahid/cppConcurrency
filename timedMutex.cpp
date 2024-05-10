#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::cout;
using std::string;
using std::thread;
using namespace std::literals;

std::timed_mutex mutx;

void task1()
{
    cout << "trying to lock task1\n";
    mutx.lock();
    cout << "locked task1\n";
    std::this_thread::sleep_for(5s);
    cout << "task1 unlocking \n";
    mutx.unlock();
}

void task2()
{
    std::this_thread::sleep_for(500ms);
    cout << "task2 trying to lock\n";
    auto deadline = std::chrono::system_clock::now() + 900ms;

    while (!mutx.try_lock_until(deadline))
    {
        /* code */
        cout << "task2 couldnt lock; trying again \n";
        deadline = std::chrono::system_clock::now() + 900ms;
    }

    cout << "task2 could lock\n";
    mutx.unlock();
}

int main()
{
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}
