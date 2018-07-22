#include <stdio.h>
#include <pigpio.h> 
#include <unistd.h>
#define PINNO 13

#define DUTYCYCLE(x,range) x/(float)range*100

int main()
{
    int default_range = 50;
    int range;

    if((gpioInitialise()) < 0){
        fprintf(stderr, "gpioInitialise error\n");
        return 0;
    }


    gpioSetPWMrange(PINNO, default_range);
    range = gpioGetPWMrange(PINNO);

    printf("range:%d\n", range);

    for(int j = 0 ; j < 10 ; j++){
        for(int i = 0 ; i <= range ; i++) {
            gpioPWM(PINNO, i);
            time_sleep(0.02);
            printf("duty cycle:%.1f%% %d/%d\n", DUTYCYCLE(i,range), i, range);
        }
        for(int i = range ; i >= 0 ; i--) {
            gpioPWM(PINNO, i);
            time_sleep(0.02);
            printf("duty cycle:%.1f%% %d/%d\n", DUTYCYCLE(i,range), i, range);
        }
    }

    gpioPWM(PINNO, 0);

    gpioTerminate();
    return 0;
}
