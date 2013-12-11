#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
  mpz_t x,y,z,r;
  mpz_init(x); mpz_init(y); mpz_init(z); mpz_init(r);

  if (argc != 5)
    {
      printf("SPECIFY TWO INTEGERS!\n");
      exit(1);
    }
  else
    {
      mpz_set_str(y,argv[2],10);
      mpz_set_str(z,argv[3],10);
      mpz_set_str(r,argv[4],10);
    }

  // printf("x = ");
  // mpz_out_str (stdout, 10, x);
  // printf (".\n");
  // printf("y = ");
  // mpz_out_str (stdout, 10, y);
  // printf (".\n");
  // printf("z = ");
  // mpz_out_str (stdout, 10, z);
  // printf (".\n");
  // printf("r = ");
  // mpz_out_str (stdout, 10, r);
  // printf (".\n");

  mpz_mul(x, y, z);
  mpz_mod(x, x, r);

  printf("x = (y * z) mod r = ");
  mpz_out_str (stdout, 10, x);
  printf (".\n");

  mpz_clear(x); mpz_clear(y); mpz_clear(z); mpz_clear(r);
  return 0;
}
