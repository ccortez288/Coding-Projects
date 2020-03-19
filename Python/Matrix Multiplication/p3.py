import sys 

#Program #3
#Matrix Multiplication in Python through reading in a file 
#CS320 - 01
#10/14/2019
#@Author: Christian Cortez 


# This function begins execution of program.
# Verify data input filename provided on command line: len(sys.argv)
# If error, output message for user: Usage: p3.py dataFileName'
# and quit, using sys.exit()
#
# Declare A, B, call read_matrices to initialize A, B, and store
# return value as C
#
# Print A and B contents
#
# Call mult_matrices
#
# Print result contents
#
def main():
  print("Program #3, cssc0468, Christian Cortez")
  
  if len(sys.argv) != 2:
    print("Usage: p3.py dataFileName")
    sys.exit()

  matrixA = []
  matrixB = []
  matrixC = read_matrices(matrixA,matrixB)

  print("Matrix A contents: \n")
  print_matrix(matrixA)
  print("\n Matrix B contents: \n")
  print_matrix(matrixB)
  mult_matrices(matrixA,matrixB,matrixC)
  print("\n Matrix A * B is: \n")
  print_matrix(matrixC)


# This function reads m, n, and p from the datafile.
# Then matrices A and B are filled from the datafile.
# Matrix C is then allocated size m x p.
# The values for m, n, and p are local values filled in by this function
# PARAMETERS in order are:
# list matrix A
# list matrix B
# RETURN matrix C
#
def read_matrices(A,B):
  with open(sys.argv[1]) as f:
    m = [int(i) for i in next(f).split()][0]
    n = [int(i) for i in next(f).split()][0]
    p = [int(i) for i in next(f).split()][0]

    for j in range(m):
      A.append([int(i) for i in next(f).split()])

    for j in range(n):
      B.append([int(i) for i in next(f).split()])
    
  matrixC = [[0 for i in range(p)] for j in range(m)] 
  return matrixC


# This function prints a matrix. Rows and columns should be preserved.
# PARAMETERS in order are:
# list The matrix to print
#
def print_matrix(matrix): 
    for i in matrix:
      print(i)

  
# The two matrices A and B are multiplied, and matrix C contains the
# result.
# PARAMETERS in order are:
# list Matrix A
# list Matrix B
# list Matrix C (all zeros at this point)
#
def mult_matrices(A,B,C):
  for i in range(len(A)):
    for j in range (len(B[0])):
      for k in range(len(B)):
        C[i][j] += A[i][k] * B[k][j]

# Begin program
if __name__ == '__main__':
 main()
