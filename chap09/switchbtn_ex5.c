#include <stdio.h>
#include <pigpio.h>
#define PINNO 17
int count;
uint32_t falling_tick, rising_tick;
void cb_func(int gpio, int level, uint32_t tick)
{
    if(level == 1){
        rising_tick = tick;
        printf("count:%d period:%d\n", ++count, rising_tick-falling_tick);
    }else{
        falling_tick = tick;
    }
}

int main()
{
    if(gpioInitialise() < 0){
        fprintf(stderr, "error\n");
        return 1;
    }

    gpioSetMode(PINNO, PI_INPUT);
    gpioSetPullUpDown(PINNO, PI_PUD_UP);

	// callback function 설정
	gpioSetAlertFunc(PINNO, cb_func);

	getchar();
    printf("버튼 누른 총 횟수:%d\n", count);

    gpioTerminate();
	return 0;
}

