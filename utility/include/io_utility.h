#pragma once

/// Read user input and scan integer from it.
/// @param out out parameter that will hold an entered integer.
/// @return true if integer scanning succeeded; false otherwise.
/// @note original solution https://www.reddit.com/r/cprogramming/comments/1aop62k/alternatives_to_scanf_for_reading_integers/.
bool readAndScanInteger(int* out);

/// Ask user for an integer and loop until a valid input is received.
/// @param prompt prompt to be displayed before getting user input.
/// @return integer entered by the user.
int loopReadInteger(const char* prompt);

/// Ask user for an integer in a specified range and loop until a valid (and in range) input is received.
/// @param prompt prompt to be displayed before getting user input.
/// @param min minimal number in a range of supported values.
/// @param max maximum number in a range of supported values.
/// @return user integer in a specified range.
int loopReadIntegerInRange(const char* prompt, const int min, const int max);

/// Ask user for a line.
/// @param prompt prompt to be displayed before getting user input.
/// @param discardEmpty discard empty input or not. Whitespaces-only input is considered empty.
/// @return line entered by the user (without newline character at the end).
char* readLine(const char* prompt, const bool discardEmpty);
