#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int MAX_QUEUE {5};
const int MAX_SPECIALIZATIONS {20};

struct hospital_queue{
    deque<pair<string, int>> dque;
    int spec;

    hospital_queue(){ spec = -1; }

    hospital_queue(int _spec){
        spec = _spec;
    }

    bool add_front(string name, int st){
        if(dque.size()==MAX_QUEUE)
            return false;
        dque.push_front(make_pair(name, st));
        return true;
    }

    bool add_end(string name, int st){
        if(dque.size()==MAX_QUEUE)
            return false;
        dque.push_back(make_pair(name, st));
        return true;
    }

    void print(){
        if(dque.size()==0)
            return;
        cout << "\nThere are " << dque.size() << " patients in specialization " << spec << "\n";
        for(const auto &[st,nd] : dque){ // structured binding
            cout << st << " ";
            if(nd)
                cout << "urgent\n";
            else
                cout << "regular\n";
        }
    }

    void remove_patient(){
        if(dque.size()==0){
            cout << "No patients at the moment. Have rest, Dr.\n";
            return;
        }
        auto &[st, nd] = dque.front(); // structured binding
        cout << st << " please go with the Dr.\n";
        dque.pop_front();
        return;
    }
};


struct hospital_system{
    vector<hospital_queue> data;

    hospital_system(){
        data = vector<hospital_queue>(MAX_SPECIALIZATIONS);

        for(int i=0; i<MAX_SPECIALIZATIONS; ++i) // feed vector with specs numbers
            data[i] = hospital_queue(i+1); // ONE based
    }

    int menu(){
        int choose = -1;
        while(choose == -1){
            cout << "\n>> MENU\n";
            cout << "Enter your choice: \n";
            cout << "1) Add new patient\n";
            cout << "2) Print all patients\n";
            cout << "3) Get next patient\n";
            cout << "4) Exit\n";

            cin >> choose;
            if(!(1<=choose && choose <=4)){
                cout << "Invalid input. Try again!\n";
                choose = -1;
            }
        }
        return choose;
    }

    void add_patient(){
        int spec, st;
        string name;
        cout << "Enter specialization, name, and status: ";
        cin >> spec >> name >> st;
        spec--; // zero based
        if(!(0<=spec && spec <=19)){
            cout << "Invalid inputs.\n";
            return;
        }
        bool flag;
        if(st==0)
            flag = data[spec].add_end(name, st);
        else if(st==1)
            flag = data[spec].add_front(name, st);
        else
            cout << "Invalid inputs.\n";

        if(!flag)
            cout << "Sorry we cannot add more patients to this specialization.\n";

        return;
    }

    void print_patients(){
        cout << "****************************";
        for(int i=0; i<MAX_SPECIALIZATIONS; i++)
            data[i].print();
    }

    void get_next(){
        int spec;
        cout << "Enter specialization: ";
        cin >> spec;
        spec--; //zero based
        if(!(0<=spec && spec <=19)){
            cout << "Invalid inputs.\n";
            return;
        }
        data[spec].remove_patient();
    }

    void run(){
        while(true){
            int choise = menu();

            if(choise==1)
                add_patient();
            else if(choise==2)
                print_patients();
            else if(choise==3)
                get_next();
            else
                break;
        }
    }
};




int main(){
    //freopen("\\test_sample.txt", "rt", stdin);
    hospital_system hospital;
    hospital.run();

    return 0;
}
