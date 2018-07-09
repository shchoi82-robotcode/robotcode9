#include <stdio.h>
#include <pigpio.h>
#define PINNO 17

int main()
{
    int level;
    if(gpioInitialise() < 0){
        fprintf(stderr, "error\n");
        return 1;
    }

    gpioSetMode(PINNO, PI_INPUT);
    gpioSetPullUpDown(PINNO, PI_PUD_UP);

    while(1){
        level = gpioRead(PINNO);
        printf("%s %d\n", level?"------":"--__--", level);
        time_sleep(0.1);
    }

    gpioTerminate();
    return 0;
}

