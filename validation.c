#include <dirent.h> // DIR*, dirent
#include <stdio.h> //fprintf
#include <stdlib.h> //malloc

void validate_opendir(DIR *_result)
{
    if ((_result == NULL)) // if opendir() failed
    {
        fprintf(stderr, "Provided directory could not be opened.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_readdir(struct dirent *_result)
{
    if ((_result == NULL)) // if readdir() failed
    {
        fprintf(stderr, "Provided directory could not be read.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_chdir(int _result)
{
    if (_result == -1) // if chdir() failed
    {
        fprintf(stderr, "Provided directory acces error.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_stat(int _result)
{
    if (_result == -1) // if stat() failed
    {
        fprintf(stderr, "Entity access error.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_closedir(int _result)
{
    if (_result != 0) // if closedir() failed
    {
        fprintf(stderr, "Directory closing failed.\n");
        exit(EXIT_FAILURE);
    }
}

void validate_malloc(void *_result)
{
    if (_result == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
}