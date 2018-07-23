#include <stdio.h>
#include <pigpiod_if2.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include "max7219_functions.h"

int main(void)
{
    init_max7219();

    int c = 0;
    int rand_row;
    int rand_col;
    uint8_t buf[2];

    uint8_t mat[8] = { 0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000};

    while(1){
        rand_row =  rand()%8;
        rand_col =  rand()%8;
        uint8_t mask = 1 << rand_col;
        if((mat[rand_row] & mask) == 0){
            mat[rand_row] = mat[rand_row] | mask;
            c++;
            time_sleep(0.05);
        }
        for(int i = 0; i < 8; i++){
            buf[0] = i+1;
            buf[1] = mat[i];
            spi_write_max7219(buf[0], buf[1]);
        }
        if(c == 64)
            break;
    }
    if(ferror(stdin)){
        printf("input error\n");        return 1;
    }

    release_max7219();
    return 0;
}

