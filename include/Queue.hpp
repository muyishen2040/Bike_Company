#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED
//latest version
template<class T>
struct Node{
    Node* next;
    Node* prev;
    T data;
};

template<class T>
class Queue{
friend class Company;
friend class Event;
public:
    Queue();
    ~Queue();
    void push(T newData);
    void push(T*& newData);
    void pop();
    T& front();
    Node<T>* newNode(T newData, Node<T>* prevNode);
    void print();
private:
    Node<T>* head;
    Node<T>* tail;
    int num;
};

#include "Queue.tpp"

#endif // QUEUE_HPP_INCLUDED
