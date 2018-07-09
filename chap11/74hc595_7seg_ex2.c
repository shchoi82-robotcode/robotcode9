#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include "74hc595_functions.h"

#define DIGIT1 23
#define DIGIT2 24

int main(void)
{
    uint8_t arr[] = {           //abcdefg
                      (uint8_t)~0b11111100,  // 0
                      (uint8_t)~0b01100000,  // 1
                      (uint8_t)~0b11011010,  // 2
                      (uint8_t)~0b11110010,  // 3
                      (uint8_t)~0b01100110,  // 4
                      (uint8_t)~0b10110110,  // 5
                      (uint8_t)~0b00111110,  // 6
                      (uint8_t)~0b11100100,  // 7
                      (uint8_t)~0b11111110,  // 8
                      (uint8_t)~0b11100110   // 9
    };

    int ret;

    ret = init();
    if(ret == 0)
        return 0;

    gpioSetMode(DIGIT1, PI_OUTPUT);
    gpioSetMode(DIGIT2, PI_OUTPUT);

    for(int i = 0 ; ; i++){
        set8(arr[1]);
        gpioWrite(DIGIT1, PI_HIGH); 
        gpioWrite(DIGIT2, PI_LOW);
        usleep(10000);

        set8(arr[2]);
        gpioWrite(DIGIT1, PI_LOW); 
        gpioWrite(DIGIT2, PI_HIGH);
        usleep(10000);
    }

    release();
    return 0;
}

