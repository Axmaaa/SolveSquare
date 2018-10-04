/**
    \file
    \brief Solves square equation

    Solves square equation \f$ ax^2 + bx + c = 0 \f$ and prints roots.

    \return A_INFINITE if a is infinite
    \return B_INFINITE if b is infinite
    \return C_INFINITE if c is infinite
    \return ROOT_1_NULL_PTR if the 1st root pointer is NULL
    \return ROOT_2_NULL_PTR if the 2nd root pointer is NULL
    \return ROOT_1_INFINITE if the 1st root is infinite
    \return ROOT_2_INFINITE if the 2nd root is infinite
    \return DISCR_INFINITE if the discriminant is infinite
    \return UNKNOWN_ERROR else
*/

#include <iostream>
#include <stdlib.h>
#include <cmath>

#define N_ROOTS_INFINITE -1
#define UNKNOWN_ERROR     3
#define A_INFINITE        4
#define B_INFINITE        5
#define C_INFINITE        6
#define ROOT_1_NULL_PTR   7
#define ROOT_2_NULL_PTR   8
#define ROOT_1_INFINITE   9
#define ROOT_2_INFINITE  10
#define DISCR_INFINITE   11
#define N_TESTS           3


/**
    \brief Solves linear equation

    Solves linear equation \f$ bx + c = 0\f$.
    If there is 1 root, records root value at pointer x.

    \param[in] b coefficient at \f$ x \f$
    \param[in] c free coefficient
    \param[out] x root pointer

    \return Number of linear equation's roots,
    \return -1 if it has infinite number of roots.
    \return B_INFINITE if b is infinite
    \return C_INFINITE if c is infinite
    \return ROOT_1_NULL_PTR if the 1st root pointer is NULL
    \return UNKNOWN_ERROR else
*/
int SolveLine(double b, double c, double * x);


/**
    \brief Solves square equation

    Solves square equation \f$ ax^2 + bx + c = 0 \f$ .
    If there are 2 roots, records root values at pointers x1 and x2,
    if there is 1 root, record root value at pointer x1.

    \param[in] a coefficient at \f$ x^2 \f$
    \param[in] b coefficient at \f$ x \f$
    \param[in] c free coefficient
    \param[out] x1 1st root pointer
    \param[out] x2 2nd root pointer

    \return Number of square equation's roots
    \return -1 if it has infinite number of roots
    \return A_INFINITE if a is infinite
    \return B_INFINITE if b is infinite
    \return C_INFINITE if c is infinite
    \return ROOT_1_NULL_PTR if the 1st root pointer is NULL
    \return ROOT_2_NULL_PTR if the 2nd root pointer is NULL
    \return DISCR_INFINITE if the discriminant is infinite
    \return UNKNOWN_ERROR else
*/
int SolveSquare(double a, double b, double c, double * x1, double * x2);


/**
    \brief Tests program

    Tests program with preset values

    \return If all test were passed 1, else 0
*/
int Test();

int main()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int nRoots = UNKNOWN_ERROR;

    fprintf(stdout, "Solve square equation a * x^2 + b * x + c = 0\n");
    fprintf(stdout, "Input a, b and c: ");
    int scret = scanf("%lg%lg%lg", &a, &b, &c);
    while (scret == EOF || scret == 0 || scret == 1 || scret == 2)
    {
        while (getchar() != '\n');
        fprintf(stderr, "You inputed something deadbeef, try again\n");
        scret = scanf("%lg%lg%lg", &a, &b, &c);
    }

    nRoots = SolveSquare(a, b, c, &x1, &x2);
    switch (nRoots)
    {
    case N_ROOTS_INFINITE:
        fprintf(stdout, "The equation has an infinite number of roots\n");
        break;
    case 0:
        fprintf(stdout, "The equation has no roots\n");
        break;
    case 1:
        if (std::isfinite(x1) == 0)
        {
            fprintf(stderr, "x1 is infinite\n");
            return ROOT_1_INFINITE;
        }
        fprintf(stdout, "The equation has 1 root: x = %lg\n", x1);
        break;
    case 2:
        if (std::isfinite(x1) == 0)
        {
            fprintf(stderr, "x1 is infinite\n");
            return ROOT_1_INFINITE;
        }
        if (std::isfinite(x2) == 0)
        {
            fprintf(stderr, "x1 is infinite\n");
            return ROOT_2_INFINITE;
        }
        fprintf(stdout, "The equation has 2 roots: x1 = %lg, x2 = %lg\n", x1, x2);
        break;
    case A_INFINITE:
        fprintf(stderr, "a is infinite\n");
        return A_INFINITE;
    case B_INFINITE:
        fprintf(stderr, "b is infinite\n");
        return B_INFINITE;
    case C_INFINITE:
        fprintf(stderr, "c is infinite\n");
        return C_INFINITE;
    case ROOT_1_NULL_PTR:
        fprintf(stderr, "&x1 = nil\n");
        return ROOT_1_NULL_PTR;
    case ROOT_2_NULL_PTR:
        fprintf(stderr, "&x2 = nil\n");
        return ROOT_2_NULL_PTR;
    case DISCR_INFINITE:
        fprintf(stderr, "Discriminant is infinite\n");
        return DISCR_INFINITE;
    case UNKNOWN_ERROR:
        fprintf(stderr, "Unknown error was happened\n");
    default:
        fprintf(stdout, "Something strange was happend:"
                        "SolveSquare returned %d, "
                        "I have roots (%lg and %lg)"
                        "with a = %lg, b = %lg and c = %lg\n", nRoots, x1, x2, a, b, c);
        break;
    }

    puts("");
    Test();

    return 0;
}


