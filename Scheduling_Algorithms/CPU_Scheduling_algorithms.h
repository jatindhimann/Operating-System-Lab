#include "Sort_helper.h"
#include "helper.h"
#include <map>
#include <set>
#include <queue>
#include <deque>

class CPU_Scheduling_algos
{
public:
    pair<int, vector<PCB>> FCFS(vector<PCB> &process_list)
    {
        sort_arrival_time_then_id(process_list);

        int time = 0;
        cout << "0 | ";
        for (auto &current_process : process_list)
        {
            time += current_process.burst_time;
            cout << "P" << current_process.process_id << " | " << time << " | ";
            current_process.completion_time = time;

            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;
        }
        cout << endl;
        return {time, process_list};
    }

    pair<int, vector<PCB>> SJF_Non_premptive(vector<PCB> &process_list)
    {
        int time = 0;
        cout << "0 | ";
        deque<PCB> remain_processes(process_list.begin(), process_list.end());
        while (!remain_processes.empty())
        {
            sort_on_sjf(remain_processes, time);
            PCB current_process = remain_processes.front();
            remain_processes.pop_front();

            time += current_process.burst_time;
            cout << "P" << current_process.process_id << " | " << time << " | ";
            int id = current_process.process_id;
            int index = -1;
            for (int i = 0; i < process_list.size(); i++)
            {
                if (id == process_list[i].process_id)
                {
                    index = i;
                    break;
                }
            }
            process_list[index].completion_time = time;
            process_list[index].turnaround_time = process_list[index].completion_time - process_list[index].arrival_time;
            process_list[index].waiting_time = process_list[index].turnaround_time - process_list[index].burst_time;
        }

        cout << endl;
        return {time, process_list};
    }

    pair<int, vector<PCB>> SJF_premptive(vector<PCB> &process_list)
    {
        int time = 0;
        cout << "0 | ";
        deque<PCB> remain_processes(process_list.begin(), process_list.end());
        while (!remain_processes.empty())
        {
            sort_on_sjf(remain_processes, time);
            PCB current_process = remain_processes.front();
            current_process.remaining_burst -= 1;
            remain_processes.pop_front();

            time += 1;
            cout << "P" << current_process.process_id << " | " << time << " | ";
            int id = current_process.process_id;
            int index = -1;
            for (int i = 0; i < process_list.size(); i++)
            {
                if (id == process_list[i].process_id)
                {
                    index = i;
                    break;
                }
            }

            if (current_process.remaining_burst > 0)
            {
                remain_processes.push_back(current_process);
            }
            else
            {
                process_list[index].completion_time = time;
                process_list[index].turnaround_time = process_list[index].completion_time - process_list[index].arrival_time;
                process_list[index].waiting_time = process_list[index].turnaround_time - process_list[index].burst_time;
            }
        }

        cout << endl;
        return {time, process_list};
    }

    pair<int, vector<PCB>> priority_Non_Premptive(vector<PCB> &process_list)
    {
        deque<PCB> remaining_process(process_list.begin(), process_list.end());
        int time = 0;
        cout << "0 |";
        while (!remaining_process.empty())
        {
            sort_priority(remaining_process, time);
            PCB curr_process = remaining_process.front();
            remaining_process.pop_front();
            time += curr_process.burst_time;
            cout << "P" << curr_process.process_id << " | " << time << " | ";
            int id = curr_process.process_id;
            int index = -1;
            for (int i = 0; i < process_list.size(); i++)
            {
                if (id == process_list[i].process_id)
                {
                    index = i;
                    break;
                }
            }
            process_list[index].completion_time = time;
            process_list[index].turnaround_time = process_list[index].completion_time - process_list[index].arrival_time;
            process_list[index].waiting_time = process_list[index].turnaround_time - process_list[index].burst_time;
        }
        cout << endl;
        return {time, process_list};
    }

    pair<int, vector<PCB>> priority_Premptive(vector<PCB> &process_list)
    {
        // checking change of parameters every second
        int time = 0;
        cout << "0 | ";
        deque<PCB> remain_processes(process_list.begin(), process_list.end());
        while (!remain_processes.empty())
        {
            sort_priority(remain_processes, time);
            PCB current_process = remain_processes.front();
            current_process.remaining_burst -= 1;
            remain_processes.pop_front();

            time += 1;
            cout << "P" << current_process.process_id << " | " << time << " | ";

            if (current_process.remaining_burst > 0)
            {
                remain_processes.push_back(current_process);
            }
            else
            {
                int id = current_process.process_id;
                int index = -1;
                for (int i = 0; i < process_list.size(); i++)
                {
                    if (id == process_list[i].process_id)
                    {
                        index = i;
                        break;
                    }
                }
                process_list[index].completion_time = time;
                process_list[index].turnaround_time = process_list[index].completion_time - process_list[index].arrival_time;
                process_list[index].waiting_time = process_list[index].turnaround_time - process_list[index].burst_time;
            }
        }

        cout << endl;
        return {time, process_list};
    }
    pair<int, vector<PCB>> round_robin(vector<PCB> &process_list, int quantum)
    {
        int n = process_list.size();
        int time = 0;
        int completedProcesses = 0;
        sort_arrival_time_then_id(process_list);
        deque<PCB> q; // Queue for ready processes

        int i = 0; // Index to track the current process

        cout<<" 0 |";
        while (completedProcesses < n)
        {
            // Add processes that have arrived before or at the current time to the queue
            while (i < n && process_list[i].arrival_time <= time)
            {
                q.push_back(process_list[i]);
                i++;
            }

            if (q.empty())
            {
                // If no process is in the ready queue, jump to the next arrival time
                time = process_list[i].arrival_time;
                continue;
            }

            PCB current_process = q.front();
           q.pop_front();

            // Execute the process for the quantum time or remaining burst time, whichever is smaller
            int executeTime = min(quantum, current_process.remaining_burst);
            time += executeTime;
            cout << "P" << current_process.process_id << " | " << time << " | ";
            current_process.remaining_burst -= executeTime;

            // Add processes that have arrived during the execution of the current process
            while (i < n && process_list[i].arrival_time <= time)
            {
                q.push_back(process_list[i]);
                i++;
            }

            if (current_process.remaining_burst > 0)
            {
                // If the process still has remaining burst time, re-add it to the queue
                q.push_back(current_process);
            }
            else
            {
                // Process has completed
                int id = current_process.process_id;
                int index = -1;
                for (int j = 0; j < process_list.size(); j++)
                {
                    if (id == process_list[j].process_id)
                    {
                        index = j;
                        break;
                    }
                }
                process_list[index].completion_time = time;
                process_list[index].turnaround_time = process_list[index].completion_time - process_list[index].arrival_time;
                process_list[index].waiting_time = process_list[index].turnaround_time - process_list[index].burst_time;
                completedProcesses++;
            }
        }

        return {time, process_list};
    }
};