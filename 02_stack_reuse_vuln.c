/* Run with 
gcc -std=c11 -O0 -fno-inline -fno-omit-frame-pointer -fno-stack-protector 02_stack_reuse_vuln.c -o stack_reuse
./stack_reuse
*/

#include <stdio.h>

__attribute__((noinline))
static void store_secret(void)
{
    volatile unsigned char secret[32] = "DEMO_PASSWORD=abc123";

    /* Volatile writes help keep the array in memory. */
    for (unsigned i = 0; i < sizeof secret; ++i)
        secret[i] = secret[i];
}

__attribute__((noinline))
static void inspect_stack(void)
{
    volatile unsigned char buffer[32];  /* Uninitialized */

    fputs("Residual bytes: ", stdout);
    for (unsigned i = 0; i < sizeof buffer; ++i) {
        unsigned char c = buffer[i];    /* Intentional invalid read */
        putchar(c >= 32 && c <= 126 ? c : '.');
    }
    putchar('\n');
}

int main(void)
{
    store_secret();
    inspect_stack();
    return 0;
}
