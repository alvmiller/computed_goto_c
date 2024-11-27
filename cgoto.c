#include <stdio.h>

// https://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables
// https://dev.to/lexplt/implementing-computed-gotos-in-c-193p

int op_switch(int initval) {
    int val = initval;
	int id = 1;
   
    #define OP_1        1
    #define OP_2        2
    #define OP_3        3

    while (1) {
        switch (id++) {
            case OP_1:
                printf("SW: OP_1\n");
                val = 1;
                break;
            case OP_2:
                printf("SW: OP_10\n");
                val = 10;
                break;
            case OP_3:
                printf("SW: OP_100\n");
                val = 100;
                break;
            default:
                printf("SW: default\n");
                printf("SW: val = %d\n", val);
                return val;
        }
    }
   
    val = 0;
    printf("SW: val = %d\n", val);
    return val;
}

int op_cgoto(int initval) {
    int id = 0;
    static void* dispatch_table[] = { &&do_1, &&do_10, &&do_100 };
    #define DISPATCH() goto *dispatch_table[id++]
   
    int val = initval;

    DISPATCH();
    while (1) {
        do_1:
            printf("GT: do_1\n");
            val = 1;
            DISPATCH();
        do_10:
            printf("GT: do_10\n");
            val = 10;
            DISPATCH();
        do_100:
            printf("GT: do_100\n");
            val = 100;
            DISPATCH();
    }
   
    val = 0;
    printf("GT: val = %d\n", val);
    return val;
}

int main()
{
    printf("\n");
    printf("Switch\n");
    (void)op_switch(1);
    printf("\n\n");
    printf("CGoto\n");
    (void)op_cgoto(1);
    printf("\n");

    return 0;
}
