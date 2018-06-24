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
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    #ifdef USE_MYMATH
        printf("now use my power\n");
        double result = power(base, exponent);
    #else
        printf("now use standard library \n");
        double result = pow(base,exponent);
    #endif
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}