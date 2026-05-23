#pragma once
#include <vector>
#include <algorithm>  // std::swap

namespace Sorting {

// ── Bubble Sort ─────────────────────────────────────────────────────────────
// Repeatedly swaps adjacent elements that are out of order.
// Time: O(n²) average/worst  |  Space: O(1)
template <typename T>
void bubbleSort(std::vector<T>& arr) {
    const std::size_t n = arr.size();
    for (std::size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (std::size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // already sorted — early exit
    }
}

// ── Selection Sort ──────────────────────────────────────────────────────────
// Selects the minimum element and places it at the current position.
// Time: O(n²) all cases  |  Space: O(1)
template <typename T>
void selectionSort(std::vector<T>& arr) {
    const std::size_t n = arr.size();
    for (std::size_t i = 0; i < n - 1; ++i) {
        std::size_t minIdx = i;
        for (std::size_t j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx]) minIdx = j;
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
}

// ── Insertion Sort ──────────────────────────────────────────────────────────
// Builds the sorted portion one element at a time by inserting each new
// element into its correct position.
// Time: O(n) best, O(n²) average/worst  |  Space: O(1)
template <typename T>
void insertionSort(std::vector<T>& arr) {
    const std::size_t n = arr.size();
    for (std::size_t i = 1; i < n; ++i) {
        T key = arr[i];
        std::size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

// ── Merge Sort ──────────────────────────────────────────────────────────────
// Divides the array in half, sorts each half, then merges them.
// Time: O(n log n) all cases  |  Space: O(n)

namespace detail {
    template <typename T>
    void merge(std::vector<T>& arr, std::size_t left, std::size_t mid, std::size_t right) {
        std::vector<T> temp(arr.begin() + left, arr.begin() + right + 1);
        std::size_t lLen = mid - left + 1;
        std::size_t i = 0, j = lLen, k = left;

        while (i < lLen && j < temp.size()) {
            if (temp[i] <= temp[j]) arr[k++] = temp[i++];
            else                    arr[k++] = temp[j++];
        }
        while (i < lLen)        arr[k++] = temp[i++];
        while (j < temp.size()) arr[k++] = temp[j++];
    }

    template <typename T>
    void mergeSortHelper(std::vector<T>& arr, std::size_t left, std::size_t right) {
        if (left >= right) return;
        std::size_t mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
} // namespace detail

template <typename T>
void mergeSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    detail::mergeSortHelper(arr, 0, arr.size() - 1);
}

// ── Quick Sort ───────────────────────────────────────────────────────────────
// Partitions around a pivot so that all smaller elements come before it.
// Time: O(n log n) average, O(n²) worst  |  Space: O(log n) stack
// Uses the median-of-three pivot selection to reduce worst-case probability.

namespace detail {
    template <typename T>
    std::size_t medianOfThree(std::vector<T>& arr, std::size_t lo, std::size_t hi) {
        std::size_t mid = lo + (hi - lo) / 2;
        if (arr[lo] > arr[mid]) std::swap(arr[lo], arr[mid]);
        if (arr[lo] > arr[hi])  std::swap(arr[lo], arr[hi]);
        if (arr[mid] > arr[hi]) std::swap(arr[mid], arr[hi]);
        // Place pivot just before hi to keep the partition loop simple.
        std::swap(arr[mid], arr[hi - 1]);
        return hi - 1;
    }

    template <typename T>
    void quickSortHelper(std::vector<T>& arr, std::size_t lo, std::size_t hi) {
        if (lo + 1 >= hi) {
            // Fall back to insertion sort for tiny sub-arrays.
            if (lo < hi && arr[hi] < arr[lo]) std::swap(arr[lo], arr[hi]);
            return;
        }
        std::size_t pivotIdx = medianOfThree(arr, lo, hi);
        T pivot = arr[pivotIdx];
        std::size_t i = lo, j = hi - 1;

        while (true) {
            while (arr[++i] < pivot) {}
            while (arr[--j] > pivot) {}
            if (i >= j) break;
            std::swap(arr[i], arr[j]);
        }
        std::swap(arr[i], arr[pivotIdx]);  // restore pivot
        if (i > 0) quickSortHelper(arr, lo, i - 1);
        quickSortHelper(arr, i + 1, hi);
    }
} // namespace detail

template <typename T>
void quickSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    detail::quickSortHelper(arr, 0, arr.size() - 1);
}

} // namespace Sorting
