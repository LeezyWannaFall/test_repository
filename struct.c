#include <stdio.h>
#include <string.h>

struct first {
    int num;
    char word[50];
    float dotnum;
};

int main() {
    struct first second;
    second.num = 145;
    strcpy(second.word, "second structure");
    second.dotnum = 213.123;

    struct first third = {123, "third structures", 456.654};
    printf("%s: %d, %f\n", third.word, third.num, third.dotnum);
    printf("%s: %d, %f\n", second.word, second.num, second.dotnum);

    return 0;
}