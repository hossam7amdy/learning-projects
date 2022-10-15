#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

/// Let's Rewrite from scratch ///

const string USERS_FILE = "users.txt";
const string QUESTIONS_FILE = "questions.txt";

////////////Helpers////////////////
vector<string> ReadFromFile(string path) {
    vector<string> Lines;
    ifstream file_handler(path.c_str());
    if (file_handler.fail()) {
        cout << "ERROR: can't open this file.\n";
        return Lines;
    }
    string line;
    while (getline(file_handler, line))
        Lines.push_back(line);
    return Lines;
}

vector<string> SplitString(string line, string delimiter = "~") {
    vector<string> data;
    int pos;
    string substr;
    while ((pos = line.find(delimiter)) != -1) {
        substr = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        data.push_back(substr);
    }
    data.push_back(line);
    return data;
}

void WriteToFile(string path, vector<string> Lines, bool append = true) {
    auto status = ios::in | ios::out | ios::app;
    if (!append)
        status = ios::in | ios::out | ios::trunc;
    ofstream file_handler(path.c_str(), status);
    if (file_handler.fail()) {
        cout << "ERROR: Can't open this file.\n";
        return;
    }
    for (auto& line : Lines)
        file_handler << line << "\n";
    return;
}

int toInt(string str) {
    istringstream iss(str);
    int num;
    iss >> num;
    return num;
}

int Choice(int low, int high) {
    int choose;
    cout << "Enter number between [" << low << " - " << high << "] : ";
    cin >> choose;
    if (low <= choose && choose <= high && !cin.fail())
        return choose;
    cout << "\nInvalid choice. Try again!\n\n";
    cin.clear();
    cin.ignore(264, '\n');
    return Choice(low, high);
}

int Menu(vector<string> Lines) {
    cout << "Menu\n";
    for (int i = 0; i < (int)Lines.size(); i++)
        cout << "\t" << i + 1 << "- " << Lines[i] << "\n";

    return Choice(1, (int)Lines.size());
}

struct User {
    int user_id;
    string name;
    string password;
    string user_name;
    string email;
    int allow_anonymous;

    vector<int> questions_from_me;
    map<int, vector<int>> questionIdtoquestionIds; // For CURRENT USER

    User() {
        user_id = allow_anonymous = -1;
    }

    User(string line) {
        vector<string> user_data = SplitString(line);
        assert((int)user_data.size() == 6);

        user_id = toInt(user_data[0]);
        name = user_data[1];
        password = user_data[2];
        user_name = user_data[3];
        email = user_data[4];
        allow_anonymous = toInt(user_data[5]);
    }

    string toString() {
        ostringstream oss;
        oss << user_id << "~" << name << "~" << password << "~" << user_name << "~" << email << "~" << allow_anonymous;
        return oss.str();
    }

    void print() {
        cout << user_id << " " << name << "\n";
        return;
    }
};

struct Question {
    int question_id;
    int parent_question_id;
    int from_user;
    int to_user;
    int anonymous_question;
    string question;
    string answer;

    Question() {
        question_id = parent_question_id = from_user = to_user = -1;
        anonymous_question = -1;
    }

    Question(string line) {
        vector<string> question_data = SplitString(line);
        assert(question_data.size() == 7);

        question_id = toInt(question_data[0]);
        parent_question_id = toInt(question_data[1]);
        from_user = toInt(question_data[2]);
        to_user = toInt(question_data[3]);
        anonymous_question = toInt(question_data[4]);
        question = question_data[5];
        answer = question_data[6];
    }

    void PrintQuestionFromMe() {
        cout << "Question ID (" << question_id << ")";
        if (!anonymous_question)
            cout << " !AQ";

        cout << " to User ID(" << to_user << ")";
        cout << " Question: " << question;

        if (!answer.empty())
            cout << "\n\tAnswer: " << answer << endl;
        else
            cout << "\n\tNot Answered YET\n";
        return;
    }

