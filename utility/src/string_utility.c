#include <string_utility.h>

#include <ctype.h>

bool isWhitespaceOnly(const char* string)
{
    if (!string)
    {
        return false;
    }

    for (const char* ch = string; *ch != 0; ++ch)
    {
        if (!isspace(*ch))
        {
            return false;
        }
    }

    return true;
}
