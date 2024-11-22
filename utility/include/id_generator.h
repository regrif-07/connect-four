#pragma once

#include <error_codes.h>

long long GenerateNextId(const char* idCounterFilepath, ErrorCode* errorCode);
