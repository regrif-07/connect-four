#include <id_generator.h>

#include <error_codes.h>

#include <stdio.h>

const long long ID_START = 1;
const long long ID_NOT_FOUND = -1;

/// Save the specified id to the counter file.
/// @param idCounterFilepath filepath of the id counter.
/// @param id id to save.
/// @param errorCode out error parameter; ERROR_FILE_IO in case file IO operation (open file/write to file) failed,
/// NO_ERROR otherwise.
void saveId(const char* idCounterFilepath, const long long id, ErrorCode* errorCode);


long long loadPreviousId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    FILE* idCounterFile = fopen(idCounterFilepath, "r");
    if (!idCounterFile)
    {
        if (errorCode) *errorCode = NO_ERROR;
        return ID_START - 1;
    }

    long long previousId;
    if (fscanf(idCounterFile, "%lld", &previousId) != 1)
    {
        fclose(idCounterFile);
        if (errorCode) *errorCode = ERROR_FILE_STATE;
        return ID_NOT_FOUND;
    }

    fclose(idCounterFile);
    if (errorCode) *errorCode = NO_ERROR;
    return previousId;
}

long long generateNextId(const char* idCounterFilepath, ErrorCode* errorCode)
{
    long long id = loadPreviousId(idCounterFilepath, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return ID_NOT_FOUND;
    }

    ++id;
    saveId(idCounterFilepath, id, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return ID_NOT_FOUND;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return id;
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