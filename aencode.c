#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <math.h>

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
  //printf("------------\n");

  char low_output[100];

  char high_output[100];
  mpfr_sprintf(low_output, "%.15Rf", low);
  mpfr_sprintf(high_output, "%.15Rf", high);

  mpfr_t tmp_low;
  mpfr_init2(tmp_low, precision);
  mpfr_t tmp_high;
  mpfr_init2(tmp_high, precision);
  
  for (int i = 0; i < 99; i++) {
    //printf("low = %c high = %c\n", low_output[i], high_output[i]);
    if (low_output[i] != high_output[i]) {
      int prec = (int)ceil((i-1)/log10(2))+1;
      //printf("i = %d, prec = %d\n", i, prec);
      mpfr_prec_round(low, prec, MPFR_RNDU);
      mpfr_prec_round(high, prec, MPFR_RNDD);
      break;
    }
  }
  //printf("%s\n", low_output);
  //printf("%s\n", high_output);
  //mpfr_prec_round(low, 25, MPFR_RNDU);
  //mpfr_prec_round(high, 25, MPFR_RNDD);
  
  mpfr_printf("%.20Rf", low);
  printf(" ");
  mpfr_printf("%.20Rf", high);
  printf("\n");
  
  return 0;
}
