#!/usr/bin/env python3
# taken from https://www.geeksforgeeks.org/python-program-for-merge-sort

from random import randint


def merge(array, left, middle, rigth):
    n1 = middle - left + 1
    n2 = rigth - middle

    # copy data to temp arrays array_left[] and array_rigth[]
    array_left  = array[left : middle + 1]
    array_rigth = array[middle + 1 : rigth + 1]

    # Merge the temp arrays back into arr[l..r]
    i = 0     # Initial index of first subarray
    j = 0     # Initial index of second subarray
    k = left  # Initial index of merged subarray

    while i < n1 and j < n2:
        print(f"compare {left+i} {middle+1+j}")
        if array_left[i] <= array_rigth[j]:
            print(f"set {k} {array_left[i]}")
            array[k] = array_left[i]
            i += 1
        else:
            print(f"set {k} {array_rigth[j]}")
            array[k] = array_rigth[j]
            j += 1
        k += 1

    # Copy the remaining elements of array_left[], if there
    # are any
    while i < n1:
        print(f"set {k} {array_left[i]}")
        array[k] = array_left[i]
        i += 1
        k += 1

    # Copy the remaining elements of array_rigth[], if there
    # are any
    while j < n2:
        print(f"set {k} {array_rigth[j]}")
        array[k] = array_rigth[j]
        j += 1
        k += 1

# l is for left index and r is right index of the
# sub-array of arr to be sorted

def merge_sort(array, left, rigth):
    if rigth <= left: return

    m = left + (rigth - left)//2
    merge_sort(array, left, m)
    merge_sort(array, m+1, rigth)
    merge(array, left, m, rigth)

def shuffle(arr: list[int]):
    i = len(arr) - 1
    while i != 0:
        j = randint(0, i)
        arr[i], arr[j] = arr[j], arr[i]
        i -= 1
    return arr

def main():
    # define and send your array to sorthem
    arr = shuffle(list(range(1, 100000, 100)))
    print("[ " + " ".join(map(str, arr)) + " ]")

    merge_sort(arr, 0, len(arr) - 1)

if __name__ == '__main__':
    main()
