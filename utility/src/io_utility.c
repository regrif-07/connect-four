#include <io_utility.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

constexpr int IO_BUFFER_SIZE = 4096;

bool readAndScanInteger(int* out)
{
    static char line[IO_BUFFER_SIZE]; // our buffer that will persist between function calls
    int chars = 0; // number of characters read
    if (!fgets(line, sizeof(line), stdin) || // read a line to the buffer
        sscanf(line, " %d %n", out, &chars) != 1 || // try to parse an integer out of our buffer
        line[chars] != 0) // discard input with extra characters
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

char* readLine(const char* prompt, const bool discardEmpty)
{
    while (true)
    {
        printf("%s", prompt);

        char* line = nullptr;
        size_t buffSize;
        if (getline(&line, &buffSize, stdin) < 0) // if getline() failed to read a line...
        {
            printf("Unexpected error occurred.");
            continue;
        }

        size_t lineLen = strlen(line);
        if (lineLen == 1 && line[0] == '\n' && discardEmpty)
        {
            printf("Empty input is not supported.\n");
            continue;
        }
        if (line[lineLen - 1] == '\n')
        {
            line[lineLen-- - 1] = '\0'; // remove the newline character at the end
        }

        return line;
    }
}