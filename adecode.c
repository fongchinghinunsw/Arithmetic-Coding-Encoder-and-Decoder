#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <mpfr.h>

#include "ac_helper.h"

int main(void) {
  ac_table *table = init_ac_table();
  char *space;
  char buffer[2048];
  while ((fgets(buffer, 2048, stdin)) != NULL) {
    space = strrchr(buffer, ' ');
    *space = '\0';
    int ch = (int)(buffer[0]);
    int chars = atoi(space+1);
    if (chars != 0) {
      table->nchar = table->nchar + chars;
      table->chars[ch] = chars;
    }
  }
  init_range(table);

  mpfr_rnd_t rnd = MPFR_RNDN;
  mpfr_t encoded_number;
  mpfr_init2(encoded_number, precision);
  mpfr_set_str(encoded_number, buffer, 10, rnd);

  mpfr_t code_range;
  mpfr_init2(code_range, precision);

  for (int i = 0; i < table->nchar; i++) {
    for (int j = 0; j < 256; j++) {
      if (mpfr_cmp(encoded_number, table->low_range[j]) >= 0 &&
          mpfr_cmp(encoded_number, table->high_range[j]) < 0) {
        putchar(j);
        //printf(" ");
        //mpfr_printf("%.10Rf", table->low_range[j]);
	//mpfr_out_str(stdout, 10, 5, table->low_range[i], rnd);
        //printf(" ");
        //mpfr_printf("%.10Rf", table->high_range[j]);
	//mpfr_out_str(stdout, 10, 5, table->high_range[i], rnd);
        //printf(" ");
        //mpfr_printf("%.50Rf", encoded_number);
	//mpfr_out_str(stdout, 10, 5, encoded_number, rnd);
        //printf("\n");

        mpfr_sub(code_range, table->high_range[j], table->low_range[j], rnd);
        mpfr_sub(encoded_number, encoded_number, table->low_range[j], rnd);
        mpfr_div(encoded_number, encoded_number, code_range, rnd);

        break;
      }
    }
  }

}
