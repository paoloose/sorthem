#include <stdio.h>

void selection_sort(int* arr, size_t size);
void swap(int* a, int* b);

/**
 * Recursive selection sort:
 *
 * - set i = size - 1
 * - find the maximun between 0 and i   [O(n)]
 * - move that maximun to the end       [O(1)]
 * - repeat for 0 to i - 1
*/

#define SIZE 200

int main() {
    int arr[SIZE] = { 135, 138, 22, 23, 60, 139, 71, 86, 120, 34, 82, 137, 154, 17, 148, 103, 110, 43, 107, 46, 190, 157, 199, 101, 151, 3, 169, 73, 162, 77, 7, 108, 182, 159, 33, 116, 95, 31, 53, 28, 32, 57, 6, 133, 131, 167, 94, 76, 111, 93, 75, 125, 171, 126, 41, 102, 58, 193, 16, 132, 123, 62, 124, 80, 8, 172, 146, 2, 70, 115, 147, 24, 128, 47, 79, 29, 180, 50, 195, 184, 166, 36, 155, 118, 141, 64, 122, 178, 100, 168, 38, 78, 119, 161, 143, 165, 179, 145, 90, 12, 35, 56, 142, 89, 149, 114, 106, 150, 152, 188, 87, 191, 153, 4, 127, 11, 61, 92, 74, 19, 173, 186, 200, 88, 99, 136, 170, 55, 112, 69, 91, 39, 63, 185, 121, 144, 14, 197, 97, 130, 83, 163, 37, 134, 51, 96, 30, 129, 140, 5, 187, 84, 21, 181, 98, 81, 65, 189, 72, 15, 13, 109, 117, 66, 59, 198, 158, 25, 9, 49, 1, 176, 67, 192, 52, 113, 104, 54, 105, 26, 183, 164, 27, 196, 177, 10, 68, 45, 44, 40, 156, 85, 42, 20, 175, 174, 18, 48, 194, 160 };

    // First print the data
    printf("[ ");
    for (size_t i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    // Then start with the sorting
    selection_sort(arr, SIZE);
    return 0;
}

void selection_sort(int* arr, size_t size) {
    if (size == 0) return;

    // find the max index
    int max_index = 0;
    for (size_t i = 0; i < size; i++) {
		printf("compare %d %d\n", i, max_index);
        if (arr[i] > arr[max_index]) {
            printf("mark %d as max\n", i);
            max_index = i;
        }
    }

    // move it to the end
	printf("swap %d %d\n", max_index, size - 1);
    swap(&arr[max_index], &arr[size - 1]);

    // repeat for size - 1
    selection_sort(arr, size - 1);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
