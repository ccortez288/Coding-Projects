#include <stdio.h>
#include <stdlib.h>
#include "p2.h"

/**
*Program #2
*Matrix multiplcation strictly through pointers (no brackets)
*CS320 - 01
*9/30/2019
*@author Christian Cortez cssc0468
*/

/* This function reads m, n, and p from the datafile.
   It then allocates the correct amount of memory required for matrices
   A, B, and C.
   Then matrices A and B are filled from the datafile.
   The values for m, n, and p are passed by reference, and are
   thus filled in by this function
   PARAMETERS in order are:
   int ** matrix A
   int ** matrix B
   int ** matrix C
   int * m The number of rows in matrix A
   int * n The number of columns in matrix A and
   The number of rows in matrix B
   int * p The number of columns in matrix B
   char * The name of the datafile, from the command line
*/
void read_matrices(int **matrixA, int **matrixB, int **matrixC, int *m, int
  *n, int *p, char *fileName) {
FILE *f = fopen(fileName, "r");
int i, j;
if(f == NULL) {
   printf("File is empty \n");
   exit(1);
}

fscanf(f, "%d %d %d", m, n, p);

*matrixA = (int *)malloc(*m * *n * sizeof(int));
if(matrixA == NULL) {
 exit(1);
}

*matrixB = (int *)malloc(*n * *p * sizeof(int));
if(matrixB == NULL) {
 exit(1);
}

*matrixC = (int *)malloc(*m * *p * sizeof(int));
if(matrixC == NULL) {
 exit(1);
}

for(i = 0; i < *m; i++){
   for(j = 0; j < *n; j++){
    fscanf(f,"%d", (*matrixA + (i * *n + j)));
 }
}

for(i = 0; i < *n; i++){
  for(j = 0; j < *p; j++){
    fscanf(f,"%d", (*matrixB + (i * *p + j)));
 }
}

fclose(f);
}


/* This function prints a matrix. Rows and columns should be preserved.
   PARAMETERS in order are:
   int * The matrix to print
   int The number of rows in the matrix
   int The number of columns in the matrix
*/
void print_matrix(int *matrix, int rows, int columns) {
  int i, j;
    for(i = 0; i < rows; i++) {
      for(j = 0; j < columns; j++) {
        printf("%d ", *(matrix + (i*columns + j)));
      }
      printf("\n");
 }
}


/* The two matrices A and B are multiplied, and matrix C contains the
 result.
   PARAMETERS in order are:
   int * Matrix A
   int * Matrix B
   int * Matrix C
   int m 
   int n
   int p
*/
void mult_matrices(int *matrixA, int *matrixB, int *matrixC, int m, int n, int
p) {
 int i, j, k;
 int sum;
    for (i = 0; i < m; i++)
    {
      for (j = 0; j < p; j++)
      {
        *(matrixC + (i*p + j)) = 0;
        for (k = 0; k < n; k++)
        {
          *(matrixC + (i*p + j)) += *(matrixA + (i*n + k)) * *(matrixB + (k*p + j));
        }
      }
   }
}


int main(int argc, char **argv) {
 int m, n, p;
 int *matrixA;
 int *matrixB;
 int *matrixC;
 char *fileName;
 
 if(argc != 2) {
  printf("No file found");
  return 0;
 }
 
 if(*(argv + 1) == NULL) {
  printf("No file found");
  return 0;
 }
 
 fileName = *(argv + 1);
 read_matrices(&matrixA, &matrixB, &matrixC, &m, &n, &p, fileName);
 
 printf("Program #2, cssc0468, Christian Cortez" );
 printf("\n");
 printf("The first matrix is: ");
 printf("\n");
 print_matrix(matrixA, m, n);
 printf("\n");
 printf("The second matrix is: ");
 printf("\n");
 print_matrix(matrixB, n, p);
 printf("\n");
 mult_matrices(matrixA, matrixB, matrixC, m, n, p);
 printf("The product of these matrices is: " );
 print_matrix(matrixC, m, p);
 return 0;
};
