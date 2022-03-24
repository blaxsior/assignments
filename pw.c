#include <stdio.h> 
#include <sys/types.h>//pid가 정의되어 있다.
#include <sys/wait.h> //wait
#include <unistd.h> //sleep,fork, exit
#include <stdlib.h>

int main() { 
    pid_t pid; //현재 프로세스의 id
    int status;  // status 정보

/*
    fork 사용시, 부모 프로세스는 자식 프로세스의 주소를, 자식 프로세스는 0을 pid로 가진다.
    만약 fork에 실패한다면, pid < 0이 된다.
    fork는 현재 코드 진행 분기를 기점으로 현재 프로세스를 복제하여 자식 프로세스를 생성하는 과정이다.
*/
    pid = fork(); 
    if(pid > 0) {		/* 부모 프로세스 */ 
        printf("parent: waiting..\n"); 
        wait(&status); 
        printf("exited %d\n",WIFEXITED(status));
        printf("parent: status is %d\n", status); 
    } 
    else if(pid == 0) {	/* 자식 프로세스 */
        sleep(1); // 1초 대기
        printf("child: bye!\n"); 
        exit(1108); 
    } 
    else 
        printf("fail to fork\n"); 

    printf("bye!\n"); 
    return 0;
}
