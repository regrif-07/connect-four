#pragma once

#include <board.h>

#include <error_codes.h>

/// Get the corresponding char representation of the cell.
/// @param cell cell, char representation of which to receive.
/// @return char representation of cell.
/// @note assertion will fail in case some kind of cell is unhandled (doesn't have corresponding char).
char cellToChar(const Cell cell);

/// Get the corresponding cell representation of the cell char.
/// @param cellChar char, cell representation of which to receive.
/// @param errorCode out error parameter; ERROR_INVALID_ARGUMENT in case char is not bound to any cell,
/// NO_ERROR otherwise.
/// @return cell representation of the char
Cell charToCell(const char cellChar, ErrorCode* errorCode);

/// Serialize the board into a plain text format (string).
/// @param board board to serialize.
/// @return serialized board (string).
char* serializeBoard(const Board* board);

/// Deserialize the board string into a Board structure.
/// @param serializedBoard board serialized into string.
/// @param errorCode out error parameter; ERROR_INVALID_ARGUMENT in case serializedBoard has invalid size or if it
/// contains invalid cell character, ERROR_MEMORY in case board memory allocation failed, NO_ERROR otherwise.
/// @return board, that was deserialized from the provided serializedBoard (string), or nullptr in case of
/// deserialization failure.
Board* deserializeBoard(const char* serializedBoard, ErrorCode* errorCode);