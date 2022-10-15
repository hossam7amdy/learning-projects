#ifndef ROUNDROBIN_H_INCLUDED
#define ROUNDROBIN_H_INCLUDED

#include "Queue.h"
#include "process.h"

class RoundRobin{
private:
	const int time_quantum = 10;

	Queue<process> processes;
	int total_burst_time{};

public:
	RoundRobin();
	RoundRobin(const RoundRobin&) = delete;
	void operator=(const RoundRobin&) = delete;

	void Add_process();
	void Serve_process();
	void How_many_waiting_processes();
	void Display_information_of_waiting_processes();
	void Display_total_CPU_burst_time();

	~RoundRobin();
};

#endif // ROUNDROBIN_H_INCLUDED
