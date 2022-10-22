#include "DLL.h"
#include "process.h"
#include<iostream>
using namespace std;

template<class type>
DLL<type>::DLL(){ }

template<class type>
void DLL<type>::link(Node* first, Node* second){
    if(first)
        first->next = second;
    if(second)
        second->previous = first;
}

template<class type>
void DLL<type>::delete_node(Node* node){
    if(!head)
        return;

    if(node == head)
        head = head->next;
    else if(node == tail)
        tail = tail->previous;
    else
        link(node->previous, node->next);

    delete node;
}

template<class type>
void DLL<type>::add_end(const type &data){
	Node* node = new Node(data);

	if(!head)
		head = tail = cursor = node;
    else{
        link(tail, node);
        tail = node;
    }

}

template<class type>
void DLL<type>::delete_cursor(){
    Node* target = cursor;
    cursor = cursor->previous;
    delete_node(target);
}

template<class type>
type DLL<type>::get_current_data(){
    return cursor->data;
}

template<class type>
void DLL<type>::modify_cursor(const type& data){
    this->cursor->data = data;
}

template<class type>
void DLL<type>::move_cursor(){
    if(!head)
        return;
    if(cursor == tail)
        cursor = head;
    else
        cursor = cursor->next;;
}

template<class type>
void DLL<type>::print_list_content(){
	for(Node* cur=head; cur; cur=cur->next)
		cout << cur->data << endl;
}

template<class type>
int DLL<type>::total_added_nodes(){
	int ret{};
	for(Node* cur=head; cur; cur=cur->next)
		ret++;
	return ret;
}

template<class type>
DLL<type>::~DLL(){
	while(head){
	    Node* cur = head;
		head = head->next;
		delete cur;
	}
}

template class DLL<process>;
template class DLL<int>;
