#pragma once

/// represent a state/result of operation (e.g. function execution).
typedef enum
{
    NO_ERROR = 0,
    ERROR_GENERAL = -1,
    ERROR_INVALID_ARGUMENT = -2,
    ERROR_ARGUMENT_OUT_OF_RANGE = -3,
    ERROR_NULLPTR_ARGUMENT = -4,
    ERROR_MEMORY = -5,
    ERROR_FILE_STATE = -6,
    ERROR_FILE_IO = -7,
} ErrorCode;