#include "singleton.h"
#include <thread>
#include <vector>

// Singleton *Singleton::single = nullptr;

void task()
{
    Singleton &single = get_single();
    std::cout << &single << std::endl;
}

int main()
{
    std::vector<std::thread> threads;

    for (size_t i = 0; i < 10; ++i)
        threads.push_back(std::thread(task));

    for (auto &t : threads)
        t.join();

    return 0;
}
