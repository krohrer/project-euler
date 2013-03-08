#include "pskel.inc"

#define FRAG_DIGITS	9
#define FRAG_FORMAT	"%09u"
#define FRAG_CUTOFF	(1000*1000*1000)
#define FRAG_MAX	(FRAG_CUTOFF-1)

typedef uint32_t frag_t;

void frag_mult(frag_t x, frag_t y, frag_t *low, frag_t *high) {
  uint64_t product = (uint64_t)x * (uint64_t)y;
  *low = product & (uint32_t)(-1);
  *high = product >> 32;
}

typedef struct bignat_s {
  unsigned size;
  unsigned capacity;
  frag_t *fragments;
} bignat;

bignat* bignat_new(unsigned cap) {
  bignat *x = malloc(sizeof(bignat));
  x->size = 0;
  x->capacity = cap > 0 ? cap : 2;
  x->fragments = malloc(sizeof(frag_t) * x->capacity);
  return x;
}

void bignat_delete(bignat *x) {
  free(x->fragments);
  free(x);
}

void bignat_reset(bignat *x, unsigned cap) {
  x->size = 0;
  if (cap > x->capacity) {
    x->capacity = cap;
    x->fragments = realloc(x->fragments, sizeof(frag_t) * x->capacity);
  }
}

frag_t bignat_get_frag(bignat *x, unsigned idx) {
  return idx < x->size ? x->fragments[idx] : 0;
}

void bignat_set_frag(bignat *x, unsigned idx, frag_t frag) {
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
}

void bignat_normalize(bignat *x) {
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
}

bignat *bignat_from_unsigned(unsigned i) {
  bignat *x = bignat_new(0);
  bignat_set_frag(x, 0, i);
  bignat_normalize(x);
  return x;
}

size_t bignat_asprint(bignat *x, char **buff) {
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

void bignat_print(bignat *x) {
  char *str = NULL;
  bignat_asprint(x, &str);
  puts(str);
  free(str);
}

void bignat_dump(bignat *x) {
  printf("bignat(%d, ", x->size);
  frag_t *f = x->fragments + x->size - 1;
  for (unsigned i = 0; i < x->size; ++i, --f) {
    if (i == 0) {
      printf("%u", *f);
    }
    else {
      printf(" ");
      printf("%09u", *f);
    }
  }
  puts(")");
}

void bignat_zero(bignat *x) {
  x->size = 0;
}

void bignat_add(bignat *dest, bignat *x, bignat *y) {
  assert(dest != x && dest != y);
  unsigned maxsize = x->size > y->size ? x->size : y->size;
  bignat_reset(dest, maxsize);

  for (int i = 0; i < maxsize; ++i) {
    bignat_set_frag(dest, i, bignat_get_frag(x, i) + bignat_get_frag(y, i));
  }

  bignat_normalize(dest);
}

void bignat_mult(bignat *dest, bignat *x, bignat *y) {
  assert(dest != x && dest != y);
  assert(false);
}

void calculate_solution(void) {
  bignat *x = bignat_new(0);
  bignat_set_frag(x, 10, 987654321);
  bignat_set_frag(x, 1, FRAG_MAX);
  bignat_set_frag(x, 0, FRAG_MAX);
  bignat_normalize(x);
  bignat *y = bignat_new(0);
  bignat_set_frag(y, 10, 12561);
  bignat_set_frag(y, 5, 1234123412);
  bignat_set_frag(y, 0, FRAG_MAX);
  bignat_normalize(y);

  bignat_print(x);
  bignat_print(y);
  bignat *r = bignat_new(0);
  bignat_add(r, x, y);
  bignat_print(r);

  bignat_delete(r);
  bignat_delete(y);
  bignat_delete(x);
}
