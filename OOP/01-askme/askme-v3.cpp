#include<iostream>
#include<map>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<stdlib.h>
using namespace std;

//////////////////Helpers//////////////////
vector<string> ReadFromFile(const string &path)
{
    fstream file_handler(path.c_str());
    vector<string> v;

    if(file_handler.fail()){
        cout << "Cannot open this file\n";
        return v;
    }

    string line;
    while(getline(file_handler, line))
        v.push_back(line);

    file_handler.close();

    return v;
}
vector<string> Splitter(string& line, char delimiter = '~')
{
    int len;
    vector<string> v;
    while((len = line.find('~'))!=-1){
        string sub = line.substr(0, len);
        v.push_back(sub);
        line.erase(0,len+1);
    }
    v.push_back(line);
    return v;
}
const int ToInt(const string &str)
{
    stringstream iss(str);
    int num;
    iss>>num;
    return num;
}
void WriteToFile(const vector<string>& data, const string& path, bool append = true)
{
    auto status = ios::in | ios::out | ios::app;
    if(!append)
        status = ios::in | ios::out | ios::trunc;

    fstream file_handler(path.c_str(), status);

    if(file_handler.fail()){
        cout << "Cannot open this file\n";
        return;
    }

    for(const auto &line : data){
        file_handler.clear();
        file_handler << line << "\n";
    }

    file_handler.close();
}
const int readInRange(const int &high, int low = 1)
{
    int choice;
    cout << "Choose from [" << low  << " - " << high << "]: ";
    cin >> choice;
    if(low<=choice && choice<=high && !cin.fail())
        return choice;
    cin.clear();
    cin.ignore(264, '\n');
    cout << "Invalid Input. TRY AGAIN!\n";
    return readInRange(high);
}
const int ShowMenu(const vector<string> &menu)
{
    cout << "Menu:\n";
    for(int i=0; i<(int)menu.size(); ++i)
        cout << "\t" << i+1 << ") " << menu[i] << "\n";
    return readInRange(menu.size());
}
///////////////////////////////////////////////
class Question
{
private:
    int parent_Id;
    int child_Id;
    string from_user;
    string to_user;
    bool is_anonymous;
    string question_text;
    string answer_text;
    //Setters
    void setParentId(const int& parent_Id)
    {
        this->parent_Id = parent_Id;
    }
    void setChildId(const int& child_Id)
    {
        this->child_Id = child_Id;
    }
    void setFromUser(const string& from_user)
    {
        this->from_user = from_user;
    }
    void setToUser(const string& to_user)
    {
        this->to_user = to_user;
    }
    void setIsAnonymous(const bool& is_anonymous)
    {
        this->is_anonymous = is_anonymous;
    }
    void setQuestionText(const string& question_text)
    {
        this->question_text = question_text;
    }
    //Getters
    const bool& getIsAnonymous() const
    {
        return this->is_anonymous;
    }
    const string& getAnswerText() const
    {
        return this->answer_text;
    }
public:
    //Constructors
    Question():parent_Id(-1), child_Id(-1), is_anonymous(1)
    {
        //cout << "Question Constructor Call\n";
    }
    Question(int parent_Id, int child_Id, string from_user, string to_user, bool is_anonymous):
        parent_Id(parent_Id), child_Id(child_Id), from_user(from_user), to_user(to_user), is_anonymous(is_anonymous)
        {
            cout << "Enter question text: ";
            cin.ignore(264, '\n');
            string str;
            getline(cin, str);
            setQuestionText(str);
        }
    Question(string& line)
    {
        vector<string> rawData = Splitter(line);
        assert((int)rawData.size() == 7);
        setParentId(ToInt(rawData[0]));
        setChildId(ToInt(rawData[1]));
        setFromUser(rawData[2]);
        setToUser(rawData[3]);
        setIsAnonymous(ToInt(rawData[4]));
        setQuestionText(rawData[5]);
        setAnswerText(rawData[6]);
    }
    Question(const Question&) = delete;
    //void operator=(const Question&) = delete;
    //Member Functions
    const int& getParentId() const
    {
        return this->parent_Id;
    }
    const int& getChildId() const
    {
        return this->child_Id;
    }
    const string& getToUser() const
    {
        return this->to_user;
    }
    const string& getFromUser() const
    {
        return this->from_user;
    }
    const string& getQuestionText() const
    {
        return this->question_text;
    }
    void setAnswerText(const string& answer_text)
    {
        this->answer_text = answer_text;
    }
    void PrintToMe() const
    {
        if(getChildId()==-1)
            cout << "\nParent Question Id:[" << getParentId() <<"]";
        else
            cout << "\tThread: Question Id:[" << getParentId() << "]";
        if(getIsAnonymous()==0)
            cout << " From: " << getFromUser();
        cout << "\tQuestion: " << getQuestionText();
        if(getAnswerText()=="")
            cout << "\n\t\tNot Answered YET.\n";
        else
            cout << "\n\t\tAnswer: " << getAnswerText() << endl;
    }
    void PrintFromMe() const
    {
        cout << "\nQuestion Id:[" << getParentId() << "]";
        if(getIsAnonymous()==0)
            cout << " (!AQ)";
        cout << " To: " << getToUser();
        cout << "\tQuestion: " << getQuestionText();
        if(getAnswerText()=="")
            cout << "\n\tNot Answered YET.\n";
        else
            cout << "\n\tAnswer: " << getAnswerText() << endl;
    }
    void PrintFeed() const
    {
        if(getAnswerText()=="")
            return;
        if(getChildId()==-1)
            cout << "\nParent Question Id:[" << getParentId() <<"]";
        else
            cout << "\tThread: Question Id:[" << getParentId() << "]";
        if(getIsAnonymous()==0)
            cout << " From(" << getFromUser() <<")";
        cout << " To(" << getToUser() << ")";
        cout << "\tQuestion: " << getQuestionText();
        cout << "\n\t\tAnswer: " << getAnswerText() << endl;

    }
    const string ToString() const
    {
        ostringstream oss;
        oss << getParentId() << "~" << getChildId() << "~" << getFromUser() << "~" << getToUser() << "~" << getIsAnonymous() << "~" << getQuestionText() << "~" << getAnswerText();
        return oss.str();
    }
    //Destructor
    ~Question()
    {
        //cout << "Question Destructor Call\n";
    }
};

