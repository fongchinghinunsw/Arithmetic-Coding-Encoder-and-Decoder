#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <mpfr.h>
#include <math.h>

#include "ac_helper.h"

static void find_gap(ac_table *table, char *low_output, char *high_output);
int is_equal(char *num1, char *num2);

int main(void) {
  mpfr_rnd_t rnd = MPFR_RNDN;

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
  //printf("------------\n");

  // 2 extra space for "0." at the beginning.
  char low_output[MAX_ENCODE_LENGTH+2];
  char high_output[MAX_ENCODE_LENGTH+2];
  mpfr_sprintf(low_output, "%.2048Rf", low);
  mpfr_sprintf(high_output, "%.2048Rf", high);

  //mpfr_printf("%.150Rf\n", low);
  //mpfr_printf("%.150Rf\n", high);


  // save the value of low and high for future reference.
  mpfr_t tmp_low, tmp_high;
  mpfr_init2(tmp_low, precision);
  mpfr_init2(tmp_high, precision);
  mpfr_set(tmp_low, low, rnd);
  mpfr_set(tmp_high, high, rnd);

//printf("%d %d\n", mpfr_cmp(tmp_low, low), mpfr_cmp(high, tmp_high));

  //printf("--------------\n");
  int pos = 0;
  while (pos < MAX_ENCODE_LENGTH+2) {
    //printf("low = %c high = %c\n", low_output[pos], high_output[pos]);
    if (low_output[pos] != high_output[pos]) {
      //do {
	//mpfr_set(low, tmp_low, rnd);
	//mpfr_set(high, tmp_high, rnd);

	int prec = (int)ceil((pos-1)/log10(2))+1;
	//printf("!!! low = %c high = %c\n", low_output[pos], high_output[pos])
	//printf("pos = %d, prec = %d\n", pos, prec);
	mpfr_prec_round(low, prec, MPFR_RNDU);
	mpfr_prec_round(high, prec, MPFR_RNDD);

	mpfr_sprintf(low_output, "%.2048Rf", low);
	mpfr_sprintf(high_output, "%.2048Rf", high);
	low_output[pos+2] = '\0';
	high_output[pos+2] = '\0';

	//mpfr_printf("%.150Rf\n", low);
	//mpfr_printf("%.150Rf\n", high);

        pos++;
/*
        mpfr_clear(low);
        mpfr_clear(high);
	mpfr_init2(low, precision);
	mpfr_init2(high, precision);
*/

      //} while (is_equal(low_output, high_output));
      break;
    }
    pos++;
  }

  printf("%s ", low_output);
  printf("%s\n", high_output);
  //printf("--------------\n");
/*
  mpfr_printf("%.150Rf", low);
  printf(" ");
  mpfr_printf("%.150Rf", high);
  printf("\n");
*/
  return 0;
}

static void find_gap(ac_table *table, char *low_output, char *high_output) {

  int pos = 0;
  while (pos < table->nchar+2) {
    //printf("low = %c high = %c\n", low_output[pos], high_output[pos]);
    if (low_output[pos] != high_output[pos]) {
      break;
    }
    pos++;
  }
}

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
