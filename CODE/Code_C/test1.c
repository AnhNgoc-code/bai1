#include <stdio.h>
#include <stdbool.h>

// Hàm kiểm tra số nguyên tố
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
        if (condition)
        {
                
        }
        
    }
    return true;
}

int main() {
    int a;
    int sum = 0;
    printf("Nhap so nguyen: ");
    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        sum += i;
        
        printf("Tong la: %d\n", sum);
        // Kiểm tra số nguyên tố
        if (is_prime(i)) {
            printf("%d la so nguyen to\n", i);
        }
    }
    return 0;
}