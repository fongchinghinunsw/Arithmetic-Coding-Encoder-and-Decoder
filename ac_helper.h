#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

#define precision 100

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


ac_table *init_ac_table();

// init the range for each character.
void init_range(ac_table *);

// print range for each character.
void print_range(ac_table *);

// print frequency for each character.
void print_frequency(ac_table *);
