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

void pr(int arr[])
{
    printf("%d", arr[0]);
}

int main(){
    // create_melong();
    int arr[] = {1,2,3,4,5};
    pr(arr);
    pr((arr + 1));
}