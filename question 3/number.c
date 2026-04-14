#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    printf("enter a integer:");
    scanf("%d", &N);

    // Edge cases
    if (N == 0) {
        printf("Not possible\n");
        return 0;
    }

    if (N >= 1 && N <= 9) {
        printf("%d\n", N);
        return 0;
    }

    int digits[100], count = 0;

    // Factorize N using digits 9 to 2
    for (int i = 9; i >= 2; i--) {
        while (N % i == 0) {
            digits[count++] = i;
            N /= i;
        }
    }

    // If not fully factorized
    if (N != 1) {
        printf("Not possible\n");
        return 0;
    }

    // Sorting all the digits in ascending order
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (digits[i] > digits[j]) {
                int temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
            }
        }
    }

    // Print the smallest number
    for (int i = 0; i < count; i++) {
        printf("%d", digits[i]);
    }

    printf("\n");
    return 0;
}