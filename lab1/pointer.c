/*
 * CSE 351 Lab 1 (Data Lab - Pointers)
 *
 * <Please put your name and userid here>
 *
 * pointer.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>. The included file, "common.c" contains a function declaration
 * that should prevent a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However you are allowed to add constants to values greater
     than 255. e.g. 250+250 = 500.
  2. Function arguments and local variables (no global variables).
  3. For 1-3, only use the following:
     Pointer operations *, &. (Note that these are only for dereferencing
     and taking addresses, bitwise & is not allowed).
     Binary integer operations - + *.
     Unary interger operation !.
     For the last three, you may also use shifts (<<, >>), ~, ==, and ^.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, ?:, sizeof,
     != or binary (bitwise & or |)
  6. Use the [] operator to index into arrays for reading or writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
  greater than or equal to the number of bits in the value being shifted.
  e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
  e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
  Undefined means you do not know what result you will get from the operation.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 * Test the code below in your own 'main' program.
 *
 */

/*
 * For the following exercises remember:
 * Pointer operations *, & are allowed and should be used vigorously.
 * Pointer operation & is for taking addresses, bitwise & is still not allowed.
 * Do not use the [] operator to index into arrays for reading or writing.
 */

/*
 * Return the size of an integer in bytes.
 */
int intSize() {
  int intArray[10];
  int * intPtr1;
  int * intPtr2;
  // Write code to compute size of an integer.

  intPtr1 = intArray;
  intPtr2 = (intPtr1 + 1);
  long int a = (long int)intPtr1;
  long int b = (long int)intPtr2;
  return b - a; 
}

/*
 * Return the size of a double in bytes.
 */
int doubleSize() {
  double doubArray[10];
  double * doubPtr1;
  double * doubPtr2;
  // Write code to compute size of a double.
  doubPtr1 = doubArray;
  doubPtr2 = doubPtr1 + 1;
  return (int)((long int)doubPtr2 - (long int)doubPtr1);
}

/*
 * Return the size of a pointer in bytes.
 */
int pointerSize() {
  double * ptrArray[10];
  double ** ptrPtr1;
  double ** ptrPtr2;
  // Write code to compute size of a pointer.

  ptrPtr1 = ptrArray;
  ptrPtr2 = ptrPtr1 + 1;
  return (int)((long int)ptrPtr2 - (long int)ptrPtr1);
}

/*
 * For the 3 remaining problems you are allowed to use shifts (<<, >>), ~, ==, and ^
 * in addition to the previously specified operators.
 * The previous restrictions still apply.
 */

/*
 * Modify intArray[5] to be the value 351 using only intArray and pointer arithmetic.
 */
int changeValue() {
  int intArray[10];
  int * intPtr1 = intArray;
  // Remember not to use constants greater than 255.
  // Remember to use * to dereference.

  int value = (175<<1) + 1;
  int * ptr = intPtr1 + 5;
  *ptr = value;

  return intArray[5];
}

/*
 * Return 1 if the addresses stored in ptr1 and ptr2 are within the
 * *same* 64-byte aligned  block of memory. Return zero otherwise.
 * Operators / and % and loops are NOT allowed.
 */
int withinSameBlock(int *ptr1, int *ptr2) {
    // right shifting 6 to get the result of dividing 64
    int a1 = ((long int)ptr1 - 1) >> 6;
    int a2 = ((long int)ptr2 - 1) >> 6;
    return !(a1^a2);
}

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 * Pointing anywhere in the array is fair game, ptr does not have to
 * point to the beginning of an element.
 * size is the size of intArray in number of ints. Can assume size != 0.
 * Operators / and % and loops are NOT allowed.
 */
int withinArray(int * intArray, int size, int * ptr) {
    // intArray <= ptr <= intArray+size*4-1
    // 0 <= ptr - intArray <= size*4 -1
    int limit = size* 4 - 1;
    int diff = (long int)ptr - (long int)intArray;

  return !(diff>>31) * !((limit-diff)>>31);
}
