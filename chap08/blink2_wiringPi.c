#include <stdio.h>
#include <wiringPi.h>

#define LED1 5
#define LED2 6
#define LED3 13
#define LED4 19
#define LED5 26

int gpios[] = {LED1, LED2, LED3, LED4, LED5};

int main(void)
{
    int i;
    wiringPiSetupGpio();

    for(i = 0 ; i < sizeof(gpios)/sizeof(int) ; i++)
        pinMode(gpios[i], OUTPUT);

    for(i = 0 ; i < sizeof(gpios)/sizeof(int) ; i++){
        digitalWrite(gpios[i], 0);
        delay(1000);
    }

    for(i = 0 ; i < sizeof(gpios)/sizeof(int) ; i++){
        digitalWrite(gpios[i], 1);
        delay(200);
        digitalWrite(gpios[i], 0);
    }
    return 0;
}

