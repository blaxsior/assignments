#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
int main(){
    //2018112070 이희준 시소프 리눅스 시스템 프로그래밍 2
    int fp; // 파일 디스크립터
    int fp2; // 출력 파일을 위한 디스크립터
    fp = open("SRCFILE", O_RDONLY); // 파일을 읽기 전용으로 받음.
    fp2 = open("copyfile", O_WRONLY|O_CREAT, 0600); // 파일을 쓰기 전용으로 열되, 없으면 생성.
    char buffer[110];
    int count = 0;  // 읽어들인 문자의 수
    if(fp > 0 && fp2 > 0) // 둘 다 정상적으로 열렸다면
    {
        do {
            count = read(fp, buffer, 100); // 최대 100글자씩 buffer으로 읽어들인다.
            write(fp2, buffer, count); // buffer에 적힌 글자를 count 만큼 쓴다.
        } while(count > 0);
        close(fp);
        close(fp2); // 파일을 닫는다.
    }
    else {
        perror("Error"); // 에러를 출력한다.
    }
}