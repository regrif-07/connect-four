#pragma once

#define DEFINE_TO_STRING_CONVERSION_FUNCTION(TYPE, TYPE_NAME, FORMAT_SPECIFIER) \
    char* TYPE_NAME##ToString(TYPE value, ErrorCode* errorCode)                 \
    {                                                                           \
        const int stringLength = sprintf(nullptr, FORMAT_SPECIFIER, value);     \
        char* string = malloc(sizeof(char) * stringLength + 1);                 \
        if (!string)                                                            \
        {                                                                       \
            if (errorCode) *errorCode = ERROR_MEMORY;                           \
            return nullptr;                                                     \
        }                                                                       \
                                                                                \
        sprintf(string, FORMAT_SPECIFIER, value);                               \
        return string;                                                          \
    }                                                                           \

/// Check if the specified string is whitespace only.
/// @param string string to check.
/// @return true in case any non-whitespace character was found; false otherwise.
bool isWhitespaceOnly(const char* string);