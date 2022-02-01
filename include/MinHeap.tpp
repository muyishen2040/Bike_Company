#include <iostream>

using namespace std;

template<class T>
MinHeap<T>::MinHeap(int init){
    arr = new T[init];
    cnt = 1;
    capacity = init;
}

template<class T>
MinHeap<T>::MinHeap(T* data, int data_size){
    arr = new int[data_size*2];
    cnt = 1 + data_size;
    capacity = data_size*2;
    copy(data, data+data_size, arr+1);
}

template<class T>
MinHeap<T>::~MinHeap(){
    delete [] arr;
}

template<class T>
void MinHeap<T>::change_size1D(T*& arr, int old_size, int new_size){
    T* newPtr = new T[new_size];
    copy(arr, arr+old_size, newPtr);
    delete [] arr;
    arr = newPtr;
}

template<class T>
void MinHeap<T>::push(T new_item){
    if(cnt==capacity-1){
        change_size1D(arr, capacity, capacity*2);
        capacity = capacity*2;
    }
    arr[cnt++] = new_item;
    int cur_idx = cnt-1;
    while(cur_idx>1){
        if(arr[cur_idx]<arr[cur_idx/2]){
            T tmp = arr[cur_idx];
            arr[cur_idx] = arr[cur_idx/2];
            arr[cur_idx/2] = tmp;
            cur_idx = cur_idx/2;
        }
        else
            break;
    }
}

template<class T>
void MinHeap<T>::pop(){
    if(cnt<=1)
        return;
    arr[1] = arr[cnt-1];
    cnt = cnt - 1;
    int cur_idx = 1;
    while(cur_idx<cnt){
        if(cur_idx*2<cnt&&cur_idx*2+1<cnt){
            if(arr[cur_idx*2]<=arr[cur_idx*2+1]&&arr[cur_idx*2]<arr[cur_idx]){
                T tmp = arr[cur_idx*2];
                arr[cur_idx*2] = arr[cur_idx];
                arr[cur_idx] = tmp;
                cur_idx = cur_idx*2;
            }
            else if(arr[cur_idx*2+1]<arr[cur_idx*2]&&arr[cur_idx*2+1]<arr[cur_idx]){
                T tmp = arr[cur_idx*2+1];
                arr[cur_idx*2+1] = arr[cur_idx];
                arr[cur_idx] = tmp;
                cur_idx = cur_idx*2 + 1;
            }
            else
                break;

        }
        else if(cur_idx*2<cnt){
            if(arr[cur_idx*2]<arr[cur_idx]){
                T tmp = arr[cur_idx*2];
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

template<class T>
T MinHeap<T>::top(){
    if(cnt>1){
        return arr[1];
    }
    return -1;//The Heap is empty
}

template<class T>
void MinHeap<T>::print(){
    for(int i=1;i<cnt;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

template<class T>
int MinHeap<T>::get_count(){
    return cnt-1;
}
