#include <stdio.h>

int main() {
    int a = 10 + 20;
    int b = 20 - 35;

    if(a == 10) {
        printf("cannot reach!");
    } else {
        printf("can reach!");
    }

    if(a != 10) {
        printf("can reach b !");
    } else {
        printf("cannot reach!");
    }

    return 0;
}