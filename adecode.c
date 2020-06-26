#include "ac_helper.h"

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDF;
  ac_table *table = init_ac_table();
  char *space;

  int len = (MAX_ENCODE_LENGTH+2)*3;
  char buffer[len];
  while ((fgets(buffer, len, stdin)) != NULL) {
    //printf("!\n");
    space = strrchr(buffer, ' ');
    //printf("%s@", buffer);
    if (space == NULL) {
      break;
    }
    *space = '\0';
    int ch = (unsigned char)buffer[0];
    int chars = atoi(space+1);
    if (chars != 0 && space[2] != '.') {
      //printf("Hehehe\n");
      table->nchar = table->nchar + chars;
      table->chars[ch] = chars;
    }
  }

  init_range(table);

  mpfr_t encoded_number;
  mpfr_init2(encoded_number, precision);
  mpfr_set_str(encoded_number, buffer, 10, rnd);

  mpfr_t code_range;
  mpfr_init2(code_range, precision);
/*
  //printf("--------------\n");
  char num[2050];
  mpfr_sprintf(num, "%.2048Rf", encoded_number);
  printf("%s\n", num);
  print_range(table);
*/

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
