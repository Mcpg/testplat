#include <stdio.h>

extern void test_function();

int main(int argc, char* argv[])
{
    printf("Hello world!\n");
    test_function();
    return 0;
}
