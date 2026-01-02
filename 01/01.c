/*
To write a C program to perform various file operations like
create, write, read, delete, copy, move and list files in the
current directory with a specific extension (.txt).
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void listFiles()
{
    DIR *dir;
    struct dirent *entry;
    char *ext;

    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Failed to open directory!\n");
        return;
    }

    printf("\n===== .txt Files in current directory =====\n");
    while ((entry = readdir(dir)) != NULL)
    {
        ext = strrchr(entry->d_name, '.');
        if (ext != NULL && strcmp(ext, ".txt") == 0)
        {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    printf("============================================\n");
}

void createFile()
{
    FILE *fp;
    char filename[50];

    printf("Enter file name to create: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("File creation failed!\n");
        return;
    }

    fclose(fp);
    printf("File created successfully.\n");
}

void writeFile()
{
    FILE *fp;
    char filename[50], text[200];

    printf("Enter file name to write: ");
    scanf("%s", filename);
    getchar(); // clear buffer

    fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("File opening failed!\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    fputs(text, fp);

    fclose(fp);
    printf("Data written successfully.\n");
}

void readFile()
{
    FILE *fp;
    char filename[50], ch;

    printf("Enter file name to read: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\nFile content:\n");
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);
    printf("\n");
}

void deleteFile()
{
    char filename[50];

    printf("Enter file name to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        printf("File deletion failed!\n");
}

void copyFile()
{
    FILE *src, *dest;
    char srcFile[50], destFile[50], ch;

    printf("Enter source file name: ");
    scanf("%s", srcFile);
    printf("Enter destination file name: ");
    scanf("%s", destFile);

    src = fopen(srcFile, "r");
    dest = fopen(destFile, "w");

    if (src == NULL || dest == NULL)
    {
        printf("File copy failed!\n");
        return;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully.\n");
}

void moveFile()
{
    char oldName[50], newName[50];

    printf("Enter existing file name: ");
    scanf("%s", oldName);
    printf("Enter new file name: ");
    scanf("%s", newName);

    if (rename(oldName, newName) == 0)
        printf("File moved successfully.\n");
    else
        printf("File move failed!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n===== FILE OPERATIONS MENU =====\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Copy File\n");
        printf("6. Move File\n");
        printf("7. List Files\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createFile();
            break;
        case 2:
            writeFile();
            break;
        case 3:
            readFile();
            break;
        case 4:
            deleteFile();
            break;
        case 5:
            copyFile();
            break;
        case 6:
            moveFile();
            break;
        case 7:
            listFiles();
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
