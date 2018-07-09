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
	gpioWrite(SHR_CLEAR, 1);

	gpioWrite(SDATA, 1);   // serial data
	gpioWrite(SHR_CLK, 0);
	gpioWrite(SHR_CLK, 1); // shift register
	gpioWrite(STR_CLK, 0);
	gpioWrite(STR_CLK, 1); // storage register

	gpioTerminate();
	return 1;
}

