#include "process.h"

process::process(){ }

process::process(const string &name, const int &burstTime):
    name(name), burstTime(burstTime){
}

void process::read(){
	string p_name;
	int burstTime;
	cout << "Enter Process Name and BurstTime: ";
	cin >> p_name >> burstTime;

	set_process_name(p_name);
	set_burst_time(burstTime);
}
string process::get_process_name() const {
	return name;
}
void process::serve(const int &quantamTime){
    if(burstTime < quantamTime)
        burstTime = 0;
    else
        this->burstTime -= quantamTime;
}
int process::get_brust_time() const{
	return burstTime;
}
void process::set_process_name(const string &name){
	this->name = name;
}
void process::set_burst_time(const int &time){
	this->burstTime = time;
}

ostream& operator<<(ostream &output, const process &p){
	output << p.get_process_name() << "\t" << p.get_brust_time();
	return output;
}
