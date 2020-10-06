#include <stdio.h>

int main() {
    char buf[10] = {0};
    printf("give input with space: ");
    scanf("%[^\n]", buf);
    printf("your input is: %s\n", buf);
}
