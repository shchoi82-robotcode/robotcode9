#include <stdio.h>
#include <wiringPi.h>

#define LED 13          // gpio 13

#define EXIT_SUCC  0
#define EXIT_FAIL  1

int main(void)
{
	if(wiringPiSetupGpio() == -1)
		return EXIT_FAIL;

	pinMode(LED, OUTPUT);

	while(1) {
		digitalWrite(LED, 1);      

		delay(1000);

		digitalWrite(LED, 0);      

		delay(1000);
	}

	return EXIT_SUCC;
}