    void PrintQuestionToMe() {
        string prefix = "";

        if (parent_question_id != -1)
            prefix = "\tThread ";

        cout << prefix << "Question ID (" << question_id << ")";

        if (!anonymous_question)
            cout << " From User ID (" << from_user << ")";

        cout << " Question: " << question << "\n";
        if (!answer.empty())
            cout << prefix << "\tAnswer: " << answer << "\n";

        cout << "\n";
        return;
    }

    void PrintQuestionFeed() {
        if (parent_question_id != -1)
            cout << "\tThread Parent Question ID (" << parent_question_id << ") ";

        cout << "Question ID (" << question_id << ")";

        if (!anonymous_question)
            cout << "From User ID (" << from_user << ")";

        cout << " To User ID (" << to_user << ") Question: " << question;
        cout << "\n\t\tAnswer: " << answer << "\n\n";
    }

    string ToString() {
        ostringstream oss;
        oss << question_id << "~" << parent_question_id << "~" << from_user << "~" << to_user << "~" << anonymous_question << "~" << question << "~" << answer;
        return oss.str();
    }
};

struct UsersManager {
    map<string, User> users;
    User current_user;
    int user_id;

    UsersManager() { user_id = 0; }

    void LoadDatabase() {
        users.clear();

        vector<string> Lines = ReadFromFile(USERS_FILE);
        for (auto& line : Lines) {
            if (line.empty())
                continue;
            User tempUser(line);
            users[tempUser.name] = tempUser;
            user_id = max(user_id, tempUser.user_id);
        }
        return;
    }

    void DoSignIn(int trials = 3) {
        LoadDatabase(); //in case of parallel sessions

        while (trials--) {
            cout << "Enter Username and Password: ";
            User user_exist;
            cin >> current_user.name >> current_user.password;

            if (!users.count(current_user.name)) {
                cout << "Invalid User Name of Password. Try again!\n";
                continue;
            }
            user_exist = users[current_user.name];
            if (user_exist.password != current_user.password) {
                cout << "Invalid User Name of Password. Try again!\n";
                continue;
            }
            current_user = user_exist;
            return;
        }
        cout << "\nMany Invalid trials. Try to SignUp first.\n";
        return;
    }

    void UpdateDatabase() {
        vector<string> user_data(1, current_user.toString());
        WriteToFile(USERS_FILE, user_data);
        return;
    }

    void DoSignUp() {
        while (true) {
            cout << "Enter Name (No Spaces): ";
            cin >> current_user.name;
            if (users.count(current_user.name)) {
                cout << "Already taken. Enter another one\n";
                continue;
            }
            else
                break;
        }
        cout << "Enter Password: ";
        cin >> current_user.password;

        cout << "Enter UserName: ";
        cin >> current_user.user_name;

        cout << "Enter Email: ";
        cin >> current_user.email;

        cout << "Allow anonymous questions (0 or 1): ";
        cin >> current_user.allow_anonymous;

        current_user.user_id = ++user_id;
        UpdateDatabase();
        return;
    }

    void AccessSystem() {
        int choose = Menu({ "Sign In", "Sign Up" });
        if (choose == 1)
            DoSignIn();
        else
            DoSignUp();
        return;
    }

    void ListUsers() {
        for (auto& pair : users)
            pair.second.print();
        return;
    }

    pair<int, int> ReadUserId() {
        int u_id;
        cout << "Enter User ID or -1 to cancel: ";
        cin >> u_id;

        if (u_id == -1)
            return make_pair(-1, -1);

        for (auto& pair : users) {
            User& user = pair.second;
            if (u_id == user.user_id)
                return make_pair(u_id, user.allow_anonymous);
        }
        cout << "Invalid User Id\n";
        return make_pair(-1, -1);
    }
};

struct QuesionsManager {
    // map from a question id to its thread ids
    map<int, vector<int>> questionIdtoThreads; // For ALL USERS
    // map from question id to question object
    map<int, Question> questions;

