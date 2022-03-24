#include <unistd.h> //close, access, link, symlink, readlink, W_OK
#include <fcntl.h>  //mode_t , open
#include <sys/types.h>
#include <sys/stat.h> // struct stat, umask, chmod, stat
#include <stdio.h>    //rename

int main()
{
    char *originalname = "test.txt";
    char *hardfilename = "test.txt.hard";
    char *softfilename = "test.txt.soft";

    int filedes, retval;
    mode_t oldmask;
    char buffer[1024];
    int nread;
    struct stat finfo;
    oldmask = umask(0377); //새로운 마스크로 변경 & 이전 마스크를 반환
    // r-------- 에 해당된다. 즉, 읽기만 가능
    printf("old mask %03o\n", oldmask);

    filedes = open(originalname, O_RDWR | O_CREAT, 0755); // 파일을 생성 rwxr-xr-x
    close(filedes);                                       //파일 닫기

    if ((retval = access(originalname, W_OK)) == -1)
    { //파일을 읽을 수 없다면
        printf("%s is not writable\n", originalname);
        chmod(originalname, 0644); // 파일의 모드를 변경. 실행 제외 가능해짐.
    }
    link(originalname, hardfilename); // 동일 파일을 가리키는 링크 형성. 이전 것과 구분이 없음.
    symlink(originalname, softfilename); // original을 가리키는 일종의 바로가기.

    rename(hardfilename, "newname.txt");
    nread = readlink(softfilename, buffer, 1024);
    write(1, buffer, nread);

    stat(originalname, &finfo);
    printf("\n%s\n", originalname);
    printf("File mode   : %o\n", finfo.st_mode);
    printf("Files size  : %ld\n", finfo.st_size);
    printf("Num of blocks  : %ld\n", finfo.st_blocks);
    return 0;
}
