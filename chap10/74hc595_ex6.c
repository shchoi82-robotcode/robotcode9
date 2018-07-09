#include <stdio.h>
#include <unistd.h>
#include "74hc595_functions.h"

int main(void)
{
    int ret;

    ret = init();
    if(ret == 0)
        return 0;

    for(int i = 0 ; i < 100 ; i++){
        set8(0b10101010);
        usleep(100000);
        set8(0b01010101);
        usleep(100000);
    }

    release();
    return 0;
}