class User
{
private:
    int id;
    string name;
    string userName;
    string password;
    string email;
    bool allow_anonymous;

    vector<int> questions_from_me;
    map<int, vector<int> > questions_to_me;

    //setters => private
    void setId(const int &id)
    {
        this->id = id;
    }
    void setName(const string &name)
    {
        this->name = name;
    }
    void setUserName(const string &userName)
    {
        this->userName = userName;
    }
    void setPassword(const string &password)
    {
        this->password = password;
    }
    void setEmail(const string &email)
    {
        this->email = email;
    }
    void setAllowAnonymous(const int &allow_anonymous)
    {
        this->allow_anonymous = allow_anonymous;
    }

    //getters
    const string& getName() const
    {
        return this->name;
    }
    const string& getEmail() const
    {
        return this->email;
    }
    const string& getPassword() const
    {
        return this->password;
    }

public:
    //constructors
    User(): id(0), allow_anonymous(true)
    {
        //ctor
        //cout << "User Constructor Call\n";
    }
    User(string& Line)
    {
        vector<string> rawData = Splitter(Line);
        assert((int)rawData.size()==6);
        setId(ToInt(rawData[0]));
        setName(rawData[1]);
        setPassword(rawData[2]);
        setUserName(rawData[3]);
        setEmail(rawData[4]);
        setAllowAnonymous(ToInt(rawData[5]));
    }
    //User(const User& user) = delete;
    //void operator=(const User& user) = delete;

