#pragma once
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <iomanip>
using namespace std;

pair<vector<int>,int > read_input_page_algo(vector<int> &reference_string, int no_of_frames)
{
    int length;
    int choice;

    cout << "Do you want to enter new reference string(0/1) ";
    cin >> choice;
    if (choice)
    {
        cout << "Please enter the length of refernce string: ";
        cin >> length;
        fstream outputFile("Page_Replacement_algorithms/Page_reference.txt", ios::out);

        cout << "Enter Reference string: " << endl;
        for (int i = 0; i < length; i++)
        {
            int temp;
            cin >> temp;
            outputFile << temp << " ";
        }
        outputFile.close();
    }
    fstream inputFile("Page_Replacement_algorithms/Page_reference.txt", ios::in);

    while (!inputFile.eof())
    {
        int temp;
        inputFile >> temp;

        if (!inputFile.fail())
        {
            reference_string.push_back(temp);
        }
    }
    inputFile.close();

    cout << "Please enter the number of frames: ";
    cin >> no_of_frames;
    cout << endl;

    return {reference_string,no_of_frames};
}

void print(vector<int> &arr)
{

    cout << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int maxValueIndex(vector<int> &v) {
	
	int max_val = INT_MIN;
	int max_idx;
	for( int i = 0; i < v.size(); i++ ) {
		if( v[i] > max_val ) {
			max_val = v[i];
			max_idx = i;
		}
	}
	return max_idx;
}

int minValueIndex(vector<int> &v) {
	
	int min_val = INT_MAX;
	int min_idx;
	for ( int i = 0; i < v.size(); i++ ) {
		if (v[i] < min_val) {
			min_val = v[i];
			min_idx = i;
		}
	}
	return min_idx;
}

int search(vector<int> &v, int idx, int value) {
	
	for(int i = idx; i < v.size(); i++) {
		if( v[i] == value ) {
			return i;
		}
	}
	return INT_MAX;
}

void print_frame(vector<int> &frames, int page) {
	
	cout <<page << " : ";
	for ( int i = 0; i < frames.size(); i++ ) {
		if (frames[i] == INT_MAX ) {
			cout << "* ";
		}
		else {
			cout << frames[i] << " ";
		}
	}
	cout << endl;
}

void print_statistics_faults(int &misses, int &hits)
{
    cout << "--------------------------------------" << endl;
    cout << "Page faults: " << misses << endl;
    cout << "Page hits: " << hits << endl;
    cout << "Hit Percentage: " << (1.0 * hits / (hits + misses)) * 100 << "%" << endl;
    cout << "--------------------------------------" << endl;
}