    int question_id;

    QuesionsManager() { question_id = 0; }

    void LoadDatabase() {
        questionIdtoThreads.clear();
        questions.clear();

        vector<string> Lines = ReadFromFile(QUESTIONS_FILE);
        for (auto& line : Lines) {
            if (line.empty())
                continue;

            Question current = Question(line);
            questions[current.question_id] = current;

            if (current.parent_question_id == -1)
                questionIdtoThreads[current.question_id].push_back(current.question_id);
            else
                questionIdtoThreads[current.parent_question_id].push_back(current.question_id);

            question_id = max(question_id, current.question_id);
        }
        return;
    }

    void FillUsersQuestions(User& user) {
        user.questionIdtoquestionIds.clear();
        user.questions_from_me.clear();

        for (auto& pair : questionIdtoThreads) { // <int, vector<int>>
            for (auto& id : pair.second) {      // vector<int>

                Question& question = questions[id];

                if (user.user_id == question.from_user)
                    user.questions_from_me.push_back(id);

                if (user.user_id == question.to_user) {
                    if (question.parent_question_id == -1)
                        user.questionIdtoquestionIds[question.question_id].push_back(question.question_id);
                    else
                        user.questionIdtoquestionIds[question.parent_question_id].push_back(question.question_id);
                }
            }
        }
        return;
    }

    void PrintQuestionsFromMe(User& user) {
        if (user.questions_from_me.empty()) {
            cout << "No questions at the moment.\n";
            return;
        }

        for (auto& id : user.questions_from_me)
            questions[id].PrintQuestionFromMe();

        return;
    }

    void PrintQuestionsToMe(User& user) {
        if (user.questionIdtoquestionIds.empty()) {
            cout << "No questions at the moment.\n";
            return;
        }
        for (auto& pair : user.questionIdtoquestionIds) {
            for (auto& id : pair.second)
                questions[id].PrintQuestionToMe();
        }
        return;
    }

    void AnswerQuestion(User& user) {
        int q_id;
        cout << "Enter Question ID or -1 to Cancel: ";
        cin >> q_id;

        if (q_id == -1)
            return;

        if (!questions.count(q_id)) {
            cout << "Invalid Question ID\n";
            return;
        }

        if (questions[q_id].to_user != user.user_id) {
            cout << "Invalid Question ID\n";
            return;
        }

        if (!questions[q_id].answer.empty())
            cout << "Warning: Already answered. Answer will be updated.\n";

        cout << "Enter answer text: ";
        cin.ignore();
        getline(cin, questions[q_id].answer);
        //getline(cin, questions[q_id].answer);
        return;
    }

    void DeleteQuestion(User& user) {
        int q_id;
        cout << "Enter Question ID or -1 to Cancel: ";
        cin >> q_id;

        if (q_id == -1)
            return;

        if (!questions.count(q_id)) {
            cout << "Invalid Question ID\n";
            return;
        }

        if (user.user_id != questions[q_id].to_user) {
            cout << "Invalid Question ID\n";
            return;
        }

        vector<int> thread;
        if (questionIdtoThreads.count(q_id)) { // Thread
            thread = questionIdtoThreads[q_id];
            questionIdtoThreads.erase(q_id);
        }
        else {
            thread.push_back(q_id);
            for (auto& pair : questionIdtoThreads) {
                vector<int>& vec = pair.second; // point at same memory
                for (int pos = 0; pos < (int)vec.size(); pos++) {
                    if (q_id == vec[pos]) {
                        vec.erase(vec.begin() + pos);
                        break;
                    }
                }
            }
        }
        for (auto id : thread)
            questions.erase(id);
        return;
    }

