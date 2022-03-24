#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>

void create_melong()
{
    int fp;
    fp = open("melong.txt", O_WRONLY|O_CREAT, 0600);
    const char* str = "sys melong!!";
    write(fp, str, strlen(str));
    close(fp);
}

int main(){
    create_melong();
}