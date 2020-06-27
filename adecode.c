#include "ac_helper.h"

mpfr_rnd_t rnd = MPFR_RNDF;

int main(void) {
  ac_table *table = init_ac_table();
  char *space;

  int len = MAX_ENCODE_LENGTH * 3; // allocate ENOUGH space
  char buffer[len];
  while ((fgets(buffer, len, stdin)) != NULL) {
    // get the start point of the frequency.
    space = strrchr(buffer, ' ');
    // finished reading the whole character frequency table.
    if (space == NULL) {
      break;
    }
    *space = '\0';
    int ch = (unsigned char)buffer[0];
    int chars = atoi(space+1);
    // prevent matching the encoded number.
    if ((unsigned char)buffer[1] != '.') {
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
  mpfr_set_d(code_range, 0, rnd);

  // main decoding algorithm.
  for (int i = 0; i < table->nchar; i++) {
    for (int j = 0; j < 256; j++) {
      if (mpfr_cmp(encoded_number, table->low_range[j]) >= 0 &&
          mpfr_cmp(encoded_number, table->high_range[j]) < 0) {
        putchar(j);

        mpfr_sub(code_range, table->high_range[j], table->low_range[j], rnd);
        mpfr_sub(encoded_number, encoded_number, table->low_range[j], rnd);
        mpfr_div(encoded_number, encoded_number, code_range, rnd);

        break;
      }
    }
  }
}
