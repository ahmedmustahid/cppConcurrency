#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using std::cout;
using std::string;
using namespace std::literals;

string data{};

bool progressFlag = false;
bool completed = false;

std::condition_variable dataCondVar;
std::condition_variable completedCondVar;

std::mutex dataMtx;
std::mutex procMtx;

void fetch()
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "obtaining data....\n";
        std::this_thread::sleep_for(2s);
        std::lock_guard<std::mutex> dataLock(dataMtx);
        data += "Byte" + std::to_string(i);
        cout << data << " received\n";
        progressFlag = true;
        dataCondVar.notify_all();
    }

    std::lock_guard<std::mutex> procLock(procMtx);
    completed = true;
}

void progressBar()
{
    while (true)
    {
        std::unique_lock<std::mutex> progLock(dataMtx);
        // while (!progressFlag)
        //{
        //     progLock.unlock();
        //     std::this_thread::sleep_for(2ms);
        //     progLock.lock();
        // }
        dataCondVar.wait(progLock, []() { return progressFlag; });
        int sz = data.size();
        progressFlag = false;
        // progLock.unlock();
        cout << "progressed " << sz << " bytes\n";

        std::lock_guard<std::mutex> procLock(procMtx);
        if (completed)
        {
            cout << "download completed\n";
            break;
        }
    }
}

void process()
{
    std::unique_lock<std::mutex> lock(procMtx);
    while (!completed)
    {
        lock.unlock();
        std::this_thread::sleep_for(10ms);
        lock.lock();
    }

    lock.unlock();
    cout << "processing the data ..\n";
}

int main()
{
    std::thread t1(fetch);
    std::thread t2(progressBar);
    std::thread t3(process);

    t1.join();
    t2.join();
    t3.join();
}