    //used getters & member functions
    const int& getId() const
    {
        return this->id;
    }
    const string& getUserName() const
    {
        return this->userName;
    }
    const bool& getAllowAnonymous() const
    {
        return this->allow_anonymous;
    }
    const bool IsValid(const string& username, const string& password) const
    {
        if(getUserName() == username && getPassword() == password)
            return true;
        return false;
    }
    void printUser() const
    {
        cout << getName() << " (" << getUserName() << ")\n";
    }
    void ReadUser(const int& id, const string& userName)
    {
        setId(id);
        setUserName(userName);
        //some extra verification needed
        //Using actual data members to construct new USER
        string str;
        cout << "Enter Your Name: ";
        cin.ignore(20,'\n');
        getline(cin,str);
        setName(str);

        cout << "Enter Password: ";
        cin >> str;
        setPassword(str);

        cout << "Enter Email: ";
        cin >> str;
        setEmail(str);

        bool aq;
        cout << "Allow Anonymous Questions [0 - 1]: ";
        cin >> aq;
        setAllowAnonymous(aq);
    }
    const string ToString() const
    {
        ostringstream oss;
        oss << getId() << "~" << getName() << "~" << getPassword() << "~" << getUserName() << "~" << getEmail() << "~" << getAllowAnonymous();
        return oss.str();
    }
    void resetToMe(const map<int, vector<int> >& questions_to_me)
    {
        this->questions_to_me.clear();
        this->questions_to_me = questions_to_me; // copying by assignment operator

    }
    void resetFromMe(const vector<int>& questions_from_me)
    {
        this->questions_from_me.clear();
        this->questions_from_me = questions_from_me;
    }
    const map<int, vector<int> >& getQustionsToMe() const
    {
        return this->questions_to_me;
    }
    const vector<int>& getQuestionsFromMe() const
    {
        return this->questions_from_me;
    }
    //destructor
    ~User()
    {
        //dtor
        //cout << "User Destructor Call\n";
    }
};

class UserManager
{
private:
    map<string, User> AllUsers;
    int IdGenerator;
    User LoggedUser;
    //constructor
    UserManager():IdGenerator(10)
    {
        cout << "UserManager Constructor Call\n";
    }
    void UpdateDatabase(const User& LoggedUser)
    {
        string userInfo = LoggedUser.ToString();
        WriteToFile(vector<string>(1,userInfo), "users.txt");
    }
    static UserManager * umr;
public:
    void LoadUsersData()
    {
        cout << "Loading users data ...\n";
        AllUsers.clear();
        vector<string> lines = ReadFromFile("users.txt");
        for(auto &line : lines){
            if(line.empty())
                continue;
            User tempUser = User(line);
            IdGenerator = max(IdGenerator, tempUser.getId());
            AllUsers[tempUser.getUserName()] = tempUser;
        }
    }
    //OneSharedInstance
    static UserManager * getInstance();
    static void FreeInstance();
    UserManager(const UserManager&) = delete;
    void operator=(const UserManager&) = delete;
    //member functions
    void LogIn(int trials = 3)
    {
        while(true)
        {
            string username, password;
            cout << "Enter UserName & Password: ";
            cin >> username >> password;
            for(const auto& pair : AllUsers)
            {
                if(pair.second.IsValid(username, password) && !cin.fail())
                {
                    LoggedUser = pair.second;
                    return;
                }
            }
            cout << "Invalid UserName or Password. TRY AGAIN!\n";
        }
        cout << "Invalid UserName or Password. Try SignUp!\n";
    }
    void SignUp()
    {
        string userName;
        while(true)
        {
            cout << "Enter UserName [Unique]: ";
            cin >> userName;
            if(AllUsers.count(userName))
                cout << "Already Taken. Try Again!\n";
            else
                break;
        }
        LoggedUser.ReadUser(++IdGenerator,userName);
        UpdateDatabase(LoggedUser);
    }
    void AccessSystem()
    {
        int choose = ShowMenu({"LogIn","SignUp"});
        if(choose == 1)
            LogIn();
        else
            SignUp();
    }
    void ListUsers()
    {
        for(const auto &pair : AllUsers)
            pair.second.printUser();
    }
    User& getLoggedUser()
    {
        return this->LoggedUser;
    }
    const pair<string, int> IsAvailable()
    {
        string Uname;
        cout << "Enter UserName or -1 to cancel: ";
        cin >> Uname;
        if(Uname == "-1")
            return make_pair("-1",-1);
        if(AllUsers.count(Uname))
            return make_pair(Uname, AllUsers[Uname].getAllowAnonymous());
        cout << "Invalid UserName. TRY AGAIN!\n";
        return IsAvailable();
    }
    ~UserManager()
    {
        cout << "UserManager Destructor Call\n";
    }
};

