#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "PCB.h"
using namespace std;

void read_input_CPUschedule_algo(vector<PCB> &process_list)
{
    bool choice;
    cout << "Do you want to enter new process(0/1) ";
    cin >> choice;

    if (choice)
    {
        int number_of_process;
        cout << "Enter the number of process ";
        cin >> number_of_process;
        fstream outputFile("Scheduling_Algorithms/Process_details.txt", ios::out);

        for (int i = 0; i < number_of_process; i++)
        {
            int pid;
            int arrival_time;
            int burst_time;
            int priority;
            cout << "Process " << i + 1 << ": " << endl;
            cout << "Enter process id ";
            cin >> pid;
            cout << "Enter arrival time ";
            cin >> arrival_time;
            cout << "Enter burst time ";
            cin >> burst_time;
            cout << "Enter priority";
            cin >> priority;
            outputFile << pid << " " << arrival_time << " " << burst_time<< " " <<priority;
            outputFile << endl;
        }
        outputFile.close();
    }
    
    fstream inputFile("Scheduling_Algorithms/Process_details.txt", ios::in);

    while (!inputFile.eof())
    {
        int pid;
        int arrival_time;
        int burst_time;
        int priority;
        inputFile >> pid >> arrival_time >> burst_time >> priority;

        if (!inputFile.fail())
        {
            process_list.push_back(PCB(pid, arrival_time, burst_time,priority));
        }
    }
    inputFile.close();
}

void print(vector<PCB> &process_list)
{
    sort(process_list.begin(), process_list.end(), [](PCB a, PCB b)
         { return a.process_id <= b.process_id; });

    for (auto current_process : process_list)
    {
        cout << "Process ID: " << current_process.process_id << endl
             << " Completion time: " << current_process.completion_time << endl
             << " Waiting time: " << current_process.waiting_time << endl
             << " Turnaround time: " << current_process.turnaround_time<<endl;
    }
}

void print_statistics(vector<PCB> &process_list, int end_of_all_processes_time)
{
    int number_of_processes = process_list.size();
    double average_waiting_time = 0;
    double average_turnaround_time = 0;
    double cpu_utilization = process_list.size();
    double throughput = 0;
    double execution_time = 0;

    for (auto process : process_list)
    {
        average_turnaround_time += process.turnaround_time;
        average_waiting_time += process.waiting_time;
        execution_time += process.burst_time;
    }
    throughput = number_of_processes * 1.0 / end_of_all_processes_time;
    cpu_utilization = 1.0 * execution_time / end_of_all_processes_time;
    average_turnaround_time /= 1.0 * number_of_processes;
    average_waiting_time /= 1.0 * number_of_processes;
    cout << "\nRESULTS"<<endl
         << " Average Waiting Time = " << average_waiting_time << endl
         << " Average Turnaround Time = " << average_turnaround_time << endl
         << " CPU Utilization = " << cpu_utilization << endl
         << " Throughput = " << throughput << endl;
}