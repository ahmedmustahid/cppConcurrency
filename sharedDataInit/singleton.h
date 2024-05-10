#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

class Singleton
{
  public:
    // static Singleton *single;
    Singleton()
    {
        std::cout << "Singleton initialized\n";
    }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(const Singleton &&) = delete;
    Singleton &operator=(const Singleton &&) = delete;

    // static Singleton *get_single();
};

Singleton &get_single();
