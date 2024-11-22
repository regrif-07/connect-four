#include <id_generator.h>

#include <error_codes.h>

#include <stdio.h>

/// Load previous id from the counter file or return initial id - 1 (because it will be incremented afterward).
/// @param idCounterFilepath filepath of the id counter.
/// @param errorCode output error parameter; ERROR_FILE_STATE in case there was an invalid id in the counter file,
/// NO_ERROR otherwise.
/// @return 0 in case no counter file was found, previous index from counter file otherwise.
long long loadPreviousId(const char* idCounterFilepath, ErrorCode* errorCode);

/// Save the specified id to the counter file.
/// @param idCounterFilepath filepath of the id counter.
/// @param id id to save.
/// @param errorCode out error parameter; ERROR_FILE_IO in case file IO operation (open file/write to file) failed,
/// NO_ERROR otherwise.
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