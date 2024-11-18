#pragma once

bool readAndScanInteger(int* out);
int loopReadInteger(const char* prompt);

bool readAndScanLongLong(long long* out);
long long loopReadLongLong(const char* prompt);

char* readLine(const char* prompt, const bool discardEmpty);
