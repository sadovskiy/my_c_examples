#include <stdio.h>
#include <math.h>

int main()
{
    int n = pow(2, 5);
    int m = 1;

//    int i = 0;
//    while (i < 5) {
//        m *= 2;
//        i++;
//    }

    for (int var = 0; var < 5; ++var) {
        m *= 2;
    }

    printf("%d\n", n);
    printf("%d\n", m);

    return 0;
}
