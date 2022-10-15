#include<iostream>
#include<algorithm>
using namespace std;

int const MAX {100};
int const MAX_borrowed {5};

struct book{
    int book_id;
    string book_name;
    int total_quantity;
    int total_borrowed;
    string users_names[MAX_borrowed];
    int user_ids;

    book(){
        book_id = 0;
        total_quantity = total_borrowed = 0;
        for(int i=0; i<MAX_borrowed; i++)
            users_names[i] = "$";
        user_ids = 0;
    }

    void add(){
        cout << "Enter book ID, Name, and Quantity: ";
        cin >> book_id >> book_name >> total_quantity;
        return;
    }

    bool search_by_prefix(string str){
        int sz = str.size();
        if(sz>(int)book_name.size())
            return false;
        for(int i=0; i<sz; i++){
            if(book_name[i]!=str[i])
                return false;
        }
        return true;
    }

    void print(){
        cout << "ID: " << book_id << ", Name: " << book_name;
        cout << " Total Quantity: " << total_quantity << " Total Borrowed: " << total_borrowed;
        return;
    }

    bool is_valid_operation(string u_name){
        if(total_borrowed==total_quantity){
            cout << "No enough copies.\n";
            return false;
        }
        for(int i=0; i<MAX_borrowed; i++){
            if(users_names[i]==u_name){
                cout << "He already borrowed this item.\n";
                return false;
            }
        }
        return true;
    }

    void borrow_book(string u_name){
        for(int i=0; i<MAX_borrowed; i++){
            if(users_names[i]=="$"){
                users_names[i] = u_name;
                total_borrowed++;
                user_ids++;
                break;
            }
        }
        return;
    }

    void return_book(string u_name){
        for(int i=0; i<MAX_borrowed; i++){
            if(users_names[i]==u_name){
                users_names[i] = "$";
                total_borrowed--;
                user_ids--;
                break;

            }
        }
        return;
    }

    void borrowed_names(){
        if(user_ids==0){
            cout << "No borrowed copies.\n";
            return;}
        for(int i=0; i<MAX_borrowed; i++){
            if(users_names[i]!="$")
                cout << users_names[i] << "\n";
        }
    }
};

bool compare_by_id(book &id1, book &id2){
        return id1.book_id<id2.book_id;
}

bool compare_by_name(book &n1, book &n2){
        return n1.book_name<n2.book_name;
}

struct user{
    int user_id;
    string user_name;
    int books_IDs[MAX] {0};
    int ids_cnt;

    user(){
        user_id = 0;
        user_name = "";
        ids_cnt = 0;
    }

    void add(){
        cout << "Enter user's Name, and ID: ";
        cin >> user_name >> user_id;
        return;
    }

    void print(){
        cout << "ID: " << user_id << " Name: " << user_name;
        cout << " Books_IDs: ";
        if(ids_cnt==0)
            return;
        for(int i=0; i<MAX; i++){
            if(books_IDs[i]!=0)
                cout << books_IDs[i] << " ";
        }
        return;
    }

    bool is_valid_operation(){
        if(ids_cnt==MAX_borrowed){
            cout << "Sorry, he borrowed 5 items already.\n";
            return false;
        }
        return true;
    }

    void borrow_book(int book_id){
        for(int i=0; i<MAX_borrowed; i++){
            if(books_IDs[i]==0){
                books_IDs[i] = book_id;
                ids_cnt++;
                break;
            }
        }
       return;
    }

    bool return_book(int book_id){
        for(int i=0; i<MAX_borrowed; i++){
            if(book_id==books_IDs[i]){
                books_IDs[i]=0;
                ids_cnt--;
                return true;
            }
        }
        cout << "He dosn't have this book.\n";
        return false;
    }
};


struct library_system{
    book books[MAX];
    int books_cnt;
    user users[MAX];
    int users_cnt;

    library_system(){
        for(int i=0; i<MAX; i++){
            books[i] = book();
            users[i] = user();
        }
        books_cnt = 0;
        users_cnt = 0;
    }

    int menu(){
        int choose = -1;
        while(choose==-1){
            cout << "\nLibrary System;\n";
            cout << "1) Add a book\n";
            cout << "2) Search books\n";
            cout << "3) Who borrowed book\n";
            cout << "4) Print library by IDs\n";
            cout << "5) Print library by Names\n";
            cout << "6) Add a user\n";
            cout << "7) Borrow a book\n";
            cout << "8) Return a book\n";
            cout << "9) Print users\n";
            cout << "10) Exit\n";
            cout << "\nEnter a choice from [1 - 10]: ";
            cin >> choose;

            if(!(1<=choose && choose<=10)){
                cout << "Invalid Input. Try again!\n";
                choose = -1;
            }
        }
        return choose;
    }

