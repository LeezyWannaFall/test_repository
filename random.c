#include <stdio.h>

int main() {
    char c = ' ';
    int wtf = 0;
    if ((scanf("%d", &wtf) == 1) && c != '\n') {
        printf("%d\n", wtf);
    } else {
        printf("n/a\n");
    }
}