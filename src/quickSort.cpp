#include <iostream>
#include <vector>

// 快速排序核心函数
void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[left]; // 基准值
    int i = left, j = right;

    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        while (i < j && arr[i] <= pivot) i++;
        if (i < j) std::swap(arr[i], arr[j]);
    }

    std::swap(arr[left], arr[i]); // 把基准值放到中间

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

int main() {
    std::vector<int> arr = {34, 7, 23, 32, 5, 62};

    std::cout << "原数组: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "排序后: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
