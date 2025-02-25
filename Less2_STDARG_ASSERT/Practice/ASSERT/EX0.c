#include <stdio.h>
#include<assert.h>

#define LOG(conddition, cmd)    assert(conddition && #cmd)

double divide(double a, double b)
{
    //assert(b != 0 && "Divide by zero");
    LOG(b != 0, Divide by zero);
    return a / b;
}

int main( int argc, char *argv[] )
{
    printf("Result: %f\n", divide(10, 2));
    return 0;
}