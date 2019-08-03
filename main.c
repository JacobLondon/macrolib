
#include <stdio.h>
#include "vector.h"

void main()
{
    VECTOR_CONSTRUCT(cool, int);
    VECTOR_APPEND(cool, 10);

    printf("%d\n", VECTOR_AT(cool, -1));

}