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

class Vector {
 private:
  /* data */
  std::mutex mutx;
  vector<int> vec;

  std::shared_mutex sm;

 public:
  vector<int> &push_back(const int &i) {
    mutx.lock();
    vec.push_back(i);
    mutx.unlock();

    return vec;
  }
};

int main() {
  Vector v;
  thread t1(&Vector::push_back, &v, 1);
  thread t2(&Vector::push_back, &v, 2);

  t1.join();
  t2.join();
}
