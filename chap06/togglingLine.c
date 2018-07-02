#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
    int gpio = 13;
    char buf[100];

    FILE* fd = fopen("/sys/class/gpio/export", "w");
    fprintf(fd, "%d", gpio);
    fclose(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
    fd = fopen(buf, "w");
    fprintf(fd, "out");
    fclose(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
    fd = fopen(buf, "w");

    for (;;) {
        fprintf(fd, "1");
        fflush(fd);
        sleep(1);
        fprintf(fd, "0");
        fflush(fd);
        sleep(1);
    }
    return 0;
}
