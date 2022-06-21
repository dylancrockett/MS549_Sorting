#ifndef MS549_SORTING
#define MS549_SORTING

#include <iostream>

namespace sorting {
	using namespace std;

    /// <summary>
    /// Implementation of selection sort.
    /// </summary>
    /// <param name="arr">The array to be sorted.</param>
    /// <param name="size">The number of elements in the array.</param>
    void selection_sort(int arr[], int size)
    {
        //step through the array, for each step moving the minimum value for the current sub array to the front of the sub array
        for (int i = 0; i < size - 1; i++)
        {
            //find the minimum element for the current unsorted sub array
            int min_index = i;
            for (int j = i + 1; j < size; j++) {
                //update the index for the minimum value if a new minimum is found
                if (arr[j] < arr[min_index]) min_index = j;
            }

            //swap the minimum element with the first element
            swap(arr[min_index], arr[i]);
        }
    }

    /// <summary>
    /// Quick sort partition function.
    /// </summary>
    /// <param name="arr">Array being partitioned.</param>
    /// <param name="start">The current start index.</param>
    /// <param name="end">The current end index.</param>
    /// <returns>The new position of the pivot element (element at start index)</returns>
    int qs_partition(int arr[], int start, int end)
    {
        //get the pivot value for this partition
        int pivot = arr[start];

        //counter
        int count = 0;

        //find the offset to the correct position of the pivot element from the start index
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot) count++;
        }

        //the correct new position for the pivot element
        int pivotIndex = start + count;

        //swap the pivot element into it's correct position
        swap(arr[pivotIndex], arr[start]);

        //sort left and right of the pivot element.
        int i = start, j = end;

        //sort elements arouind the pivot element
        while (i < pivotIndex && j > pivotIndex) {
            //coninue to step right until an element less than the pivot element is found
            while (arr[i] <= pivot) i++;

            //contine to step left until an elment larger than the pivot element is found
            while (arr[j] > pivot) j--;

            //swap the two elements, bringing the array closer to being sorted
            if (i < pivotIndex && j > pivotIndex) swap(arr[i++], arr[j--]);
        }

        //return the correct index for the pivot element
        return pivotIndex;
    }

    /// <summary>
    /// Recursive quick sort function implementation.
    /// </summary>
    /// <param name="arr">Array being sorted.</param>
    /// <param name="start">Current starting position.</param>
    /// <param name="end">Current ending position.</param>
    void quick_sort(int arr[], int start, int end)
    {
        //return if start is > end index
        if (start >= end) return;

        //partition the array
        int pivotIndex = qs_partition(arr, start, end);

        //sort the left part of the array
        quick_sort(arr, start, pivotIndex - 1);

        //sort the right part of the array
        quick_sort(arr, pivotIndex + 1, end);
    }

    /// <summary>
    /// An implementation of the quick sort algorithm.
    /// </summary>
    /// <param name="arr">Array to be sorted.</param>
    /// <param name="size">Size of the array being sorted.</param>
    inline void quick_sort(int arr[], int size) {
        quick_sort(arr, 0, size - 1);
    }
}

#endif