#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

/**
 * nchar: number of total characters
 * chars: appearance of each character. 
 * text: store the whole file's text
 * portion_size: 1/n where n == nchar
*/
typedef struct ac_table {
  int nchar;
  int *chars;
  int *text;
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
  table->nchar = 0;
  table->chars = calloc(256, sizeof(int));
  table->text = calloc(1024, sizeof(int));
  mpfr_init2(table->portion_size, 256);
  mpfr_set_d(table->portion_size, 0, rnd);
  table->low_range = calloc(256, sizeof(mpfr_t));
  table->high_range = calloc(256, sizeof(mpfr_t));

  int ch;
  while ((ch = getchar()) != EOF) {
    table->chars[ch]++;
    table->text[table->nchar] = ch;
    table->nchar++;
  }

  // get the size of one portion.
  // a portion is defined as 1/n when nchar is n.
  mpfr_t nchar;
  mpfr_init2(nchar, 256);
  mpfr_set_d(nchar, table->nchar, rnd);
  mpfr_div(table->portion_size, one, nchar, rnd);

  // compute low range and high range for each character.
  mpfr_t cur_bottom_line;
  mpfr_init2(cur_bottom_line, 256);
  mpfr_set_d(cur_bottom_line, 0, rnd);

  mpfr_t cur_whole_portion;
  mpfr_init2(cur_whole_portion, 256);
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      mpfr_init2(table->low_range[i], 256);
      mpfr_init2(table->high_range[i], 256);
      mpfr_set(table->low_range[i], cur_bottom_line, rnd);
      mpfr_mul_si(cur_whole_portion, table->portion_size, table->chars[i], rnd);
      mpfr_add(cur_bottom_line, cur_bottom_line, cur_whole_portion, rnd);
      mpfr_set(table->high_range[i], cur_bottom_line, rnd);
    }
  }

  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      mpfr_out_str(stdout, 10, 10, table->low_range[i], rnd);
      printf(" - ");
      mpfr_out_str(stdout, 10, 10, table->high_range[i], rnd);
      printf("\n\n");
    }
  }

  /*
  mpfr_t code_range;
  mpfr_init2(code_range, 256);
  for (int i = 0; i < table->nchar; i++) {
    mpfr_sub(code_range, table->high_range[table->chars[i]], table->low_range[table->chars[i]], rnd);
  }
  */
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      printf("%c %d\n", i, table->chars[i]);
    }
  }
}
