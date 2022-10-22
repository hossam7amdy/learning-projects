#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

template<class type>
class DLL{
private:
	struct Node{
		type data{};
		Node* next{};
		Node* previous{};

		Node(const type &data):
		    data(data){
        }
	};

	Node* head{};
	Node* tail{};
	Node* cursor{};

	void link(Node* first, Node* second);
	void delete_node(Node* node);
public:
	DLL();
	DLL(const DLL&) = delete;
	void operator=(const DLL&) = delete;

	void add_end(const type &data);
	int total_added_nodes();
	type get_current_data();
	void modify_cursor(const type &data);
	void move_cursor();
	void delete_cursor();
	void print_list_content();

	~DLL();
};

#endif // DLL_H_INCLUDED
