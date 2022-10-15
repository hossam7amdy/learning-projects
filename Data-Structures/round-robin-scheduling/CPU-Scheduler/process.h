#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include<iostream>
using namespace std;

class process{
private:
	string name;
	int burstTime{};
public:
	process();
	process(const string &name, const int &burstTime);

	void read();
	void serve(const int &quantamTime);

	string get_process_name() const;
	int get_brust_time() const;
	void set_process_name(const string &name);
	void set_burst_time(const int &time);

	friend ostream& operator<<(ostream &output, const process &p);
};


#endif // PROCESS_H_INCLUDED
