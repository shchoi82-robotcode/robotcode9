#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define GPIO_PINNO 13

#define BILLION 1000000000L 

int busyWaitCalibrate() {
    struct timespec btime, etime;

    volatile int i;
    clock_gettime(CLOCK_REALTIME, &btime);
    for (i = 0; i < 10000000; i++) {};
    clock_gettime(CLOCK_REALTIME, &etime);
    double nseconds = (double) ((etime.tv_sec - btime.tv_sec)* BILLION)+
          (double) (etime.tv_nsec - btime.tv_nsec);
    int n = (int) 10 / nseconds * BILLION + 0.5;
    printf("time = %f (s)  \n \r", nseconds / BILLION);
    printf("n= %d \n\r", n);
    return n;
} 

int main(int argc, char *argv[])
{
    volatile int i;
    int n;
    if (!bcm2835_init())
        return 1;
    bcm2835_gpio_fsel(GPIO_PINNO, BCM2835_GPIO_FSEL_OUTP);
    n = busyWaitCalibrate();
    for(;;) {
        for(i = 0 ; i < n ; i++) {};
        bcm2835_gpio_write(GPIO_PINNO, HIGH);
        for(i = 0 ; i < n ; i++) {};
        bcm2835_gpio_write(GPIO_PINNO, LOW);
    }
    bcm2835_close();
    return 0;
}

