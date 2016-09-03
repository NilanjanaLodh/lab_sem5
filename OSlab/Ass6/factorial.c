#include <stdio.h>
#include <stdlib.h>

long long int factorial(long long int n)
{
    if(n==0)
    return 1;

    return n * factorial(n-1);
}
int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    printf("factorial(%d) = %lld\n", n, factorial(n));fflush(stdout);
    exit(0);
}
