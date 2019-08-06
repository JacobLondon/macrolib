
#include <stdio.h>
#include "vector.h"

void main()
{
    VECTOR_CONSTRUCT(cool, int);
    for (int i = 0; i < 100; i++)
        VECTOR_APPEND(cool, i);

    VECTOR_COPY(cooler, cool);

    for (int i = 0; i < VECTOR_LEN(cooler); i++)
        printf(" %d", VECTOR_AT(cooler, i));
    printf("\n");
}