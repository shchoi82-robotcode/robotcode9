#include <stdio.h>
#include <pigpio.h> 
#include <unistd.h>

#define DUTYCYCLE(x,range) x/(float)range*100

int range;
int gpios[] = {26,19};
int default_range = 100;
void* dimming_thread(void* arg)
{
    int gpio = (int)arg;
    printf("dimming_thread start gpio:%d\n", gpio);
    for(int i = 0 ; i <= range ; i++){
        gpioPWM(gpio, i);
        time_sleep(0.007);
    }

    for(int i = range ; i >= 0 ; i--){
        gpioPWM(gpio, i);
        time_sleep(0.007);
    }
    printf("dimming_thread exit gpio:%d\n", gpio);
    return NULL;
}

int main()
{
    if((gpioInitialise()) < 0){
        fprintf(stderr, "gpioInitialise error\n");
        return 0;
    }

    for(int i = 0 ; i < 2 ; i++){
        gpioSetPWMrange(gpios[i], default_range);
        range = gpioGetPWMrange(gpios[i]);
    }
    printf("range:%d\n", range);

    for(int i = 0 ; ; i++){
        gpioStartThread(dimming_thread, (void*)gpios[i%2]);
        time_sleep(1);
    }

    gpioTerminate();
    return 0;
}
