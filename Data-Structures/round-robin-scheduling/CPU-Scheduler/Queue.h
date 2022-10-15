#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<class type>
class Queue{
private:
    struct Node{
        type data;
        Node* next{};

        Node(const type &data):
            data(data){
        }
    };

    Node* head{};
    Node* tail{};
    int sz{};

public:
    Queue();
    Queue(const Queue &another) = delete;
    void operator=(const Queue &another) = delete;

    void Enqueue(const type &data);
    type Dequeue();
    int Size() const ;
    void print() const;
    bool isEmpty() const;

    ~Queue();
};

#endif // QUEUE_H_INCLUDED
