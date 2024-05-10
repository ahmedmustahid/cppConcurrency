#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::string;
using std::thread;
using std::vector;

std::mutex mutx;
int x = 0;

void write()
{
    std::lock_guard<std::mutex> lock(mutx);
    ++x;
}

void read()
{
    std::lock_guard<std::mutex> lock(mutx);
    using namespace std::literals;
    std::this_thread::sleep_for(100ms);
}

int main()
{
    vector<thread> threads;
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        thread t(read);
        threads.push_back(std::move(t));
    }

    threads.push_back(thread(write));
    threads.push_back(thread(write));

    for (auto &t : threads)
        t.join();
    cout << "x " << x << "\n";
}
