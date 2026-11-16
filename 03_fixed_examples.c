#include <stdio.h>
#include <stdlib.h>

static void store_secret(void)
{
    volatile unsigned char secret[32] = "DEMO_PASSWORD=abc123";

    for (unsigned i = 0; i < sizeof secret; ++i) {
        secret[i] = secret[i];
    }
}

static void inspect_stack_safe(void)
{
    unsigned char buffer[32] = {0};  /* Fix 1: Zero-initialize every byte */

    fputs("Buffer bytes: ", stdout);
    for (unsigned i = 0; i < sizeof buffer; ++i) {
        unsigned char c = buffer[i];
        putchar(c >= 32 && c <= 126 ? c : '.');
    }
    putchar('\n');
}

static void heap_calloc_safe(void)
{
    /* Fix 2: Use calloc() to allocate and zero-initialize heap arrays */
    int *values = calloc(10, sizeof *values);
    if (values == NULL) {
        return;
    }

    values[0] = 42;

    printf("Heap array: ");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", values[i]);
    }
    putchar('\n');

    free(values);
}

int main(void)
{
    store_secret();
    inspect_stack_safe();
    heap_calloc_safe();
    return 0;
}
