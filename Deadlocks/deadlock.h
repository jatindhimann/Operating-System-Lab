#pragma once
#include <iostream>
#include <vector>
using namespace std;

class process_info
{
public:
    int process_id;
    vector<int> max_need;
    vector<int> allocated;
    vector<int> need;
    process_info(int process_id, int no_of_resources)
    {
        this->process_id = process_id;
        max_need.resize(no_of_resources);
        allocated.resize(no_of_resources);
        need.resize(no_of_resources);
        cout << "Enter the max need of resources for process P" << process_id << ": ";
        for (int i = 0; i < no_of_resources; i++)
        {
            cin >> max_need[i];
        }
        cout << "Enter the no. of already allocated resources to process P" << process_id << ": ";
        for (int i = 0; i < no_of_resources; i++)
        {
            cin >> allocated[i];
        }

        for (int i = 0; i < no_of_resources; i++)
        {
            need[i] = max_need[i] - allocated[i];
        }
    }
};

class banker
{
public:
    vector<process_info> process_details;
    vector<int> available;
    int no_of_process;
    int no_of_resources;
    banker()
    {
        for (int i = 0; i < no_of_process; i++)
        {
            process_info process(i, no_of_resources);
            process_details.push_back(process);
        }
        available.resize(no_of_resources);
        cout << "Enter the available number of instances for each resource " << endl;
        for (int i = 0; i < no_of_resources; i++)
        {
            cin >> available[i];
        }
    }

    bool safety_algorithm()
    {
        vector<bool> finish(no_of_process, false);
        vector<int> safe_sequence;

        for (int k = 0; k < no_of_process; k++)
        {
            for (int i = 0; i < no_of_process; i++)
            {
                if (finish[i] == false)
                {
                    bool flag = false;
                    for (int j = 0; j < no_of_resources; j++)
                    {
                        if (process_details[i].need[j] > available[j])
                        {
                            flag = true;
                            break;
                        }
                    }

                    if (flag == false)
                    {
                        safe_sequence.push_back(i);
                        for (int p = 0; p < no_of_resources; p++)
                        {
                            available[p] += process_details[i].allocated[p];
                        }
                        finish[i] = true;
                    }
                }
            }
        }
        bool flag = true;

        for (int i = 0; i < no_of_process; i++)
        {
            if (finish[i] == 0)
            {
                flag = false;
                cout << "The given sequence is not safe\n";
                return false;
                break;
            }
        }

        if (flag == true)
        {
            cout << "Safe Sequence is :- " << endl;
            for (int i = 0; i <= no_of_process - 2; i++)
            {
                cout << "P" << safe_sequence[i] << " -> ";
            }
            cout << "P" << safe_sequence[no_of_process - 1] << endl;
            return true;
        }
    }

    bool requestResourceAllocation()
    {
        vector<int> request(no_of_resources);
        int id;
        cout << "Enter the id of process which made request (0-" << no_of_process - 1 << "): ";
        cin >> id;

        cout << "Enter the Requested resource instances: ";
        for (int i = 0; i < no_of_resources; i++)
        {
            cin >> request[i];
        }

        for (int i = 0; i < no_of_resources; i++)
        {
            if (process_details[id].need[i] < request[i] && request[i] > available[i])
            {
                return false;
            }
        }

        for (int i = 0; i < no_of_resources; i++)
        {
            available[i] -= request[i];
            process_details[id].allocated[i] += request[i];
            process_details[id].need[i] -= request[i];
        }

        if (safety_algorithm())
        {
            cout<<"Request Granted"<<endl;
            return true;
        }
        else
        {
            cout<<"Request Denied"<<endl;
            return false;
        }
    }
};