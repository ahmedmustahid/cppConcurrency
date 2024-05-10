#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using namespace std::literals;
using std::thread;

std::mutex mtx1;
std::mutex mtx2;

void func1()
{
    cout << std::this_thread::get_id() << "locking mutx1\n";
    std::lock_guard<std::mutex> lock(mtx1);
    cout << std::this_thread::get_id() << "locked mutx1\n";
    std::this_thread::sleep_for(50ms);
    cout << std::this_thread::get_id() << "locking mutx2\n";
    std::lock_guard<std::mutex> lock2(mtx2);
    cout << std::this_thread::get_id() << "locked mutx2\n";
}

void func2()
{
    cout << std::this_thread::get_id() << "locking mutx2\n";
    std::lock_guard<std::mutex> lock(mtx2);
    cout << std::this_thread::get_id() << "locked mutx2\n";
    std::this_thread::sleep_for(50ms);
    cout << std::this_thread::get_id() << "locking mutx1\n";
    std::lock_guard<std::mutex> lock2(mtx1);
    cout << std::this_thread::get_id() << "locked mutx2\n";
}

int main()
{
    thread t1(func1);
    thread t2(func2);

    t1.join();
    t2.join();
}
