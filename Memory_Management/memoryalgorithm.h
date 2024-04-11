#include <iostream>
#include <cstdlib>
#include <vector>
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

void FirstFit(Partition *listPart, int numOfPart, process *listProc, int numOfProc)
{
    for (int i = 0; i < numOfProc; i++)
    {
        for (int j = 0; j < numOfPart; j++)
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

void BestFit(Partition *listPart, int numOfPart, process *listProc, int numOfProc)
{
    for (int i = 0; i < numOfProc; i++)
    {
        int *satisfyingList = new int[numOfPart];
        vector<int> listKey;
        int noOfSatisfy = 0;
        for (int j = 0; j < numOfPart; j++)
        {
            if (listProc[i].memory_required > listPart[j].size)
                continue;
            else
            {
                satisfyingList[noOfSatisfy++] = listPart[j].id;
                listKey.push_back(j);
            }
        }
        if (noOfSatisfy != 0)
        {
            int current = satisfyingList[0], key = listKey[0];
            for (int j = 1; j < noOfSatisfy; j++)
            {
                if (listPart[listKey[j]].size < listPart[key].size)
                {
                    key = listKey[j];
                    current = satisfyingList[j];
                }
            }
            listProc[i].allocated = true;
            listProc[i].allocated_Partition = current;
            listPart[key].alloted = true;
            listPart[key].size -= listProc[i].memory_required;
            listPart[key].noOfProc.push_back(listProc[i].id);
        }
    }
}

void WorstFit(Partition *listPart, int numOfPart, process *listProc, int numOfProc)
{
    for (int i = 0; i < numOfProc; i++)
    {
        int maxFreePart = listPart[0].id, key = 0;
        for (int j = 1; j < numOfPart; j++)
        {
            if (listPart[j].size > listPart[key].size)
            {
                maxFreePart = listPart[j].id;
                key = j;
            }
        }
        if (listProc[i].memory_required > listPart[key].size)
            continue;
        else
        {
            listProc[i].allocated = true;
            listProc[i].allocated_Partition = maxFreePart;
            listPart[key].alloted = true;
            listPart[key].size -= listProc[i].memory_required;
            listPart[key].noOfProc.push_back(listProc[i].id);
        }
    }
}

pair<Partition *, process *> read_input_mem(int numOfPart, int numOfProc)
{
    // double timeUsed, timeUsed2, timeUsed3;
    Partition *listPart = new Partition[numOfPart];
    cout << "Enter the size of each Partition: ";
    for (int i = 0; i < numOfPart; i++)
    {
        listPart[i].id = i + 1;
        cin >> listPart[i].size;
    }
    process *listProc = new process[numOfProc];
    cout << "Enter memory required for each process: ";
    for (int i = 0; i < numOfProc; i++)
    {
        listProc[i].id = i + 1;
        cin >> listProc[i].memory_required;
    }

    return {listPart, listProc};
}

pair<int, int> read_num(int numOfPart, int numOfProc)
{
    cout << "Enter the number of Partition: ";
    cin >> numOfPart;
    cout << "Enter the number of process: ";
    cin >> numOfProc;

    return {numOfPart, numOfProc};
}

void print_memory_results(Partition *listPart, int numOfPart, process *listProc, int numOfProc)
{
    cout << endl
         << "ProcID\tMemRequired\tAllocated\tAllocatedPartID" << endl;
    for (int i = 0; i < numOfProc; i++)
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
    for (int i = 0; i < numOfPart; i++)
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