#include <iostream>
#include "Scheduling_Algorithms\CPU_Scheduling_algorithms.h"
#include "Scheduling_Algorithms\PCB.h"
#include "Scheduling_Algorithms\helper.h"
#include "Page_Replacement_algorithms\Page_replace_algo.h"
#include <cstdlib> // clrcsr
#include <vector>
#include "Page_Replacement_algorithms\helper.h"
#include "Memory_Management\memoryalgorithm.h"

using namespace std;

CPU_Scheduling_algos algo;
vector<PCB> process_list;

Page_replace_algo pg_replace;
vector<int> reference_string;
int no_of_frames;
pair<vector<int>, int> input;

int numOfPart, numOfProc;
pair<int, int> num;
pair<Partition *, process *> list;

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
        pair<int, vector<PCB>> result;
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
                    break;
                case 3:
                    pg_replace.LRU(input.first, input.second);
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    system("cls");
                    break;
                }
            } while (pg_algo_choice != 6);
            break;
        case 5:
            break;
        case 6:
            system("cls");
            num = read_num(numOfPart, numOfProc);
            list = read_input_mem(num.first, num.second);
            system("cls");
            int mem_algo_choice;
            cout<<"Select the algorihtm"<<endl;
            do
            {
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
                    FirstFit(list.first, num.first, list.second, num.second);
                    print_memory_results(list.first, num.first, list.second, num.second);
                    break;
                case 2:
                    cout << "                BEST FIT ALGORITHM                  " << endl;
                    cout << "-------------------------------------------------------" << endl;
                    BestFit(list.first, num.first, list.second, num.second);
                    print_memory_results(list.first, num.first, list.second, num.second);
                    break;
                case 3:
                    cout << "                WORST FIT ALGORITHM                  " << endl;
                    cout << "-------------------------------------------------------" << endl;
                    WorstFit(list.first, num.first, list.second, num.second);
                    print_memory_results(list.first, num.first, list.second, num.second);
                    break;
                case 4:
                    system("cls");
                    break;
                }
            } while (mem_algo_choice != 6);
            break;
        case 7:
            break;
        default:
            cout << "Invalid Choice! Enter valid option" << endl;
        }
    } while (choice != 7);
    return 0;
}