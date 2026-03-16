#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isUserPresent(const map<string, vector<string>> &directory, const string &userName)
{
    return directory.find(userName) != directory.end();
}

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

void createUserDirectory(map<string, vector<string>> &directory)
{
    string userName;
    cout << "Enter user name: ";
    cin >> userName;

    if (isUserPresent(directory, userName))
    {
        cout << "User directory already exists.\n";
        return;
    }

    directory[userName] = {};
    cout << "User directory created successfully.\n";
}

void createFile(map<string, vector<string>> &directory)
{
    string userName;
    cout << "Enter user name: ";
    cin >> userName;

    if (!isUserPresent(directory, userName))
    {
        cout << "User directory not found.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to create: ";
    cin >> fileName;

    if (isFilePresent(directory[userName], fileName))
    {
        cout << "File already exists for this user.\n";
        return;
    }

    directory[userName].push_back(fileName);
    cout << "File created successfully.\n";
}

void deleteFile(map<string, vector<string>> &directory)
{
    string userName;
    cout << "Enter user name: ";
    cin >> userName;

    if (!isUserPresent(directory, userName))
    {
        cout << "User directory not found.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to delete: ";
    cin >> fileName;

    vector<string> &files = directory[userName];
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (files[i] == fileName)
        {
            files.erase(files.begin() + static_cast<long>(i));
            cout << "File deleted successfully.\n";
            return;
        }
    }

    cout << "File not found for this user.\n";
}

void searchFile(const map<string, vector<string>> &directory)
{
    string userName;
    cout << "Enter user name: ";
    cin >> userName;

    auto userIt = directory.find(userName);
    if (userIt == directory.end())
    {
        cout << "User directory not found.\n";
        return;
    }

    string fileName;
    cout << "Enter file name to search: ";
    cin >> fileName;

    if (isFilePresent(userIt->second, fileName))
    {
        cout << "File found.\n";
    }
    else
    {
        cout << "File not found for this user.\n";
    }
}

void displayAll(const map<string, vector<string>> &directory)
{
    if (directory.empty())
    {
        cout << "No user directories available.\n";
        return;
    }

    cout << "Two Level Directory Structure:\n";
    for (const auto &userEntry : directory)
    {
        cout << "User: " << userEntry.first << "\n";
        if (userEntry.second.empty())
        {
            cout << "  No files\n";
        }
        else
        {
            for (size_t i = 0; i < userEntry.second.size(); ++i)
            {
                cout << "  " << i + 1 << ". " << userEntry.second[i] << "\n";
            }
        }
    }
}

void showMenu()
{
    cout << "\nTwo Level Directory Operations\n";
    cout << "1. Create User Directory\n";
    cout << "2. Create File\n";
    cout << "3. Delete File\n";
    cout << "4. Search File\n";
    cout << "5. Display All\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    map<string, vector<string>> directory;
    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 6.\n";
            continue;
        }

        if (choice == 1)
        {
            createUserDirectory(directory);
        }
        else if (choice == 2)
        {
            createFile(directory);
        }
        else if (choice == 3)
        {
            deleteFile(directory);
        }
        else if (choice == 4)
        {
            searchFile(directory);
        }
        else if (choice == 5)
        {
            displayAll(directory);
        }
        else if (choice == 6)
        {
            cout << "Exiting program.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }
    }

    return 0;
}
