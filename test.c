#include <stdio.h>
#include "queue.h"

enum {
    TEST_NR = 1000
};

struct fake_struct {
    int a;
    int b;
    char c;
    char name[24];
};

int main(void) 
{
    int i;
    struct queue *q; 
    
    for (i = 1; i <= TEST_NR; i++) {
        printf("%dth test\n", i);
        q = init_queue(i, sizeof(struct fake_struct));
        debug_queue(q);
        destroy_queue(q);
    }
    printf("test finished\n"); 
    return 0;
}

