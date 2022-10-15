#include<iostream>
using namespace std;

struct Node{
    int data;
    int index;
    Node* next{};
    Node* previous{};

    Node(int data, int index): data(data), index(index) {  }
    ~Node(){
        cout << "Node " << data << " deleted with address " << &data << " at index " << index << "\n";
    }
};

class ArrayLinkedList{
private:
    Node* head{};
    Node* tail{};
    int length{}; // total number of nodes
    int capacity; // total length

    // private member functions (Abstraction)
    void link(Node *first, Node *second){
        if(first)
            first->next = second;
        if(second)
            second->previous = first;
    }
    Node* embed_after(Node* node_before, int data, int idx){
        Node* new_node = new Node(data, idx);
        length++;

        Node* node_after = node_before->next;
        link(node_before, new_node);

        if(!node_after)
            tail = new_node;
        else
            link(new_node, node_after); // it is a middle node

        return new_node;
    }
    Node* get_index(int idx, bool create_one = false){
        Node* cur = head;
        while(cur->next && cur->next->index < idx)
            cur = cur->next;

        bool found = cur->next && cur->next->index == idx;

        if(found)
            return cur->next;

        if(!create_one)
            return nullptr;

        return embed_after(cur, 0, idx);
    }

public:
    ArrayLinkedList(int capacity):capacity(capacity){
        if(capacity<0)
            this->capacity = 0;

        Node* dummy = new Node(0,-1);
        head=tail=dummy;
    }
    ArrayLinkedList(const ArrayLinkedList&) = delete;
    void operator=(const ArrayLinkedList&) = delete;
    ~ArrayLinkedList(){
        Node* cur = head;
        while(head){
            cur=head->next;
            delete head;
            head = cur;
        }
    }

    void set_value(const int &data, const int &pos){ // time O(n) - memory O(1)
        if(0>pos || pos>=capacity)
            return;

        get_index(pos,true)->data = data;
    }
    int get_value(int pos) { // time O(n) - memory o(1)
        if(0>pos || pos>=capacity)
            return -1;

        return get_index(pos,true)->data;
    }

    void add_array(const ArrayLinkedList &other){ // only if two of the same length
        if(!other.length)
            return;

        for(Node* other_cur=other.head->next; other_cur; other_cur = other_cur->next){
            Node* this_node = get_index(other_cur->index, true);
            this_node->data += other_cur->data;
        }
    }

    void print_array() const {
        if(!capacity)
            return;

        Node* cur = head->next;
        for(int i=0; i<capacity; ++i){
            if(cur && cur->index == i)
                cout << cur->data, cur = cur->next;
            else
                cout << 0;

            cout << " ";
        }
        cout << "\n";
    }
    void print_array_nonzero() const {
        if(!length)
            return;

        for(Node* cur=head->next; cur; cur=cur->next)
            cout << "(" << cur->data << ", " << cur->index << ") ";
        cout << "\n";
    }
};

void test_index() {
	ArrayLinkedList array1(10);	// length 10
	array1.set_value(50, 5);
	array1.set_value(20, 2);
	array1.set_value(70, 7);
	array1.set_value(40, 4);
	array1.set_value(0, 4); // modify
	array1.print_array();
	// 0 0 20 0 40 50 0 70 0 0
	array1.print_array_nonzero();
	// 20 40 50 70
	cout << array1.get_value(7) << "\n";	// 70

	ArrayLinkedList array2(15);
	array2.set_value(1, 9);
	array2.set_value(2, 10);
	array2.set_value(3, 13);

	array1.add_array(array2);
	array1.print_array();
	// 0 0 20 0 41 50 4 73 0 0
}

int main() {
	test_index();
	//test_sparse();

	cout << "\n\n\nNO RTE\n";

	return 0;
}