UserManager * UserManager::umr = nullptr;
UserManager * UserManager::getInstance()
{
    if(umr==nullptr)
        umr = new UserManager();
    return umr;
}
void UserManager::FreeInstance()
{
    if(umr==nullptr)
        return;
    delete umr;
    umr = nullptr;
    cout << "I'm Free\n";
}

class QuestionManager
{
private:
    map<int, Question> AllQuestions;
    map<int, vector<int> > parent_to_child;
    int IdGenerator;
    void UpdateDatabase() const
    {
        vector<string> questions_data;
        for(const auto& pair : AllQuestions)
        {
            questions_data.push_back(pair.second.ToString());
        }
        WriteToFile(questions_data, "questions.txt", false); // overwrite
    }
    const bool IsValidParent(const int& question_id, const string& Uname)
    {
        return (AllQuestions[question_id].getToUser() == Uname);
    }
public:
    QuestionManager():IdGenerator(100)
    {
        cout << "QuestionManager Constructor Call\n";
    }
    void LoadQuestionsData()
    {
        cout << "Loading questions data ...\n";
        AllQuestions.clear();
        parent_to_child.clear();
        vector<string> lines = ReadFromFile("questions.txt");
        for(auto& line : lines)
        {
            Question curr_question(line);
            AllQuestions[curr_question.getParentId()] = curr_question;

            if(curr_question.getChildId()==-1)
                parent_to_child[curr_question.getParentId()].push_back(curr_question.getParentId());
            else
                parent_to_child[curr_question.getChildId()].push_back(curr_question.getParentId());

            IdGenerator = max(IdGenerator, curr_question.getParentId());
        }
    }
    void fillUserQuestions(User& curr_user)
    {
        cout << "Loading User's questions ... \n";
        vector<int> from_me;
        map<int, vector<int> > to_me;
        for(const auto& pair : AllQuestions)
        {
            if(pair.second.getFromUser() == curr_user.getUserName())
                from_me.push_back(pair.first);

            if(pair.second.getToUser() == curr_user.getUserName())
            {
                if(pair.second.getChildId() == -1)
                    to_me[pair.second.getParentId()].push_back(pair.second.getParentId());
                else
                    to_me[pair.second.getChildId()].push_back(pair.second.getParentId());
            }
        }
        curr_user.resetToMe(to_me);
        curr_user.resetFromMe(from_me);
    }
    void QuestionsToMe(const User& curr_user)
    {
        map<int, vector<int> > to_me(curr_user.getQustionsToMe()); // copy constructor
        if(to_me.empty())
        {
            cout << "No questions at the moment.\n";
            return;
        }
        for(const auto& pair : to_me)
        {
            for(const int& id : pair.second)
                AllQuestions[id].PrintToMe();
        }
    }
    void QuestionsFromMe(const User& curr_user)
    {
        vector<int> from_me(curr_user.getQuestionsFromMe());
        if(from_me.empty())
        {
            cout << "No questions at the moment.\n";
            return;
        }
        for(const int& id : curr_user.getQuestionsFromMe())
            AllQuestions[id].PrintFromMe();
    }
    void AskQuestion(const pair<string, int>& UserInfo, const User& curr_user)
    {
        if(UserInfo.first == "-1")
            return;

        if(UserInfo.second == 0)
            cout << "NOTE: Anonymous questions are not allowed for this user.\n";

        int question_id;
        while(true)
        {
            cout << "For thread question Enter question's Id or -1 for new question: ";
            cin >> question_id;
            if(question_id == -1)
                break;
            else if(parent_to_child.count(question_id) && !cin.fail())
            {
                if(IsValidParent(question_id, UserInfo.first))
                   break;
            }
            cin.clear();
            cin.ignore(264,'\n');
            cout << "Invalid question id. TRY AGAIN!\n";
        }
        Question New(++IdGenerator,question_id, curr_user.getUserName(), UserInfo.first, UserInfo.second);
        WriteToFile(vector<string>(1,New.ToString()), "questions.txt");
    }
    void AnsweQuestion(const User& curr_user)
    {
        int question_id;
        cout << "Enter question id or -1 to cancel: ";
        cin >> question_id;
        if(question_id == -1)
            return;
        if(AllQuestions.count(question_id))
        {
            if(AllQuestions[question_id].getToUser() == curr_user.getUserName())
            {
            	if(!AllQuestions[question_id].getQuestionText().empty())
            		cout << "NOTE: Already answered. Answer will be updated.\n";
                string str;
                cout << "Enter answer text: ";
                cin.ignore(264, '\n');
                getline(cin, str);
                AllQuestions[question_id].setAnswerText(str);
                UpdateDatabase();
                return;
            }
        }
        cin.clear();
        cin.ignore(264,'\n');
        cout << "Invalid question id. TRY AGAIN!\n";
        return AnsweQuestion(curr_user);
    }
    void DeleteQuestion(const User& curr_user)
    {
        int question_id;
        cout << "Enter question id of -1 to cancel: ";
        cin >> question_id;
        if(question_id == -1)
            return;
        if(AllQuestions.count(question_id))
        {
            if(AllQuestions[question_id].getToUser() == curr_user.getUserName())
            {
                const auto iter = parent_to_child.find(question_id);
                if(iter != parent_to_child.end())// parent question
                    {
                        //for(const auto& pair = it : parent_to_child) // <int, vector<int> >
                        {
                            for(const auto& id : iter->second) // vector<int>
                                AllQuestions.erase(id);
                        }
                    }
                else
                    AllQuestions.erase(question_id); // child question

                UpdateDatabase();
                return;
            }
        }
        cin.clear();
        cin.ignore(5,'\n');
        cout << "Invalid question id. TRY AGAIN!\n";
        return DeleteQuestion(curr_user);
    }
    void ListFeed() const
    {
        for(const auto& pair : AllQuestions)
            pair.second.PrintFeed();
    }
};

