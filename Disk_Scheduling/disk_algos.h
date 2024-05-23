#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <limits.h>
#include "helper.h"
using namespace std;

pair<int, vector<int>> fcfs(vector<pair<int, bool>> requests, int initialPosition)
{
    vector<int> seekSequence;
    int distance = 0;

    for (int i = 0; i < requests.size(); i++)
    {
        int d = abs(initialPosition - requests[i].first);
        initialPosition = requests[i].first;
        distance += d;
        requests[i].second = true;
        seekSequence.push_back(requests[i].first);
    }

    return {distance, seekSequence};
}

pair<int, vector<int>> sstf(vector<pair<int, bool>> requests, int initialPosition)
{
    vector<int> seekSequence;
    int distance = 0;

    int pos = initialPosition;
    while (!requests.empty())
    {
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < requests.size(); i++)
        {
            int d = abs(pos - requests[i].first);
            if (d < minDist)
            {
                minDist = d;
                minIndex = i;
            }
        }

        pos = requests[minIndex].first;
        distance += minDist;

        seekSequence.push_back(requests[minIndex].first);

        requests.erase(requests.begin() + minIndex);
    }

    return {distance, seekSequence};
}

pair<int, vector<int>> scan(vector<pair<int, bool>> requests, int initialPosition, bool direction, int no_of_cylinders)
{
    sort(requests.begin(), requests.end());
    int distance = 0;
    vector<int> seekSequence;
    int pos = initialPosition;
    int idx = -1;
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i].first < initialPosition && requests[i + 1].first > initialPosition)
        {
            idx = i + 1;
            break;
        }
    }

    if (direction)
    {
        for (int i = idx; i < requests.size(); i++)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        distance += (no_of_cylinders - 1) - requests.back().first;
        pos = no_of_cylinders - 1;
        for (int i = requests.size() - 1; i >= 0; i--)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }
    else
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        distance += requests.front().first;
        pos = 0;

        for (int i = 0; i < requests.size(); i++)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }

    return {distance, seekSequence};
}

pair<int, vector<int>> cscan(vector<pair<int, bool>> requests, int initialPosition, bool direction, int no_of_cylinders)
{
    sort(requests.begin(), requests.end());
    int distance = 0;
    vector<int> seekSequence;
    int pos = initialPosition;
    int idx = -1;
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i].first < initialPosition && requests[i + 1].first > initialPosition)
        {
            idx = i + 1;
            break;
        }
    }

    if (direction)
    {
        for (int i = idx; i < requests.size(); i++)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        distance += (no_of_cylinders - 1) - requests.back().first;
        pos = 0;
        distance += (no_of_cylinders - 1);
        for (int i = 0; i < requests.size(); i++)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }
    else
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        distance += requests.front().first;
        distance += (no_of_cylinders - 1);
        pos = (no_of_cylinders - 1);

        for (int i = requests.size() - 1; i >= 0; i--)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }

    return {distance, seekSequence};
}

pair<int, vector<int>> look(vector<pair<int, bool>> requests, int initialPosition, bool direction, int no_of_cylinders)
{
    sort(requests.begin(), requests.end());
    int distance = 0;
    vector<int> seekSequence;
    int pos = initialPosition;
    int idx = -1;
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i].first < initialPosition && requests[i + 1].first > initialPosition)
        {
            idx = i + 1;
            break;
        }
    }

    if (direction)
    {
        for (int i = idx; i < requests.size(); i++)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        pos = requests.back().first;
        for (int i = requests.size() - 1; i >= 0; i--)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }
    else
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        pos = requests.front().first;
        for (int i = 0; i < requests.size(); i++)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }

    return {distance, seekSequence};
}

pair<int, vector<int>> clook(vector<pair<int, bool>> requests, int initialPosition, bool direction, int no_of_cylinders)
{
    sort(requests.begin(), requests.end());
    int distance = 0;
    int pos = initialPosition;
    vector<int> seekSequence;
    int idx = -1;
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i].first < initialPosition && requests[i + 1].first > initialPosition)
        {
            idx = i + 1;
            break;
        }
    }

    if (direction)
    {
        for (int i = idx; i < requests.size(); i++)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        pos = requests.front().first;
        distance += (requests.back().first - requests.front().first);
        for (int i = 0; i < requests.size(); i++)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }
    else
    {
        for (int i = idx - 1; i >= 0; i--)
        {
            int d = abs(pos - requests[i].first);
            pos = requests[i].first;
            distance += d;
            requests[i].second = true;
            seekSequence.push_back(requests[i].first);
        }
        pos = requests.back().first;
        distance += (requests.back().first - requests.front().first);

        for (int i = requests.size() - 1; i >= 0; i--)
        {
            if (!requests[i].second)
            {
                int d = abs(pos - requests[i].first);
                pos = requests[i].first;
                distance += d;
                requests[i].second = true;
                seekSequence.push_back(requests[i].first);
            }
        }
    }

    return {distance, seekSequence};
}