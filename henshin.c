// Initial structure for the HENSHIN: file names changing cli tool.

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "bool.h"
#include "boolflags.h"
// #include "colors.h" (later...)

#define MAX_FILE_NAME_LENGTH 255 // in modern OS, this is the maximum file length
#define PARENT_DIRECTORY ".."
#define CURRENT_DIRECTORY "."

bool is_directory(char *_currentEntityName, struct stat _currentEntityType);

void parse_directory(struct dirent *_currentDirectory, DIR *_directory, boolflags _flags,
                     struct stat _currentEntityType, char *_directoryPath);

// Functions:
void remove_prefix(char *_fileName);
void remove_suffix(char *_fileName);
void change_file_type(char *_fileName);
void zero_fill(char *_fileType);
void trim_spaces_left(char *_fileName);
void trim_spaces_right(char *_fileName);
void trim_spaces_all(char *_fileName);

int main(int argc, char *argv[])
{
    // Program's boolean helpers for flow control:
    boolflags flags;
    memset(&flags, FALSE, sizeof(flags));

    // Goes to the defined directory and opens it into 'directory' variable:
    char *directoryPath = argv[1];
    if ((chdir(directoryPath) == -1)) // if chdir() failed
    {
        fprintf(stderr, "Provided directory path could not be accessed.\n");
        exit(EXIT_FAILURE);
    }

    DIR *directory = opendir(CURRENT_DIRECTORY); // a pointer to directory's location
    if ((directory == NULL))                     // if opendir() failed
    {
        fprintf(stderr, "Provided directory could not be opened.\n");
        exit(EXIT_FAILURE);
    }

    // Reads directory (basically this will provide us a pointer to first entity in the directory):
    struct dirent *currentDirectory = readdir(directory); // a pointer to directory's first entry
    if ((currentDirectory == NULL))                       // if readdir() failed
    {
        fprintf(stderr, "Provided directory could not be read.\n");
        exit(EXIT_FAILURE);
    }

    struct stat currentEntityType; // this could be either a file or a folder

    parse_directory(currentDirectory, directory, flags, currentEntityType, directoryPath);

    return EXIT_SUCCESS;
}

bool is_directory(char *_currentEntityName, struct stat _currentEntityType)
{
    // Determines if current entity is a directory:
    if (stat(_currentEntityName, &_currentEntityType) == -1)
    {
        fprintf(stderr, "Entity access error\n");
        exit(EXIT_FAILURE);
    }
    if (S_ISDIR(_currentEntityType.st_mode))
        return TRUE;

    return FALSE;
}

void parse_directory(struct dirent *_currentDirectory, DIR *_directory, boolflags _flags,
                     struct stat _currentEntityType, char *_directoryPath)
{
    while (_currentDirectory != NULL) // traverse directory  if is not empty and exists
    {
        char *_currentEntityName = _currentDirectory->d_name; // syntactic sugar

        if (is_directory(_currentEntityName, _currentEntityType))
        {
            /*
            Parses subdirectories if recursive argument will be given:
            we will not traverse CURRENT_DIRECTORY and PARENT_DIRECTORY to avoid inifinite recursion
            This feature should be added last...
            
            if (_flags.isRecursive)
                if (strcmp(_currentEntityName, CURRENT_DIRECTORY) != 0 && strcmp(_currentEntityName, PARENT_DIRECTORY) != 0)
                    parse_subdirectory();
            */
        }
        else // entity is not a directory, perform file operations
        {
            /*
            if (_flags.removePrefix)
                remove_prefix(fileName);
            if (_flags.removeSuffix)
                remove_suffix(fileName);
            .
            .
            .
            if (_flags.trimSpacesALL)
                    trim_spaces_all(_fileName);
            */
        }

        // Goes to next entity:
        _currentDirectory = readdir(_directory);
    }

    if (closedir(_directory) != 0) // if closedir() failed
    {
        fprintf(stderr, "Directory closing failed.\n");
        exit(EXIT_FAILURE);
    }
}