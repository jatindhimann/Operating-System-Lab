#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "PCB.h"
using namespace std;

void sort_arrival_time_then_id(vector<PCB> &process_list)
{
    sort(process_list.begin(), process_list.end(), [](PCB a, PCB b)
         {
        if(a.arrival_time != b.arrival_time){
            return a.arrival_time <= b.arrival_time;
        }

        return a.process_id <= b.process_id; });
}

void sort_on_sjf(deque<PCB> &process_list, int &time)
{
    sort(process_list.begin(), process_list.end(), [time](PCB a, PCB b)
         {
        if(a.arrival_time <= time && b.arrival_time<=time){
            return a.burst_time <= b.burst_time;
        }else if(a.arrival_time <= time){
            return true;
        }else if(b.arrival_time <= time){
            return false;
        }else{
            return a.process_id <= b.process_id;
        } });
}

// keeping scheme of lower the number higher the priority
void sort_priority(deque<PCB> &process_list, int &time)
{
    sort(process_list.begin(), process_list.end(), [time](PCB a, PCB b)
         {
        if(a.arrival_time <= time && b.arrival_time<=time){
            return a.priority <= b.priority;
        }else if(a.arrival_time <= time){
            return true;
        }else if(b.arrival_time <= time){
            return false;
        }else{
            return a.process_id <= b.process_id;
        } });
}