    void add_book(){ //can aggregate same books name, and ID to quantity only
        books[books_cnt++].add();
        return;
    }

    void search_books_by_prefix(){
        string str;
        cout << "Enter book name: ";
        cin >> str;
        bool found = true;
        for(int i=0; i<books_cnt; i++){
            if(books[i].search_by_prefix(str)){
                cout << books[i].book_name <<"\n";
                found = false;
            }
        }
        if(found)
            cout << "There is no books with such a prefix.\n";
        return;
    }

    void print_who_borrowed_book_by_name(){
        string b_name;
        cout << "Enter book name: ";
        cin >> b_name;
        int book_idx;
        bool found = false;
        for(int i=0; i<books_cnt; i++){
            if(books[i].book_name==b_name){
                book_idx = i;
                found = true;
                break;
            }
        }
        if(found)
            books[book_idx].borrowed_names();
        else
            cout << "Invalid Book.\n";
        return;
    }

    void print_library_by_id(){
        sort(books, books + books_cnt, compare_by_id);
        for(int i=0; i<books_cnt; i++){
            books[i].print();
            cout << "\n";
        }
        return;
    }

    void print_library_by_name(){
        sort(books, books + books_cnt, compare_by_name);
        for(int i=0; i<books_cnt; i++){
            books[i].print();
            cout << "\n";
        }
        return;
    }

    void add_user(){
        users[users_cnt++].add();
        return;
    }

    void user_borrow_book(){
        string u_name, b_name;
        cout << "Enter user name, and book name: ";
        cin >> u_name >> b_name;
        int user_idx, book_idx;
        bool found = false;
        for(int i=0; i<users_cnt; i++){
            if(users[i].user_name == u_name){
                user_idx = i;
                found = true;
                break;
            }
        }
        if(!found){
            cout << "Invalid User name.\n";
            return;
        }
        found = false;
        for(int i=0; i<=books_cnt; i++){
            if(books[i].book_name==b_name){
                book_idx = i;
                found = true;
                break;
        }
    }
    if(!found){
        cout << "Invalid book name.\n";
        return;
        }
    found = books[book_idx].is_valid_operation(u_name);
    if(found)
        found = users[user_idx].is_valid_operation();
    else
        return;
    if(found){
        int book_id = books[book_idx].book_id;
        books[book_idx].borrow_book(u_name);
        users[user_idx].borrow_book(book_id);
        }
        return;
    }

    void user_return_book(){
        string u_name, b_name;
        cout << "Enter user name, and book name: ";
        cin >> u_name >> b_name;
        int user_idx, book_idx;
        bool found = false;
        for(int i=0; i<users_cnt; i++){
            if(users[i].user_name==u_name){
                user_idx = i;
                found = true;
                break;
            }
        }
        if(!found){
            cout << "Invalid User name.\n";
            return;
        }
        found = false;
        for(int i=0; i<=books_cnt; i++){
            if(books[i].book_name==b_name){
                book_idx = i;
                found = true;
                break;
        }
    }
    if(!found){
        cout << "Invalid book name.\n";
        return;
        }
    int book_id = books[book_idx].book_id;
    found = users[user_idx].return_book(book_id);
    if(found)
        books[book_idx].return_book(u_name);
    return;
    }

    void print_users(){
        for(int i=0; i<users_cnt; i++){
            users[i].print();
            cout << "\n";
        }
        return;
    }

    void run(){
        while(true){
            int choice = menu();

            if(choice==1)
                add_book();
            else if(choice==2)
                search_books_by_prefix();
            else if(choice==3)
                print_who_borrowed_book_by_name();
            else if(choice==4)
                print_library_by_id();
            else if(choice==5)
                print_library_by_name();
            else if(choice==6)
                add_user();
            else if(choice==7)
                user_borrow_book();
            else if(choice==8)
                user_return_book();
            else if(choice==9)
                print_users();
            else
                break;
        }
    }
};



int main(){
    //freopen("\\test_sample.txt", "rt", stdin);
    library_system Library = library_system();
    Library.run();

    return 0;
}
