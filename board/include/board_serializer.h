#pragma once

#include <board.h>

#include <error_codes.h>

/// Get a corresponding char representation of a cell.
/// @param cell cell, char representation of which to receive.
/// @return char representation of cell.
/// @note assertion will fail in case some kind of cell is unhandled (doesn't have corresponding char).
char cellToChar(const Cell cell);

char* serializeBoard(const Board* board);
Board* deserializeBoard(const char* serializedBoard, ErrorCode* errorCode);