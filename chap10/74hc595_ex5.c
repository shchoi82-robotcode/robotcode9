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
        allclear();
        set(i%8);
        usleep(100000);
    }

    release();
    return 0;
}

