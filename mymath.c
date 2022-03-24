#include <stdio.h>
#include <math.h>

void func(char *op[6])
{

    int i;

    for (i = 0; i < 6; ++i)

        printf("%c", *op[i]);
}

int main()
{

    int input = 0;

    float num = 0, num2 = 0;

    char add = '+';

    char sub = '-';

    char mul = '*';

    char div = '/';

    char por = '%';

    char exp = '^';

    char *op[6] = {&add, &sub, &mul, &div, &por, &exp};

    printf("Operand 번호를 입력하세요. >>\n");

    for (int i = 0; i < 6; i++)
    {

        if (i == 5)

        {

            printf("[^] : 5 >>");
        }

        else
        {

            printf("[%c] : %d,", *op[i], i);
        }
    }

    scanf("%d\n", &input);

    switch (input)
    {

    case 0:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

        printf("%f+%f= %f", num, num2, num + num2);
    }

    break;

    case 1:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

        printf("%f-%f= %f", num, num2, num - num2);
    }

    break;

    case 2:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

        printf("%f*%f= %f", num, num2, num * num2);
    }

    break;

    case 3:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

        printf("%f/%f= %f", num, num2, num / num2);
    }

    break;

    case 4:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

        printf("%f %% %f= %d", num, num2, (int)num % (int)num2);
    }

    break;

    case 5:

    {

        printf("실수 2개를 입력하세요. >>\n");

        scanf("%f %f", &num, &num2);

      //  printf("%f^%f= %f", num, num2, pow(num, num2));
    }

    break;

    default:

        break;
    }

    return 0;
}