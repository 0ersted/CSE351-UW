/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M])
{
    if ( M == 32 ){
        int i, j, ii;
        int t1, t2, t3, t4, t5, t6, t7, t8;

        for (i = 0; i < M; i+=8) {
            for (j = 0; j < N; j+=8) {
                for ( ii = i; ii < i+8; ii++ ){
                    t1 = A[ii][j];
                    t2 = A[ii][j + 1];
                    t3 = A[ii][j + 2];
                    t4 = A[ii][j + 3];
                    t5 = A[ii][j + 4];
                    t6 = A[ii][j + 5];
                    t7 = A[ii][j + 6];
                    t8 = A[ii][j + 7];
                    B[j][ii] = t1;
                    B[j + 1][ii] = t2;
                    B[j + 2][ii] = t3;
                    B[j + 3][ii] = t4;
                    B[j + 4][ii] = t5;
                    B[j + 5][ii] = t6;
                    B[j + 6][ii] = t7;
                    B[j + 7][ii] = t8;
                }
            }
        }    
    }
    else if ( M == 64 ){
        int i, j, ii;
        int t1, t2, t3, t4;

        for (i = 0; i < M; i+=4) {
            for (j = 0; j < N; j+=4) {
                for ( ii = i; ii < i+4; ii++ ){
                    t1 = A[ii][j];
                    t2 = A[ii][j + 1];
                    t3 = A[ii][j + 2];
                    t4 = A[ii][j + 3];
                    B[j][ii] = t1;
                    B[j + 1][ii] = t2;
                    B[j + 2][ii] = t3;
                    B[j + 3][ii] = t4;
                }
            }
        }    
    }
    else if ( M == 67 ) {

        int i, j, ii;
        int t1, t2, t3, t4, t5, t6, t7, t8;
        for (i = 0; i < M; i+=8) {
            for (j = 0; j < N; j+=8) {
                for ( ii = i; ii < i+8 && ii < M; ii++ ){
                    t1 = A[ii][j];
                    t2 = A[ii][j + 1];
                    t3 = A[ii][j + 2];
                    t4 = A[ii][j + 3];
                    t5 = A[ii][j + 4];
                    t6 = A[ii][j + 5];
                    t7 = A[ii][j + 6];
                    t8 = A[ii][j + 7];
                    B[j][ii] = t1;
                    B[j + 1][ii] = t2;
                    B[j + 2][ii] = t3;
                    B[j + 3][ii] = t4;
                    B[j + 4][ii] = t5;
                    B[j + 5][ii] = t6;
                    B[j + 6][ii] = t7;
                    B[j + 7][ii] = t8;
                }
            }
        }
    }    
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M])
{
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M])
{
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

