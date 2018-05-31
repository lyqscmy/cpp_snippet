#include <cstdio>
#include <cstdlib>

static int FLAGS_iteration = 100;

int main(int argc, char **argv) {
  // parse options
  for (int i = 1; i < argc; i++) {
    int n;
    char junk;
    if (sscanf(argv[i], "--iter=%d%c", &n, &junk) == 1) {
      FLAGS_iteration = n;
    } else {
      fprintf(stderr, "Invalid flag '%s'\n", argv[i]);
      exit(1);
    }
  }
}
