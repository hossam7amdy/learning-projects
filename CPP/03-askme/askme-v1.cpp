#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;

const string USERS_FILE = "users.txt";
const string QUESTIONS_FILE = "questions.txt";

int USER_ID_GENERATOR{ 10 };
int QUESTIONS_ID_GENERATOR{ 100 };

vector<string> read_from_file(string path) {
    vector<string> lines;
    fstream file_handler(path.c_str());
    if (file_handler.fail()) {
        cout << "Can't open this file.\n";
        return lines;
    }
    string line;
    while (getline(file_handler, line))
        lines.push_back(line);

    file_handler.close();
    return lines;
}

void write_to_file(string path, vector<string> lines, bool append = true) {
    auto status = ios::in | ios::out | ios::app;
    if (!append)
        status = ios::in | ios::out | ios::trunc; //overwrite

    fstream file_handler(path.c_str(), status);
    if (file_handler.fail()) {
        cout << "Can't open this file.\n";
        return;
    }

    for (auto line : lines)
        file_handler << line << "\n";

    file_handler.clear();
    file_handler.close();
    return;
}

vector<string> decompostion(string line, char delimiter = '~') {
    vector<string> vec;
    string str = "";
    for (auto ch : line) {
        if (ch == delimiter) {
            vec.push_back(str);
            str = "";
            continue;
        }
        else
            str += ch;
    }
    vec.push_back(str);
    return vec;
}

int toInt(string str) {
    istringstream iss(str);
    int num;
    iss >> num;
    return num;
}

int read_number(int low, int high) {
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int num;
    cin >> num;
    if (low <= num && num <= high)
        return num;
    cout << "ERROR: invalid number...Try again\n";
    return read_number(low, high);
}

struct Question {
    int question_id, from, to;
    int thread; //-1 or its id
    bool AnonQ; //AnonQ = 1
    string question, answer;

    Question() {
        question_id = from = to = thread = 0;
        AnonQ = 1;
    }

    void LoadQuestions(string line) {
        vector<string> question_info = decompostion(line);
        question_id = toInt(question_info[0]);
        thread = toInt(question_info[1]);
        from = toInt(question_info[2]);
        to = toInt(question_info[3]);
        AnonQ = toInt(question_info[4]);
        question = question_info[5];
        answer = question_info[6];
        return;
    }

    void QuestionsToMe() {
        if (thread != -1)
            cout << "\tThread: ";
        cout << "Question ID: (" << question_id << ")";
        if (!AnonQ)
            cout << " From user id(" << from << ")";
        cout << "\tQuestion: " << question;
        if (answer.size() && thread != -1)
            cout << "\n\tThread:\tAnswer: " << answer;
        else if (answer.size())
            cout << "\n\tAnswer: " << answer;
        cout << "\n\n";
        return;
    }

    void QuestionsFromMe() {
        cout << "Question ID(" << question_id << ")";
        if (!AnonQ)
            cout << " !AQ";
        cout << " To User Id(" << to << ")";
        cout << "\tQuestion: " << question;
        if (answer.size())
            cout << "\tAnswer: " << answer << "\n";
        else
            cout << "\tAnswer: Not Answered YET.\n";
    }

    void Print_Feed() {
        if (!answer.size())
            return;
        if (thread != -1)
            cout << "\tThread: ";
        cout << "Question ID(" << question_id << ") ";
        if (!AnonQ)
            cout << " From User Id(" << from << ") to User Id(" << to << ")";
        else
            cout << " To User Id(" << to << ")";
        cout << "\tQuestion: " << question << "\n";
        if (thread != -1)
            cout << "\tThread: ";
        cout << "\tAnswer: " << answer << "\n\n";
        return;
    }

    void Read(int _from, int _to, int _AQ) {
        from = _from, to = _to, AnonQ = _AQ;
        question_id = ++QUESTIONS_ID_GENERATOR;
        cout << "Enter question text: ";
        cin.ignore();
        getline(cin, question, '\n');
        return;
    }

    string Compress() {
        ostringstream oss;
        oss << question_id << "~" << thread << "~" << from << "~" << to << "~" << AnonQ << "~" << question << "~" << answer;
        return oss.str();
    }

};

struct User {
    int user_id;
    string name, user_name, email, password; // allow chars in password
    bool allow_AQ; //0 or 1

    User() {
        user_id = -1;
        allow_AQ = 1;
    }

    void LoadUsers(string line) {
        vector<string> user_info = decompostion(line);
        user_id = toInt(user_info[0]);
        name = user_info[1];
        password = user_info[2];
        user_name = user_info[3];
        email = user_info[4];
        allow_AQ = toInt(user_info[5]);
        return;
    }

    void print() {
        cout << user_id << " " << user_name << "\n";
        return;
    }

