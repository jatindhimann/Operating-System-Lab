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
        frames.clear();
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
        frames.clear();
    }

    void LFU(vector<int> &reference_string, int num_of_frames)
    {

        int misses = 0;
        int hits = 0;

        vector<int> frames(num_of_frames, INT_MAX);
        vector<int> counts(num_of_frames, INT_MIN);

        cout << endl;

        for (int i = 0; i < reference_string.size(); i++)
        {
            int idx = search(frames, 0, reference_string[i]);

            if (idx == INT_MAX)
            {
                frames.erase(frames.begin() + minValueIndex(counts));
                counts.erase(counts.begin() + minValueIndex(counts));
                frames.push_back(reference_string[i]);
                counts.push_back(0);
                misses++;
            }
            else
            {
                counts[idx] = counts[idx] + 1;
                hits++;
            }
            print_frame(frames, reference_string[i]);
        }

        print_statistics_faults(misses, hits);
        frames.clear();
        counts.clear();
    }

    void MFU(vector<int> &reference_string, int num_of_frames)
    {
        int misses = 0;
        int hits = 0;

        vector<int> frames(num_of_frames, INT_MAX);
        vector<int> counts(num_of_frames, INT_MAX);

        cout << endl;

        for (int i = 0; i < reference_string.size(); i++)
        {
            int idx = search(frames, 0, reference_string[i]);

            if (idx == INT_MAX)
            {
                frames.erase(frames.begin() + maxValueIndex(counts));
                counts.erase(counts.begin() + maxValueIndex(counts));
                frames.push_back(reference_string[i]);
                counts.push_back(0);
                misses++;
            }
            else
            {
                counts[idx] = counts[idx] + 1;
                hits++;
            }

            print_frame(frames, reference_string[i]);
        }

        print_statistics_faults(misses, hits);
        frames.clear();
        counts.clear();
    }

    void OPT(vector<int> &reference_string, int num_of_frames)
    {

        int misses = 0;
        int hits = 0;

        vector<int> frames(num_of_frames, INT_MAX);
        vector<int> indices(num_of_frames, INT_MAX);

        cout << endl;
        for (int i = 0; i < reference_string.size(); i++)
        {
            int idx = search(frames, 0, reference_string[i]);

            if (idx == INT_MAX)
            {
                frames.erase(frames.begin() + maxValueIndex(indices));
                indices.erase(indices.begin() + maxValueIndex(indices));
                frames.push_back(reference_string[i]);
                indices.push_back(search(reference_string, i + 1, reference_string[i]));
                misses++;
            }
            else
            {
                indices[idx] = search(reference_string, i + 1, reference_string[i]);
                hits++;
            }
            print_frame(frames, reference_string[i]);
        }

        print_statistics_faults(misses, hits);
        frames.clear();
        indices.clear();
    }
};