#include <stdio.h>

int main() {
    float length;
    float total;
    int count;
    while (1) {
        scanf("%f", &length);
        if (length == 0) {
            return 0;
        }
        total = 0;
        count = 0;
        while (total < length) {
            count++;
            total += 1 / (float)(count + 1);
        }
        printf("%d card(s)\n", count);
    }
}
