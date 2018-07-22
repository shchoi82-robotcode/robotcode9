#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#define PINNO 13

#define DUTYCYCLE(x,range) x/(float)range*100

int main()
{
    int default_range = 255;
    int range;

    if((gpioInitialise()) < 0){
        fprintf(stderr, "gpioInitialise error\n");
        return 0;
    }

    gpioSetPWMrange(PINNO, default_range);
    range = gpioGetPWMrange(PINNO);

    printf("range:%d\n", range); 

    for(int i = 0 ; i <= range ; i++) {
        gpioPWM(PINNO, i);
        int duty = gpioGetPWMdutycycle(PINNO);
        time_sleep(0.02);
        printf("duty cycle:%.1f%% %d/%d\n", DUTYCYCLE(duty,range), i, range);
    }

    gpioPWM(PINNO, 0);
    gpioTerminate();
    return 0;
}
