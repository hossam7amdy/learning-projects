#include<iostream>
#include<sstream>
#include<fstream>
#include<assert.h>
#include<map>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<chrono>
using namespace std;

/// ToDo & Bugs:
/*
1- prevent dublicated sessions
2- Input validations/streaming/prober format => such full name & full page content
3- provide cancel bottom
4-
*/

//////////////////////////Global Helper Methods///////////////////////
const vector<string> ReadFromFile(const string &path)
{
    vector<string> lines;

    fstream file_handler(path.c_str());
    if(file_handler.fail())
    {
        cout << "ERROR: Can't open this file\n";
        return lines;
    }

    string line;
    while(getline(file_handler, line))
    {
        if(line.size()==0)
            continue;
        lines.push_back(line);
    }

    file_handler.close();
    return lines;
}
void WriteToFile(const vector<string> &lines, const string &path, bool append = true)
{
    auto status = ios::in | ios::out | ios::app;
    if(!append)
        status = ios::in | ios::out | ios::trunc;

    fstream file_handler(path.c_str(), status);
    if(file_handler.fail())
    {
        cout << "ERROR: Can't open this file\n";
        return;
    }

    for(const auto &line : lines)
        file_handler << line << "\n";

    file_handler.close();
}
const vector<string> Splitter(const string &line, const string delimiter = "~")
{
    string s = line;
    vector<string> data;

    int pos;
    string sub;
    while((pos = s.find(delimiter)) != -1)
    {
        sub = s.substr(0, pos);
        data.push_back(sub);
        s.erase(0, pos + delimiter.length());
    }
    data.push_back(s);
    return data;
}
const int ToInt(const string &str)
{
    int num;
    istringstream iss(str);
    iss >> num;
    return num;
}
const int ChooseInRange(const int &low, const int &high, string delimiter = " - ")
{
    int choice;
    cout << "\nEnter Number in Range [" << low << delimiter << high << "]: ";
    cin >> choice;
    if(low<=choice && choice <=high && !cin.fail())
        return choice;
    cout << "Invalid Entry, Try Again!\n";
    cin.clear();
    cin.ignore(264, '\n');
    return ChooseInRange(low, high);
}
const int ShowMenu(const vector<string> &menu)
{
    cout << "\nMenu:\n";
    for(int i=0; i<(int)menu.size(); i++)
        cout << "\t" << i+1 << ") " << menu[i] << "\n";
    return ChooseInRange(1, (int)menu.size());
}
const string GetCurrentTimeDate()
{	// src: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}
string ToTitleFormat(const string &name)
{
    string str = "";
    str += toupper(name[0]);
    for(int i=1; i<(int)name.size(); ++i){
        str += tolower(name[i]);
        if(name[i]==' ')
            str += toupper(name[++i]);
    }
    return str;
}
string ToUpper(const string &str)
{
    string s = "";
    for(int i=0; i<(int)str.size(); ++i)
        s += toupper(str[i]);
    return s;
}
////////////////////////////////////////////////////////////////////////

class Book
{
private:
    string ISBN;
    string Title;
    string Author;
    vector<string> Content;

public:
    Book(){
        cout << "Book Constructor\n";
    }
    ~Book(){
        cout << "Destructing Book\n";
    }
    Book(const Book&) = delete;
    void operator=(const Book&) = delete;

    void setISBN(const string &ISBN){
        this->ISBN = ISBN;
    }
    void setTitle(const string &title){
        this->Title = title;
    }
    void setAuthor(const string &author){
        this->Author = author;
    }
    void setContent(const vector<string> &content){
        this->Content = content;
    }
    const string& getISBN() const {
        return this->ISBN;
    }
    const string& getTitle() const {
        return this->Title;
    }
    const string& getAuthor() const {
        return this->Author;
    }
    const vector<string>& getBookContent() const {
        return this->Content;
    }
    const int getHowManyPages() const {
        return Content.size();
    }

    void ReadBookInfo(const string &ISBN){
        setISBN(ISBN);

        string str;
        cout << "Enter Title: ";
        cin.ignore(30, '\n');
        getline(cin, str);
        setTitle(str);

        cout << "Enter Author: ";
        cin >> str;
        setAuthor(str);

        cout << "How Many Pages: ";
        int pages;
        cin >> pages;
        for(int curr_page=1; curr_page<=pages; ++curr_page){
            cout << "Enter Page #" << curr_page << ": ";
            cin.ignore(264, '\n');
            getline(cin, str);
            Content.push_back(str);
        }
    }
    const string ToString() const{
        ostringstream oss;
        oss << " Title: " << getTitle() << " - Author: " << getAuthor();
        return oss.str();
    }
};

class BooksManager
{
private:
    map<string, Book*> books;

    void FreeLoadedData(){
        for(auto &pair : books)
            delete pair.second;

        books.clear();
    }

public:
    BooksManager(){
        cout << "BookManager Constructor\n";
    }
    BooksManager(const BooksManager&) = delete;
    void operator=(const BooksManager&) = delete;

    void LoadDatabase() {
		cout << "BooksManager: LoadDatabase\n";
		FreeLoadedData();

		Book* book1 = new Book();
		book1->setISBN("00001");
		book1->setAuthor("Mostafa");
		book1->setTitle("C++ how to program");
		vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
		book1->setContent(pages1);
		books[book1->getISBN()] = book1;

		Book* book2 = new Book();
		book2->setISBN("00002");
		book2->setAuthor("Morad");
		book2->setTitle("Intro to algo");
		vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
		book2->setContent(pages2);
		books[book2->getISBN()] = book2;

		Book* book3 = new Book();
		book3->setISBN("00003");
		book3->setAuthor("Morad");
		book3->setTitle("Data Structures in C++");
		vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
		book3->setContent(pages3);
		books[book3->getISBN()] = book3;
	}

	// CRUD operations
    void AddBook(){ // create / read
        string ISBN;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        if(books.count(ISBN)){
            cout << "\nAlready Exist.\n";
            return;
        }
        Book *book = new Book();
        book->ReadBookInfo(ISBN);
        books[ISBN] = book;
    }
    void UpdateBook(const string& isbn, const Book* book){
    }
    void DeleteBook(const string& isbn){
    }

    const map<string, Book*> getBooks() const {
        return books;
    }
    void setBooks(const map<string, Book*>& books){
        this->books = books;
    }

    ~BooksManager() {
        cout << "Free: BooksDatabase\n";
		FreeLoadedData();
    }
};

class ReadingSession
{
private:
    Book * book;
    int curr_page;
    string last_read_date;

public:
    ReadingSession():ReadingSession(nullptr) {
        cout << "Session Constructor\n";
    }
    ReadingSession(Book *book): book(book), curr_page(0), last_read_date(GetCurrentTimeDate()) {
    }
    ~ReadingSession(){
        cout << "Destruction ReadingSession\n";
    }
    ReadingSession(const ReadingSession&) = delete;
    void operator=(const ReadingSession&) = delete;

    const int& getLastReadingPage() const {
        return this->curr_page;
    }
    void setLastReadingPage(const int &curr_page) {
        this->curr_page = curr_page;
    }
    const string& getDateOfLastReadingPage() const {
        return this->last_read_date;
    }
    void setDateOfLastReadingPage(const string &last_read_date) {
        this->last_read_date = last_read_date;
    }

    const string& getCurrentPageContent(){
        return book->getBookContent()[curr_page];
    }
    const string PageIdxStr(){
        ostringstream oss;
        oss << getLastReadingPage()+1 << "\\" << book->getHowManyPages();
        return oss.str();
    }
    void GoNextPage(){
        if(curr_page<book->getHowManyPages()-1)
            setLastReadingPage(++curr_page);
    }
    void GoPreviousPage(){
        if(curr_page>0)
            setLastReadingPage(--curr_page);
    }
    void StopReading(){
        setDateOfLastReadingPage(GetCurrentTimeDate());
    }
    const string ToString() const {
        ostringstream oss;
        oss << "Book: " << book->getTitle() << " Page: " << getLastReadingPage()+1 << " - " << getDateOfLastReadingPage();
        return oss.str();
    }
};

class User
{
private:
    string name;
    string userName;
    string email;
    string password;
    bool is_admin;

    vector<ReadingSession*> sessions;
    void FreeSessions(){
        for(auto & s : sessions)
            delete s;
        sessions.clear();
    }

public:
    User(): is_admin(false){
       cout << "User Constructor\n";
    }
    User(const User&) = delete;
    void operator=(const User&) = delete;

    void setName(const string &name){
        this->name = name;
    }
    void setUserName(const string &userName){
        this->userName = userName;
    }
    void setPassword(const string &password){
        this->password = password;
    }
    void setIsAdmin(const int &is_admin){
        this->is_admin = is_admin;
    }
    void setEmail(const string &email){
        this->email = email;
    }
    const string& getName() const{
        return this->name;
    }
    const string& getUserName() const{
        return this->userName;
    }
    const string& getPassword() const{
        return this-> password;
    }
    const bool& getIsAdmin() const{
        return this->is_admin;
    }
    const string& getEmail() const {
        return this->email;
    }

    const string ToString() const {
		ostringstream oss;
		oss << "Name: " << getName();
		if (is_admin)
			oss << " | Admin";
		oss << "\n";
		oss << "Email: " << getEmail() << "\n";
		oss << "User name: " << getUserName() << "\n";
		return oss.str();
	}
    void ReadUser(const string &user_name){
        setUserName(user_name);
        setIsAdmin(false);

        string str;

        cout << "Enter Name: ";
        cin.ignore(20, '\n');
        getline(cin, str);
        setName(str);

        cout << "Enter Email: ";
        cin >> str;
        setEmail(str);

        cout << "Enter Password: ";
        cin >> str;
        setPassword(str);
    }

    const vector<ReadingSession*> getCurrentSessions() const {
        return sessions;
    }
    ReadingSession * AddNewSession(Book *book){
        ReadingSession *session = new ReadingSession(book);
        sessions.push_back(session);
        return session;
    }

    ~User(){
        cout << "Free Sessions\n";
        FreeSessions();
    }
};

class UsersManager
{
private:
    map<string, User*> users;
    User * current_user;

    void FreeLoadedData() {
        for(auto &pair : users)
            delete pair.second;

        users.clear();
        current_user = nullptr;
    }
    void LogIn(){
        string user_name, password;
        cout << "Enter UserName & Password: ";
        cin >> user_name >> password;
        if(users.count(user_name))
        {
            if(users[user_name]->getPassword() == password){
                current_user = users[user_name];
                return;
            }
        }
        cout << "Invalid UserName or Password. Try Again!\n";
        LogIn();
    }
    void SignUp(){
        string user_name;
        cout << "Enter UserName(Unique): ";
        cin >> user_name;
        if(!users.count(user_name)){
            User* user = new User();
            user->ReadUser(user_name);
            users[user_name] = user;
            current_user = user;
            return;
        }
        cout << "Already Taken. Try Another!\n";
        SignUp();
    }
public:
    UsersManager(): current_user(nullptr) {
        cout << "UserManager Constructor\n";
    }
    UsersManager(const UsersManager&) = delete;
    void operator=(const UsersManager&) = delete;

	void LoadDatabase() {
		cout << "UsersManager: LoadDatabase\n";

		FreeLoadedData();
		// Some "Dummy Data" for simplicity
		User* user1 = new User();
		user1->setUserName("mostafa");
		user1->setPassword("111");
		user1->setEmail("most@gmail.com");
		user1->setIsAdmin(true);
		user1->setName("Mostafa Saad Ibrahim");
		users[user1->getUserName()] = user1;

		User* user2 = new User();
		user2->setUserName("asmaa");
		user2->setPassword("222");
		user2->setEmail("asmaa@gmail.com");
		user2->setIsAdmin(false);
		user2->setName("Asmaa Saad Ibrahim");
		users[user2->getUserName()] = user2;
	}
    void AccessSystem(){
        int choice = ShowMenu({"LogIn","SignUp"});
        if(choice==1)
            LogIn();
        else
            SignUp();
    }
    User* getCurrentUser() const {
        return current_user;
    }

    ~UsersManager(){
        FreeLoadedData();
        cout << "Free: UsersDatabase\n";
    }
};

class AdminView{
private:
    UsersManager &umr;
    BooksManager &bmr;
public:
    AdminView(UsersManager &users_manager, BooksManager &books_manager): umr(users_manager), bmr(books_manager) {   }

    void Display(){
        const User * user = umr.getCurrentUser();
        cout << "\nWellcome " << user->getName() << " | AdminView\n";
        while(true){
            int choice = ShowMenu({"View Profile", "Add Book", "Logout"});
            if(choice==1)
                cout << user->ToString();
            else if(choice==2)
                bmr.AddBook();
            else
                break;
        }
    }
};

class UserView{
private:
    UsersManager &umr;
    BooksManager &bmr;
public:
    UserView(UsersManager &users_manager, BooksManager &books_manager): umr(users_manager), bmr(books_manager) {
    }

    void Display(){
        const User * user = umr.getCurrentUser();
        cout << "\nWellcome " << user->getName() << " | UserView\n";
        while(true){
            int choice = ShowMenu({"View Profile", "List System Books", "List My Reading Sessions", "Logout"});
            if(choice==1)
                cout << user->ToString();
            else if(choice==2)
                ListSystemBooks();
            else if(choice==3)
                CurrentReadingSessions();
            else
                break;
        }
    }
    void DisplaySession(ReadingSession *session){
        while(true){
            cout << "\t" << session->PageIdxStr() << "\n";
            cout << session->getCurrentPageContent() << "\n";
            int choice = ShowMenu({"Go Next", "Go Previous", "Stop Reading"});
            if(choice==1)
                session->GoNextPage();
            else if(choice==2)
                session->GoPreviousPage();
            else
                break;
        }
        session->StopReading();
    }
    void ListSystemBooks(){
        const auto &sys_books = bmr.getBooks();
        int idx = 0;
        cout << "\nOur Current book collections\n";
        for(const auto &pair : sys_books)
            cout << ++idx << "- " << pair.second->ToString() << "\n";

        cout << "\n\nWhich book to read?: ";
		int choice = ChooseInRange(1, idx);	// For simplicity, assume a new book is selected

		idx = 0;
		for (const auto &pair : sys_books) {
			if (++idx == choice) {
				ReadingSession* session = umr.getCurrentUser()->AddNewSession(pair.second);
				DisplaySession(session);
				break;
			}
		}
    }
    void CurrentReadingSessions(){
        const auto &curr_sessions = umr.getCurrentUser()->getCurrentSessions();
        if(curr_sessions.empty())
            cout << "No Reading History at The Moment\n";
        else{
            int idx = 0;
            for(const auto &s : curr_sessions){
                cout << ++idx << "- " << s->ToString() << "\n";
            }
            cout << "\nWhich session to open: ";
            int choice = ChooseInRange(1, idx);
            DisplaySession(curr_sessions[choice-1]);
        }
    }
};

class OnlineBookService
{
private:
    UsersManager *umr;
    BooksManager *bmr;

    void LoadDatabase(){
        umr->LoadDatabase();
        bmr->LoadDatabase();
    }
public:
    OnlineBookService(): umr(new UsersManager()), bmr(new BooksManager()) {
    }
    void Run(){
        LoadDatabase();
        while(true){
            umr->AccessSystem();
            if(umr->getCurrentUser()->getIsAdmin()){
                AdminView admin(*umr, *bmr);
                admin.Display();
            }
            else{
                UserView user(*umr, *bmr);
                user.Display();
            }
        }
    }

    ~OnlineBookService(){
        if(umr!=nullptr)
            delete umr;
        umr = nullptr;

        if(bmr!=nullptr)
            delete bmr;
        bmr = nullptr;
    }
};

int main()
{
    OnlineBookService OnlineBookReader;
    OnlineBookReader.Run();


    return 0;
}
