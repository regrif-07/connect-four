#pragma once

bool readAndScanInteger(int* out);
int loopReadInteger(const char* prompt);
int loopReadIntegerInRange(const char* prompt, const int min, const int max);

char* readLine(const char* prompt, const bool discardEmpty);
