#ifndef MINHEAP_HPP_INCLUDED
#define MINHEAP_HPP_INCLUDED
//latest version
class MinHeap{
friend class Station;
friend class Company;
public:
    MinHeap(int init=5);
    MinHeap(int* data, int data_size);
    ~MinHeap();
    void change_size1D(int*& arr, int old_size, int new_size);
    void push(int new_item);
    void pop();
    int top();
    void print();
    int get_count();
private:
    int* arr;
    int cnt;//init value = 1  num = cnt-1
    int capacity;
};

#endif // MINHEAP_HPP_INCLUDED
