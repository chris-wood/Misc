#include <stdio.h>
#include <time.h>
#include <gmp.h>

// copied from: http://comp.ist.utl.pt/ec-csc/Labs/sol-RSA/rsa2.c
void str2int(mpz_t ret, char *str, long int str_len) {
/* string to integer */
  long int i;
  unsigned char c;

  /* ret = 0 */
  mpz_set_ui(ret, 0UL);

  /* ret = str[str_len - 1] * BASE^(str_len - 1) + ... + str[1] * BASE + str[0] */
  for(i = str_len - 1; i >= 0; i--) {
    c = str[i];

    /* Horner's method */
    mpz_mul_ui(ret, ret, (unsigned long)BASE);
    mpz_add_ui(ret, ret, (unsigned long)c); }
}

int main(int argc, char **argv)
{
  int i, trials, mode, bit_size = 0;
  long elapsed = 0L;
  double secs = 0.0;
  mpz_t x,y,z,r;
  mpz_init(x); mpz_init(y); mpz_init(z); mpz_init(r);
  struct timespec ts, te;

  if (argc < 4)
  {
    printf("usage: mod_test mode bit_size <modulus> trials\n");
    return -1;
  }
  else
  {
    mode = atoi(argv[1]);
    bit_size = atoi(argv[2]);
    if (argc == 4) trials = atoi(argv[3]);
    else if (argc == 5) trials = atoi(argv[4]);
  }

  if (argc == 4)
  {
    mpz_init(r);
    mpz_random(r, bit_size);
    mpz_nextprime(r, r);
  }
  else if (argc == 5)
  {
    str2int(r, argv[3], strlen(argv[3]));
    printf("Initializing modulus to: %s\n", argv[3]);
    mpz_out_str(stdout, bit_size, r);
    printf("\n");
  }

  for (i = 0; i < trials; i++) 
  {
    mpz_init(x);
    mpz_init(y);
    mpz_init(z);

    // fill y/z randomly, and then generate the next 160-bit prime
    mpz_random(y, bit_size);
    mpz_random(z, bit_size);
  
    // Time the operation and add up the time
    if (mode == 0)
    {
      clock_gettime(CLOCK_MONOTONIC, &ts);
      mpz_mul(x, y, z);
      mpz_mod(x, x, r);
      clock_gettime(CLOCK_MONOTONIC, &te);
      secs = difftime(te.tv_sec, ts.tv_sec);
      elapsed += ((secs * 1.0e9) + ((double)(te.tv_nsec - ts.tv_nsec)));
    }
    if (mode == 1)
    {
      clock_gettime(CLOCK_MONOTONIC, &ts);
      mpz_mul(x, y, z);
      mpz_mod(x, x, r);
      clock_gettime(CLOCK_MONOTONIC, &te);
      secs = difftime(te.tv_sec, ts.tv_sec);
      elapsed += ((secs * 1.0e9) + ((double)(te.tv_nsec - ts.tv_nsec)));
    }
    else if (mode == 2)
    {
      clock_gettime(CLOCK_MONOTONIC, &ts);
      mpz_add(x, y, z);
      clock_gettime(CLOCK_MONOTONIC, &te);
      secs = difftime(te.tv_sec, ts.tv_sec);
      elapsed += ((secs * 1.0e9) + ((double)(te.tv_nsec - ts.tv_nsec)));
    }
  }

  printf("Trials:       %d\n", trials);
  printf("Total time:   %ld\n", elapsed);
  printf("Average time: %ld\n", elapsed / trials);

  // printf("x = (y * z) mod r = ");
  // mpz_out_str (stdout, 10, x);
  // printf (".\n");

  mpz_clear(x); mpz_clear(y); mpz_clear(z); mpz_clear(r);
  return 0;
}
