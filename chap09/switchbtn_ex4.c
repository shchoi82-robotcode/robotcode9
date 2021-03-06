#include <stdio.h>
#include <pigpio.h>
#define PINNO 17
int count;
void cb_func(int gpio, int level, uint32_t tick)
{
    if(level == 1){
        count++;
        //printf("count : %d\t", ++count);
        //printf("gpio:%d level:%d tick:%u\n", gpio, level, tick);
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