    bool ValidUser(string u_name, string pass) {
        if (u_name == name && pass == password)
            return true;
        return false;
    }

    void ReadUserInfo() {
        user_id = ++USER_ID_GENERATOR;
        cout << "Enter user name. (No spaces): "; cin >> name;
        cout << "Enter Password: "; cin >> password;
        cout << "Enter name: "; cin >> user_name;
        cout << "Enter email: "; cin >> email;
        cout << "Allow Anonymous questions?: (0 of 1) "; cin >> allow_AQ;
        return;
    }

    string Compress() {
        ostringstream oss;
        oss << user_id << "~" << name << "~" << password << "~" << user_name << "~" << email << "~" << allow_AQ;
        return oss.str();
    }

};

bool by_user_name(User n1, User n2) {
    return n1.user_name < n2.user_name;
}

struct Ask_Sevice {
    int LoggedID; // Helper
    vector<User> users;
    vector<Question> questions;

    Ask_Sevice() { LoggedID = 0; }

    void LoadUsers() {
        users.clear();
        vector<string> lines = read_from_file(USERS_FILE);
        for (auto& line : lines) {  // load users data
            if (!line.size()) //empty line
                continue;
            User u;
            u.LoadUsers(line);
            USER_ID_GENERATOR = max(USER_ID_GENERATOR, u.user_id); //guarantee next is unique
            users.push_back(u);
        }
    }

    void LoadQuestions() {
        questions.clear();
        vector<string> lines = read_from_file(QUESTIONS_FILE);
        for (auto& line : lines) { //load questions data
            if (line.size() == 0) //empty line
                continue;
            Question q;
            q.LoadQuestions(line);
            QUESTIONS_ID_GENERATOR = max(QUESTIONS_ID_GENERATOR, q.question_id);
            questions.push_back(q);
        }
    }

    int MainMenu() {
        int choose;
        cout << "Menu\n";
        cout << "\t1: Login\n";
        cout << "\t2: Sign Up\n";
        choose = read_number(1, 2);
        return choose;
    }

    int SubMenu() {
        int choose;
        cout << "Menu\n";
        cout << "\t1: Print Questions To Me\n";
        cout << "\t2: Print Questions From Me\n";
        cout << "\t3: Answer Question\n";
        cout << "\t4: Delete Question\n";
        cout << "\t5: Ask Question\n";
        cout << "\t6: List System Users\n";
        cout << "\t7: Feed\n";
        cout << "\t8: Logout\n";
        choose = read_number(1, 8);
        return choose;
    }

    int Login(int trials = 2) { // 3 trials recursively
        string UserName, PassWord;
        cout << "Enter user name & password: ";
        cin >> UserName >> PassWord;
        for (auto& user : users) {
            if (user.ValidUser(UserName, PassWord)) {
                LoggedID = user.user_id;
                return LoggedID;
            }
        }
        if (!trials) {
            cout << "\nToo many trials. Try to SignUp First?\n";
            return 0;
        }
        cout << "Invalid User Name of Password. Try again!\n";
        return Login(trials - 1);
    }

    void SignUp() {
        User u;
        u.ReadUserInfo();
        vector<string> v{ u.Compress() };
        write_to_file(USERS_FILE, v);
        users.push_back(u);
        LoadUsers();
        return;
    }

    vector<Question> questions_to_me(int logged_id, int which) {
        vector<Question> ques;
        for (auto& q : questions) {
            if (which == 2) {
                if (logged_id == q.to)
                    ques.push_back(q);
            }
            else {
                if (logged_id == q.from)
                    ques.push_back(q);
            }
        }
        return ques;
    }

    void PrintQuestionsToMe() {
        vector<Question> ques = questions_to_me(LoggedID, 2);
        if (!ques.size()) {
            cout << "You don't have any questions now.\n";
            return;
        }
        for (auto& q : ques)
            q.QuestionsToMe();
        return;
    }

    void PrintQuestionsFromMe() {
        vector<Question> ques = questions_to_me(LoggedID, 4);
        if (!ques.size()) {
            cout << "No questions at the moment.\n";
            return;
        }
        for (auto& q : ques)
            q.QuestionsFromMe();
        return;
    }

    bool AnswerQuestion() {
        int q_id;
        cout << "Enter question id or -1 to cancel: "; cin >> q_id;
        if (q_id == -1)
            return false;
        for (auto& q : questions) {
            if (q.question_id == q_id && q.to == LoggedID) {
                if (!q.answer.empty())
                    cout << "Warning: Already Answered. Answer will be updated.\n";
                cout << "Enter answer: "; cin.ignore();
                getline(cin, q.answer, '\n');
                return true;
            }
        }
        cout << "\nInvalid question ID.\n\n";
        return false;
    }

