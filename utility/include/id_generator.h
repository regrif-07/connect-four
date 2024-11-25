#pragma once

#include <error_codes.h>

extern const long long ID_START;
extern const long long ID_NOT_FOUND;

/// Generate next id with the counter specified by idCounterFilepath.
/// @param idCounterFilepath filepath of the id counter.
/// @param errorCode out error parameter. ERROR_FILE_STATE in case provided counter file has invalid contents
/// (not valid id), ERROR_FILE_IO in case file IO error occurred while trying to read/write to the counter file,
/// NO_ERROR otherwise.
/// @return 1 (first id) if the counter file did not exist, previous id (stored in counter file) + 1 otherwise.
/// @note id counter will be created if it was not found initially.
long long generateNextId(const char* idCounterFilepath, ErrorCode* errorCode);
