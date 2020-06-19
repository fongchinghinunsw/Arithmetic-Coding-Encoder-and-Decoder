#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

typedef struct ac_table {
  int nchar;
  int *chars;
  mpfr_t portion_size;
  mpfr_t *low_range;
  mpfr_t *high_range;
} ac_table;

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDN;

  mpfr_t low, high, one;
  mpfr_init2(low, 256);
  mpfr_init2(high, 256);
  mpfr_init2(one, 256);
  mpfr_set_d(one, 1, rnd);

  // initialize the ac table.
  ac_table *table = calloc(1, sizeof(*table));
  table->chars = calloc(1024, sizeof(int));
  mpfr_init2(table->portion_size, 256);
  mpfr_set_d(table->portion_size, 0, rnd);

  int ch;
  while ((ch = getchar()) != EOF) {
    table->chars[ch]++;
    table->nchar++;
  }

  // get the size of one portion.
  // a portion is defined as 1/n when nchar is n.
  mpfr_t nchar;
  mpfr_init2(nchar, 256);
  mpfr_set_d(nchar, table->nchar, rnd);
  mpfr_div(table->portion_size, one, nchar, rnd);
  mpfr_out_str(stdout, 10, 0, table->portion_size, rnd);

  for (int i = 0; i < table->nchar; i++) {
    
  }

  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      printf("%c %d\n", i, table->chars[i]);
    }
  }
}
