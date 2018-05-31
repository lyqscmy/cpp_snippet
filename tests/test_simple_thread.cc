#include "../simple_thread.h"
#include "../stats.h"
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <vector>

static int FLAGS_nthreads = 2;
int main(int argc, char **argv) {
  using namespace std::chrono_literals;
  // parse options
  for (int i = 1; i < argc; i++) {
    int n;
    char junk;
    if (sscanf(argv[i], "--nthreads=%d%c", &n, &junk) == 1) {
      FLAGS_nthreads = n;
    } else {
      fprintf(stderr, "Invalid flag '%s'\n", argv[i]);
      exit(1);
    }
  }

  const int nthreads = FLAGS_nthreads;
  std::vector<SimpleThread> threads(nthreads);
  std::atomic<int> ready(0);
  std::vector<Stats> stats(nthreads);
  for (int tid = 0; tid != nthreads; ++tid) {
    threads[tid] = SimpleThread(
        [&](int tid) {
          ready.fetch_add(1, std::memory_order_seq_cst);
          while (ready.load(std::memory_order_relaxed) != nthreads)
            continue;

          stats[tid].start();
          std::this_thread::sleep_for(2s);
          stats[tid].stop();
          fprintf(stdout, "tid: %d\t waited: %fms\n", tid, stats[tid].millis());
        },
        tid);
  }
  for (int tid = 0; tid != nthreads; ++tid) {
    threads[tid].join();
  }
}
