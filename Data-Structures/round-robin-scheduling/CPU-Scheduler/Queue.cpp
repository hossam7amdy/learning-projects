#include "Queue.h"
#include "process.h"

#include<assert.h>
#include<iostream>

using namespace std;

template<class type>
Queue<type>::Queue(){ }

template<class type>
void Queue<type>::Enqueue(const type &data){
    Node* item = new Node(data);

    if(isEmpty())
        head = tail = item;
    else{
        tail->next = item;
        tail = item;
        tail->next = head;
    }
    sz++;
}

template<class type>
type Queue<type>::Dequeue(){
    assert(!isEmpty());
    type cur = head->data;

    Node* h = head;
    if(h->next){
        head = h->next;
        tail->next = head;
    }
    else
        head = tail = nullptr;

    delete h;
    --sz;

    return cur;
}

template<class type>
int Queue<type>::Size() const {
    return sz;
}

template<class type>
void Queue<type>::print() const {
    assert(!isEmpty());

    Node* cur=head;
    for(int i=0; i<sz; i++){
        cout << cur->data << endl;
        cur=cur->next;
    }
}

template<class type>
bool Queue<type>::isEmpty() const {
    return !sz;
}

template<class type>
Queue<type>::~Queue(){
    while(head){
        Node* cur = head->next;
        delete head;
        head = cur;
    }
}

template class Queue<process>;
template class Queue<int>;
