#include <math.h>
#include <stdio.h>

int main(void)
{
    float avRed;

    avRed = (255 + 255 + 255 + 255 + 255 + 0 + 0 + 0 + 0) / (float) 9;

    printf("red %i\n", (int) round(avRed));

}
