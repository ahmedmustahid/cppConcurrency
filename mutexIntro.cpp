#include <iostream>
#include <string>
#include <thread>

using std::cout;
using std::string;
using std::thread;

std::mutex mutx;

void task(const string &str)
{
    mutx.lock();
    cout << str[0] << str[1] << str[2] << "\n";
    mutx.unlock();
}

int main()
{
    thread t1(task, "abc");
    thread t2(task, "def");
    thread t3(task, "ghi");

    t1.join();
    t2.join();
    t3.join();
}
