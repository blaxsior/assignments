#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep

int main()
{
    pid_t t; // 부모 자식 식별 용도.

    t = fork();

    if (t > 0) { // 부모 프로세스라면,
        sleep(100);
        printf("parent is dead ...\n");
        exit(0); // 100초 후 탈출. 하지만 kill로 죽일 예정
    }
    else if (t == 0) { // 자식 프로세스라면,
        printf("child is dead ...\n");
        exit(0);
    }
    else { // 에러
        perror("Error accured!");
    }
}
