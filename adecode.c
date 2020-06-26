#include "ac_helper.h"

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDF;
  ac_table *table = init_ac_table();
  char *space;

  char buffer[MAX_ENCODE_LENGTH];
  while ((fgets(buffer, 2048, stdin)) != NULL) {
    space = strrchr(buffer, ' ');
    *space = '\0';
    int ch = (unsigned char)buffer[0];
    int chars = atoi(space+1);
    if (chars != 0) {
      table->nchar = table->nchar + chars;
      table->chars[ch] = chars;
    }
  }

  //printf("---------\n");
  init_range(table);

  mpfr_t encoded_number;
  mpfr_init2(encoded_number, precision);
  mpfr_set_str(encoded_number, buffer, 10, rnd);

  mpfr_t code_range;
  mpfr_init2(code_range, precision);

  //print_range(table);

  for (int i = 0; i < table->nchar; i++) {
    for (int j = 0; j < 256; j++) {
      if (mpfr_cmp(encoded_number, table->low_range[j]) >= 0 &&
          mpfr_cmp(encoded_number, table->high_range[j]) < 0) {
        putchar(j);
/*
        mpfr_printf("\n%.2048Rf\n", table->low_range[j]);
        mpfr_printf("%.2049Rf\n", table->high_range[j]);
        mpfr_printf("%.2049Rf\n", encoded_number);
*/
        mpfr_sub(code_range, table->high_range[j], table->low_range[j], rnd);
        mpfr_sub(encoded_number, encoded_number, table->low_range[j], rnd);
        mpfr_div(encoded_number, encoded_number, code_range, rnd);

        break;
      }
    }
  }
}
