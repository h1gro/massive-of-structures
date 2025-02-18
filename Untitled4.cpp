#include <TXLib.h>
#include <stdio.h>
#include <math.h>

#define NO_ROOTS 0
#define ONE_ROOT 1
#define TWO_ROOTS 2
#define INFINITY_ROOTS 3
#define TEST_DONE 4
#define TEST_FAILED 5
#define DIFFERENCE 1e-4
#define ALL_TESTS_DONE 6
#define INCORRECT_TEST 7

struct Str_for_tester
{
    double a, b, c;
    double x1exp, x2exp;
    int nRootsExp;
}str_test;

int SolveSquare ( double a, double b, double c, double* x1, double* x2);
void clrbuf();
int Tests_Check();
int diff(double elem1, double elem2);
int tester(struct Str_for_tester str_test, int nTest);

int SolveSquare ( double a, double b, double c, double* x1, double* x2)
{
        double D = 0;
        D = b * b - 4 * a * c;
        if ( !diff(a, 0) )
        {
            if ( !diff(b, 0) )
            {
                if ( !diff(c, 0) )
                {
                    return INFINITY_ROOTS;
                }
                else
                {
                    return NO_ROOTS;
                }
            }
            else
            {
                *x1 = -c / b;
                return ONE_ROOT;
            }
        }
        else
        {
            if (D >= 0)
            {
                *x1 = (-b + sqrt(D)) / (2 * a);
                *x2 = (-b - sqrt(D)) / (2 * a);
                if ( *x1 == *x2 )
                {
                    return ONE_ROOT;
                }
                else
                {
                    return TWO_ROOTS;
                }

            }
            else
            {
                return NO_ROOTS;
            }
        }
}

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    int identificator = Tests_Check();

    if (identificator == ALL_TESTS_DONE)
    {
        while (scanf("%lg %lg %lg", &a, &b, &c) != 3)
        {
            printf("wrong input");
            clrbuf();
        }
        int nRoots = SolveSquare (a, b, c, &x1, &x2);

        //txSetConsoleAttr (0x4E);
        switch(nRoots)
        {
            case NO_ROOTS:       printf("no roots\n");
                                 break;

            case ONE_ROOT:       printf("%lg\n", x1);
                                 break;

            case TWO_ROOTS:      printf("%lg %lg\n", x1, x2);
                                 break;

            case INFINITY_ROOTS: printf("any number");
                                 break;

        }
        //txSetConsoleAttr (0x07);
    }

}

void clrbuf()
{

    //printf("����� � �������");
    int ch = getchar();
    while (ch != EOF && ch != '\n' )
    {
        //printf("� ������� ������, (%c), %d\n", ch, ch);
        ch = getchar();
    }
    //printf("����� �� �������");
}

int tester(struct Str_for_tester str_test, int nTest)
{
    //printf("� ����� � �������\n");
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    printf("%d: a = %lg, b = %lg, c = %lg\n", __LINE__, str_test.a, str_test.b, str_test.c);

    int nRoots = SolveSquare(str_test.a, str_test.b, str_test.c, &x1, &x2);

    printf("%d: a = %lg, b = %lg, c = %lg\n", __LINE__, str_test.a, str_test.b, str_test.c);

    if (nRoots != str_test.nRootsExp || diff(x1, str_test.x1exp) || diff(x2, str_test.x2exp))
    {
        printf("%d: a = %lg, b = %lg, c = %lg\n", __LINE__, str_test.a, str_test.b, str_test.c);

        printf("\n" "error test = %d, a = %lg, b = %lg, c = %lg\n"
               " x1 = %lg, x2 = %lg, nRoots = %d\n"
               "expected, x1exp = %lg, x2exp = %lg, nRootsExp = %d\n"
               "x1-x1exp = %lg, x2-x2exp= %lg\n\n",
               nTest, str_test.a, str_test.b, str_test.c,
               x1, x2, nRoots,
               str_test.x1exp, str_test.x2exp, str_test.nRootsExp,
               x1-str_test.x1exp, x2-str_test.x2exp);

        return TEST_FAILED;
    }
    else
    {
        //txSetConsoleAttr (0x4E);

        printf("Successfully\n");

        //txSetConsoleAttr (0x07);

        return TEST_DONE;
    }

}

int Tests_Check()
{
    struct Str_for_tester tests[] = {{0, 1, -2, 2, 0, 1},
                                     {0, 0, 0, 0, 0, 3},
                                     {0, 1, -2, 2, 0, 1},
                                     {0, 0, -1243, 0, 0, 0},
                                     {0, 65, 0, 0, 0, 1},
                                     {1, 2, -3, 1, -3, 2},
                                     {1, 2, 3, 0, 0, 0},
                                     {1.33, -2.6, -7.5, 3.54542, -1.59053, 2},
                                     {0.09, 69.96, -1.87, 0.0267286, -777.36, 2},
                                     {1, 2, 1, -1, -1, 1}};

    //printf("%d %d\n", sizeof mass, sizeof mass[0]);
    for (int i = 0; i < (sizeof tests)/(sizeof tests[0]); i++)
    {
        int check = 0;
        //printf("%d\n", i);
        int nTest = i;
        check = tester( tests[ i ], nTest);
        if ( check == TEST_FAILED)
        {
            return INCORRECT_TEST;
        }
    }
    return ALL_TESTS_DONE;
}

int diff(double elem1, double elem2)
{


    if (fabs(elem1 - elem2) >= DIFFERENCE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


