#include <stdio.h>
#include <stdlib.h>
#include"config.h"
/**
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */
#ifdef USE_MYMATH
    #include"math/power.h"
#else
    #include<math.h>
#endif
int main(int argc, char *argv[])
{
    /*if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
<<<<<<< HEAD
    int exponent = atoi(argv[2]);
    #ifdef USE_MYMATH
        printf("now use my power\n");
        double result = power(base, exponent);
    #else
        printf("now use standard library \n");
        double result = pow(base,exponent);
    #endif
=======
    int exponent = atoi(argv[2]);*/
	double base = 2.0;
	int exponent = 3;
    double result = power(base, exponent);
>>>>>>> 6e3a3d0cd9770a57a81e3d63cd47c58170dceaec
    printf("%g ^ %d is %g\n", base, exponent, result);
	getchar();
    return 0;
}