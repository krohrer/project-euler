#include "pskel.inc"

typedef struct row_s {
  unsigned columns;
  unsigned *values;
  struct row_s *next;
} row_t;

row_t *row_new(row_t *prev, unsigned cols) {
  row_t *r = malloc(sizeof(row_t));
  r->columns = cols;
  r->values = malloc(sizeof(unsigned)*cols);
  r->next = NULL;
  if (prev != NULL) {
    prev->next = r;
  }
  return r;
}

void row_delete(row_t *r) {
  if (r != NULL) {
    free(r->values);
    row_delete(r->next);
  }
}

void calculate_solution(void) {
  row_t *top = NULL;
  row_t *curr = NULL;

  FILE *f = fopen_or_die("p18.txt");
  {
    unsigned d;
    // First row is special
    curr = top = row_new(NULL, 1);
    if (fscanf(f, "%u", &d) == 0) die("Malformed input");
    top->values[0] = d;

    for (int r = 2; fscanf(f, "%u", &d) > 0; ++r) {
      curr = row_new(curr, r);
      curr->values[0] = d;
      for (int c = 2; c <= r; ++c) {
	if (fscanf(f, "%u", &d) == 0) die("Malformed input");
	curr->values[c-1] = d;
      }
    }
  }
  fclose(f);

  /*
  curr = top;
  while (curr != NULL) {
    for (int c = 1; c <= curr->columns; ++c) {
      printf("%u ", curr->values[c-1]);
    }
    puts("");
    curr = curr->next;
    }*/

  row_t *prevr = top;
  curr = prevr->next;
  do {
    int c = 0;
    curr->values[c] += prevr->values[c];
    for (c = 1; c < curr->columns-1; ++c) {
      int l = prevr->values[c-1];
      int r = prevr->values[c];
      curr->values[c] += (l > r ? l : r);
    }
    curr->values[c] += prevr->values[c-1];

    prevr = curr;
    curr = prevr->next;
  } while (curr != NULL);

  unsigned max = 0;
  for (int c = 0; c < prevr->columns; ++c) {
    unsigned v = prevr->values[c];
    if (v > max) max = v;
  }

  printf("Solution = %d\n", max);

  row_delete(top);
}

