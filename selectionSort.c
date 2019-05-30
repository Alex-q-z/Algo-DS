#include <stdio.h>
#include <stdlib.h>

void pull_min(int arr[], int len){
  if(len <= 1) return ;
  int minidex = 0;
  int minval = arr[0];
  for(int i=1; i<len; i++){
    if(arr[i] < minval){
      minidex = i;
      minval = arr[i];
    }
  }
  int tmp = arr[0];
  arr[0] = arr[minidex];
  arr[minidex] = tmp;
}

void selection_sort(int arr[], int len){
  while(len >= 1){
    pull_min(arr++,len--);
  }
}
