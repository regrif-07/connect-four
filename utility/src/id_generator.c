#include <id_generator.h>

#include <error_codes.h>

#include <stdio.h>

long long loadPreviousId(const char* idCounterFilepath, ErrorCode* errorCode);
void saveId(const char* idCounterFilepath, const long long id, ErrorCode* errorCode);

long long generateNextId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    long long id = loadPreviousId(idCounterFilepath, errorCode);
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

    if (errorCode) *errorCode = NO_ERROR;
    return id;
}

long long loadPreviousId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    FILE* idCounterFile = fopen(idCounterFilepath, "r");
    if (!idCounterFile)
    {
        if (errorCode) *errorCode = NO_ERROR;
        return 0;
    }

    long long previousId;
    if (fscanf(idCounterFile, "%lld", &previousId) != 1)
    {
        fclose(idCounterFile);
        if (errorCode) *errorCode = ERROR_FILE_STATE;
        return -1;
    }

    if (errorCode) *errorCode = NO_ERROR;
    fclose(idCounterFile);
    return previousId;
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
        fclose(idCounterFile);
        if (errorCode) *errorCode = ERROR_FILE_IO;
        return;
    }

    fclose(idCounterFile);
    if (errorCode) *errorCode = NO_ERROR;
}