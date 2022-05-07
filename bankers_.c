#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUSTOMERS 5
#define RESOURCES 4

#define BUFFER_SIZE 100

int available[RESOURCES] = {0};             // 현재 사용가능한 자원량
int maximum[CUSTOMERS][RESOURCES] = {0};    // 프로세스가 사용하는 최대 자원
int allocation[CUSTOMERS][RESOURCES] = {0}; // 현재 프로세스에게 할당된 자원
int need[CUSTOMERS][RESOURCES] = {0};       // 현재 필요환 자원

int req_resources(int c_num, int request[]);  // 자원 요청하기
void rel_resources(int c_num, int release[]); // 자원 요구하기
void printInfo();


int is_safe()
{
    int all_unavailable = 0; // 모든 프로세스가 동작 X
    int work[RESOURCES];     // 자원량
    for (int i = 0; i < RESOURCES; i++)
    {
        work[i] = available[i];
        printf("%d ", work[i]);
    } // work에 값 할당
    putchar('\n');
    int finish[CUSTOMERS] = {0}; // 해당 라인이 끝났는지 여부

    while (!all_unavailable) // 현재 프로세스들이 다 안되는건 아닐때
    {
        all_unavailable = 1; // 우선 다 안된다고 가정
        // printf("[finish] : ");
        // for (int i = 0; i < RESOURCES; i++)
        // {
        //     printf("%d ", finish[i]);
        // }
        // putchar('\n');

        for (int i = 0; i < CUSTOMERS; i++)
        {
            if (finish[i] == 0) // finish = false인 프로세스들
            {
                int cond = 1; // 현재 프로세스가 리소스를 얻을 수 있는지
                for (int j = 0; j < RESOURCES; j++) // 리소스 검사
                {
                    if (need[i][j] > work[j]) //자원 할당이 안되면
                    {
                        printf("할당 X %d\n",i);        
                        cond = 0;
                        break;
                        // 컨디션 바꾸고 break
                    }
                }
                if (cond)
                { //  자원 할당 되는 상태면
                    // 자원 반환
                    for (int j = 0; j < RESOURCES; j++)
                    { // 각각의 자원을 반환 ...
                        work[j] = work[j] + allocation[i][j];
                        printf("%d ", work[j]);
                    }
                    putchar('\n');

                    finish[i] = 1;       // finish[i] == true로
                    all_unavailable = 0; // 하나는 실행됨!
                }
            }
        }

        int end = 1; // 종료 조건 : 모두 종료됨

        for (int i = 0; i < CUSTOMERS; i++)
        {
            if (finish[i] == 0)
            {
                end = 0;
                break;
            }
        }

        if (end) // 종료조건 만족하는 경우
        {
            return 1; // true 반환
        }
    }

    return 0; // 모든 프로세스 자원 못먹고 무한 대기하는 상태.
}

int req_resources(int c_num, int request[])
{
    //(1)
    for (int i = 0; i < RESOURCES; i++)
    {
        if (request[i] > need[c_num][i]) // request <= need 인지 조건 검사
        {                                // 필요한 개수 이상으로 요구할 수는 없다.
            return -1;                   // 실패 의미로 -1 반환
        }
    }
    //(2)
    for (int i = 0; i < RESOURCES; i++)
    {
        if (request[i] > available[i]) // request <= available 인지 조건 검사
        {                              // 실제 가능한 자원 이상으로 제공할 수 없다.
            return -1;                 // 실패 의미로 -1 반환
        }
    }
    //(3)
    for (int i = 0; i < RESOURCES; i++)
    {
        available[i] = available[i] - request[i];                 // 사용 가능한 양에서 요구량 빼서
        allocation[c_num][i] = allocation[c_num][i] + request[i]; // 해당 프로세스에 할당하고
        need[c_num][i] = need[c_num][i] - request[i];             // 남은 필요 자원량 감소
    }
    int safety = is_safe();

    if (safety) // 바꾼 상태가 안전 상태라면
    {
        return 0; // 트랜잭션 그대로 수행
    }
    else
    { // 아니면 이전 상태로 되돌아가기.
        rel_resources(c_num, request);
        return -1;
    }
}

