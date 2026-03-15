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

int getLFUIndex(const vector<int> &frequency, const vector<int> &arrivalOrder)
{
    int victim = 0;
    for (int i = 1; i < static_cast<int>(frequency.size()); i++)
    {
        if (frequency[i] < frequency[victim])
        {
            victim = i;
        }
        else if (frequency[i] == frequency[victim] && arrivalOrder[i] < arrivalOrder[victim])
        {
            victim = i;
        }
    }
    return victim;
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

void simulateLFU(const vector<int> &referenceString, int frameCount)
{
    vector<int> frames(frameCount, -1);
    vector<int> frequency(frameCount, 0);
    vector<int> arrivalOrder(frameCount, -1);

    int pageHits = 0;
    int pageFaults = 0;
    int orderCounter = 0;

    cout << "\nLFU Page Replacement\n";
    cout << left << setw(10) << "Page" << setw(25) << "Frames" << "Result\n";

    for (int page : referenceString)
    {
        int pageIndex = findPageIndex(frames, page);
        bool isHit = (pageIndex != -1);

        if (isHit)
        {
            pageHits++;
            frequency[pageIndex]++;
        }
        else
        {
            pageFaults++;

            int emptyIndex = findPageIndex(frames, -1);
            if (emptyIndex != -1)
            {
                frames[emptyIndex] = page;
                frequency[emptyIndex] = 1;
                arrivalOrder[emptyIndex] = orderCounter;
                orderCounter++;
            }
            else
            {
                int victim = getLFUIndex(frequency, arrivalOrder);
                frames[victim] = page;
                frequency[victim] = 1;
                arrivalOrder[victim] = orderCounter;
                orderCounter++;
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
    cout << "LFU Page Replacement Simulation\n";

    int totalReferences = readPositiveInt("Enter number of page references: ");
    vector<int> referenceString = readReferenceString(totalReferences);
    int frameCount = readPositiveInt("Enter number of frames: ");

    simulateLFU(referenceString, frameCount);

    return 0;
}