    int ReadQuestionId(pair<int, int> u_id) { // verify (question id)
        int question_id;
        cout << "For anonymous question Enter Question Id or -1 for new question: ";
        cin >> question_id;

        if (question_id == -1)
            return question_id;

        if (!questionIdtoThreads.count(question_id)) {
            cout << "No thread question with such ID. Try again!\n";
            ReadQuestionId(u_id);
        }

        if (questions[question_id].to_user != u_id.first) {
            cout << "This question does not belong to this user. Try again\n";
            ReadQuestionId(u_id);
        }

        return question_id;
    }

    void AskQuestion(User& user, pair<int, int> u_id) {
        Question question;

        if (u_id.second == 0) {
            cout << "Note: Anonymous questions are not allowed for this user\n";
            question.anonymous_question = 0;
        }
        else {
            cout << "Ask anonymously? (0 or 1): ";
            cin >> question.anonymous_question;
        }

        question.parent_question_id = ReadQuestionId(u_id);

        question.to_user = u_id.first;
        question.from_user = user.user_id;

        cout << "Enter question text: ";
        cin.ignore(264,'\n');
        getline(cin, question.question);
        //getline(cin, question.question);

        question.question_id = ++question_id;
        questions[question.question_id] = question;

        if (question.parent_question_id == -1)
            questionIdtoThreads[question.question_id].push_back(question.question_id);
        else
            questionIdtoThreads[question.parent_question_id].push_back(question.question_id);

        return;
    }

    void PrintUsersFeed() {
        if (questionIdtoThreads.empty())
            cout << "No Questions to print.\n";

        for (auto& pair : questionIdtoThreads) {
            for (auto& id : pair.second) {
                if (questions[id].answer.empty())
                    continue;
                else
                    questions[id].PrintQuestionFeed();
            }
        }
        return;
    }

    void UpdateDatabase() {
        vector<string> vec;
        for (auto& pair : questions)
            vec.push_back(pair.second.ToString());

        WriteToFile(QUESTIONS_FILE, vec, false);
        return;
    }
};

struct AskMeSystem {
    UsersManager users_manager;
    QuesionsManager questions_manager;

    void LoadSystemData(bool fill_users_questions = false) {
        users_manager.LoadDatabase();
        questions_manager.LoadDatabase();

        if(fill_users_questions)
            questions_manager.FillUsersQuestions(users_manager.current_user);
    }

    void Run() {
        LoadSystemData();
        users_manager.AccessSystem();
        questions_manager.FillUsersQuestions(users_manager.current_user);

        vector<string> menu;
        menu.push_back("Print Questions To Me");
        menu.push_back("Print Questions From Me");
        menu.push_back("Answer Question");
        menu.push_back("Delete Question");
        menu.push_back("Ask Question");
        menu.push_back("List System Users");
        menu.push_back("Feed");
        menu.push_back("Logout");

        while (true) {
            LoadSystemData(true);
            int choice = Menu(menu);

            if (choice == 1)
                questions_manager.PrintQuestionsToMe(users_manager.current_user);
            else if (choice == 2)
                questions_manager.PrintQuestionsFromMe(users_manager.current_user);
            else if (choice == 3) {
                questions_manager.AnswerQuestion(users_manager.current_user);
                questions_manager.UpdateDatabase();
            }
            else if (choice == 4) {
                questions_manager.DeleteQuestion(users_manager.current_user);
                questions_manager.FillUsersQuestions(users_manager.current_user);
                questions_manager.UpdateDatabase();
            }
            else if (choice == 5) {
                pair<int, int> u_id = users_manager.ReadUserId();

                if (u_id.first != -1) {
                    questions_manager.AskQuestion(users_manager.current_user, u_id);
                    questions_manager.FillUsersQuestions(users_manager.current_user);
                    questions_manager.UpdateDatabase();
                }
            }
            else if (choice == 6)
                users_manager.ListUsers();
            else if (choice == 7)
                questions_manager.PrintUsersFeed();
            else
                break;
        }
        Run();
    }
};

int main() {
    AskMeSystem ask_me;
    ask_me.Run();

    return 0;
}

