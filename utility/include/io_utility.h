//
// Created by regrif07 on 11/7/24.
//

#pragma once

bool readAndScanInteger(int* out);
int loopReadInteger(const char* prompt);

bool readAndScanLongLong(long long* out);
long long loopReadLongLong(const char* prompt);

char* readLine(const char* prompt, const bool discardEmpty);
