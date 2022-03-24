#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

/*
stat : 파일 있는지 여부 조사 
: https://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call
write : 파일 쓰기 
: https://man7.org/linux/man-pages/man2/write.2.html
open : 파일 열기
close : 파일 닫기
argv[0] : 파일 실행 경로
argv[1] : 정보 가져올 파일
argv[2] : 정보 붙여넣을 파일
*/
// by write, read, open, close, stat

int getLength(const char str[])
{
    int count = 0;
    while (str[count++] != '\0')
        ;
    return count;
}

int main(int argc, char *argv[])
{
    struct stat st;
    struct stat dest;
    if (argc < 3) //인수가 제대로 전달되지 않았다면
    {
        char err_message[] = "Give More Info!\n";
        write(STDOUT_FILENO, err_message, 17); // 에러 메시지 출력
        _exit(1);                              // 탈출
    }

    const char *from = argv[1];
    const char *to = argv[2];

    if (stat(from, &st) == 0 && (S_ISREG(st.st_mode) || S_ISLNK(st.st_mode))) // 파일이 있다면
    {
        if (stat(to, &dest) != 0) // 파일이 없다면
        {

            int fd_src = open(from, O_RDONLY);     // 소스 파일 오픈
            int fd_dest = open(to, O_CREAT, 0666); // 대상 파일 오픈
            char buf[256];                         // 버퍼의 값을 0으로 초기화
            size_t read_len = 0;

            if (fd_src <= 0 || fd_dest <= 0) // 파일을 제대로 열 수 없는 경우
            {
                char err_message[] = "Cannot open file (src or dest)!\n";
                write(STDOUT_FILENO, err_message, 33); // 에러 메시지 출력
                _exit(1);                              // 탈출
            }

            do
            {
                read_len = read(fd_src, buf, 256);
                write(fd_dest, buf, read_len);
            } while (read_len > 0); // 파일을 끝까지 읽고 쓴다.
            close(fd_src);
            close(fd_dest);
        }
        else // 해당 이름의 파일이 이미 있을 때
        {
            char err_message[] = "Destination file is already exist!\n";
            write(STDOUT_FILENO, err_message, 36); // 에러 메시지 출력
            _exit(1);                              // 탈출
        }
    }
    else
    {
        char err_message[] = "Cannot open the source file!\n";
        write(STDOUT_FILENO, err_message, 30); // 에러 메시지 출력
        _exit(1);                              // 나가기
    }                                        

    return 0;
}