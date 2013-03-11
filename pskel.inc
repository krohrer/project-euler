#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>

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

//////////////////////////////////////////////////////////////////////////////
// Prime number sieve
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
// Prime factors
//////////////////////////////////////////////////////////////////////////////

typedef struct {
  unsigned i;
  unsigned count;
  bool is_prime;
  uint8_t *V;
} pfactors;

void pfactors_init(pfactors *F, unsigned i, psieve *S) {
  F->i = i;
  F->count = 0;
  F->is_prime = psieve_contains(S, i);
  F->V = malloc(sizeof(uint8_t) * S->count);

  int k;
  for (k = 0; k < S->count; ++k) {
    unsigned p = psieve_prime_at_index(S, k);
    unsigned d = i;
    /* If a natural number i is not prime itself, it cannot have a
       prime factor greater than i/2 */
    if (i*2 < p) break;
    
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

//////////////////////////////////////////////////////////////////////////////
// Big natural numbers
//////////////////////////////////////////////////////////////////////////////

#define FRAG_DIGITS	9
#define FRAG_FORMAT	"%09u"
#define FRAG_CUTOFF	(1000*1000*1000)
#define FRAG_MAX	(FRAG_CUTOFF-1)

typedef uint32_t frag_t;

typedef struct bignat_s {
  unsigned size;
  unsigned capacity;
  frag_t *fragments;
} bignat_t;

void frag_mult(frag_t x, frag_t y, frag_t *lo, frag_t *hi);

// Lifecycle

bignat_t* bignat_new(unsigned cap);
bignat_t* bignat_copy(bignat_t *x);
bignat_t* bignat_reset(bignat_t *x, unsigned cap);

void bignat_delete(bignat_t *x);

// Building blocks

void bignat_swap(bignat_t *x, bignat_t *y);

bignat_t* bignat_set_zero(bignat_t *x);
bignat_t* bignat_set_unsigned(bignat_t *x, unsigned i);
bignat_t* bignat_set_frag(bignat_t *x, unsigned idx, frag_t frag);

frag_t bignat_get_frag(bignat_t *x, unsigned idx);

bignat_t* bignat_normalize(bignat_t *x);

// Printing

size_t bignat_asprint(bignat_t *x, char **buff);
void bignat_print(bignat_t *x);
bignat_t* bignat_dump(bignat_t *x);

void bignat_add_frag_un(bignat_t *dest, frag_t f, unsigned offs);
void bignat_madd_frag_un(bignat_t *dest, bignat_t *x, frag_t f, unsigned offs);

// Arith

bignat_t* bignat_add(bignat_t *dest, bignat_t *x, bignat_t *y);
bignat_t* bignat_mult(bignat_t *dest, bignat_t *x, bignat_t *y);

// Digits

unsigned bignat_count_digits(bignat_t *x);
unsigned bignat_get_digit(bignat_t *x, unsigned idx);

////////////////////////////////////////

void frag_mult(frag_t x, frag_t y, frag_t *lo, frag_t *hi) {
  uint64_t product = (uint64_t)x * (uint64_t)y;
  *lo = product % FRAG_CUTOFF;
  *hi = product / FRAG_CUTOFF;
}

////////////////////////////////////////

bignat_t* bignat_new(unsigned cap) {
  bignat_t *x = malloc(sizeof(bignat_t));
  x->size = 0;
  x->capacity = cap > 0 ? cap : 2;
  x->fragments = malloc(sizeof(frag_t) * x->capacity);
  return x;
}

bignat_t* bignat_reset(bignat_t *x, unsigned cap) {
  x->size = 0;
  if (cap > x->capacity) {
    x->capacity = cap;
    free(x->fragments);
    x->fragments = malloc(sizeof(frag_t) * x->capacity);
  }
  return x;
}

void bignat_delete(bignat_t *x) {
  free(x->fragments);
  free(x);
}

frag_t bignat_get_frag(bignat_t *x, unsigned idx) {
  return idx < x->size ? x->fragments[idx] : 0;
}

bignat_t* bignat_set_frag(bignat_t *x, unsigned idx, frag_t frag) {
  if (idx < x->size) {
    x->fragments[idx] = frag;
  }
  else if (frag > 0) {
    // Zero new fragments
    unsigned oldsize = x->size;
    x->size = idx + 1;
    unsigned cap = 2*x->capacity;
    if (x->size > cap) cap = x->size;
    x->capacity = cap;
    x->fragments = realloc(x->fragments, sizeof(frag_t) * x->capacity);

    memset(x->fragments + oldsize, 0, (idx - oldsize)*sizeof(frag_t));
    x->fragments[idx] = frag;
  }
  else {
    // Do nothing, as fragments out of range are zero anyway.
  }
  return x;
}

bignat_t* bignat_set_unsigned(bignat_t *x, unsigned n) {
  x->size = 0;
  bignat_set_frag(x, 0, n);
  bignat_normalize(x);
  return x;
}

void bignat_add_frag_un(bignat_t *dest, frag_t f, unsigned offs) {
  frag_t d = bignat_get_frag(dest, offs);
  bignat_set_frag(dest, offs, d + f);
}

void bignat_madd_frag_un(bignat_t *dest, bignat_t *x, frag_t f, unsigned offs) {
  for (unsigned idx = 0; idx < x->size; ++idx) {
    frag_t dlo;
    frag_t dhi;
    frag_t xf = bignat_get_frag(x, idx);
    frag_mult(bignat_get_frag(x, idx), f, &dlo, &dhi);
    //printf(FRAG_FORMAT"*"FRAG_FORMAT" = "FRAG_FORMAT" "FRAG_FORMAT"\n", xf, f, dhi, dlo);
    bignat_add_frag_un(dest, dlo, idx+offs);
    bignat_add_frag_un(dest, dhi, idx+offs+1);
  }
}

bignat_t* bignat_normalize(bignat_t *x) {
  frag_t *f;

  // Normalize each fragment
  f = x->fragments;
  unsigned size = x->size;
  for (unsigned i = 0; i < size; ++i, ++f) {
    if (*f > FRAG_MAX) {
      frag_t high = *f / FRAG_CUTOFF;
      *f %= FRAG_CUTOFF;
      bignat_set_frag(x, i + 1, bignat_get_frag(x, i + 1) + high);
    }
  }

  // Cull leading zeros (for printing)
  f = x->fragments + x->size - 1;
  unsigned leading_zeros = 0;
  for (unsigned i = 0; i < x->size; ++i, --f) {
    if (*f != 0) break;
    ++leading_zeros;
  }
  x->size -= leading_zeros;
  return x;
}

bignat_t* bignat_copy(bignat_t *x) {
  bignat_t *c = bignat_new(x->size);
  c->size = x->size;
  memcpy(c->fragments, x->fragments, sizeof(frag_t) * x->size);
  return c;
}

size_t bignat_asprint(bignat_t *x, char **buff) {
  bignat_normalize(x);
  size_t size = (FRAG_DIGITS * x->size + 2) * sizeof(char);
  size_t count = 0;

  *buff = malloc(size);
  char *s = *buff;

  if (x->size > 0) {
    frag_t *f = x->fragments + x->size - 1;
    count += sprintf(s, "%u", *f);
    for (unsigned i = 0; i < x->size - 1; ++i) {
      --f;
      count += sprintf(s + count, FRAG_FORMAT, *f);
    }
  }
  else {
    s[count++] = '0';
  }
  s[count] = '\0';

  return count;
}

void bignat_print(bignat_t *x) {
  char *str = NULL;
  bignat_asprint(x, &str);
  puts(str);
  free(str);
}

bignat_t* bignat_dump(bignat_t *x) {
  printf("bignat_t(%d, ", x->size);
  frag_t *f = x->fragments + x->size - 1;
  for (unsigned i = 0; i < x->size; ++i, --f) {
    if (i == 0) {
      printf("%u", *f);
    }
    else {
      printf(" ");
      printf(FRAG_FORMAT, *f);
    }
  }
  puts(")");
  return x;
}

bignat_t* bignat_add(bignat_t *dest, bignat_t *x, bignat_t *y) {
  assert(dest != x && dest != y);
  unsigned maxsize = x->size > y->size ? x->size : y->size;
  bignat_reset(dest, maxsize);

  for (unsigned i = 0; i < maxsize; ++i) {
    bignat_set_frag(dest, i, bignat_get_frag(x, i) + bignat_get_frag(y, i));
  }

  bignat_normalize(dest);
  return dest;
}

bignat_t* bignat_mult(bignat_t *dest, bignat_t *x, bignat_t *y) {
  assert(dest != x && dest != y);

  bignat_reset(dest, x->size * y->size + 1);

  for (unsigned idx = 0; idx < x->size; ++idx) {
    bignat_madd_frag_un(dest, y, bignat_get_frag(x, idx), idx);
    bignat_normalize(dest);
  }
  return dest;
}

unsigned bignat_count_digits(bignat_t *x) {
  bignat_normalize(x);
  if (x->size > 0) {
    unsigned count = (x->size - 1) * FRAG_DIGITS;
    frag_t msf = bignat_get_frag(x, x->size-1);
    while (msf > 0) {
      ++count;
      msf /= 10;
    }
    return count;
  }
  else {
    return 1;
  }
}

unsigned bignat_get_digit(bignat_t *x, unsigned idx) {
  bignat_normalize(x);
  unsigned fi = idx / FRAG_DIGITS;
  unsigned di = idx % FRAG_DIGITS;
  frag_t f = bignat_get_frag(x, fi);
  while (di > 0) {
    f /= 10;
    --di;
  }
  return f % 10;
}

void bignat_swap(bignat_t *x, bignat_t *y) {
  bignat_t t;
  memcpy(&t, x, sizeof(bignat_t));
  memcpy(x,  y, sizeof(bignat_t));
  memcpy(y, &t, sizeof(bignat_t));
}
