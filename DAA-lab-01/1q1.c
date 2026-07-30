#include <stdio.h>
#include <math.h>
#include <string.h>

struct Function {
    char name[50];
    double value;
};

int main() {
    double n = 100.0;
    struct Function funcs[11];
    struct Function temp;
    int i, j;

    strcpy(funcs[0].name, "log2(n)"); funcs[0].value = log2(n);
    strcpy(funcs[1].name, "12*sqrt(n)"); funcs[1].value = 12 * sqrt(n);
    strcpy(funcs[2].name, "50*n^0.5"); funcs[2].value = 50 * pow(n, 0.5);
    strcpy(funcs[3].name, "n^0.51"); funcs[3].value = pow(n, 0.51);
    strcpy(funcs[4].name, "2^32 * n"); funcs[4].value = pow(2, 32) * n;
    strcpy(funcs[5].name, "n*log2(n)"); funcs[5].value = n * log2(n);
    strcpy(funcs[6].name, "100n^2 + 6n"); funcs[6].value = 100 * pow(n, 2) + 6 * n;
    strcpy(funcs[7].name, "n^2 - 324"); funcs[7].value = pow(n, 2) - 324;
    strcpy(funcs[8].name, "2n^3"); funcs[8].value = 2 * pow(n, 3);
    strcpy(funcs[9].name, "n^log2(n)"); funcs[9].value = pow(n, log2(n));
    strcpy(funcs[10].name, "3^n"); funcs[10].value = pow(3, n);

    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10 - i; j++) {
            if(funcs[j].value > funcs[j+1].value) {
                temp = funcs[j];
                funcs[j] = funcs[j+1];
                funcs[j+1] = temp;
            }
        }
    }

    for(i = 0; i < 11; i++) {
        printf("%s\n", funcs[i].name);
    }

    return 0;
}