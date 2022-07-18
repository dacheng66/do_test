#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000

static int left[MAX_LEN];
static int right[MAX_LEN];

void InitChildren(const int arr[], int arrLen){
  int max = 1;
  for(int i = 0; i < arrLen; i++){
    if(arr[i] != -1){
      left[i] = max++;   //给的数组你想要处理左右树时，可以这么处理，不然MyTree *left;不好给定义
      right[i] = max++;
    }
  }
}

int GetSum(const int arr[], int arrLen, int index){ //二叉树从index节点计算二叉树的和
  if(index >= arrLen){
    return 0;
  }
  if(arr[index] == -1){
    return 0;
  }
  int l = GetSum(arr, arrLen, left[index]);
  int r = GetSum(arr, arrLen, right[index]);
  return arr[index] + l + r;
}

int GetSubTreeRoot(const int* arr, int arrLen){
  InitChildren(arr, arrLen);
  int total = GetSum(arr, arrLen, 0);
  for(int i = 1; i < arrLen; ++i){
    int sum = GetSum(arr, arrLen, i);
    if(total == sum * 2){
      return i;
    }
  }
  return -1;
}

int main(void){
  int arrLen = 7;
  int arr[MAX_LEN] = {9,13,12,-1,-1,2,8};
  int result = GetSubTreeRoot(arr, arrLen);
  printf("%d", result);
  return 0;
}