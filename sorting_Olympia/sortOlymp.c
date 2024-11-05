#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 100001

// Functions for sorting algorithms
/*void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void displayList(int arr[], int size);*/


/*compares two consecutive elements and swaps them if needed*/
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*finds the smallest element and swaps it with the first element
then finds the next smallest element and swaps it with the second*/
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

/*the first number is considered "sorted"
other numbers are inserted into the sorted section one by one*/
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

/*pivot element is chosen and partition is applied
from the second pass, there are two pivots, from the third pass, four, and so on.*/
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void displayList(int arr[], int size) {
    printf("Sorted list:\n");

    if (size <= 10) {
        for (int i = 0; i < size; i++) {
            printf("%d\n", arr[i]);
        }
    } else {
        printf("%d\n", arr[0]);
        printf("%d\n", arr[1]);
        printf("%d\n", arr[2]);
        printf("...\n");
        printf("%d\n", arr[size - 3]);
        printf("%d\n", arr[size - 2]);
        printf("%d\n", arr[size - 1]);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    int arr[MAX_SIZE];
    int size = 0;
    clock_t start, end;
    double cpu_time_used;

    if (argc != 3) {
        printf("Please provide the filename and sorting algorithm as command line options.\n");
        printf("Example: ./sortprogram file.txt bubblesort\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(fp, "%d", &arr[size]) == 1) {
        size++;
        if (size >= MAX_SIZE) {
            printf("The maximum number of numbers has been reached.\n");
            break;
        }
    }

    fclose(fp);

    start = clock();

    if (strcmp(argv[2], "bubblesort") == 0) {
        bubbleSort(arr, size);
    } else if (strcmp(argv[2], "selectionsort") == 0) {
        selectionSort(arr, size);
    } else if (strcmp(argv[2], "insertionsort") == 0) {
        insertionSort(arr, size);
    } else if (strcmp(argv[2], "quicksort") == 0) {
        quickSort(arr, 0, size - 1);
    } else {
        printf("Invalid sorting algorithm.\n");
        return 1;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    displayList(arr, size);

    printf("Sorting time: %f seconds\n", cpu_time_used);

    return 0;
}
