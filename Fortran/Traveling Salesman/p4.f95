!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Program #4
!Traveling Salesman Problem
!CS320- 1 
!10/19/19
!@author Christian Cortez cssc0468
! 
!             Traveling Salesman Problem in FORTRAN 95
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
PROGRAM P4

IMPLICIT NONE

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Variable declarations

CHARACTER(20) :: filename 
INTEGER :: numCities, permCount, i, j, k, ST, bestDist, dist
CHARACTER(20), ALLOCATABLE, DIMENSION(:) :: cities
INTEGER, ALLOCATABLE, DIMENSION(:,:) :: dist_table
INTEGER, DIMENSION(:), ALLOCATABLE :: path, bestPath 

WRITE (*, '(1x,A)', ADVANCE="NO") "Enter filename:  "
READ *, filename

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Open the file and read number of cities

OPEN(UNIT=21, FILE=filename, STATUS="OLD", ACTION="READ",&
    IOSTAT= ST) 
    
if(ST /= 0) THEN
    PRINT *, "ERROR, could not open file for reading."
    stop
END IF

DO i = 0, 0 
    READ(UNIT = 21, FMT = *, IOSTAT = ST) numCities
    IF(ST < 0) THEN 
        exit
    END IF
END DO

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Allocate memory for all needed arrays


ALLOCATE(cities(1:numCities))
ALLOCATE (dist_table(1:numCities,1:numCities)) 
ALLOCATE(path(1:numCities)) 
ALLOCATE (bestPath(1:numCities))

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Fill in arrays from data file
DO i = 1, numCities
    READ(21, '(A)') cities(i)
        IF(ST < 0) THEN
            exit
        END IF 
    path(i) = i
    DO j = 1, numCities
        READ(UNIT = 21, FMT = *, IOSTAT = ST) dist_table(i,j)
        IF(ST < 0) THEN
            exit
        END IF
    END DO
END DO
DO k = 1, numCities
    bestPath(i) = 0
END DO
bestDist = 100000
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Use recursion to find minimal distance

call permute(2, numCities)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Print formatted output 
DO i = 1, numCities - 1
    PRINT *, TRIM(cities(i)), " to ", TRIM(cities(i + 1)), " -- ", (dist_table(bestPath(i), bestPath(i+1)))
END DO 
    PRINT *, TRIM(cities(numCities)), " to ", TRIM(cities(1)), " -- ", (dist_table(bestPath(numCities), bestPath(1)))
    
  
PRINT *, "Best Distance: ", bestDist, " miles"
PRINT *, "Permutations: ", permCount 
    
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!Format labels
100 FORMAT (I6)
200 FORMAT (A)


CONTAINS
!Permute function
RECURSIVE SUBROUTINE permute(first, last)

INTEGER :: first, last, tmp, I

IF (first == last) THEN
    dist = dist_table(path(1), path(2))
    DO I = 2, last-1
        dist = dist + dist_table(path(I), path(I+1))
    END DO 
    dist = dist + dist_table(path(last),path(1))
    permCount = permCount + 1
    IF (dist < bestDist) THEN
        bestDist = dist 
        bestPath = path
    END IF
ELSE
    DO I = first, last 
        !swap(path(first),path(i))
        tmp = path(first)
        path(first) = path(I)
        path(I) = tmp
        
        call permute(first + 1, last)
        
        !swap(path(first), path(i))
        tmp = path(first)
        path(first) = path(I)
        path(I) = tmp
    END DO
    
END IF
END SUBROUTINE permute        

END PROGRAM P4
