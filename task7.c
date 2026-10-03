#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment)
{
    void *raw_ptr;
    uintptr_t aligned_address;
    uintptr_t offset;

    raw_ptr = malloc(size + alignment - 1 + sizeof(void *));

    if (raw_ptr == NULL) {
        return NULL;
    }

    aligned_address = (uintptr_t)raw_ptr + sizeof(void *);

    offset = alignment - (aligned_address % alignment);

    aligned_address += offset;

    ((void **)aligned_address)[-1] = raw_ptr;

    return (void *)aligned_address;
}

void aligned_free(void *ptr)
{
    if (ptr != NULL) {
        void *raw_ptr = ((void **)ptr)[-1];
        free(raw_ptr);
    }
}

int main()
{
    int *array;
    size_t alignment = 16;

    array = (int *)aligned_malloc(5 * sizeof(int), alignment);

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;
    array[3] = 40;
    array[4] = 50;

    printf("Array: ");

    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    printf("Memory address: %p\n", (void *)array);

    printf("Address modulo %zu: %zu\n",
           alignment,
           (uintptr_t)array % alignment);

    aligned_free(array);

    return 0;
}
