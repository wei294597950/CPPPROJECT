#include <stdio.h>
#include <stdlib.h>
#include"math/power.h"
/**
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */

int main(int argc, char *argv[])
{
    /*if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);*/
	double base = 2.0;
	int exponent = 3;
    double result = power(base, exponent);
    printf("%g ^ %d is %g\n", base, exponent, result);
	getchar();
    return 0;
}