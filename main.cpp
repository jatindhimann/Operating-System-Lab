#include <iostream>
#include "Scheduling_Algorithms\CPU_Scheduling_algorithms.h"
#include "Scheduling_Algorithms\PCB.h"
#include "Scheduling_Algorithms\helper.h"
#include "Page_Replacement_algorithms\Page_replace_algo.h"
#include <cstdlib> // clrcsr
#include <vector>
#include "Page_Replacement_algorithms\helper.h"
#include "Memory_Management\memoryalgorithm.h"
#include "Disk_Scheduling/disk_algos.h"
#include "Deadlocks\deadlock.h"
using namespace std;

// cpu scheduling
CPU_Scheduling_algos algo;
vector<PCB> process_list;
pair<int, vector<PCB>> result;

// page replacement
Page_replace_algo pg_replace;
vector<int> reference_string;
int no_of_frames;
pair<vector<int>, int> input;

// deadlock
int no_of_process;
int no_of_resources;
banker b;
// memory management
vector<Partition> listPart;
vector<process> listProc;

// disk scheduling
vector<pair<int, bool>> requests;
pair<vector<pair<int, bool>>, pair<int, int>> input_req;
pair<int, vector<int>> output;
bool direction;

int main()
{
    cout << "*********************** Operating System Algorithms ************************" << endl;
    int choice;
    do
    {
        cout << "1. CPU Scheduling Algorithms" << endl;
        cout << "2. Deadlock Algorithms" << endl;
        cout << "3. Process Synchronization Algorithms" << endl;
        cout << "4. Page Replacement Algorithms" << endl;
        cout << "5. Disk Scheduling Algorithms" << endl;
        cout << "6. Memory Management Algorithms" << endl;
        cout << "7. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            read_input_CPUschedule_algo(process_list);
            system("cls");
            cout << "Select the Scheduling algorithm " << endl;
            int sub_choice;
            cout << " 1. First Come First Serve(FCFS)" << endl;
            cout << " 2. Shorest Job first(SJF)" << endl;
            cout << " 3. Priority Scheduling" << endl;
            cout << " 4. Round Robin" << endl;
            cout << " 5. Back" << endl;
            cin >> sub_choice;
            switch (sub_choice)
            {
            case 1:
                system("cls");
                cout << "First Come First Serve" << endl;
                cout << "------------------------------------------------------------------" << endl;
                cout << "Gant Chart =>";
                result = algo.FCFS(process_list);
                cout << endl;
                print(result.second);
                cout << "-------------------------------------------------------------------" << endl;
                print_statistics(result.second, result.first);
                cout << "-------------------------------------------------------------------" << endl;
                cout << "\n\n";
                break;
            case 2:
                int sjf_choice;
                do
                {
                    cout << "1. Premptive" << endl;
                    cout << "2. Non Preemptive" << endl;
                    cout << "3. Back" << endl;
                    cin >> sjf_choice;
                    switch (sjf_choice)
                    {
                    case 1:
                        system("cls");
                        cout << "Shortest Job First Premptive" << endl;
                        cout << "------------------------------------------------------------------" << endl;
                        cout << "Gant Chart =>";
                        result = algo.SJF_premptive(process_list);
                        cout << endl;
                        print(result.second);
                        cout << "-------------------------------------------------------------------" << endl;
                        print_statistics(result.second, result.first);
                        cout << "-------------------------------------------------------------------" << endl;
                        cout << "\n\n";
                        break;
                    case 2:
                        system("cls");
                        cout << "Shortest Job First Non-Premptive" << endl;
                        cout << "------------------------------------------------------------------" << endl;
                        cout << "Gant Chart =>";
                        result = algo.SJF_Non_premptive(process_list);
                        cout << endl;
                        print(result.second);
                        cout << "-------------------------------------------------------------------" << endl;
                        print_statistics(result.second, result.first);
                        cout << "-------------------------------------------------------------------" << endl;
                        cout << "\n\n";
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Invalid Choice! Enter valid option" << endl;
                    }
                } while (sjf_choice != 3);
                break;
            case 3:
                int pri_choice;
                do
                {
                    cout << "1. Premptive" << endl;
                    cout << "2. Non Preemptive" << endl;
                    cout << "3. Back" << endl;
                    cin >> pri_choice;
                    switch (pri_choice)
                    {
                    case 1:
                        system("cls");
                        cout << "Priority Premptive" << endl;
                        cout << "------------------------------------------------------------------" << endl;
                        cout << "Gant Chart =>";
                        result = algo.priority_Premptive(process_list);
                        cout << endl;
                        print(result.second);
                        cout << "-------------------------------------------------------------------" << endl;
                        print_statistics(result.second, result.first);
                        cout << "-------------------------------------------------------------------" << endl;
                        cout << "\n\n";
                        break;
                    case 2:
                        system("cls");
                        cout << "Priority Non Premptive" << endl;
                        cout << "------------------------------------------------------------------" << endl;
                        cout << "Gant Chart =>";
                        result = algo.priority_Non_Premptive(process_list);
                        cout << endl;
                        print(result.second);
                        cout << "-------------------------------------------------------------------" << endl;
                        print_statistics(result.second, result.first);
                        cout << "-------------------------------------------------------------------" << endl;
                        cout << "\n\n";
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Invalid Choice! Enter valid option" << endl;
                    }
                } while (pri_choice != 3);
                break;
            case 4:
                system("cls");
                int quantum;
                char c;
                cout << "Do you want to specify time quantum(y/n)\n";
                cin >> c;
                if (c == 'y' || c == 'Y')
                {
                    cout << "Enter time quantum value :- ";
                    cin >> quantum;
                }
                else
                {
                    quantum = 4;
                    cout << "Taking time quantum as 4 \n";
                }
                cout << "Round Robin" << endl;
                cout << "------------------------------------------------------------------" << endl;
                cout << "Gant Chart =>";
                result = algo.round_robin(process_list, quantum);
                cout << endl;
                print(result.second);
                cout << "-------------------------------------------------------------------" << endl;
                print_statistics(result.second, result.first);
                cout << "-------------------------------------------------------------------" << endl;
                cout << "\n\n";
                break;
            case 5:
                break;
            default:
                cout << "Invalid Choice! Enter valid option" << endl;
            }
            break;
        case 2:
            system("cls");
            cout << "Select Deadlock Algorithm:\n";
            int dl_choice;
            do
            {
                cout << "1. Safety Algorithm\n2. Request and Resource Allocation\n3. Back\nEnter your choice: ";
                cin >> dl_choice;
                cout << "Enter the number of process: ";
                cin >> no_of_process;
                cout << "Enter the no. of instances of resource: ";
                cin >> no_of_resources;
                switch (dl_choice)
                {
                case 1:
                    b.safety_algorithm();
                    break;
                case 2:
                    b.requestResourceAllocation();
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid Choice\n";
                    break;
                }
            } while (dl_choice != 3);
            break;
        case 3:
            break;
        case 4:
            system("cls");
            input = read_input_page_algo(reference_string, no_of_frames);
            system("cls");
            cout << "Select the Page Replacement Algorithm " << endl;
            int pg_algo_choice;
            do
            {
                cout << " 1. FIFO Page Replacement" << endl;
                cout << " 2. Optimal Page Replacement" << endl;
                cout << " 3. Least Recently Used (LRU)" << endl;
                cout << " 4. Most Frequently Used (MFU)" << endl;
                cout << " 5. Least Frequently Used (LFU)" << endl;
                cout << " 6. Back" << endl;
                cin >> pg_algo_choice;
                switch (pg_algo_choice)
                {
                case 1:
                    pg_replace.FIFO(input.first, input.second);
                    break;
                case 2:
                    pg_replace.OPT(input.first, input.second);
                    break;
                case 3:
                    pg_replace.LRU(input.first, input.second);
                    break;
                case 4:
                    pg_replace.MFU(input.first, input.second);
                    break;
                case 5:
                    pg_replace.LFU(input.first, input.second);
                    break;
                case 6:
                    system("cls");
                    break;
                }
            } while (pg_algo_choice != 6);
            break;
        case 5:
            system("cls");
            input_req = read_input_req(requests);
            system("cls");
            int req_algo_choice;
            cout << "Select the algorihtm" << endl;

            cout << " 1. FCFS" << endl;
            cout << " 2. SSTF" << endl;
            cout << " 3. SCAN" << endl;
            cout << " 4. C-SCAN" << endl;
            cout << " 5. LOOK" << endl;
            cout << " 6. C-LOOK" << endl;
            cout << " 7. Back" << endl;
            cin >> req_algo_choice;
            switch (req_algo_choice)
            {
            case 1:
                system("cls");
                cout << "\n";
                cout << "                FCFS ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = fcfs(input_req.first, input_req.second.first);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 2:
                system("cls");
                cout << "\n";
                cout << "                SSTF ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = sstf(input_req.first, input_req.second.first);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 3:
                system("cls");
                cout << "Enter head movement direction (1-right/0-left): ";
                cin >> direction;
                cout << "\n";
                cout << "                SCAN ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = scan(input_req.first, input_req.second.first, direction, input_req.second.second);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 4:
                system("cls");
                cout << "Enter head movement direction (1-right/0-left): ";
                cin >> direction;
                cout << "\n";
                cout << "                C-SCAN ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = cscan(input_req.first, input_req.second.first, direction, input_req.second.second);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 5:
                system("cls");
                cout << "Enter head movement direction (1-right/0-left): ";
                cin >> direction;
                cout << "\n";
                cout << "                LOOK ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = look(input_req.first, input_req.second.first, direction, input_req.second.second);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 6:
                system("cls");
                cout << "Enter head movement direction (1-right/0-left): ";
                cin >> direction;
                cout << "\n";
                cout << "                C-LOOK ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                output = clook(input_req.first, input_req.second.first, direction, input_req.second.second);
                cout << "\n";
                print_req_res(input_req, output.first, output.second);
                break;
            case 7:
                break;
            }
            break;
        case 6:
            read_input_mem(listPart, listProc);
            system("cls");
            int mem_algo_choice;
            cout << "Select the algorihtm" << endl;

            cout << " 1. First Fit" << endl;
            cout << " 2. Best Fit" << endl;
            cout << " 3. Worst Fit" << endl;
            cout << " 4. Back" << endl;
            cin >> mem_algo_choice;
            switch (mem_algo_choice)
            {
            case 1:
                cout << "                FIRST FIT ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                FirstFit(listPart, listProc);
                print_memory_results(listPart, listProc);
                break;
            case 2:
                cout << "                BEST FIT ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                BestFit(listPart, listProc);
                print_memory_results(listPart, listProc);
                break;
            case 3:
                cout << "                WORST FIT ALGORITHM                  " << endl;
                cout << "-------------------------------------------------------" << endl;
                WorstFit(listPart, listProc);
                print_memory_results(listPart, listProc);
                break;
            case 4:
                system("cls");
                break;
            }
            break;
        case 7:
            break;
        default:
            cout << "Invalid Choice! Enter valid option" << endl;
        }
    } while (choice != 7);
    return 0;
}