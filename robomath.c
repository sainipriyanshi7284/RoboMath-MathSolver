#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define PI 3.14159265

// ---------- ARITHMETIC EXPRESSION EVALUATOR ----------
struct materials
{
    char op;
    float operand;
};

int arithmetic(struct materials s1[], int *c)
{
    int i = 0;
    while (i < *c)
    {
        if (s1[i].op == '*' || s1[i].op == '/')
        {
            float result = s1[i].operand;
            while ((i < *c - 1) && (s1[i].op == '*' || s1[i].op == '/'))
            {
                if (s1[i].op == '*')
                    result *= s1[i + 1].operand;
                else
                    result /= s1[i + 1].operand;

                s1[i].op = s1[i + 1].op;
                for (int j = i + 1; j < *c; j++)
                    s1[j] = s1[j + 1];
                (*c)--;
            }
            s1[i].operand = result;
        }
        else
        {
            i++;
        }
    }

    float sum = s1[0].operand;
    for (int i = 0; i < *c - 1; i++)
    {
        if (s1[i].op == '+')
            sum += s1[i + 1].operand;
        else if (s1[i].op == '-')
            sum -= s1[i + 1].operand;
    }
    printf("RESULT = %.4f\n", sum);
    return 0;
}

void split(char *exp, struct materials s[], int *count)
{
    int i = 0, k = 0;
    while (exp[i] != '\0')
    {
        if (isspace(exp[i]))
        {
            i++;
            continue;
        }
        char operandstr[50];
        int j = 0;
        while (isdigit(exp[i]) || exp[i] == '.')
        {
            operandstr[j++] = exp[i++];
        }
        operandstr[j] = '\0';
        s[k].operand = atof(operandstr);

        if (exp[i] == '=' || exp[i] == '\0')
        {
            s[k].op = '\0';
            k++;
            break;
        }
        if (strchr("*/+-", exp[i]))
        {
            s[k].op = exp[i];
            i++;
        }
        else
        {
            s[k].op = '\0';
        }
        k++;
    }
    *count = k;
    arithmetic(s, count);
}

void arithmeticCalc()
{
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        char expression[200];
        struct materials s[100];
        int count = 0;
        printf("Enter the expression:\n");
        scanf(" %[^\n]", expression);
        split(expression, s, &count);
        printf("\nWant to continue with more arithmetic calculations? (y/n): ");
        scanf(" %c", &cont);
    }
}

// ---------- SCIENTIFIC CALCULATOR ----------
void scientificCalc()
{
    int choice;
    double num, result;

    printf("\n--- Scientific Calculator ---\n");
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        printf("1. Sine\n2. Cosine\n3. Tangent\n4. Logarithm (ln)\n5. Square Root\n6. Power (x^y)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter angle in degrees: ");
            scanf("%lf", &num);
            result = sin(num * PI / 180.0);
            printf("sin(%.2lf) = %.4lf\n", num, result);
            break;
        case 2:
            printf("Enter angle in degrees: ");
            scanf("%lf", &num);
            result = cos(num * PI / 180.0);
            printf("cos(%.2lf) = %.4lf\n", num, result);
            break;
        case 3:
            printf("Enter angle in degrees: ");
            scanf("%lf", &num);
            result = tan(num * PI / 180.0);
            printf("tan(%.2lf) = %.4lf\n", num, result);
            break;
        case 4:
            printf("Enter number: ");
            scanf("%lf", &num);
            if (num <= 0)
                printf("Logarithm undefined for non-positive numbers.\n");
            else
            {
                result = log(num);
                printf("ln(%.2lf) = %.4lf\n", num, result);
            }
            break;
        case 5:
            printf("Enter number: ");
            scanf("%lf", &num);
            if (num < 0)
                printf("Square root undefined for negative numbers.\n");
            else
            {
                result = sqrt(num);
                printf("sqrt(%.2lf) = %.4lf\n", num, result);
            }
            break;
        case 6:
        {
            double base, exp;
            printf("Enter base: ");
            scanf("%lf", &base);
            printf("Enter exponent: ");
            scanf("%lf", &exp);
            result = pow(base, exp);
            printf("%.2lf ^ %.2lf = %.4lf\n", base, exp, result);
            break;
        }
        default:
            printf("Invalid choice.\n");
            break;
        }
        printf("\nWould you like to perform another Scientific Calculation? (y/n): ");
        scanf(" %c", &cont);
    }
}
// --------EQUATION SOLVER ------------
void solveLinear(float *ptr)
{
    float a = ptr[0];
    float b = ptr[1];
    if (a == 0)
    {
        printf("Not a valid linear equation\n");
        return;
    }
    float x = -b / a;
    printf("x = %.2f\n", x);
}

