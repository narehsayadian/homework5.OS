#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{ 
void *new_ptr;

new_ptr = malloc(new_size); 

if (new_ptr == NULL) {
    return NULL;
}
memcpy(new_ptr, ptr, old_size);
free(ptr);
return new_ptr;
}
int main()
{
    int *array;

    array = malloc(3 * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;

    printf("Original array: ");

    for (int i = 0; i < 3; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    array = my_realloc(array,
                       3 * sizeof(int),
                       5 * sizeof(int));

    if (array == NULL) {
        printf("Memory reallocation failed.\n");
        return 1;
    }

    array[3] = 40;
    array[4] = 50;

    printf("Resized array: ");

    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    free(array);

    return 0;
}
