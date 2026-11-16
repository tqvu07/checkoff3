#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int stack_value;                        // Not initialized
    int *heap_value = malloc(sizeof *heap_value);

    if (heap_value == NULL)
        return 1;

    // Both reads below have undefined behavior.
    printf("Stack: %d\n", stack_value);
    printf("Heap:  %d\n", *heap_value);

    free(heap_value);
    return 0;
}
