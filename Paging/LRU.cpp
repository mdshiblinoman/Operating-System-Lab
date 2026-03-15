#include <bits/stdc++.h>
using namespace std;

int readPositiveInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (!cin.fail() && value > 0)
        {
            return value;
        }

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a positive integer.\n";
    }
}

vector<int> readReferenceString(int totalReferences)
{
    vector<int> pages(totalReferences);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < totalReferences; i++)
    {
        cin >> pages[i];
    }
    return pages;
}

int findPageIndex(const vector<int> &frames, int page)
{
    for (int i = 0; i < static_cast<int>(frames.size()); i++)
    {
        if (frames[i] == page)
        {
            return i;
        }
    }
    return -1;
}

int getLeastRecentlyUsedIndex(const vector<int> &lastUsed)
{
    int index = 0;
    for (int i = 1; i < static_cast<int>(lastUsed.size()); i++)
    {
        if (lastUsed[i] < lastUsed[index])
        {
            index = i;
        }
    }
    return index;
}

void printFrames(const vector<int> &frames)
{
    for (int value : frames)
    {
        if (value == -1)
        {
            cout << setw(4) << "-";
        }
        else
        {
            cout << setw(4) << value;
        }
    }
}

void simulateLRU(const vector<int> &referenceString, int frameCount)
{
    vector<int> frames(frameCount, -1);
    vector<int> lastUsed(frameCount, -1);
    int pageHits = 0;
    int pageFaults = 0;

    cout << "\nLRU Page Replacement\n";
    cout << left << setw(10) << "Page" << setw(25) << "Frames" << "Result\n";

    for (int time = 0; time < static_cast<int>(referenceString.size()); time++)
    {
        int page = referenceString[time];
        int pageIndex = findPageIndex(frames, page);
        bool isHit = (pageIndex != -1);

        if (isHit)
        {
            pageHits++;
            lastUsed[pageIndex] = time;
        }
        else
        {
            pageFaults++;

            int emptyIndex = findPageIndex(frames, -1);
            if (emptyIndex != -1)
            {
                frames[emptyIndex] = page;
                lastUsed[emptyIndex] = time;
            }
            else
            {
                int lruIndex = getLeastRecentlyUsedIndex(lastUsed);
                frames[lruIndex] = page;
                lastUsed[lruIndex] = time;
            }
        }

        cout << left << setw(10) << page;
        printFrames(frames);
        cout << "   " << (isHit ? "Hit" : "Fault") << "\n";
    }

    cout << "\nTotal Page Hits: " << pageHits << "\n";
    cout << "Total Page Faults: " << pageFaults << "\n";
}

int main()
{
    cout << "LRU Page Replacement Simulation\n";

    int totalReferences = readPositiveInt("Enter number of page references: ");
    vector<int> referenceString = readReferenceString(totalReferences);
    int frameCount = readPositiveInt("Enter number of frames: ");

    simulateLRU(referenceString, frameCount);

    return 0;
}