class AskService{
private:
    UserManager * umr = UserManager::getInstance();
    QuestionManager qmr;

    void LoadDatabase(bool fill_users_questions = false)
    {
        umr->LoadUsersData();
        qmr.LoadQuestionsData();

        if(fill_users_questions)
            qmr.fillUserQuestions(umr->getLoggedUser()); //if logged in load questions data base and users questions
    }

public:
    void Run()
    {
        LoadDatabase();
        umr->AccessSystem();
        qmr.fillUserQuestions(umr->getLoggedUser());
        while(true)
        {
            int choice = ShowMenu({"Print Questions To Me", "Print Questions From Me", "Ask Question", "Answer Question", "Delete Question", "List System Users", "Feed", "LogOut"});
            LoadDatabase(true);
            if(choice==1)
            {
                qmr.QuestionsToMe(umr->getLoggedUser());
            }
            else if(choice==2)
            {
                qmr.QuestionsFromMe(umr->getLoggedUser());
            }
            else if(choice==3)
            {
                //PASSES: asked user's info & current user object
                qmr.AskQuestion(umr->IsAvailable(), umr->getLoggedUser());
            }
            else if(choice==4)
            {
                qmr.AnsweQuestion(umr->getLoggedUser());
            }
            else if(choice==5)
            {
                qmr.DeleteQuestion(umr->getLoggedUser());
            }
            else if(choice==6)
            {
                umr->ListUsers();
            }
            else if(choice==7)
            {
                qmr.ListFeed();
            }
            else
                break;
        }
        return Run();
    }

    ~AskService()
    {
        cout << "AskMe destructor Call\n";
        UserManager::FreeInstance();
    }
};

int main(){
    AskService AskMe;
    AskMe.Run();

    return 0;
}
