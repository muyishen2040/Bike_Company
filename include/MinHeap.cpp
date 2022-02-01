#include <iostream>
#include "MinHeap.hpp"

using namespace std;
//latest version
MinHeap::MinHeap(int init){
    arr = new int[init];
    cnt = 1;
    capacity = init;
}

MinHeap::MinHeap(int* data, int data_size){
    arr = new int[data_size*2+5];
    cnt = 1 + data_size;
    capacity = data_size*2+5;
    copy(data, data+data_size, arr+1);
}

MinHeap::~MinHeap(){
    delete [] arr;
}

void MinHeap::change_size1D(int*& arr, int old_size, int new_size){
    int* newPtr = new int[new_size];
    copy(arr, arr+old_size, newPtr);
    delete [] arr;
    arr = newPtr;
}

void MinHeap::push(int new_item){
    if(cnt==capacity-1){
        change_size1D(arr, capacity, capacity*2);
        capacity = capacity*2;
        
    }
    arr[cnt++] = new_item;
    int cur_idx = cnt-1;
    
    while(cur_idx>1){
        if(arr[cur_idx]<arr[cur_idx/2]){
            int tmp = arr[cur_idx];
            arr[cur_idx] = arr[cur_idx/2];
            arr[cur_idx/2] = tmp;
            cur_idx = cur_idx/2;
        }
        else
            break;
    }
    
}

void MinHeap::pop(){
    if(cnt<=1)
        return;
    arr[1] = arr[cnt-1];
    cnt = cnt - 1;
    int cur_idx = 1;
    while(cur_idx<cnt){
        if(cur_idx*2<cnt&&cur_idx*2+1<cnt){
            if(arr[cur_idx*2]<=arr[cur_idx*2+1]&&arr[cur_idx*2]<arr[cur_idx]){
                int tmp = arr[cur_idx*2];
                arr[cur_idx*2] = arr[cur_idx];
                arr[cur_idx] = tmp;
                cur_idx = cur_idx*2;
            }
            else if(arr[cur_idx*2+1]<arr[cur_idx*2]&&arr[cur_idx*2+1]<arr[cur_idx]){
                int tmp = arr[cur_idx*2+1];
                arr[cur_idx*2+1] = arr[cur_idx];
                arr[cur_idx] = tmp;
                cur_idx = cur_idx*2 + 1;
            }
            else
                break;

        }
        else if(cur_idx*2<cnt){
            if(arr[cur_idx*2]<arr[cur_idx]){
                int tmp = arr[cur_idx*2];
                arr[cur_idx*2] = arr[cur_idx];
                arr[cur_idx] = tmp;
                break;
            }
            else
                break;
        }
        else
            break;
    }
}

int MinHeap::top(){
    if(cnt>1){
        return arr[1];
    }
    return -1;//The Heap is empty
}

void MinHeap::print(){
    for(int i=1;i<cnt;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int MinHeap::get_count(){
    return cnt-1;
}
