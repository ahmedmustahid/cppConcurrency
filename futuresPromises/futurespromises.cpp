#include <functional>
#include <future>
#include <iostream>
#include <thread>

using std::cout;

void produce(std::promise<int> &px)
{
    int x = 45;
    px.set_value(x);
}

// void consume(std::future<int> &fut)
void consume(std::shared_future<int> &fut)
{
    int x = fut.get();
    cout << "received the value " << x << "\n";
}

int main()
{
    std::promise<int> prom;
    // std::future fut = prom.get_future();
    std::shared_future<int> fut = prom.get_future();
    std::shared_future<int> fut2 = fut;
    std::thread t1(produce, std::ref(prom));
    std::thread t2(consume, std::ref(fut));
    std::thread t3(consume, std::ref(fut2));

    t1.join();
    t2.join();
    t3.join();
}
