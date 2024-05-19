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

bool var = false;

void reader()
{
    std::unique_lock<std::mutex> ul(mtx);
    cout << "waiting ...\n";
    cond.wait(ul, []() { return var; });
    // while (!var)
    //{
    //     ul.unlock();
    //     std::this_thread::sleep_for(50ms);
    //     ul.lock();
    // }
    cout << "received data is " << data << "\n";
    var = false;
}

void writer()
{
    {
        std::lock_guard<std::mutex> lg(mtx);
        std::this_thread::sleep_for(2s);
        data = "hello";
        var = true;
    }

    cout << "data written \n";
    cond.notify_one();
    cout << "writer sends notification \n";
}

int main()
{
    data = "empty";
    std::thread t2(writer);
    std::this_thread::sleep_for(500ms);
    std::thread t1(reader);

    t1.join();
    t2.join();
}
