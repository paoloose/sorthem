#!/usr/bin/env python3
import sys
from time import sleep

# taken from https://www.geeksforgeeks.org/python-program-for-merge-sort/

def merge(arr, l, m, r, deep=""):
    n1 = m - l + 1
    n2 = r - m

    # copy data to temp arrays L[] and R[]
    L = arr[l : m + 1]
    R = arr[m + 1 : r + 1]

    # Merge the temp arrays back into arr[l..r]
    i = 0     # Initial index of first subarray
    j = 0     # Initial index of second subarray
    k = l     # Initial index of merged subarray

    while i < n1 and j < n2:
        print(f"{deep}compare {l+i} {m+1+j}")
        if L[i] <= R[j]:
            print(f"{deep}set {k} {L[i]}")
            arr[k] = L[i]
            i += 1
        else:
            print(f"{deep}set {k} {R[j]}")
            arr[k] = R[j]
            j += 1
        k += 1

    # Copy the remaining elements of L[], if there
    # are any
    while i < n1:
        print(f"{deep}set {k} {L[i]}")
        arr[k] = L[i]
        i += 1
        k += 1

    # Copy the remaining elements of R[], if there
    # are any
    while j < n2:
        print(f"{deep}set {k} {R[j]}")
        arr[k] = R[j]
        j += 1
        k += 1

# l is for left index and r is right index of the
# sub-array of arr to be sorted

def mergeSort(arr, l, r, deep=""):
    if r <= l: return

    m = l+(r-l)//2
    # Sort first and second halves
    deep += " "
    print(f"{deep}partition left {l} {m}")
    mergeSort(arr, l, m, deep=deep)
    print(f"{deep}exit partition left {l} {m}")
    print(f"{deep}partition rigth {m+1} {r}")
    mergeSort(arr, m+1, r, deep=deep)
    print(f"{deep}exit partition rigth {m+1} {r}")
    print(f"{deep}merge {l}->{m}<-{r}")
    sys.stdout.flush()
    sleep(1)
    merge(arr, l, m, r, deep=deep)


# Driver code to test above
arr = [12, 11, 13, 5, 6, 7, 1, 2, 3, 4, 8, 9, 10, 12, 11, 13, 5, 6, 7, 1]

# print("Given array is:\n", arr)

mergeSort(arr, 0, len(arr) - 1)

# print("\nSorted array is:\n", arr)


