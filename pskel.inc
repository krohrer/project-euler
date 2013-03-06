#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdarg.h>

typedef int64_t num;

#define NUM(v) INT64_C(v)

void print_num(const char *name, num i) {
  printf("%s = %" PRIi64 "\n", name, i);
}

void calculate_solution(void);

void die(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  fprintf(stderr, "Fatal error:");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  fflush(stderr);

  va_end(ap);

  exit(-1);
}

int main(int argc, const char *argv[]) {
  calculate_solution();
  return 0;
}

/* File handling -----------------------------------------------------------*/

FILE *fopen_or_die(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) die("Could not open file: %s", filename);
  return f;
}

/* Prime number sieve ------------------------------------------------------*/

typedef struct {
  unsigned count;
  unsigned N;
  bool* V;
  unsigned* P;
} psieve;

void psieve_init(psieve *S, unsigned N) {
  size_t size = sizeof(bool) * (N + 1); // [0;N]
  S->count = 0;
  S->N = N;
  S->V = malloc(size);
  S->P = NULL;
  memset(S->V, true, size);
  S->V[0] = S->V[1] = false;
  for (unsigned i = 2; i <= S->N; ++i) {
    if (S->V[i]) {
      ++S->count;
      for (unsigned k = 2*i; k <= S->N; k += i) {
	S->V[k] = false;
      }
    }
  }
}

void psieve_grow(psieve *S, unsigned i) {
  fprintf(stderr, "Psieve: Resizing!\n");
  unsigned N2 = 2*S->N;
  N2 = N2 < i ? i : N2;

  size_t size = sizeof(bool) * (N2 + 1);
  bool *V = malloc(size);

  memset(V, true, size);
  unsigned k;
  for (k = 2; k <= S->N; ++k) {
    V[k] = S->V[k];
    if (V[k]) {
      for (unsigned l = S->N + k - (S->N % k); l <= N2; l += k) {
	V[l] = false;
      }
    }
  }
  for (; k <= N2; ++k) {
    if (V[k]) {
      ++S->count;
      for (unsigned l = 2*k; l <= N2; l += k) {
	V[l] = false;
      }
    }
  }

  free(S->V);
  S->V = V;
  S->N = N2;

  free(S->P);
  S->P = NULL;
}

void psieve_destroy(psieve *S) {
  free(S->V);
  free(S->P);
}

void psieve_dump(psieve *S) {
  for (unsigned i = 1; i <= S->N; ++i) {
    if (S->V[i]) printf("%u ", i);
  }
  puts("\n");
}

bool psieve_contains(psieve *S, unsigned i) {
  if (i > S->N) {
    psieve_grow(S, i);
  }
  return S->V[i];
}

unsigned psieve_prime_at_index(psieve *S, unsigned idx) {
  if (idx >= S->count)
    die("Psieve{count=%u}: index %u out of bounds.", S->count, idx);
  
  if (S->P == NULL) {
    S->P = malloc(S->count * sizeof(unsigned));
    unsigned p = 0;
    for (unsigned i = 2; i <= S->N; ++i) {
      if (S->V[i]) {
	S->P[p++] = i;
      }
    }
  }

  return S->P[idx];
}

/* Prime factors -----------------------------------------------------------*/

typedef struct {
  unsigned i;
  unsigned count;
  bool is_prime;
  uint8_t *V;
} pfactors;

void pfactors_init(pfactors *F, unsigned i, psieve *S) {
  unsigned sqrt_i = (unsigned)sqrt((double)i) + 1;

  F->i = i;
  F->count = 0;
  F->is_prime = psieve_contains(S, i);
  F->V = malloc(sizeof(uint8_t) * sqrt_i);

  int k;
  for (k = 0; k < sqrt_i; ++k) {
    unsigned p = psieve_prime_at_index(S, k);
    unsigned d = i;
    /* If a natural number i is not prime itself, it cannot have a
       prime factor greater than sqrt(i) */
    if (sqrt_i < p) break;

    /* Calculate exponent for prime p */
    F->V[k] = 0;
    while (d % p == 0) {
      F->V[k] += 1;
      d /= p;
    }
  }

  F->count = k;
}

void pfactors_dump(pfactors *F, psieve *S) {
  printf("Prime factors for %u:", F->i);
  if (F->is_prime) {
    printf(" %u\n", F->i);
  }
  else {
    for (unsigned k = 0; k < F->count; ++k) {
      unsigned exp = F->V[k];
      unsigned p = psieve_prime_at_index(S, k);
      if (exp > 0) printf(" %u^%u", p, exp);
    }
    printf("\n");
  }
}

void pfactors_destroy(pfactors *F) {
  free(F->V);
}
