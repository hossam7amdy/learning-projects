#include<iostream>
using namespace std;

int const MAX_QUEUE {5};
int const MAX_SPECIALIZATIONS {20};

struct hospital_queue{
    string names[MAX_QUEUE];
    int status[MAX_QUEUE];
    int len;

    hospital_queue(){
        len = 0;
    }

    bool add_end(string name, int st){
        if(len==MAX_QUEUE)
            return false;

        names[len] = name, status[len] = st, len++;
        return true;
    }

    bool add_front(string name, int st){
        if(len==MAX_QUEUE)
            return false;
        //Shift right
        for(int i=len; i>0; i--){
            names[i] = names[i-1];
            status[i] = status[i-1];
        }
        names[0] = name, status[0] = st, len++;
        return true;
    }

    void print(int spec){
        if(len==0)
            return;
        cout << "\nThere are " << len << " patients in specialization " << spec+1 << "\n";
        for(int i=0; i<len; i++){
            cout << names[i];
            if(status[i])
                cout << " urgent\n";
            else
                cout << " regular\n";
        }
    }

    void remove_patient(){
        if(len==0){
            cout << "No patients at the moment. Have reset, Dr.\n";
            return;
        }
        cout << names[0] << " please go with the doctor.\n";
        //Shift left
        for(int i=0; i<len-1; i++){
            names[i] = names[i+1];
            status[i] = status[i+1];
        }
        len--;
    }

};


struct hospital_system{
    hospital_queue hospital_specs[MAX_SPECIALIZATIONS];

    hospital_system(){
        for(int i=0; i<MAX_SPECIALIZATIONS; i++)
            hospital_specs[i] = hospital_queue();
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
        spec--;
        if(!(0<=spec && spec <=19)){
            cout << "Invalid inputs.\n";
            return;
        }
        bool flag;
        if(st==0)
            flag = hospital_specs[spec].add_end(name, st);
        else if(st==1)
            flag = hospital_specs[spec].add_front(name, st);
        else
            cout << "Invalid inputs.\n";

        if(!flag)
            cout << "Sorry we cannot add more patients to this specialization.\n";
    }

    void print_patients(){
        cout << "****************************";
        for(int spec=0; spec<MAX_SPECIALIZATIONS; spec++)
            hospital_specs[spec].print(spec);
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
        hospital_specs[spec].remove_patient();
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
    hospital_system hospital = hospital_system();
    hospital.run();

    return 0;
}
