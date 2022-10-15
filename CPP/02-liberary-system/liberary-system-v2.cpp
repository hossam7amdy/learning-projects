#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

//to use later
const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct book{
    int id;
    string name;
    int total_quantity;
    int total_borrowed;

    book(){
        id = -1;
        total_quantity = total_borrowed = 0;
        name = "";
    }

    void add(){
        cout << "Enter book ID, Name, and Quantity: ";
        cin >> id >> name >> total_quantity;
        return;
    }

    bool search_by_prefix(string str){
        int sz = str.size();
        if(sz>(int)name.size())
            return false;
        for(int i=0; i<sz; i++){
            if(name[i]!=str[i])
                return false;
        }
        return true;
    }

    void print(){
        cout << "ID: " << id << ", Name: " << name;
        cout << " Total Quantity: " << total_quantity << " Total Borrowed: " << total_borrowed;
        return;
    }

    bool borrow_book(){
        if(total_quantity==total_borrowed)
            return false;
        total_borrowed++;
        return true;
    }

    void return_book(){
         total_borrowed--;
         return;
     }
};

bool compare_by_id(book &id1, book &id2){
    return id1.id<id2.id;
}

bool compare_by_name(book &n1, book &n2){
    return n1.name<n2.name;
}

struct user{
    int id;
    string name;
    set<int> books_IDs;

    user(){
        id = -1;
        name = "";
    }

    void add(){
        cout << "Enter user's Name, and ID: ";
        cin >> name >> id;
        return;
    }

    void print(){
        cout << "ID: " << id << " Name: " << name;
        cout << " Books_IDs: ";

        for(const auto id : books_IDs)
            cout << id << " ";
        cout << "\n";
        return;
    }

    void borrow_book(int book_id){
        if(auto [iter, done] = books_IDs.insert(book_id); done) // structured binding
            return;
        cout << "He already has this one.\n";
        return;
    }

    bool return_book(int book_id){
        auto it = books_IDs.find(book_id);
        if(it != books_IDs.end()){
            books_IDs.erase(it);
            return true;
        }
        return false;
    }

    bool is_borrowed(int book_id){
        auto it = books_IDs.find(book_id);
        if(it != books_IDs.end())
            return true;
        return false;
    }
};


struct library_system{
    vector<book> books;
    vector<user> users;

    library_system(){ }

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

    void add_book(){
        book b;
        b.add();
        books.push_back(b);
        return;
    }

    void search_books_by_prefix(){
        string str;
        cout << "Enter book name: ";
        cin >> str;
        bool found = true;
        for(auto &book : books){
            if(book.search_by_prefix(str)){
                cout << book.name <<"\n";
                found = false;
            }
        }
        if(found)
            cout << "There is no books with such a prefix.\n";
        return;
    }

    int book_idx_by_name(string b_name){
        for(int i=0; i<(int)books.size(); i++){
            if(books[i].name==b_name)
                return i;
        }
        return -1;
    }

    int user_idx_by_name(string u_name){
        for(int i=0; i<(int)users.size(); i++){
            if(users[i].name==u_name)
                return i;
        }
            return -1;
    }

    bool read_username_and_bookname(int &user_idx, int &book_idx, int trials = 3){
        string b_name, u_name;
        while(trials--){
            cout << "Enter user and book name: ";
            cin >> u_name >> b_name;
            user_idx = user_idx_by_name(u_name);
            if(user_idx==-1){
                cout << "Invalid user name. Try again!\n";
                continue;
            }
            book_idx = book_idx_by_name(b_name);
            if(book_idx==-1){
                cout << "Invalid book name. Try again!\n";
                continue;
            }
            return true;
        }
        cout << "You did several trials. Try later.\n";
        return false;
    }

    void print_who_borrowed_book_by_name(){
        string name;
        cout << "Enter book name: ";
        cin >> name;
        int book_idx = book_idx_by_name(name);
        if(book_idx==-1){
            cout << "Invalid book name.\n";
            return;
        }
        int book_id = books[book_idx].id;
        bool found = false;
        for(int i=0; i<(int)users.size(); i++){
            if(users[i].is_borrowed(book_id)){
                cout << users[i].name << "\n";
                found = true;
            }
        }
        if(!found)
            cout << "No one borrowed this book.\n";
        return;
    }

    void print_library_by_id(){
        sort(books.begin(), books.end(), compare_by_id);
        for(auto &book : books)
            book.print(), cout << "\n";
        return;
    }

    void print_library_by_name(){
        sort(books.begin(), books.end(), compare_by_name);
        for(auto &book : books)
            book.print(), cout << "\n";
        return;
    }

    void add_user(){
        user u;
        u.add();
        users.push_back(u);
        return;
    }

    void user_borrow_book(){
        int book_idx, user_idx;
        if(!read_username_and_bookname(user_idx, book_idx))
            return;

        int book_id = books[book_idx].id;
        int user_id = users[user_idx].id;

        if(!books[book_idx].borrow_book())
            cout << "No available copies now. Check out later.\n";
        else
            users[user_idx].borrow_book(book_id);
        return;
    }

    void user_return_book(){
        int book_idx, user_idx;
        if(!read_username_and_bookname(user_idx, book_idx))
            return;

        int book_id = books[book_idx].id;
        int user_id = users[user_idx].id;

        if(!users[user_idx].return_book(book_id))
            cout << "He doesn't borrow this book.\n";
        else
            books[book_idx].return_book();
        return;
    }

    void print_users(){
        for(auto &user : users)
            user.print();
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
    library_system Library;
    Library.run();

    return 0;
}
