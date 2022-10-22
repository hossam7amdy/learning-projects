#include "RoundRobin.h"

#include<queue>

void Run(){
	RoundRobin Algorithm;

	cout << "\tALGORITHM's MENU\n";
	while(true){
		cout << "1. Add a process.\n";
		cout << "2. Serve a process.\n";
		cout << "3. How many waiting processes?\n";
		cout << "4. Display information of waiting processes.\n";
		cout << "5. Display total CPU burst time.\n";
		cout << "6. Exit.\n";
		int choose;
		cin >> choose;
		if(1>choose && choose>6)
			continue;

		if(choose == 1)
			Algorithm.Add_process();
		else if(choose == 2)
			Algorithm.Serve_process();
		else if(choose == 3)
			Algorithm.How_many_waiting_processes();
		else if(choose == 4)
			Algorithm.Display_information_of_waiting_processes();
		else if(choose == 5)
			Algorithm.Display_total_CPU_burst_time();
		else if(choose == 6)
			break;
	}
}

int main()
{
    Run();

    return 0;
}
