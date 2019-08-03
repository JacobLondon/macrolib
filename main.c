
#include <stdio.h>
#include "vector.h"

void main()
{
    VECTOR_CONSTRUCT(cool, int);
    VECTOR_APPEND(cool, 1);
    VECTOR_APPEND(cool, 2);
    VECTOR_APPEND(cool, 3);

    printf("%d\n", VECTOR_AT(cool, -1));

}