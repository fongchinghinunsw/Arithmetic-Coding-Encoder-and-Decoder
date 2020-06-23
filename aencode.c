#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

#include "ac_helper.h"

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDN;

  mpfr_t low, high;
  mpfr_init2(low, precision);
  mpfr_set_d(low, 0, rnd);
  mpfr_init2(high, precision);
  mpfr_set_d(high, 1, rnd);


  ac_table *table = init_ac_table();


  int ch;
  while ((ch = getchar()) != EOF) {
    table->chars[ch]++;
    table->text[table->nchar] = ch;
    table->nchar++;
  }

  init_range(table);
  print_frequency(table);

  // main encoding algorithm.
  mpfr_t code_range;
  mpfr_init2(code_range, precision);
  mpfr_t tmp;
  mpfr_init2(tmp, precision);
  for (int i = 0; i < table->nchar; i++) {
    mpfr_sub(code_range, high, low, rnd);

    mpfr_mul(tmp, code_range, table->high_range[table->text[i]], rnd);
    mpfr_add(high, low, tmp, rnd); 

    mpfr_mul(tmp, code_range, table->low_range[table->text[i]], rnd);
    mpfr_add(low, low, tmp, rnd);

  }

  mpfr_printf("%.10Rf", low);
  printf(" ");
  mpfr_printf("%.10Rf", high);
  printf("\n");

  return 0;
}
