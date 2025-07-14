#include <iostream>
#include <algorithm> 
#include <chrono>    
#include <cstdlib>   
#include <ctime>    

using namespace std;
using namespace std::chrono;

// Partitioning function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Merge two halves for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int target) {
    if (arr[0] == target)
        return 0;

    int i = 1;
    while (i < n && arr[i] <= target)
        i *= 2;

    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

void generateRandomNumbers(int arr[], int n, int maxVal = 10000) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % maxVal;
    }
}

int main() {
    srand(time(0));
    int size;
    cout << "Enter number of elements to sort using Quick Sort: ";
    cin >> size;

    int* quickArr = new int[size];
    generateRandomNumbers(quickArr, size);

    cout << "Random elements before Quick Sort:\n";
    printArray(quickArr, size);

    auto startQuick = high_resolution_clock::now();
    quickSort(quickArr, 0, size - 1);
    auto stopQuick = high_resolution_clock::now();
    auto durationQuick = duration_cast<milliseconds>(stopQuick - startQuick);

    cout << "Sorted elements after Quick Sort:\n";
    printArray(quickArr, size);
    cout << "Quick Sort completed in: " << durationQuick.count() << " ms" << endl;
    delete[] quickArr;

    // --Quick Sort Performance --
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 200000};
    cout << "\nPerformance Test on Large Arrays:" << endl;
    for (int s = 0; s < 6; s++) {
        int n = sizes[s];
        int* temp = new int[n];
        generateRandomNumbers(temp, n);
        auto start = high_resolution_clock::now();
        quickSort(temp, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "N = " << n << " | Time taken: " << duration.count() << " ms" << endl;
        delete[] temp;
    }

    int num;
    cout << "\nEnter the number of random elements for Merge Sort: ";
    cin >> num;
    int* mergeArr = new int[num];
    generateRandomNumbers(mergeArr, num);

    cout << "Random elements before Merge Sort:\n";
    printArray(mergeArr, num);

    auto start2 = high_resolution_clock::now();
    mergeSort(mergeArr, 0, num - 1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    cout << "Sorted elements after Merge Sort:\n";
    printArray(mergeArr, num);
    cout << "Merge Sort completed in: " << duration2.count() << " ms" << endl;
    delete[] mergeArr;

    int N;
    cout << "\nEnter the number of random elements (N) for Exponential Search: ";
    cin >> N;
    int* searchArr = new int[N];
    generateRandomNumbers(searchArr, N, 1000);
    sort(searchArr, searchArr + N);

    cout << "Sorted array:\n";
    printArray(searchArr, N);

    int target;
    cout << "Enter the number to search (Exponential): ";
    cin >> target;
    auto start3 = high_resolution_clock::now();
    int result = exponentialSearch(searchArr, N, target);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(stop3 - start3);

    if (result != -1)
        cout << "Element found at index (Exponential): " << result << endl;
    else
        cout << "Element not found in the array." << endl;

    cout << "Search Time (Exponential): " << duration3.count() << " ms" << endl;

    cout << "\nEnter the number of random elements for Binary Search: ";
    int M;
    cin >> M;
    int* binaryArr = new int[M];
    generateRandomNumbers(binaryArr, M, 1000);
    sort(binaryArr, binaryArr + M);

    cout << "Sorted array:\n";
    printArray(binaryArr, M);

    cout << "Enter the number to search (Binary): ";
    cin >> target;
    auto start4 = high_resolution_clock::now();
    result = binarySearch(binaryArr, 0, M - 1, target);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(stop4 - start4);

    if (result != -1)
        cout << "Element found at index (Binary): " << result << endl;
    else
        cout << "Element not found in the array." << endl;

    cout << "Search Time (Binary): " << duration4.count() << " ms" << endl;

    delete[] searchArr;
    delete[] binaryArr;
    return 0;
}
