#include <id_generator.h>

#include <error_codes.h>

#include <stdio.h>

long long loadInitialId(const char* idCounterFilepath, ErrorCode* errorCode);
void saveId(const char* idCounterFilepath, const long long id, ErrorCode* errorCode);

long long GenerateNextId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    long long id = loadInitialId(idCounterFilepath, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return -1;
    }

    ++id;
    saveId(idCounterFilepath, id, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return -1;
    }

    return id;
}

long long loadInitialId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    FILE* idCounterFile = fopen(idCounterFilepath, "r");
    if (!idCounterFile)
    {
        return 0;
    }

    long long initialId;
    if (fscanf(idCounterFile, "%lld", &initialId) != 1)
    {
        if (errorCode) *errorCode = ERROR_FILE_STATE;
        return -1;
    }

    if (errorCode) *errorCode = NO_ERROR;
    fclose(idCounterFile);
    return initialId;
}

void saveId(const char* idCounterFilepath, const long long id, ErrorCode* errorCode)
{
    FILE* idCounterFile = fopen(idCounterFilepath, "w");
    if (!idCounterFile)
    {
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return;
    }

    if (fprintf(idCounterFile, "%lld\n", id) < 0)
    {
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return;
    }

    if (errorCode) *errorCode = NO_ERROR;
}