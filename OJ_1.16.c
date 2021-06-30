#include <stdio.h>

void sort_3(int *array) {
    int a, b, c;
    a = array[0];
    b = array[1];
    c = array[2];
    if (a >= b && b >= c) {
        array[0] = a;
        array[1] = b;
        array[2] = c;
    }
    else if (a >= c && c >= b) {
        array[0] = a;
        array[1] = c;
        array[2] = b;
    }
    else if (b >= a && a >= c) {
        array[0] = b;
        array[1] = a;
        array[2] = c;
    }
    else if (b >= c && c >= a) {
        array[0] = b;
        array[1] = c;
        array[2] = a;
    }
    else if (c >= a && a >= b) {
        array[0] = c;
        array[1] = a;
        array[2] = b;
    }
    else if (c >= b && b >= a) {
        array[0] = c;
        array[1] = b;
        array[2] = a;
    }
}

main() {
    int a;
    int b;
    int c;
    scanf("%d %d %d",&a,&b,&c);

    int array[3] = {a, b, c};
    
    sort_3(array);

    printf("%d %d %d", array[0], array[1], array[2]);
}
