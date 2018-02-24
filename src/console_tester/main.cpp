#include <stdio.h>

#include <mytime/mytime.h>

int main(int argc, char** argv)
{
    long x = get_a_ticks();

    printf("%li\n", x);

    return 0;
}