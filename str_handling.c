#include <string.h>
#include <stdlib.h> //malloc
#include <stdio.h>  //ONLY FOR TESTING

#include "validation.h"

char *str_duplicate(char *origin)
{
    /*
    returns a duplicate of a str which was allocated in memory.
    the returned value must be freed later on!
    */
    char *destination;
    destination = malloc(strlen(origin) + 1);
    validate_malloc(destination);
    strcpy(destination, origin);
    return destination;
}

char *strrstr(char *_str, char *_substr)
{
    /*
    returns a pointer to first occurrence of of "_needle" str from the end of "_origin" str
    basically, this function works in the same way like strrchr(), but for str
    */

    char *currentStr = NULL;
    char *nextStr = NULL;

    nextStr = strstr(_str, _substr);
    currentStr = nextStr;

    if (nextStr == NULL) // no occurrence of substr found
        return NULL;

    while (nextStr != NULL)
    {
        nextStr = nextStr + strlen(_substr); // trim substr from begining of nextStr
        nextStr = strstr(nextStr, _substr);  // finds next occurrence of _substr

        if (nextStr == NULL)
            break;

        currentStr = nextStr;
    }

    return currentStr;
}
