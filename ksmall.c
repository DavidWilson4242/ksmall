#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "ksmall.h"

static void swap(int *, int *);
static int comparator(const void *, const void *);
static size_t smallest_index(int *, size_t);
static size_t largest_index(int *, size_t);
static size_t partition(int *, size_t, size_t);
static size_t selection(int *, size_t, size_t);
static size_t pick_index(int *, size_t);
int ksmall(int *, size_t, size_t);

static void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/* for qsort base cases */
static int comparator(const void *a, const void *b) {
  return *(const int *)a - *(const int *)b;
}

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
 * index of the value originally located at A[k] */
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

/* selection function, implemented as discussed in lecture */
static size_t selection(int *A, size_t N, size_t k) {
  
  size_t magic, pos;
  
  assert(k >= 0 && k < N);

  /* base cases */
  if (k == 0) {
    return smallest_index(A, N);
  }
  if (k == N - 1) {
    return largest_index(A, N);
  }
  if (N <= 5) {
    qsort(A, N, sizeof(int), comparator); 
    return k;
  }
  
  magic = pick_index(A, N);
  pos = partition(A, N, magic);

  if (pos == k) {
    return pos;
  } else if (pos > k) {
    return selection(A, pos, k);
  } else {
    return selection(&A[pos + 1], N - pos - 1, k - pos - 1) + pos + 1;
  }
}

/* implemented as discussed in lecture. Runs in linear time,
 * since the qsort of size 5 is really constant time */
static size_t pick_index(int *A, size_t N) {
  int *B, *mbuf;
  size_t median_index;

  B = malloc(sizeof(int) * N/5);
  mbuf = malloc(sizeof(int) * 5);
  assert(B);
  assert(mbuf);

  for (size_t i = 0; i < N/5; i++) {
    for (size_t j = 0; j < 5; j++) {
      mbuf[j] = A[5*i + j];
    }
    qsort(mbuf, 5, sizeof(int), comparator);
  }

  median_index = selection(B, N/5, N/10);
  free(B);
  free(mbuf);

  return median_index;
}

int ksmall(int *A, size_t N, size_t k) {
  
  assert(A && k >= 1 && k <= N);

  return A[selection(A, N, k - 1)];
}
