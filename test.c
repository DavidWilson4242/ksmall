#include <stdio.h>
#include <stdlib.h>
#include "ksmall.h"

void run_test(int *A, size_t k, size_t N, const char *name) {
  printf("smallest element #%zu in %s is %d.\n", k, name, ksmall(A, N, k));
}

int main() {
  
  /* run a couple of test cases */
  int A0[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int A1[] = {-50, -50, -50, 0, 0, 0, 42};
  int A2[] = {2, -12, 19, 47, 47, 47, 47, -45, -36, -49};
  int A3[] = {1, -1, 1, -1, 1, -1, -50, 1, 2, 3, -49, 90, 100};

  run_test(A0, 4, sizeof(A0)/sizeof(int), "A0");
  run_test(A1, 7, sizeof(A1)/sizeof(int), "A1");
  run_test(A2, 3, sizeof(A2)/sizeof(int), "A2");
  run_test(A3, 2, sizeof(A3)/sizeof(int), "A3");
  
  return 0;
}
