#include <stdio.h>
#include <pigpio.h>

#define SDATA       6    // Serial Input Data
#define STR_CLK     13   // Storage Register Clock(LATCH)
#define SHR_CLK     19   // Shift Register Clock
#define SHR_CLEAR   26   // Shift Register Clear

int main(void)
{
	if(gpioInitialise() < 0){
		fprintf(stderr, "error\n");
		return 1;
	}

    gpioSetMode(SDATA, PI_OUTPUT);
    gpioSetMode(STR_CLK, PI_OUTPUT);
    gpioSetMode(SHR_CLK, PI_OUTPUT);
    gpioSetMode(SHR_CLEAR, PI_OUTPUT);

    gpioWrite(SHR_CLEAR, 0);

    gpioWrite(STR_CLK, 0);
    gpioWrite(STR_CLK, 1);   // latch

    gpioTerminate();
    return 1;
}


