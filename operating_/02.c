#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid; // 자식 프로세스
    pid_t pid1; // 자신 프로세스
    // 부모 : 2600
    // 자식 2603

    pid = fork(); // 0 또는 자식 프로세스의 pid

    if (pid < 0)
    { // 에러 발생한다!
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) // 자식의 경우. child는 없고, 자신은 2603
    { 
        pid1 = getpid();
        printf("child: pid = %d\n", pid);   /* 0 */
        printf("child: pid1 = %d\n", pid1); /* 2603 */
    }
    else // 부모의 경우. 자식은 2603, 자신은 2600
    {
        pid1 = getpid();
        printf("parent: pid = %d\n", pid);   /* 2603 */
        printf("parent: pid1 = %d\n", pid1); /* 2600 */
        wait(NULL);
    }
    return 0;
}