void solveQuadratic(float *ptr)
{
    float a = ptr[0], b = ptr[1], c = ptr[2];
    float D = b * b - 4 * a * c;

    if (D > 0)
    {
        printf("Distinct Roots\n");
        float x1 = (-b + sqrt(D)) / (2 * a);
        float x2 = (-b - sqrt(D)) / (2 * a);
        printf("x1 = %.2f\nx2 = %.2f\n", x1, x2);
    }
    else if (D == 0)
    {
        printf("Equal Roots\n");
        float x = -b / (2 * a);
        printf("x = %.2f\n", x);
    }
    else
    {
        printf("Complex Roots\n");
        float real = -b / (2 * a);
        float imag = sqrt(-D) / (2 * a);
        printf("x1 = %.2f + %.2fi\n", real, imag);
        printf("x2 = %.2f - %.2fi\n", real, imag);
    }
}

float f(float *ptr, float x)
{
    return ptr[0] * x * x * x + ptr[1] * x * x + ptr[2] * x + ptr[3];
}

void solveCubic(float *ptr)
{
    float L = -100, R = -99, mid;
    while (f(ptr, L) * f(ptr, R) > 0 && R < 100)
    {
        L++;
        R++;
    }
    for (int i = 0; i < 50; i++)
    {
        mid = (L + R) / 2;
        if (f(ptr, L) * f(ptr, mid) < 0)
            R = mid;
        else
            L = mid;
    }

    float x1 = mid;
    printf("x1 = %.2f\n", x1);
    float a = ptr[0];
    float b = ptr[1] + a * x1;
    float c = ptr[2] + b * x1;

    float D = b * b - 4 * a * c;
    if (D > 0)
    {
        printf("Distinct Roots\n");
        float x2 = (-b + sqrt(D)) / (2 * a);
        float x3 = (-b - sqrt(D)) / (2 * a);
        printf("x2 = %.2f\nx3 = %.2f\n", x2, x3);
    }
    else if (D == 0)
    {
        printf("Equal Roots\n");
        float x = -b / (2 * a);
        printf("x2 = %.2f\nx3 = %.2f\n", x, x);
    }
    else
    {
        printf("Complex Roots\n");
        float real = -b / (2 * a);
        float imag = sqrt(-D) / (2 * a);
        printf("x2 = %.2f + %.2fi\n", real, imag);
        printf("x3 = %.2f - %.2fi\n", real, imag);
    }
}

void equationSolver()
{
    int n;
    float arr[4];
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        printf("Equation Solver\n");
        printf("Enter degree (1, 2 or 3): ");
        scanf("%d", &n);

        if (n < 1 || n > 3)
        {
            printf("Invalid degree\n");
            return;
        }

        printf("Enter coefficients (highest degree first): ");
        for (int i = 0; i <= n; i++)
        {
            scanf("%f", &arr[i]);
        }

        if (n == 1)
            solveLinear(arr);
        else if (n == 2)
            solveQuadratic(arr);
        else
            solveCubic(arr);

        printf("\nDo you want to solve another equation? (y/n): ");
        scanf(" %c", &cont);
    }
}
// ---------- MATRIX CALCULATOR ----------
void matin(int m[10][10], int rows, int columns)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            scanf("%d", &m[i][j]);
        }
    }
}
void addmat(int m1[10][10], int m2[10][10], int r[10][10], int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            r[i][j] = m1[i][j] + m2[i][j];
        }
    }
}
void submat(int m1[10][10], int m2[10][10], int r[10][10], int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            r[i][j] = m1[i][j] - m2[i][j];
        }
    }
}

