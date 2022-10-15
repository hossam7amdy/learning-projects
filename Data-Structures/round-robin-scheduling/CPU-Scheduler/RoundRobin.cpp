#include "RoundRobin.h"

RoundRobin::RoundRobin() {
    cout << "Loading processes...\n\n";
    process p1("p1", 50);
    processes.Enqueue(p1);
    process p2("p2", 10);
    processes.Enqueue(p2);
    process p3("p3", 20);
    processes.Enqueue(p3);
    process p4("p4", 60);
    processes.Enqueue(p4);
    process p5("p5", 45);
    processes.Enqueue(p5);
    process p6("p6", 5);
    processes.Enqueue(p6);
    process p7("p7", 15);
    processes.Enqueue(p7);
    process p8("p8", 35);
    processes.Enqueue(p8);

    total_burst_time = 240;
}

void RoundRobin::Add_process(){
    process p;
    p.read();

    total_burst_time += p.get_brust_time();
	processes.Enqueue(p);
}
void RoundRobin::Serve_process(){
    if(processes.isEmpty()){
        cout << "====================================\n";
        cout << "CPU is idle.\n";
        cout << "====================================\n\n";
        return;
    }

    process cur = processes.Dequeue();
    total_burst_time -= cur.get_brust_time();
    cout << "====================================\n";
    cout << cur.get_process_name() << " Processing ...\n";
    cout << "====================================\n\n";

    cur.serve(time_quantum);
    total_burst_time += cur.get_brust_time();

    if(cur.get_brust_time()>0)
        processes.Enqueue(cur);
}
void RoundRobin::How_many_waiting_processes(){
    cout << "=====================================\n";
	cout << "Total available processes = " << processes.Size() << "\n";
	cout << "=====================================\n\n";
}
void RoundRobin::Display_information_of_waiting_processes(){
    if(processes.isEmpty()){
        cout << "====================================\n";
        cout << "No Processes to Display.\n";
        cout << "====================================\n\n";
        return;
    }
	cout << "Process\tBurst Time\n";
	processes.print();
	cout << "=====================================\n\n";
}
void RoundRobin::Display_total_CPU_burst_time(){
    cout << "=====================================\n";
	cout << "Total Remaining Burst Time = " << total_burst_time << "\n";
	cout << "=====================================\n\n";
}

RoundRobin::~RoundRobin(){
}
