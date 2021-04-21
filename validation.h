#ifndef VALIDATION_H
#define VALIDATION_H

void validate_opendir(DIR *_result);
void validate_readdir(struct dirent *_result);
void validate_chdir(int _result);
void validate_closedir(int _result);
void validate_malloc(void *_result);

#endif /* VALIDATION_H */