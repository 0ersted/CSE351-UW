#include <stdio.h>

int factorial (int n) {
       int i, product = 1;
          for(i = 0; i <= n; i++)
                    product *= i;
             return product;

}

int main (int argc,char *argv[]) {
       int n = 5;
          printf("factorial(%d) = %d\n",n,factorial(n));
             return 0;

}
