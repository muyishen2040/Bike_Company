#include <iostream>
//latest version
template<class T>
Queue<T>::Queue(){
    head = nullptr;
    tail = nullptr;
    num = 0;
}

template<class T>
Queue<T>::~Queue(){
    Node<T>* curPtr = head;
    while(curPtr!=nullptr){
        Node<T>* tmp = curPtr;
        curPtr = curPtr->next;
        delete tmp;
    }
}

template<class T>
void Queue<T>::push(T*& newData){
    if(head==nullptr){
        head = newNode(*newData, nullptr);
        tail = head;
        num++;
        return ;
    }
    tail->next = newNode(*newData, tail);
    num++;
    tail = tail->next;
}

template<class T>
void Queue<T>::push(T newData){
    if(head==nullptr){
        head = newNode(newData, nullptr);
        tail = head;
        num++;
        return ;
    }
    tail->next = newNode(newData, tail);
    num++;
    tail = tail->next;
}

template<class T>
void Queue<T>::pop(){
    if(head==nullptr)
        return;
    if(head==tail){
        delete head;
        tail = nullptr;
        head = nullptr;
        num--;
    }
    else{
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        num--;
    }
}

template<class T>
Node<T>* Queue<T>::newNode(T newData, Node<T>* prevNode){
    Node<T>* ret = new Node<T>;
    ret->data = newData;
    ret->next = nullptr;
    ret->prev = prevNode;
    return ret;
}

template<class T>
T& Queue<T>::front(){
    if(head==nullptr){
        std::cerr << "The Queue is Empty" << std::endl;
        exit(1);
    }
    return head->data;
}

template<class T>
void Queue<T>::print(){
    Node<T>* curPtr = head;
    while(curPtr!=nullptr){
        std::cout<<curPtr->data<<" ";
        curPtr = curPtr->next;
    }
    std::cout<<std::endl;
    std::cout<<"Total number: "<<num<<std::endl;
}
