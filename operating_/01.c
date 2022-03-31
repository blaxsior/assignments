#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t t;   // 0 이면 자기 자신, 숫자면 부모!
    pid_t t2;
    pid_t parent;
    for(int i = 0; i < 4; i++)
    {
        t = fork();
        t2 = getpid();
        parent = getppid();

        printf("[%d] child : %d, current :%d, parent: %d\n", i, t, t2, parent);
        // 0 이면 자기 자신, 숫자면 부모!
    }
    return 0;
}