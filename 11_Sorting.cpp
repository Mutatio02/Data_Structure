#include <iostream>
#include <algorithm>
#include <vector>
// 24.10.03 sorting practice
using namespace std;

void Bubble_Sort(int arr[], int len) {

    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void Insert_Sort(int arr[], int len) {
    for (int i = 1; i < len; i++) { // 첫번째 원소의 다음 부터 비교
        int tmp = arr[i];

        int j;
        for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}
void Quick_sort(int arr[], int start, int end) {
    if (start >= end)  return;

    int pivot = arr[start];
    int left = start + 1;
    int right = end;

    while (left <= right) {
        while (left <= end && arr[left] <= pivot)  left++; // pivot보다 작은수를 찾기위해 오른쪽 이동
        while (right > start && arr[right] > pivot)  right--; // pivot보다 큰 수를 찾기 위해 왼쪽으로 이동

        if (left <= right) swap(arr[left], arr[right]); // 왼쪽과 오른쪽의 값을 비교해서 swap
    }
    swap(arr[start], arr[right]); // pivot을 right로 업데이트

    Quick_sort(arr, start, right - 1); // pivot의 왼쪽
    Quick_sort(arr, right + 1, end); // pivot의 오른쪽
}

int main()
{
    int arr[] = { 6,4,2,3,1,5 };
    int len = sizeof(arr) / sizeof(arr[0]);

    //Bubble_Sort(arr,len); 
    //Insert_Sort(arr, len);
    //Quick_sort(arr, 0, len - 1); 
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}

