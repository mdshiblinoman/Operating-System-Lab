/*
Question 12 — LRU Page Replacement
Implement the Least Recently Used (LRU) page replacement algorithm.
Display:
    frame status after each page reference
    total page faults
*/

#include <bits/stdc++.h>
using namespace std;

void printFrames(const vector<int> &frames)
{
    cout << "Frames: ";
    for (size_t i = 0; i < frames.size(); i++)
    {
        if (frames[i] == -1)
        {
            cout << "- ";
        }
        else
        {
            cout << frames[i] << " ";
        }
    }
    cout << "\n";
}

int main()
{
    int n, f;

    cout << "Enter number of pages in reference string: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> f;

    vector<int> frames(f, -1);
    vector<int> last_used(f, -1);
    int hit = 0;
    int fault = 0;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        bool found = false;

        for (int j = 0; j < f; j++)
        {
            if (frames[j] == page)
            {
                found = true;
                hit++;
                last_used[j] = i;
                break;
            }
        }

        if (!found)
        {
            fault++;
            int pos = -1;

            for (int j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
            {
                pos = 0;
                for (int j = 1; j < f; j++)
                {
                    if (last_used[j] < last_used[pos])
                    {
                        pos = j;
                    }
                }
            }

            frames[pos] = page;
            last_used[pos] = i;
        }

        cout << "After page " << page << ": ";
        printFrames(frames);
    }

    cout << "\nTotal Page Hits = " << hit << "\n";
    cout << "\nTotal Page Faults = " << fault << "\n";

    return 0;
}
