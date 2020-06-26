#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <mpfr.h>

#include "ac_helper.h"

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDN;
  ac_table *table = init_ac_table();
  char *space;

  char buffer[MAX_ENCODE_LENGTH];
  while ((fgets(buffer, 2048, stdin)) != NULL) {
    //printf("%s\n", buffer);
    space = strrchr(buffer, ' ');
    *space = '\0';
    int ch = (unsigned char)buffer[0];
    int chars = atoi(space+1);
    if (chars != 0) {
      //printf("%c %d %d\n", ch, ch, chars);
      table->nchar = table->nchar + chars;
      table->chars[ch] = chars;
    }
  }

  //printf("---------\n");
  init_range(table);

  mpfr_t cur_bottom_line;
  mpfr_init2(cur_bottom_line, precision);
  mpfr_set_d(cur_bottom_line, 0, rnd);

  mpfr_t cur_whole_portion;
  mpfr_init2(cur_whole_portion, precision);
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      //printf("%c\n", i);
      mpfr_set(table->low_range[i], cur_bottom_line, rnd);
      mpfr_mul_si(cur_whole_portion, table->portion_size, table->chars[i], rnd);
      mpfr_add(cur_bottom_line, cur_bottom_line, cur_whole_portion, rnd);
      mpfr_set(table->high_range[i], cur_bottom_line, rnd);
    }
  }

  mpfr_t encoded_number;
  mpfr_init2(encoded_number, precision);
  mpfr_set_str(encoded_number, buffer, 10, rnd);

  mpfr_t code_range;
  mpfr_init2(code_range, precision);

  //print_range(table);
  /*
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      printf("%c ", i);
      mpfr_printf("%.20Rf", table->low_range[j]);
      mpfr
    }
  }
  */

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
