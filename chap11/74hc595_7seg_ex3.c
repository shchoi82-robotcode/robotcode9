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
    int digit1, digit2;
    time_t t;
    struct tm *tmp;

    for(int i = 0 ; ; i++){
        time(&t);
        tmp = localtime(&t);
        printf("%02d:%02d:%02d\r", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

        digit1 = tmp->tm_sec / 10;
        digit2 = tmp->tm_sec % 10;

        set8(arr[digit1]);
        gpioWrite(DIGIT2, PI_LOW); gpioWrite(DIGIT1, PI_HIGH);
        usleep(1000);
        set8(arr[digit2]);
        gpioWrite(DIGIT1, PI_LOW); gpioWrite(DIGIT2, PI_HIGH);
        usleep(1000);
    }

    release();
    return 0;
}

