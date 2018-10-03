/**
    \file
    \brief Solves square equation

    Solves square equation \f$ ax^2 + bx + c = 0 \f$ and prints roots.
*/

#include <iostream>
#include <stdlib.h>
#include <cmath>

#define A_NAN_ERROR 1
#define B_NAN_ERROR 2
#define C_NAN_ERROR 3
#define A_INFINITE 4
#define B_INFINITE 5
#define C_INFINITE 6
#define ROOT_1_NULL_PTR 7
#define ROOT_2_NULL_PTR 8
#define ROOT_1_NAN 9
#define ROOT_2_NAN 10
#define DISCR_NAN_ERROR 11
#define INPUT_ERROR 12

using namespace std;

int SolveLine(double b, double c, double * x); // Solves linear equation b * x + c = 0
int SolveSquare(double a, double b, double c, double * x1, double * x2); // Solves square equation a * x ^ 2 + b * x + c = 0

int main()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int nRoots = -2;
    fprintf(stdout, "Введите a, b и c: ");
    scanf("%lg%lg%lg", &a, &b, &c);
    if (c != c)
    {
        fprintf(stderr, "Вы ввели какую-то дичь, идите нафиг\n");
        exit(INPUT_ERROR);
    }
    nRoots = SolveSquare(a, b, c, &x1, &x2);
    switch (nRoots)
    {
    case -1:
        fprintf(stdout, "The equation has an infinite nunber of roots\n");
        break;
    case 0:
        fprintf(stdout, "The equation has no roots\n");
        break;
    case 1:
        if (x1 == NULL)
        {
            fprintf(stderr, "&x1 = nil\n");
            exit(ROOT_1_NULL_PTR);
        }
        fprintf(stdout, "The equation has 1 root: x = %lg\n", x1);
        break;
    case 2:
        if (x1 == NULL)
        {
            fprintf(stderr, "&x1 = nil\n");
            exit(ROOT_1_NULL_PTR);
        }
        if (x2 == NULL)
        {
            fprintf(stderr, "&x2 = nil\n");
            exit(ROOT_2_NULL_PTR);
        }
        fprintf(stdout, "The equation has 2 roots: x1 = %lg, x2 = %lg\n", x1, x2);
        break;
    default:
        fprintf(stdout, "Something strange was happend: I have %d roots (%lg and %lg) with a = %lg, b = %lg and c = %lg\n", nRoots, x1, x2, a, b, c);
        break;
    }
    return 0;
}


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
*/

int SolveSquare(double a, double b, double c, double * x1, double * x2)
{
    double discr = NAN;
    if (a != a)
    {
        fprintf(stderr, "a = nan\n");
        exit(A_NAN_ERROR);
    }
    if (isfinite(a) == 0)
    {
        fprintf(stdout, "a is infinite\n");
        exit(A_INFINITE);
    }
    if (b != b)
    {
        fprintf(stderr, "b = nan\n");
        exit(C_NAN_ERROR);
    }
    if (isfinite(b) == 0)
    {
        fprintf(stdout, "b is infinite\n");
        exit(B_INFINITE);
    }
    if (c != c)
    {
        fprintf(stderr, "c = nan\n");
        exit(C_NAN_ERROR);
    }
    if (isfinite(c) == 0)
    {
        fprintf(stdout, "c is infinite\n");
        exit(C_INFINITE);
    }
    if (x1 == NULL)
    {
        fprintf(stderr, "&x1 = nil\n");
        exit(ROOT_1_NULL_PTR);
    }
    if (x2 == NULL)
    {
        fprintf(stderr, "&x2 = nil\n");
        exit(ROOT_2_NULL_PTR);
    }
    if (a == 0)
        return SolveLine(b, c, x1);
    discr = b * b - 4 * a * c;
    if (discr != discr)
    {
        fprintf(stderr, "Discriminant = nan\n");
        exit(DISCR_NAN_ERROR);
    }
    if (discr < 0)
        return 0;
    if (discr == 0)
    {
        *x1 = -b / (2 * a);
        return 1;
    }
    else // if (discr > 0)
    {
        *x1 = (-b + sqrt(discr)) / (2 * a);
        *x2 = (-b - sqrt(discr)) / (2 * a);
        return 2;
    }
}


/**
    \brief Solves linear equation

    Solves linear equation \f$ bx + c = 0\f$.
    If there is 1 root, records root value at pointer x.

    \param[in] b coefficient at \f$ x \f$
    \param[in] c free coefficient
    \param[out] x root pointer

    \return Number of linear equation's roots,
    \return -1 if it has infinite number of roots.
*/

int SolveLine(double b, double c, double * x)
{
    if (b != b)
    {
        fprintf(stderr, "b = nan\n");
        exit(C_NAN_ERROR);
    }
    if (isfinite(b) == 0)
    {
        fprintf(stdout, "b is infinite\n");
        exit(B_INFINITE);
    }
    if (c != c)
    {
        fprintf(stderr, "c = nan\n");
        exit(C_NAN_ERROR);
    }
    if (isfinite(c) == 0)
    {
        fprintf(stdout, "c is infinite\n");
        exit(C_INFINITE);
    }
    if (x == NULL)
    {
        fprintf(stderr, "&x1 = nil\n");
        exit(ROOT_1_NULL_PTR);
    }
    if (b == 0 && c != 0)
    {
        return 0;
    }
    if (b == 0 && c == 0)
    {
        return -1;
    }
    else // if (b != 0)
    {
        *x = -c / b;
        return 1;
    }
}
