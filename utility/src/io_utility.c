#include <io_utility.h>

#include <error_codes.h>

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_utility.h>

constexpr int IO_BUFFER_SIZE = 4096;

bool readAndScanInteger(int* out)
{
    static char lineBuffer[IO_BUFFER_SIZE]; // our buffer that will persist between function calls
    int chars = 0; // number of characters read
    if (!fgets(lineBuffer, sizeof(lineBuffer), stdin) || // read a line to the buffer
        sscanf(lineBuffer, " %d %n", out, &chars) != 1 || // try to parse an integer out of our buffer
        lineBuffer[chars] != 0) // discard input with extra characters
    {
        return false;
    }

    return true;
}

int loopReadInteger(const char* prompt)
{
    while (true)
    {
        printf("%s", prompt);

        int userInteger;
        if (readAndScanInteger(&userInteger))
        {
            return userInteger;
        }

        printf("Inlaid input. Try again.\n");
    }
}

int loopReadIntegerInRange(const char* prompt, const int min, const int max)
{
    assert(min <= max && "Invalid range");

    while (true)
    {
        const int userInteger = loopReadInteger(prompt);
        if (userInteger < min || userInteger > max)
        {
            printf("Your integer is out of range (%d, %d). Try again.\n", min, max);
            continue;
        }

        return userInteger;
    }
}

char* readLine(const char* prompt, const bool discardEmpty, ErrorCode* errorCode)
{
    static char lineBuffer[IO_BUFFER_SIZE];

    while (true)
    {
        printf("%s", prompt);

        if (fgets(lineBuffer, sizeof(lineBuffer), stdin) == nullptr)
        {
            printf("Unexpected error occurred.");
            continue;
        }

        size_t lineLen = strlen(lineBuffer);
        if (lineLen == 1 && lineBuffer[0] == '\n' && discardEmpty)
        {
            printf("Empty input is not supported.\n");
            continue;
        }
        if (discardEmpty && isWhitespaceOnly(lineBuffer))
        {
            printf("Empty input (whitespace-only) is not supported.\n");
            continue;
        }

        if (lineBuffer[lineLen - 1] == '\n')
        {
            lineBuffer[lineLen-- - 1] = '\0'; // remove the newline character at the end
        }

        char* line = calloc(sizeof(char), lineLen + 1);
        if (!line)
        {
            *errorCode = ERROR_MEMORY;
            return nullptr;
        }
        strcpy(line, lineBuffer);

        if (errorCode) *errorCode = NO_ERROR;
        return line;
    }
}