    bool DeleteQuestion() { //CAN DELETE ONLY QUESTIONS TO YOU
        int q_id;
        cout << "Enter question id or -1 to cancel: "; cin >> q_id;
        if (q_id == -1)
            return false;

        int pos = -1; //Validation of the user (TO)
        for (int i = 0; i < (int)questions.size(); i++) {
            if (q_id == questions[i].question_id && LoggedID == questions[i].to) {
                pos = i;
                break;
                cout << pos << "\n";
            }
        }
        if (pos == -1) {
            cout << "Invalid Question ID\n";
            return false;
        }

        if (questions[pos].thread != -1) {
            questions.erase(questions.begin() + pos);
            return true;
        }
        else if (questions[pos].thread == -1) {
            questions.erase(questions.begin() + pos);
            while (questions[pos].thread != -1 && questions.size() > 0) // Keep deleting untill next PARENT
                questions.erase(questions.begin() + pos);
            return true;
        }
        return false;
    }

    User get_user_by_id(int trials = 3) {
        User user;
        while (trials--) {
            cout << "Enter User Id or -1 to cancel: ";
            cin >> user.user_id;
            if (user.user_id == -1)
                return user;

            bool valid = false;
            for (auto& u : users) {
                if (u.user_id == user.user_id) {
                    user = u;
                    return user;
                }
            }
            cout << "Invalid user id. Try again!\n\n";
            continue;
        }
        cout << "Too many invalid trials. Try again later\n\n";
        user.user_id = -1;
        return user;
    }

    Question get_question_id(int trials = 3) {
        Question ques;
        while (trials--) {
            cout << "For thread question: Enter Question Id or -1 for a new Question: ";
            cin >> ques.question_id;

            if (ques.question_id == -1)
                return ques;
            else {
                for (int i = 0; i < (int)questions.size(); i++) {
                    if (ques.question_id == questions[i].question_id) {
                        ques.thread = i; //let's make (thread) carry my position
                        ques.to = questions[i].to; // and (to) carry the users id. Help in verification
                        return ques;
                    }
                }
            }
            cout << "Invalid Question Id. Try again!\n\n";
            continue;
        }

        cout << "Too many invalid trials. Try again later\n\n";
        ques.thread = -2;
        return ques;
    }

    bool AskQuestion() {
        User u = get_user_by_id();
        if (u.user_id == -1)
            return false;

        int AnonQ{ 0 };
        if (u.allow_AQ) {
            cout << "Ask Anonymously? (1 or 0): ";
            cin >> AnonQ;
        }
        else
            cout << "Note: Anonymous questions are not allowed for this user\n";

        Question q = get_question_id();
        if (q.thread == -2) // Invalid question id;
            return false;


        if (u.user_id != q.to) {
            cout << "\nEntered User id does not match the threader id!\n\n";
            return false;
        }

        q.Read(LoggedID, u.user_id, AnonQ);
        if (q.thread != -1) {
            for (int i = q.thread + 1; i < (int)questions.size(); i++) { //move to next position and check. Till reach next PARENT
                if (questions[i].thread == -1) {
                    questions.insert(questions.begin() + i, q);
                    return true;
                }
            }
        }
        questions.push_back(q);
        return true;
    }

    void ListUsers() {
        sort(users.begin(), users.end(), by_user_name);
        for (auto& user : users)
            user.print();
        return;
    }

    vector<string> questions_info() { // compress questions to file
        vector<string> info;
        for (auto& q : questions)
            info.push_back(q.Compress());
        return info;
    }

    void Feed() {
        for (auto& q : questions) {
            for (auto& u : users) {
                if (q.from == u.user_id)
                    q.Print_Feed();
            }
        }
        return;
    }

    void Run() {
        LoadUsers();
        int choice = MainMenu();
        if (choice == 1) {
            int is_logged = Login();
            while (is_logged) {
                LoadQuestions();
                choice = SubMenu();
                if (choice == 1)
                    PrintQuestionsToMe();
                else if (choice == 2)
                    PrintQuestionsFromMe();
                else if (choice == 3) {
                    if (AnswerQuestion())
                        write_to_file(QUESTIONS_FILE, questions_info(), false);
                }
                else if (choice == 4) {
                    if (DeleteQuestion())
                        write_to_file(QUESTIONS_FILE, questions_info(), false);
                }
                else if (choice == 5) {
                    if (AskQuestion())
                        write_to_file(QUESTIONS_FILE, questions_info(), false);
                }
                else if (choice == 6)
                    ListUsers();
                else if (choice == 7)
                    Feed();
                else
                    break;
            }
        }
    else
        SignUp();
    Run();
    }
};

int main() {
    Ask_Sevice askfm;
    askfm.Run();
    return 0;
}