void mulmat(int m1[10][10], int m2[10][10], int r[10][10], int r1, int c1, int r2, int c2)
{

    if (c1 != r2)
    {
        printf("Matrix multiplication not possible: columns of A != rows of B\n");
        return;
    }

    // Initialize result matrix
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            r[i][j] = 0;
            for (int k = 0; k < c1; k++)
            {
                r[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void printmat(int r[10][10], int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%4d", r[i][j]);
        }
        printf("\n");
    }
}
void matrixCalc()
{
    int mat1[10][10], mat2[10][10], result[10][10];
    int choice, rows, columns, rows2, columns2;
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        printf("1. Addition\n2. Subtraction\n3. Multiplication\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Addition
            printf("Enter rows and columns: ");
            scanf("%d %d", &rows, &columns);
            printf("Matrix 1:\n");
            matin(mat1, rows, columns);
            printf("Matrix 2:\n");
            matin(mat2, rows, columns);
            addmat(mat1, mat2, result, rows, columns);
            printf("Result (A + B):\n");
            printmat(result, rows, columns);
            break;

        case 2: // Subtraction
            printf("Enter rows and columns: ");
            scanf("%d %d", &rows, &columns);
            printf("Matrix 1:\n");
            matin(mat1, rows, columns);
            printf("Matrix 2:\n");
            matin(mat2, rows, columns);
            submat(mat1, mat2, result, rows, columns);
            printf("Result (A - B):\n");
            printmat(result, rows, columns);
            break;

        case 3: // Multiplication
            printf("Enter rows and columns for 1st matrix: ");
            scanf("%d %d", &rows, &columns);
            printf("Matrix 1:\n");
            matin(mat1, rows, columns);
            printf("Enter rows and columns for 2nd matrix: ");
            scanf("%d %d", &rows2, &columns2);

            if (columns != rows2)
            {
                printf("Matrix multiplication not possible\n");
                break;
            }
            printf("Matrix 2:\n");
            matin(mat2, rows2, columns2);
            mulmat(mat1, mat2, result, rows, columns, rows2, columns2);
            printf("Result (A * B):\n");
            printmat(result, rows, columns2);
            break;

        default:
            printf("Invalid choice.\n");
        }
        printf("\nWant to continue with more matrix operations? (y/n): ");
        scanf(" %c", &cont);
    }
}
// ---------- NUMBER THEORY TOOLS ----------

int prime_check(int *ptr)
{
    int i = 2;
    if (*ptr <= 1)
        return 1;
    while (i < *ptr)
    {
        if (*ptr % i == 0)
            return 1;
        i++;
    }
    return 0;
}
void prime_checker()
{
    int num;
    printf("\nEnter a number: ");
    scanf("%d", &num);
    int r = prime_check(&num);
    if (r == 0)
        printf("%d is a prime number.\n", num);
    else
        printf("%d is NOT a prime number.\n", num);
}

int find_prime_factors(int *fact, int *ptr)
{
    int j = 0;
    printf("Prime Factors of %d are: ", *ptr);
    for (int i = 1; i <= *ptr; i++)
    {
        int r = prime_check(&i);
        if (*ptr % i == 0)
        {
            *(fact + j) = i;
            if (r == 0)
            {
                printf("%d ", i);
                j++;
            }
        }
    }
    printf("\n");
    return j;
}
void prime_factors()
{
    int fac[20], num;
    printf("Enter the number: ");
    scanf("%d", &num);
    find_prime_factors(fac, &num);
}

