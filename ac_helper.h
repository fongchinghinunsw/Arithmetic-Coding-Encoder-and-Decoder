#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>

#define MAX_ENCODE_LENGTH 2048
#define precision 6805 // ceil(2048/log(2)) + 1, minimum number of bits required to round-trip every 2048-digit decimal floating-point number.

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
