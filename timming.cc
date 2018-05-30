#include "stats.h"
#include <iostream>
#include <thread>

int main() {
  using namespace std::chrono_literals;
  Stats stats;
  std::this_thread::sleep_for(2s);
  stats.stop();
  std::cout << "Waited " << stats.millis() << " ms\n";
}
