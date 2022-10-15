#include<iostream>
using namespace std;

/*
● Implement the following system for a hospital
● There are 20 different specialization (e.g. Children, Surgery, etc)
● For each specialization, there are only 5 available spots [queue]
● Adding a patient
    ○ Read the requested specialization [1-20].
    ○ Read his name and status (0 = regular, 1 urgent)
    ○ If 5 patients exist, apologize and don’t accept.
    ○ If the user is regular, add in end of queue. Otherwise, add in Begin
● Print patients, for the specializations that have waiting patients
● Dr pickup a patient
    ○ Read the requested specialization. If no patients, inform the doctor
    ○ Otherwise, ask the patient to go with the Dr. Remove from the queue
*/

int const MAX = 5;
string names[20][MAX];
int status[20][MAX];
int que[20]{0};

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

void add_front(int spec, string name){
    int row = que[spec];
    if(row==MAX){
        cout << "Sorry we cannot add more patients to this specialization.\n";
        return;
    }
    for(int r=row; r>=0; r--){
        names[spec][r+1] = names[spec][r];
        status[spec][r+1] = status[spec][r];
    }
    names[spec][0] = name;
    status[spec][0] = 1;
    que[spec]++;
}

void add_back(int spec, string name){
    int row = que[spec];
    if(row<MAX){
        names[spec][row] = name;
        status[spec][row] = 0;
        que[spec]++;
        return;
    }
    cout << "Sorry we cannot add more patients to this specialization.\n";
}

void add_patient(){
    cout << "Enter specialization, name, and status: ";
    int spec, stat;
    string name;

    cin >> spec >> name >> stat;
    spec--;
    if(!(0<=spec && spec <=19)){
        cout << "Invalid inputs.\n";
        return;
    }

    if(stat == 0)
        add_back(spec, name);
    else if(stat == 1)
        add_front(spec, name);
    else
        cout << "Invalid inputs.\n";
}

void print_patients(){
    bool flag = true;
    cout << "****************************";
    for(int c=0; c<20; c++){
        int row = que[c];
        if(row){
            flag = false;
            cout << "\nThere are " << row << " patients in specialization " << c+1 << "\n";
        }
        else
            continue;
        for(int r=0; r<row; r++){
            cout << names[c][r];
            if(status[c][r])
                cout << " urgent\n";
            else
                cout << " regular\n";
        }
    }
    if(flag)
        cout << "There are no patients at the moment.\n";
}

void get_next(){
    int spec;
    cout << "Enter specialization: ";
    cin >> spec;
    spec--;
    if(!(0<=spec && spec <=19)){
        cout << "Invalid inputs.\n";
        return;
    }
    int row = que[spec];
    if(row==0){
        cout << "No patients at the moment. Have rest, Dr.\n";
        return;
    }
    cout << names[spec][0] << " please go with the Dr.\n";
    for(int r=1; r<row; r++){
        names[spec][r-1] = names[spec][r];
        status[spec][r-1] = status[spec][r];
    }
    que[spec]--;
}

void hospital_sys(){
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

int main(){
    //freopen("\\test_sample.txt", "rt", stdin);
    hospital_sys();

    return 0;
}
