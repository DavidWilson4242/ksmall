/* TUFTS COMP 160
 * David Wilson */

/* NOTE: I implemented deterministic select, but it is still called randSelect.  See
 * function pick_index() */

/* Please note that I originally wrote this code in C, then translated it to C++.  It's still
 * basically C, except I made randSelect take in a std::vector.  I convert the vector to a
 * C-compatible array which I pass to the other functions, which are just standard C */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <vector>

static void swap(int *, int *);
static int comparator(const void *, const void *);
static size_t smallest_index(int *, size_t);
static size_t largest_index(int *, size_t);
static size_t partition(int *, size_t, size_t);
static size_t selection(int *, size_t, size_t);
static size_t pick_index(int *, size_t);

/* swaps two integer elements a and b */
static void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/* prints an array in the format [ A0 A1 A2 A3 ... ] */
static void print_arr(int *A, size_t N) {
  printf("[ ");
  for (size_t i = 0; i < N; i++) {
    printf("%d ", A[i]);
  }
  printf("]\n");
}

/* for qsort base cases. see function selection() */
static int comparator(const void *a, const void *b) {
  return *(const int *)a - *(const int *)b;
}

/* given array A of size N, returns the index of 
 * the smallest element in A */
static size_t smallest_index(int *A, size_t N) {
  int smallest = INT_MAX;
  size_t index;
  for (size_t i = 0; i < N; i++) {
    if (A[i] < smallest) {
      smallest = A[i];
      index = i;
    }
  }
  return index;
}

/* given array A of size N, returns the index of 
 * the largest element in A */
static size_t largest_index(int *A, size_t N) {
  int largest = INT_MIN;
  size_t index;
  for (size_t i = 0; i < N; i++) {
    if (A[i] > largest) {
      largest = A[i];
      index = i;
    }
  }
  return index;
}

/* partitions in place around A[k], returns the new
 * index of the value originally located at A[k]
 * Note: no extra memory is used, as the partition
 * is done in place.  */
static size_t partition(int *A, size_t N, size_t k) {
  size_t s = 0;
  int pivot = A[k];

  swap(&A[0], &A[k]);
  for (size_t i = 1; i < N; i++) {
    if (A[i] <= pivot) {
      swap(&A[i], &A[1 + (s++)]);
    }
  }
  swap(&A[0], &A[s]);

  return s;
}

/* given an array A of size N, returns the k-th smallest integer in A */
static size_t selection(int *A, size_t N, size_t k) {
  
  size_t pivotRank, pos;
  
  assert(k >= 0 && k < N);

  printf("Looking for value with rank %zu in the array:\n", k);
  print_arr(A, N);

  /* base cases */
  if (k == 0) {
    printf("Reached base case. We are done.\n");
    return smallest_index(A, N);
  }
  if (k == N - 1) {
    printf("Reached base case. We are done.\n");
    return largest_index(A, N);
  }
  if (N == 1) {
    return 0;
  }
  
  /* index is picked using the median of medians method */
  pivotRank = pick_index(A, N);
  pos = partition(A, N, pivotRank);

  printf("Selected %d as the pivot; its rank is %zu; ", A[pos], pivotRank);
  printf("Thus, we recurse on ");

  if (pos == k) {
    printf("nothing. We are done.\n");
    return pos;
  } else if (pos > k) {
    printf("left.\n");
    return selection(A, pos, k);
  } else {
    printf("right.\n");
    return selection(&A[pos + 1], N - pos - 1, k - pos - 1) + pos + 1;
  }
}

/* implementation of the median of medians method.  Uses groups
 * of size 5.  Runs in linear time. */
static size_t pick_index(int *A, size_t N) {
  int *B;
  int mbuf[5];
  size_t median_index;

  B = new int[N/5];

  for (size_t i = 0; i < N/5; i++) {
    for (size_t j = 0; j < 5; j++) {
      mbuf[j] = A[5*i + j];
    }
    qsort(mbuf, 5, sizeof(int), comparator);
    B[i] = mbuf[2];
  }

  median_index = selection(B, N/5, N/10);
  delete[] B;

  return median_index;
}

/* given a vector of integers, returns the k-smallest integer,
 * where rank specifies the k value.  Indexing starts at 0, i.e.
 * the smallest element is rank 0, second smallest is rank 1, ... */
int randSelect(std::vector<int> array, int rank) {
  
  /* I originally wrote this code a while ago in C, not C++.  So
   * this code is a weird mixture of C and C++.  I take the input
   * in as a vector, then convert it to a C-compatible array. 
   * The rest of the functions are ripped straight from my
   * C implementation */
  int *carr = new int[array.size()];
  for (size_t i = 0; i < array.size(); i++) {
    carr[i] = array[i];
  }

  int solution = carr[selection(carr, array.size(), rank)];

  delete[] carr;

  return solution;
}
