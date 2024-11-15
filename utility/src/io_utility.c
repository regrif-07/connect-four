//
// Created by regrif07 on 11/7/24.
//

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

bool readAndScanLongLong(long long* out)
{
    static char line[IO_BUFFER_SIZE];
    int chars = 0;
    if (!fgets(line, sizeof(line), stdin) || sscanf(line, " %lld %n", out, &chars) != 1 || line[chars] != 0)
    {
        return false;
    }

    return true;
}

// read and scan user input for long long until actual valid input is received; return the received integer value
long long loopReadLongLong(const char* prompt)
{
    while (true)
    {
        printf("%s", prompt);

        long long userLongLong;
        if (readAndScanLongLong(&userLongLong))
        {
            return userLongLong;
        }

        printf("Inlaid input. Try again.\n");
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

        const size_t lineLen = strlen(line);
        if (discardEmpty && lineLen == 0)
        {
            printf("Empty input is not supported.");
            continue;
        }
        if (line[lineLen - 1] == '\n')
        {
            line[lineLen - 1] = '\0';
        }

        return line;
    }
}