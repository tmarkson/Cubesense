#include <stdio.h>
#include "dll_test1.h"

 void hello(const char *s)
{
        printf("Hello %s\n", s);
}

int Double(int x)
{
        return 2 * x;
}

void CppFunc(void)
{
        puts("CppFunc");
}

