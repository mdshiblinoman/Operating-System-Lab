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

int calculatePages(int processSize, int pageSize)
{
    return (processSize + pageSize - 1) / pageSize;
}

int calculateFrames(int physicalMemorySize, int pageSize)
{
    return physicalMemorySize / pageSize;
}

int calculateInternalFragmentation(int processSize, int pages, int pageSize)
{
    return pages * pageSize - processSize;
}

int pagesLoadedInMemory(int pages, int frames)
{
    return (pages < frames) ? pages : frames;
}

void printPageTable(int totalPages, int totalFrames)
{
    int loadedPages = pagesLoadedInMemory(totalPages, totalFrames);

    cout << "\nPage Table (Loaded Pages)\n";
    cout << left << setw(10) << "Page" << setw(10) << "Frame" << "Status\n";

    for (int i = 0; i < totalPages; i++)
    {
        if (i < loadedPages)
        {
            cout << left << setw(10) << i << setw(10) << i << "In Memory\n";
        }
        else
        {
            cout << left << setw(10) << i << setw(10) << "-" << "On Disk\n";
        }
    }
}

void printSummary(int processSize, int physicalMemorySize, int pageSize)
{
    int totalPages = calculatePages(processSize, pageSize);
    int totalFrames = calculateFrames(physicalMemorySize, pageSize);
    int loadedPages = pagesLoadedInMemory(totalPages, totalFrames);
    int internalFragmentation = calculateInternalFragmentation(processSize, totalPages, pageSize);

    cout << "\nResult\n";
    cout << "Process Size: " << processSize << " bytes\n";
    cout << "Physical Memory Size: " << physicalMemorySize << " bytes\n";
    cout << "Page Size: " << pageSize << " bytes\n";
    cout << "Total Pages Needed: " << totalPages << "\n";
    cout << "Total Frames Available: " << totalFrames << "\n";
    cout << "Pages Loaded in Memory: " << loadedPages << "\n";
    cout << "Pages Remaining on Disk: " << totalPages - loadedPages << "\n";
    cout << "Internal Fragmentation: " << internalFragmentation << " bytes\n";
}

int main()
{
    cout << "Paging Technique Simulation\n";

    int processSize = readPositiveInt("Enter process size (in bytes): ");
    int physicalMemorySize = readPositiveInt("Enter physical memory size (in bytes): ");
    int pageSize = readPositiveInt("Enter page/frame size (in bytes): ");

    if (pageSize > physicalMemorySize)
    {
        cout << "\nPage size is larger than physical memory size.\n";
        return 0;
    }

    int totalPages = calculatePages(processSize, pageSize);
    int totalFrames = calculateFrames(physicalMemorySize, pageSize);

    if (totalFrames == 0)
    {
        cout << "\nNo frame can be created with given values.\n";
        return 0;
    }

    printSummary(processSize, physicalMemorySize, pageSize);
    printPageTable(totalPages, totalFrames);

    return 0;
}
