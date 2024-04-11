#include <vector>
#include <limits.h>
#include "helper.h"

class Page_replace_algo
{
public:
    void FIFO(vector<int> &reference_string, int num_of_frames)
    {

        int misses = 0;
        int hits = 0;

        vector<int> frames(num_of_frames, INT_MAX);

        cout << endl;

        for (int i = 0; i < reference_string.size(); i++)
        {
            int idx = search(frames, 0, reference_string[i]);

            if (idx == INT_MAX)
            {
                frames.erase(frames.begin());
                frames.push_back(reference_string[i]);
                misses++;
            }
            else
            {
                hits++;
            }
            print_frame(frames, reference_string[i]);
        }

        print_statistics_faults(misses, hits);
    }

    void LRU(vector<int> &reference_string, int num_of_frames)
    {

        int misses = 0;
        int hits = 0;

        vector<int> frames(num_of_frames, INT_MAX);

        cout << endl;

        for (int i = 0; i < reference_string.size(); i++)
        {
            int idx = search(frames, 0, reference_string[i]);

            if (idx == INT_MAX)
            {
                frames.erase(frames.begin());
                frames.push_back(reference_string[i]);
                misses++;
            }
            else
            {
                int temp = frames[idx];
                frames.erase(frames.begin() + idx);
                frames.push_back(temp);
                hits++;
            }
            print_frame(frames, reference_string[i]);
        }

        print_statistics_faults(misses, hits);
    }
};