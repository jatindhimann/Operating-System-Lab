#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

pair<vector<pair<int, bool>>, pair<int, int>> read_input_req(vector<pair<int, bool>> &requests)
{
    bool choice;
    cout << "Do you want to enter new requests details(0/1) ";
    cin >> choice;
    int no_of_process;
    int no_of_cylinders;
    int initial_position;
    if (choice)
    {
        fstream outputFile("Disk_Scheduling/disk_details.txt", ios::out);
        cout << "Enter the no. of requests: ";
        cin >> no_of_process;

        cout << "Enter the no. of cylinders: ";
        cin >> no_of_cylinders;
        cout << "Enter the initial Position of head: ";
        cin >> initial_position;
        outputFile << no_of_process << " " << no_of_cylinders << " " << initial_position;
        outputFile << endl;
        cout << "Enter the cylinder requests: \n";
        for (int i = 0; i < no_of_process; i++)
        {
            int req;
            cout << " Request " << i + 1 << ": ";
            cin >> req;
            outputFile << req << " ";
        }

        outputFile.close();
    }

    fstream inputFile("Disk_Scheduling/disk_details.txt", ios::in);

    inputFile >> no_of_process >> no_of_cylinders >> initial_position;

    for (int i = 0; i < no_of_process; i++)
    {
        int req;
        inputFile >> req;
        requests.push_back({req, false});
    }

    inputFile.close();

    return {requests, {initial_position, no_of_cylinders}};
}

void print_req_res(pair<vector<pair<int, bool>>, pair<int, int>> input_req, int head_movements,vector<int> seekSequence)
{
    cout << "Total Number of Cylinders: " << input_req.second.second<<endl;
    cout << "Initial Position of head: " << input_req.second.first << endl;
    cout << "Seek Sequence: ";
    for (auto i : seekSequence)
    {
        cout << i<< " ";
    }
    cout << "\n";
    cout << "Total head Movements required: " << head_movements << endl;
    cout << "\n";
}
