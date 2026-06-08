# RoboMath-MathSolver
Our RoboMath-Math Solver is a console-based multi-function calculator written in C that supports arithmetic expression evaluation, scientific functions, equation solving (linear, quadratic, cubic), matrix operations, number theory tools (prime check, LCM, GCD, factorial), and number system conversions — all through an interactive menu.

## Features
Arithmetic Expression Evaluator — type expressions like 3 + 5 * 2 - 1 and get the result with correct operator precedence <br>
Scientific Calculator — sine, cosine, tangent (in degrees), natural log, square root, and power <br>
Equation Solver — solves linear, quadratic, and cubic equations; handles real and complex roots <br>
Matrix Calculator — addition, subtraction, and multiplication of matrices up to 10×10 <br>
Number Theory Tools — prime check, prime factors, LCM, GCD/HCF, all factors, and factorial <br>
Number System Conversion — convert between Binary, Octal, Decimal, and Hexadecimal <br>

## Usage
On launch you will see the main menu: <br>
============ ROBOMATH ============ <br>
1. Arithmetic Expression Evaluation <br>
2. Scientific Calculator <br>
3. Equation Solver <br>
4. Matrix Calculator <br>
5. Number Theory Tools <br>
Enter the number for the section you want. Each section has its own sub-menu and asks if you want to continue or go back to the main menu after each operation.

## Project Structure
robomath.c       # All source code in a single file <br>

## Known Limitations

Arithmetic evaluator does not support parentheses <br>
Cubic equation solver uses bisection method; may miss roots outside the range -100 to 100 <br>
Factorial uses long long, so inputs above ~20 will overflow <br>
Matrix operations use int only, no floating point support <br> 

## Built With

C standard library — stdio.h, stdlib.h, string.h, ctype.h <br>
Math library — math.h <br>
