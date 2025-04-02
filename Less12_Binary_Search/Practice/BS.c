#include <stdio.h>

#define NO_FOUND -1    

int binarySearch(int* arr, int l, int r, int target)
{
    if (r >= l){
        int mid = (r + l) / 2;

        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] > target){
            return binarySearch(arr, l, mid - 1, target);
        }
        else{
            return binarySearch(arr, mid + 1, r, target);
        }
    }
    return NO_FOUND;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int result = binarySearch(arr, 0, n - 1, target);
    if (result != -1)
        printf("Phần tử %d được tìm thấy tại vị trí %d\n", target, result);
    else
        printf("Phần tử %d không tồn tại trong mảng\n", target);

    return 0;
}
