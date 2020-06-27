#include "ac_helper.h"

static void find_gap(mpfr_t *low, mpfr_t *high, char *low_output, char *high_output);
int is_equal(char *num1, char *num2);

mpfr_rnd_t rnd = MPFR_RNDF;

int main(void) {

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

  // 2 extra space for "0." at the beginning.
  char low_output[MAX_ENCODE_LENGTH+2];
  char high_output[MAX_ENCODE_LENGTH+2];
  mpfr_sprintf(low_output, "%.2048Rf", low);
  mpfr_sprintf(high_output, "%.2048Rf", high);

  find_gap(&low, &high, low_output, high_output);

  // print out the final result.
  printf("%s ", low_output);
  printf("%s\n", high_output);

  return 0;
}

/*
  Return the gap between two mpfr_t and save it into low_output and high_output.
*/
static void find_gap(mpfr_t *low, mpfr_t *high, char *low_output, char *high_output) {
  int pos = 2;
  while (pos < MAX_ENCODE_LENGTH) {
    if (low_output[pos] != high_output[pos]) {
      // number of digits required for round-trip conversionsa.
      int prec = (int)ceil((pos-1)/log10(2))+1;

      // round the mpfr_t without losing necessary precision.
      mpfr_prec_round(*low, prec, MPFR_RNDU);
      mpfr_prec_round(*high, prec, MPFR_RNDD);

      mpfr_sprintf(low_output, "%.2048Rf", *low);
      mpfr_sprintf(high_output, "%.2048Rf", *high);

      low_output[pos+2] = '\0';
      int lp = pos + 1;
      low_output[lp]++;
      while (lp > 3 && low_output[lp] == 58) { // '9' + 1 = 58
	low_output[lp] = '0';
	lp--;
	low_output[lp]++;
      }

      high_output[pos+2] = '\0';

      break;
    }
    pos++;
  }
}

/*
  Return true if two number strings are equal.
*/
int is_equal(char *num1, char *num2) {
  int i = 0;
  while (num1[i] != '\0') {
    if (num1[i] != num2[i]) {
      return 0;
    }
    i++;
  }
  return 1;
}
