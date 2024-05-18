#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::cout;
using std::string;
using namespace std::literals;

string data;

std::mutex mtx;

std::condition_variable cond;

void read1()
{
    std::unique_lock<std::mutex> ul(mtx);
    cout << "waiting ...\n";
    cond.wait(ul);

    cout << "received data is " << data << "\n";
}

void write1()
{
    {
        std::lock_guard<std::mutex> lg(mtx);
        data = "hello";
        std::this_thread::sleep_for(2s);
    }

    cout << "data written \n";
    cond.notify_one();
}

int main()
{
    data = "empty";
    std::thread t1(read1);
    std::thread t2(write1);

    t1.join();
    t2.join();
}
