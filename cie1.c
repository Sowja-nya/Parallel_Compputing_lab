#include <stdio.h>
#include <math.h>
#include <omp.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int sqrtNum = (int)sqrt(num);
    for (int i = 3; i <= sqrtNum; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    int serialCount = 0, parallelCount = 0;
    double start, end;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    start = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) {
            serialCount++;
        }
    }
    end = omp_get_wtime();
    double serialTime = end - start;

    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:parallelCount)
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) {
            parallelCount++;
        }
    }
    end = omp_get_wtime();
    double parallelTime = end - start;

    
    printf("Serial Count of primes = %d\n", serialCount);
    printf("Parallel Count of primes = %d\n", parallelCount);
    printf("Execution time (serial): %.5f seconds\n", serialTime);
    printf("Execution time (parallel): %.5f seconds\n", parallelTime);

    return 0;
}
