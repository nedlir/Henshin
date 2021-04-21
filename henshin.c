// Initial structure for the HENSHIN: file names changing cli tool.

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bool.h"
#include "boolflags.h"
#include "validation.h"

// #include "colors.h" (later...)

#define MAX_FILE_NAME_LENGTH 255 // in modern OS, this is the maximum file length
#define PARENT_DIRECTORY ".."
#define CURRENT_DIRECTORY "."

bool is_directory(char *_currentEntityName, struct stat _currentEntityType);

void parse_directory(struct dirent *_currentDirectory, DIR *_directory, boolflags _flags,
                     struct stat _currentEntityType, char *_expression);

// Functions:
void remove_prefix(char *_fileName, char *_expression);
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
    char *directoryPath = argv[1];           // syntactic sugar

    int chdir_result = chdir(directoryPath); // navigate to path
    validate_chdir(chdir_result);

    DIR *directory = opendir(CURRENT_DIRECTORY); // open current directory
    validate_opendir(directory);

    // Reads directory (basically this will provide us a pointer to first entity in the directory):
    struct dirent *currentDirectory = readdir(directory); // a pointer to directory's first entry
    validate_readdir(currentDirectory);

    struct stat currentEntityType; // this could be either a file or a folder

    flags.removePrefix = TRUE;
    parse_directory(currentDirectory, directory, flags, currentEntityType,
                    "annoyingsite.com - ");

    return EXIT_SUCCESS;
}

bool is_directory(char *_currentEntityName, struct stat _currentEntityType)
{
    // Determines if current entity is a directory:
    int stat_result = stat(_currentEntityName, &_currentEntityType);
    validate_stat(stat_result);

    if (S_ISDIR(_currentEntityType.st_mode))
        return TRUE;

    return FALSE;
}

void parse_directory(struct dirent *_currentDirectory, DIR *_directory, boolflags _flags,
                     struct stat _currentEntityType, char *_expression)
{
    while (_currentDirectory != NULL) // traverse directory if is not empty and exists
    {
        char *_currentEntityName = _currentDirectory->d_name; // syntactic sugar

        if (is_directory(_currentEntityName, _currentEntityType))
        {
            /*
            Parses subdirectories if recursive argument will be given:
            we will not traverse CURRENT_DIRECTORY and PARENT_DIRECTORY to avoid inifinite recursion
            This feature will be added last...
            
            if (_flags.isRecursive)
                if (strcmp(_currentEntityName, CURRENT_DIRECTORY) != 0 && strcmp(_currentEntityName, PARENT_DIRECTORY) != 0)
                    parse_subdirectory();
            */
        }
        else // entity is not a directory, perform file operations
        {

            if (_flags.removePrefix)
                remove_prefix(_currentEntityName, _expression);
            /*
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

    int closedir_result = closedir(_directory);
    validate_closedir(closedir_result);
}

char *string_duplicate(char *_origin)
{
    char *_destination;
    _destination = (char *)malloc(strlen(_origin) + 1);
    validate_malloc(_destination);
    strcpy(_destination, _origin);
    return _destination;
}

void remove_prefix(char *_fileName, char *_expression)
{

    /*
    // The idea of the algorithm is to simply compare the letters of the expression
    // with the target _fileName and to remove the length of the expression in case
    // a match is found.
    */

    if (strlen(_expression) >= strlen(_fileName)) //expression to remove can not exceed _fileName
        return;

    int i = 0; //counter to traverse _fileName
    int j = 0; //counter to traverse _expression

    bool _isExpressionFound = TRUE;

    while (_expression[j] != '\0')
    {
        if (_expression[j] == _fileName[i])
        {
            i++;
            j++;
        }
        else
        {
            _isExpressionFound = FALSE;
            break;
        }
    }

    if (_isExpressionFound)
    {
        char *_newFileName = string_duplicate(_fileName);

        printf("\nOriginal file name: %s", _newFileName);
        printf("\nNew file name: %s", (_newFileName + strlen(_expression)));
        //rename(_newFileName, (_newFileName + strlen(_expression)));

        free(_newFileName);
    }
}
