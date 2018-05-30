#ifndef STATS_H_
#define STATS_H_

#include <chrono>

class Stats {
private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
  std::chrono::time_point<std::chrono::steady_clock> finish_;
  double millis_;

public:
  Stats() { start(); }

  void start() {
    start_ = std::chrono::steady_clock::now();
    finish_ = start_;
  }

  double millis() const { return millis_; }

  void stop() {
    finish_ = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish_ - start_;
    millis_ = elapsed.count();
  }
};

#endif // STATS_H_
