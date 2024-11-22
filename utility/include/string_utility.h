#pragma once

/// Define a new to-string conversion function for TYPE.
/// snprintf()-based conversion.
/// @param TYPE type of value that will be converted to string
/// @param TYPE_NAME name of type that will be used in the function name generation.
/// @param FORMAT_SPECIFIER format specifier for the provided TYPE (%d for int, for example).
/// Will be used in snprintf().
#define DEFINE_TO_STRING_CONVERSION_FUNCTION(TYPE, TYPE_NAME, FORMAT_SPECIFIER)       \
    char* TYPE_NAME##ToString(TYPE value, int* outStringLength, ErrorCode* errorCode) \
    {                                                                                 \
        const int stringLength = snprintf(nullptr, 0, FORMAT_SPECIFIER, value);       \
        char* string = malloc(sizeof(char) * stringLength + 1);                       \
        if (!string)                                                                  \
        {                                                                             \
            if (errorCode) *errorCode = ERROR_MEMORY;                                 \
            return nullptr;                                                           \
        }                                                                             \
                                                                                      \
        sprintf(string, FORMAT_SPECIFIER, value);                                     \
                                                                                      \
        if (outStringLength) *outStringLength = stringLength;                         \
        if (errorCode) *errorCode = NO_ERROR;                                         \
        return string;                                                                \
    }                                                                                 \

/// Check if the specified string is whitespace only.
/// @param string string to check.
/// @return true in case any non-whitespace character was found; false otherwise.
bool isWhitespaceOnly(const char* string);