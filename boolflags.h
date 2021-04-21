#ifndef BOOLFLAGS_H
#define BOOLFLAGS_H

typedef struct boolean_flags
{
    bool removePrefix;
    bool removeSuffix;
    bool changeFilename;
    bool changeFiletype;
    bool zeroFill;
    bool trimSpacesLeft;
    bool trimSpacesRight;
    bool trimSpacesALL;
    bool isRecursive;
} boolflags;

#endif /* BOOLFLAGS_H */