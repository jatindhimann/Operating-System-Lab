#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <limits.h>
using namespace std;

class Partition
{
public:
    int id;   // id of partiton
    int size; // size of Partition
    bool alloted;
    vector<int> noOfProc;
    Partition()
    {
        this->size = 0;
        this->id = 0;
        this->alloted = false;
    }
};

class process
{
public:
    int id;
    int memory_required;
    int allocated_Partition;
    bool allocated;
    process()
    {
        this->id = 0;
        this->memory_required = 0;
        this->allocated_Partition = 0;
        this->allocated = false;
    }
};

void FirstFit(vector<Partition> &listPart, vector<process> &listProc)
{
    for (int i = 0; i < listProc.size(); i++)
    {
        for (int j = 0; j < listPart.size(); j++)
        {
            if (listProc[i].memory_required > listPart[j].size)
                continue;
            else
            {
                listProc[i].allocated = true;
                listProc[i].allocated_Partition = listPart[j].id;
                listPart[j].alloted = true;
                listPart[j].size -= listProc[i].memory_required;
                listPart[j].noOfProc.push_back(listProc[i].id);
                break;
            }
        }
    }
}

void BestFit(vector<Partition> &listPart, vector<process> &listProc)
{
    for (int i = 0; i < listProc.size(); i++)
    {
        vector<int> satisfying_part_idxs; // to store the idx of partitions that can fill the mem requirement of process, and
                                          //  select the partition having min size from it
        for (int j = 0; j < listPart.size(); j++)
        {
            if (listProc[i].memory_required > listPart[j].size)
                continue;
            else
            {
                satisfying_part_idxs.push_back(j); // storing
            }
        }
        if (!satisfying_part_idxs.empty()) // selecting
        {
            int min = INT_MAX;
            int min_idx = -1;
            for (int j = 0; j < satisfying_part_idxs.size(); j++)
            {
                if (listPart[satisfying_part_idxs[j]].size < min)
                {
                    min = listPart[satisfying_part_idxs[j]].size;
                    min_idx = satisfying_part_idxs[j];
                }
            }
            listProc[i].allocated = true;
            listProc[i].allocated_Partition = listPart[min_idx].id;
            listPart[min_idx].alloted = true;
            listPart[min_idx].size -= listProc[i].memory_required;
            listPart[min_idx].noOfProc.push_back(listProc[i].id);
        }
    }
}
// Algorithm Worst Fit
void WorstFit(vector<Partition> &listPart, vector<process> &listProc)
{
    for (int i = 0; i < listProc.size(); i++)
    {
        int maxFree_idx = 0;
        for (int j = 1; j < listPart.size(); j++) // finding the index of partition having max size
        {
            if (listPart[j].size > listPart[maxFree_idx].size)
            {
                maxFree_idx = j;
            }
        }
        if (listProc[i].memory_required > listPart[maxFree_idx].size)
            continue;
        else
        {
            listProc[i].allocated = true;
            listProc[i].allocated_Partition = listPart[maxFree_idx].id;
            listPart[maxFree_idx].alloted = true;
            listPart[maxFree_idx].size -= listProc[i].memory_required;
            listPart[maxFree_idx].noOfProc.push_back(listProc[i].id);
        }
    }
}

void read_input_mem(vector<Partition> &listPart, vector<process> &listProc)
{
    bool choice;
    cout << "Do you want to enter new Partition details(0/1) ";
    cin >> choice;
    if (choice)
    {
        int numOfPart, numOfProc;
        fstream outputFile("Memory_Management/Partition_details.txt", ios::out);
        cout << "Enter the number of Partition: ";
        cin >> numOfPart;
        cout << "Enter the number of process: ";
        cin >> numOfProc;
        outputFile << numOfPart << " " << numOfProc << endl;
        cout << "Enter the size of each Partition: " << endl;
        for (int i = 0; i < numOfPart; i++)
        {
            int size;
            cout << " Enter the size of Partition " << i + 1 << ": ";
            cin >> size;
            outputFile << size << " ";
        }
        outputFile << endl;

        cout << "Enter memory required for each process: " << endl;
        for (int i = 0; i < numOfProc; i++)
        {
            int memory;
            cout << " Enter the memory requirement of process " << i + 1 << ": ";
            cin >> memory;
            outputFile << memory << " ";
        }

        outputFile.close();
    }

    fstream inputFile("Memory_Management/Partition_details.txt", ios::in);

    int numOfPart, numOfProc;
    inputFile >> numOfPart >> numOfProc;

    listPart.resize(numOfPart);
    listProc.resize(numOfProc);

    for (int i = 0; i < numOfPart; i++)
    {
        inputFile >> listPart[i].size;
        listPart[i].id = i + 1;
    }

    for (int i = 0; i < numOfProc; i++)
    {
        inputFile >> listProc[i].memory_required;
        listProc[i].id = i + 1;
    }

    inputFile.close();
}

void print_memory_results(vector<Partition> &listPart, vector<process> &listProc)
{
    cout << endl
         << "ProcID\tMemRequired\tAllocated\tAllocatedPartID" << endl;
    for (int i = 0; i < listProc.size(); i++)
    {
        cout << listProc[i].id << "\t" << listProc[i].memory_required << "\t\t";
        if (listProc[i].allocated)
        {
            cout << "Yes\t\t";
            cout << listProc[i].allocated_Partition << endl;
        }
        else
        {
            cout << "No\t\t";
            cout << "-" << endl;
        }
    }
    cout << "-------------------------------------------------------" << endl;
    cout << endl
         << endl;
    cout << endl
         << "PartID\tAlloted\t\tInterFrag\tProcIDInPart" << endl;
    for (int i = 0; i < listPart.size(); i++)
    {
        cout << listPart[i].id << "\t";
        if (listPart[i].alloted)
        {
            cout << "Yes\t\t";
            cout << listPart[i].size << "\t\t";
            for (int j = 0; j < listPart[i].noOfProc.size(); j++)
            {
                cout << listPart[i].noOfProc[j];
                if (j != listPart[i].noOfProc.size() - 1)
                    cout << ",";
            }
            cout << endl;
        }
        else
        {
            cout << "No\t\t";
            cout << listPart[i].size << "\t\t";
            cout << "-" << endl;
            ;
        }
    }
    cout << "-------------------------------------------------------" << endl;
    cout << endl
         << endl;
}