void rel_resources(int c_num, int release[])
{
    for (int i = 0; i < RESOURCES; i++)
    {
        if (release[i] > allocation[c_num][i]) // 할당량 이상을 요구하는지?
        {                                      // 할당된 양 이상을 반환할 수는 없음.
            return;                            // 할당량 이상을 요구하면 무시.
        }
    }
    // 자원할당 과정과 부호만 다름.
    for (int i = 0; i < RESOURCES; i++)
    {
        available[i] = available[i] + release[i];                 // 사용 가능 자원 증가.
        allocation[c_num][i] = allocation[c_num][i] - release[i]; // 할당되어 있던 자원 제거.
        need[c_num][i] = need[c_num][i] + release[i];             // 남은 필요 자원량 추가.
    }
}

void printInfo()
{
    printf("[available]\n");
    for (int i = 0; i < RESOURCES; i++)
    {
        printf("R%d : %d\n", i, available[i]);
    }

    printf("[maximum]\n");
    for (int i = 0; i < CUSTOMERS; i++)
    {
        printf("C%d : ", i);

        for (int j = 0; j < RESOURCES; j++)
        {
            printf("%d ", maximum[i][j]);
        }

        putchar('\n');
    }

    printf("[allocation]\n");
    for (int i = 0; i < CUSTOMERS; i++)
    {
        printf("C%d : ", i);

        for (int j = 0; j < RESOURCES; j++)
        {
            printf("%d ", allocation[i][j]);
        }

        putchar('\n');
    }

    printf("[need]\n");
    for (int i = 0; i < CUSTOMERS; i++)
    {
        printf("C%d : ", i);

        for (int j = 0; j < RESOURCES; j++)
        {
            printf("%d ", need[i][j]);
        }

        putchar('\n');
    }
}

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        // 기본 경로 1 + 인자 개수 4
        printf("인자의 개수가 부족합니다\n");
        return 0;
    }

    // available 배열에 할당
    for (int i = 1; i < 5; i++)
    {
        printf("%s ", argv[i]);
        available[i - 1] = atoi(argv[i]);
    }

    int arr[] = {
        6, 4, 7, 3,
        4, 2, 3, 2,
        2, 5, 3, 3,
        6, 3, 3, 2,
        5, 6, 7, 5};

    // max number에 arr 내의 값 할당
    for (int i = 0; i < RESOURCES * CUSTOMERS; i++)
    {
        int c_idx = i / RESOURCES;                                             // customer 인덱스
        int r_idx = i % RESOURCES;                                             // 리소스 인덱스
        maximum[c_idx][r_idx] = arr[i];                                        // maximum 배열 초기화
        need[c_idx][r_idx] = maximum[c_idx][r_idx] - allocation[c_idx][r_idx]; // need 배열 초기화
    }

    char buffer[BUFFER_SIZE];

    printf("Banker's Algorithm! \n");

    while (1)
    {
        printf("input > ");
        fgets(buffer, BUFFER_SIZE, stdin);   // 문자 읽기
        buffer[strcspn(buffer, "\r\n")] = 0; // 개행 제거

        if (strlen(buffer) == 0) // 공백이라면
        {
            continue; // 다시 실행.
        }

        char *token = strtok(buffer, " "); // 공백 기준으로 문자 제거

        // 모든 자료구조 내용 출력
        if (strcmp(token, "*") == 0)
        {
            printInfo();
            continue;
        }
        else if (strcmp(token, "q") == 0) // quit 이면
        {
            printf("bye!\n");
            return 0; // 종료
        }
        // request인 경우

        int cond = 0; // 이후 토큰을 가져올지 여부

        if (strcmp(token, "RQ") == 0)
        {
            cond = 1; // request 의미
        }
        else if (strcmp(token, "RL") == 0)
        {
            cond = 2; // release 의미
        }

        if (cond > 0) // 이후 토큰을 가져온다.
        {
            int params[5] = {0}; // 임시 인자를 담는 공간.

            // 총 5개의 숫자를 가져와야 함. 5개가 안되면 에러 상황. 에러 메시지 출력하고 끝
            for (int i = 0; i < 5; i++)
            {
                token = strtok(NULL, " ");
                if (token == NULL) // 텅빈 토큰이면 에러상황
                {
                    printf("전달된 인자의 수가 적습니다.\n");
                    cond = -1; // 에러 상황을 의미
                    break;
                }
                params[i] = atoi(token);
            }

            if (cond == 1) // request 상황
            {
                int result = req_resources(params[0], params + 1);
                printf("%s\n", result == 0 ? "OK" : "NO");
            }
            else if (cond == 2)
            {
                rel_resources(params[0], params + 1);
            }
        }
    }
}