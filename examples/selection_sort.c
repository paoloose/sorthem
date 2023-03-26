#include <stdio.h>

void selection_sort(int* arr, size_t size);
void swap(int* a, int* b);

/* selection sort
- set i to size - 1
- find the maximun between 0 and i   [O(n)]
- move that maximun to the end       [O(1)]
- repeat for 0 to i - 1
*/

int main() {
    const size_t size = 10;
    int arr[size] = { 8, 2, 6, 9, 7, 3, 10, 5, 4, 1 };
    selection_sort(arr, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

void selection_sort(int* arr, size_t size) {
    if (size == 0) return;
    // find the max index
    int max_index = 0;
    for (size_t i = 0; i < size; i++) {
		printf("compare %d %d\n", arr[i], arr[max_index]);
        if (arr[i] > arr[max_index]) max_index = i;
    }
    // move it to the end
	printf("swap %d %d\n", arr[max_index], arr[size - 1]);
    swap(&arr[max_index], &arr[size - 1]);
    // repeat for size - 1
    selection_sort(arr, size - 1);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
