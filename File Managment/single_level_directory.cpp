#include <bits/stdc++.h>
using namespace std;

bool isFilePresent(const vector<string> &files, const string &fileName)
{
    for (const string &file : files)
    {
        if (file == fileName)
        {
            return true;
        }
    }
    return false;
}

void createFile(vector<string> &files)
{
    if (files.size() >= 100)
    {
        cout << "Directory is full. Cannot create more files.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to create: ";
    cin >> fileName;

    if (isFilePresent(files, fileName))
    {
        cout << "File already exists.\n";
        return;
    }

    files.push_back(fileName);
    cout << "File created successfully.\n";
}

void deleteFile(vector<string> &files)
{
    if (files.empty())
    {
        cout << "Directory is empty.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to delete: ";
    cin >> fileName;

    for (size_t i = 0; i < files.size(); ++i)
    {
        if (files[i] == fileName)
        {
            files.erase(files.begin() + static_cast<long>(i));
            cout << "File deleted successfully.\n";
            return;
        }
    }

    cout << "File not found.\n";
}

void searchFile(const vector<string> &files)
{
    if (files.empty())
    {
        cout << "Directory is empty.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to search: ";
    cin >> fileName;

    if (isFilePresent(files, fileName))
    {
        cout << "File found.\n";
    }
    else
    {
        cout << "File not found.\n";
    }
}

void displayFiles(const vector<string> &files)
{
    if (files.empty())
    {
        cout << "Directory is empty.\n";
        return;
    }

    cout << "Files in single-level directory:\n";
    for (size_t i = 0; i < files.size(); ++i)
    {
        cout << i + 1 << ". " << files[i] << "\n";
    }
}

void showMenu()
{
    cout << "\nSingle Level Directory Operations\n";
    cout << "1. Create File\n";
    cout << "2. Delete File\n";
    cout << "3. Search File\n";
    cout << "4. Display Files\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    vector<string> files;
    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 5.\n";
            continue;
        }

        if (choice == 1)
        {
            createFile(files);
        }
        else if (choice == 2)
        {
            deleteFile(files);
        }
        else if (choice == 3)
        {
            searchFile(files);
        }
        else if (choice == 4)
        {
            displayFiles(files);
        }
        else if (choice == 5)
        {
            cout << "Exiting program.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 5.\n";
        }
    }

    return 0;
}
