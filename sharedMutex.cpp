#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::string;
using std::thread;
using std::vector;
using namespace std::literals;

int x = 0;
std::shared_mutex shmut;

void write1()
{
    std::lock_guard<std::shared_mutex> lock(shmut);
    ++x;
}
void read1()
{
    std::shared_lock<std::shared_mutex> sh_lock(shmut);
    std::this_thread::sleep_for(100ms);
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(thread(read1));
    }

    threads.push_back(thread(write1));
    threads.push_back(thread(write1));

    for (auto &t : threads)
    {
        t.join();
    }
}