int max(int n, int *ptr)
{
    int m = ptr[0];
    for (int i = 0; i < n; i++)
        if (ptr[i] > m)
            m = ptr[i];
    return m;
}
int lcm(int *ptr, int n)
{
    int m = max(n, ptr);
    while (1)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (m % ptr[i] != 0)
                break;
        }
        if (i == n)
            return m;
        m++;
    }
}
void multiplies(int num, int lcm)
{
    int mul;

    for (int i = 1;; i++)
    {
        mul = num * i;

        if (mul == lcm)
            break;
    }
    printf("\n");
}
void lcm_finder()
{
    int n, num[10];
    printf("Enter how many numbers: ");
    scanf("%d", &n);
    printf("Enter the numbers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    int h = lcm(num, n);
    for (int i = 0; i < n; i++)
        multiplies(num[i], h);
    printf("LCM = %d\n", h);
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void gcd_finder()
{
    int n, num[10];
    printf("Enter how many numbers: ");
    scanf("%d", &n);
    printf("Enter the numbers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    int h = num[0];
    for (int i = 1; i < n; i++)
        h = gcd(h, num[i]);
    printf("GCD (HCF) = %d\n", h);
}

int find_factors(int *fact, int *ptr)
{
    int j = 0;
    printf("Factors of %d are: ", *ptr);
    for (int i = 1; i <= *ptr; i++)
    {
        if (*ptr % i == 0)
        {
            *(fact + j) = i;
            printf("%d ", i);
            j++;
        }
    }
    printf("\n");
    return j;
}
void factors_finder()
{
    int fac[20], num;
    printf("Enter the number: ");
    scanf("%d", &num);
    find_factors(fac, &num);
}

long long factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}
void factorial_finder()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Factorial of %d = %lld\n", num, factorial(num));
}

// ---------- NUMBER SYSTEM CONVERSIONS ----------
int oct_to_dec(int x)
{
    int dec = 0, i = 0, r;
    while (x != 0)
    {
        r = x % 10;
        dec += r * pow(8, i);
        x /= 10;
        i++;
    }
    return dec;
}
int bin_to_dec(int x)
{
    int dec = 0, i = 0, r;
    while (x != 0)
    {
        r = x % 10;
        dec += r * pow(2, i);
        x /= 10;
        i++;
    }
    return dec;
}
int dec_to_bin(int x)
{
    int bin = 0, i = 1, r;
    while (x != 0)
    {
        r = x % 2;
        bin += r * i;
        x /= 2;
        i *= 10;
    }
    return bin;
}
int dec_to_oct(int x)
{
    int oct = 0, i = 1, r;
    while (x != 0)
    {
        r = x % 8;
        oct += r * i;
        x /= 8;
        i *= 10;
    }
    return oct;
}
void dec_to_hex(int x)
{
    char hex[20];
    int i = 0, r;
    while (x != 0)
    {
        r = x % 16;
        if (r < 10)
            hex[i] = r + '0';
        else
            hex[i] = r - 10 + 'A';
        x /= 16;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hex[j]);
}
int hex_to_dec(char h[])
{
    int len = strlen(h), dec = 0, base = 1, v;
    for (int i = len - 1; i >= 0; i--)
    {
        if (h[i] >= '0' && h[i] <= '9')
            v = h[i] - '0';
        else if (h[i] >= 'A' && h[i] <= 'F')
            v = h[i] - 'A' + 10;
        else if (h[i] >= 'a' && h[i] <= 'f')
            v = h[i] - 'a' + 10;
        dec += v * base;
        base *= 16;
    }
    return dec;
}
void conversion()
{
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        int choice;
        printf("1. Octal\n2. Binary\n3. Decimal\n4. Hexadecimal\nChoose input type: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            int x;
            printf("Enter octal: ");
            scanf("%d", &x);
            int dec = oct_to_dec(x);
            printf("DECIMAL: %d\nBINARY: %d\nHEXA: ", dec, dec_to_bin(dec));
            dec_to_hex(dec);
        }
        else if (choice == 2)
        {
            int x;
            printf("Enter binary: ");
            scanf("%d", &x);
            int dec = bin_to_dec(x);
            printf("DECIMAL: %d\nOCTAL: %d\nHEXA: ", dec, dec_to_oct(dec));
            dec_to_hex(dec);
        }
        else if (choice == 3)
        {
            int x;
            printf("Enter decimal: ");
            scanf("%d", &x);
            printf("BINARY: %d\nOCTAL: %d\nHEXA: ", dec_to_bin(x), dec_to_oct(x));
            dec_to_hex(x);
        }
        else if (choice == 4)
        {
            char h[20];
            printf("Enter hexadecimal: ");
            scanf("%s", h);
            int dec = hex_to_dec(h);
            printf("DECIMAL: %d\nBINARY: %d\nOCTAL: %d\n", dec, dec_to_bin(dec), dec_to_oct(dec));
        }

        printf("\nWould you like to perform another number system conversion? (y/n): ");
        scanf(" %c", &cont);
    }
}

void numberTheoryTools()
{
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {

        int choice;
        printf("\n--- Number Theory Tools ---\n");
        printf("1. Prime Check\n");
        printf("2. Prime Factors\n");
        printf("3. LCM\n");
        printf("4. GCD (HCF)\n");
        printf("5. Factors\n");
        printf("6. Factorial\n");
        printf("7. Number System Conversion\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            prime_checker();
            break;
        case 2:
            prime_factors();
            break;
        case 3:
            lcm_finder();
            break;
        case 4:
            gcd_finder();
            break;
        case 5:
            factors_finder();
            break;
        case 6:
            factorial_finder();
            break;
        case 7:
            conversion();
            break;
        default:
            printf("Invalid choice.\n");
        }
        printf("\nDo you want to perform another number theory operation? (y/n): ");
        scanf(" %c", &cont);
    }
}
// ---------- Main Menu ----------
int main()
{
    int choice;
    char cont = 'y';

    while (cont == 'y' || cont == 'Y')
    {
        printf("\n============ ROBOMATH ============\n");
        printf("1. Arithmetic Expression Evaluation\n");
        printf("2. Scientific Calculator\n");
        printf("3. Equation Solver\n");
        printf("4. Matrix Calculator\n");
        printf("5. Number Theory Tools\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            arithmeticCalc();
            break;
        case 2:
            scientificCalc();
            break;
        case 3:
            equationSolver();
            break;
        case 4:
            matrixCalc();
            break;
        case 5:
            numberTheoryTools();
            break;
        default:
            printf("Invalid choice.\n");
        }

        printf("\nRETURN TO THE MAIN MENU -- PRESS 'Y'\n\x1b[31mEXIT -- PRESS 'N'\x1b[0m\n ");
        scanf(" %c", &cont);
    }

    printf("Program terminated.\n");
    return 0;
}