int SolveSquare(double a, double b, double c, double * x1, double * x2)
{
    if (std::isfinite(a) == 0)
    {
        return A_INFINITE;
    }
    if (std::isfinite(b) == 0)
    {
        return B_INFINITE;
    }
    if (std::isfinite(c) == 0)
    {
        return C_INFINITE;
    }
    if (x1 == NULL)
    {
        return ROOT_1_NULL_PTR;
    }
    if (x2 == NULL)
    {
        return ROOT_2_NULL_PTR;
    }

    if (a == 0)
        return SolveLine(b, c, x1);

    double discr = b * b - 4 * a * c;
    if (std::isfinite(discr) == 0)
    {
        return (DISCR_INFINITE);
    }
    if (discr < 0)
        return 0;
    if (discr == 0)
    {
        *x1 = -b / (2 * a);
        return 1;
    }
    if (discr > 0)
    {
        *x1 = (-b + sqrt(discr)) / (2 * a);
        *x2 = (-b - sqrt(discr)) / (2 * a);
        return 2;
    }
    else
    {
        return UNKNOWN_ERROR;
    }
}


int SolveLine(double b, double c, double * x)
{
    if (std::isfinite(b) == 0)
    {
        return B_INFINITE;
    }
    if (std::isfinite(c) == 0)
    {
        return C_INFINITE;
    }
    if (x == NULL)
    {
        return ROOT_1_NULL_PTR;
    }

    if (b == 0 && c != 0)
    {
        return 0;
    }
    if (b == 0 && c == 0)
    {
        return N_ROOTS_INFINITE;
    }
    if (b != 0)
    {
        *x = -c / b;
        return 1;
    }
    else
    {
        return UNKNOWN_ERROR;
    }
}


int Test()
{
    int status = 0, nRoots = 0;
    double x1 = NAN, x2 = NAN;
    int nRoots_list[N_TESTS] = { 2,   1,   0};
    double   a_list[N_TESTS] = { 1,   1,   1};
    double   b_list[N_TESTS] = { 5,   2,   2};
    double   c_list[N_TESTS] = { 6,   1,   2};
    double  x1_list[N_TESTS] = {-2,  -1, NAN};
    double  x2_list[N_TESTS] = {-3, NAN, NAN};
    for (int i = 0; i < N_TESTS; i++)
    {
        x1 = NAN;
        x2 = NAN;
        nRoots = SolveSquare(a_list[i], b_list[i], c_list[i], &x1, &x2);
        if (nRoots == 0)
        {
            if (nRoots_list[i] == nRoots && x1 != x1 && x2 != x2)
                status = 1;
            else
            {
                status = 0;
                fprintf(stdout, "Wrong answer on test %lg * x^2 + %lg * x + %lg = 0.\nCurrent: x1 = %lg, x2 = %lg\nRight: x1 = %lg, x2 = %lg",
                        a_list[i], b_list[i], c_list[i], x1, x2, x1_list[i], x2_list[i]);
            }
        }
        else if (nRoots == 1)
        {
            if (nRoots_list[i] == nRoots && x1_list[i] == x1 && x2 != x2)
                status = 1;
            else
            {
                status = 0;
                fprintf(stdout, "Wrong answer on test %lg * x^2 + %lg * x + %lg = 0.\nCurrent: x1 = %lg, x2 = %lg\nRight: x1 = %lg, x2 = %lg",
                        a_list[i], b_list[i], c_list[i], x1, x2, x1_list[i], x2_list[i]);
            }
        }
        else if (nRoots == 2)
        {
            if (nRoots_list[i] == nRoots && x1_list[i] == x1 && x2_list[i] == x2)
                status = 1;
            else
            {
                status = 0;
                fprintf(stdout, "Wrong answer on test %lg * x^2 + %lg * x + %lg = 0.\nCurrent: x1 = %lg, x2 = %lg\nRight: x1 = %lg, x2 = %lg\n",
                        a_list[i], b_list[i], c_list[i], x1, x2, x1_list[i], x2_list[i]);
            }
        }
        else if (nRoots == -1)
        {
            if (nRoots_list[i] == nRoots)
                status = 1;
            else
            {
                status = 0;
                fprintf(stdout, "Wrong answer on test %lg * x^2 + %lg * x + %lg = 0, there must be infinite numbers of roots\n",
                                a_list[i], b_list[i], c_list[i]);
            }
        }
        else
        {
            fprintf(stdout, "Wrong answer on test %lg * x^2 + %lg * x + %lg = 0, there are %d roots\n", a_list[i], b_list[i], c_list[i], nRoots);
        }
    }
    return status;
}

