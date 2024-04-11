#pragma once

class PCB
{
public:
    int process_id;
    int arrival_time;
    int turnaround_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int priority;
    int remaining_burst;
    PCB(int process_id, int arrival_time, int burst_time, int priority)
    {
        this->process_id = process_id;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->completion_time = 0;
        this->waiting_time = 0;
        this->turnaround_time = 0;
        this->remaining_burst = burst_time;
        this->priority = priority;
    }
};