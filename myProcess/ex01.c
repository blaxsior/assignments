#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

void cleanupaction();

void main()
{
    pid_t pid;

    for(int i = 0; i < 3; i++)
    {
        printf("before fork [%d]\n", i);
        sleep(1);
    }

    pid = fork();

    if(pid > 0)
    {
        for(int i = 0; i < 7; i++)
        {
            printf("parent [%d]\n", i);
            sleep(1);
        }

        atexit(cleanupaction);
    }
    else if (pid == 0) {
        for(int i = 0 ; i < 5; i++)
        {
            printf("child [%d]\n", i);
            sleep(1);
            execl("/bin/ls", "ls", "-l", NULL);
        }
    }
    else {
        printf("fail to fork child process\n");
    }
    exit(EXIT_SUCCESS);
}

void cleanupaction(void)
{
    printf("clean-up-action\n");
}