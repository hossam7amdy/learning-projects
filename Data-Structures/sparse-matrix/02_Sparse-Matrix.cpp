#include<iostream>
#include<assert.h>
using namespace std;

struct ColumnNode{
    int data;
    int column;
    ColumnNode* next{ };
    ColumnNode* previous{ };

    ColumnNode(const int &data, const int &column): data(data), column(column) {  }
    ~ColumnNode(){
        cout << "Column data " << data << " deleted with address " << &data << " at column " << column << "\n";
    }
};

class ColumnLinkedList{
private:
    ColumnNode* head{};
    ColumnNode* tail{};
    int length = 0; // total number of nodes
    int capacity; // total length

    void link(ColumnNode *first, ColumnNode *second){
        if(first)
            first->next = second;
        if(second)
            second->previous = first;
    }
    ColumnNode* embed_after(ColumnNode* col_before, int data, int col){
        ColumnNode* new_column = new ColumnNode(data, col);
        length++;

        ColumnNode* col_after = col_before->next;
        link(col_before, new_column);

        if(!col_after)
            tail = new_column;
        else
            link(new_column, col_after); // it is a middle node

        return new_column;
    }
    ColumnNode* get_col(int col, bool create_one = false){
        ColumnNode* cur_col = head;
        while(cur_col->next && cur_col->next->column < col)
            cur_col = cur_col->next;

        bool found = cur_col->next && cur_col->next->column == col;

        if(found)
            return cur_col->next;

        if(!create_one)
            return nullptr;

        return embed_after(cur_col, 0, col);
    }

public:
    ColumnLinkedList(int capacity):capacity(capacity){
        if(capacity<0)
            this->capacity = 0;

        ColumnNode* dummy = new ColumnNode(0,-1);
        head=tail=dummy;
    }
    ColumnLinkedList(const ColumnLinkedList&) = delete;
    void operator=(const ColumnLinkedList&) = delete;
    ~ColumnLinkedList(){
        ColumnNode* cur_col = head;
        while(head){
            cur_col = head->next;
            delete head;
            head = cur_col;
        }
    }

    void set_value(const int &data, const int &col){ // time O(n) - memory O(1)
        if(0>col || col>=capacity)
            return;

        get_col(col,true)->data = data;
    }
    int get_value(int col) { // time O(n) - memory o(1)
        if(0>col || col>=capacity)
            return -1;

        return get_col(col,true)->data;
    }

    void add(const ColumnLinkedList &other){ // only if two of the same length
        if(!other.length)
            return;

        for(ColumnNode* other_col = other.head->next; other_col; other_col = other_col->next){
            ColumnNode* this_node = get_col(other_col->column, true);
            this_node->data += other_col->data;
        }
    }

    void print_row() const {
        if(!capacity)
            return;

        ColumnNode* cur_col = head->next;
        for(int i=0; i<capacity; ++i){
            if(cur_col && cur_col->column == i)
                cout << cur_col->data << " ", cur_col = cur_col->next;
            else
                cout << "0 ";
        }
        cout << "\n";
    }
    void print_row_nonzero() const {
        if(!length)
            return;

        for(ColumnNode* cur_col = head->next; cur_col; cur_col = cur_col->next)
            cout << cur_col->data << " ";
        cout << "\n";
    }
};

struct RowNode{
    int row;
    ColumnLinkedList col_list;

    RowNode *next{ };
    RowNode *previous{ };

    RowNode(const int &row, const int &cols):
        row(row), col_list(cols){
    }
    ~RowNode(){
        //cout << "Row index " << rows << "deleted\n";
    }
};

class SparseMatrix{
private:
    RowNode *head{ };
    RowNode *tail{ };

    int length = 0;

    int rows { };
    int cols{ };

    void link(RowNode *first, RowNode *second){
        if(first)
            first->next = second;
        if(second)
            second->previous = first;
    }

    RowNode* embed_after(RowNode *row_before, const int &row){
        RowNode* new_row = new RowNode(row,cols);
        length++;

        RowNode* next_row = row_before->next;
        link(row_before, new_row);

        if(!next_row)
            tail = new_row;
        else
            link(new_row, next_row);

        return new_row;
    }
    RowNode* get_row(const int &row, bool create_new = false){
        RowNode *prev_row = head;
        while(prev_row->next && prev_row->next->row < row)
            prev_row = prev_row->next;

        bool found = prev_row->next && prev_row->next->row == row;

        if(found)
            return prev_row->next;

        if(!create_new)
            return nullptr;

        return embed_after(prev_row, row);
    }

public:
    SparseMatrix(const int &r, const int &c): rows(r), cols(c){
        head = tail = new RowNode(-1, c);
        length++;
    }
    void set_value(const int &data, const int &r, const int &c){
        if(0>r || r>rows) return;
        if(0>c || c>cols) return;

        RowNode* node = get_row(r,true);
        node->col_list.set_value(data, c);
    }
    int get_value(const int &r, const int &c){
        if(0>r || r>rows) return -1;
        if(0>c || c>cols) return -1;

        RowNode* node = get_row(r);
        return node->col_list.get_value(c);
    }
    void print_matrix(){
        if(!head) return;

        cout << "\nPrint Matrix: " << rows << " x " << cols << "\n";
        RowNode* cur_row=head->next;
        for(int r=0; r<rows; ++r){
            if(cur_row && cur_row->row == r){
                cur_row->col_list.print_row();
                cur_row = cur_row->next;
            }
            else{
                for(int j=0; j<cols; j++)
                    cout << "0 ";
                cout << "\n";
            }
        }
    }
    void print_matrix_nonzero(){
        for(RowNode* cur_row = head; cur_row; cur_row=cur_row->next)
            cur_row->col_list.print_row_nonzero();
    }
	void add(SparseMatrix &other) {
		assert(rows == other.rows && cols == other.cols);
		// Iterate on the other first, and add it to the current one
		for (RowNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
			RowNode* this_row = get_row(other_cur->row, true);  // **
			this_row->col_list.add(other_cur->col_list);
		}
		// ** We can make this function more efficient, but let's keep simple
	}
};

void test_col() {
	ColumnLinkedList collst(12);
	collst.set_value(10, 10);
	collst.set_value(5, 5);
	collst.set_value(2, 2);
	collst.set_value(7, 7);
	collst.set_value(4, 4);
	collst.print_row();
	collst.add(collst);
	collst.print_row_nonzero();
}

void test_sparse() {
	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	mat.set_value(1, 70, 1);
	mat.print_matrix();
	mat.print_matrix_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat.add(mat2);
	mat.print_matrix_nonzero();
	mat.print_matrix();
}

int main() {
	test_col();
    test_sparse();

	cout << "\n\n\nNO RTE\n";

	return 0;
}

