#include "ac_helper.h"

ac_table *init_ac_table() {
  mpfr_rnd_t rnd = MPFR_RNDF;
  // initialize the ac table.
  ac_table *table = calloc(1, sizeof(*table));
  table->nchar = 0;
  table->chars = calloc(256, sizeof(int));
  table->text = calloc(precision, sizeof(int));
  mpfr_init2(table->portion_size, precision);
  mpfr_set_d(table->portion_size, 0, rnd);
  table->low_range = calloc(256, sizeof(mpfr_t));
  table->high_range = calloc(256, sizeof(mpfr_t));
  for (int i = 0; i < 256; i++) {
    mpfr_init2(table->low_range[i], precision);
  }
  for (int i = 0; i < 256; i++) {
    mpfr_init2(table->high_range[i], precision);
  }

  return table;
}

void init_range(ac_table *table) {
  
  mpfr_rnd_t rnd = MPFR_RNDF;
  mpfr_t one;
  mpfr_init2(one, precision);
  mpfr_set_d(one, 1, rnd);

  // get the size of one portion.
  // a portion is defined as 1/n when nchar is n.
  mpfr_t nchar;
  mpfr_init2(nchar, precision);
  mpfr_set_d(nchar, table->nchar, rnd);
  mpfr_div(table->portion_size, one, nchar, rnd);

  // compute low range and high range for each character.
  mpfr_t cur_bottom_line;
  mpfr_init2(cur_bottom_line, precision);
  mpfr_set_d(cur_bottom_line, 0, rnd);

  mpfr_t cur_whole_portion;
  mpfr_init2(cur_whole_portion, precision);
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      mpfr_set(table->low_range[i], cur_bottom_line, rnd);
      mpfr_mul_si(cur_whole_portion, table->portion_size, table->chars[i], rnd);
      mpfr_add(cur_bottom_line, cur_bottom_line, cur_whole_portion, rnd);
      mpfr_set(table->high_range[i], cur_bottom_line, rnd);
    }
  }
}

void print_range(ac_table *table) {
  mpfr_rnd_t rnd = MPFR_RNDF;
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      printf("%c %d ", i, table->chars[i]);
      mpfr_out_str(stdout, 10, 5, table->low_range[i], rnd);
      printf(" - ");
      mpfr_out_str(stdout, 10, 5, table->high_range[i], rnd);
      printf("\n");
    }
  }
}

void print_frequency(ac_table *table) {
  for (int i = 0; i < 256; i++) {
    if (table->chars[i] != 0) {
      printf("%c %d\n", i, table->chars[i]);
    }
  }
}
