#include <io_utility.h>

#include <stdio.h>
#include <string.h>

constexpr int IO_BUFFER_SIZE = 4096;

// original solution https://www.reddit.com/r/cprogramming/comments/1aop62k/alternatives_to_scanf_for_reading_integers/
bool readAndScanInteger(int* out)
{
    static char line[IO_BUFFER_SIZE];
    int chars = 0;
    if (!fgets(line, sizeof(line), stdin) || sscanf(line, " %d %n", out, &chars) != 1 || line[chars] != 0)
    {
        return false;
    }

    return true;
}

// read and scan user input for integer until actual valid input is received; return the received integer value
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
    while (true)
    {
        const int userInteger = loopReadInteger(prompt);
        if (userInteger < min || userInteger > max)
        {
            printf("Your integer is out of range (%d-%d). Try again.", min, max);
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
            line[lineLen-- - 1] = '\0';
        }

        return line;
    }
}