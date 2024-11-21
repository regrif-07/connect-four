#pragma once

#include <error_codes.h>

// board dimensions
constexpr int BOARD_HEIGHT = 6;
constexpr int BOARD_WIDTH = 7;
constexpr int TOTAL_CELLS = BOARD_HEIGHT * BOARD_WIDTH;

/// Represent a type of board cell.
typedef enum
{
    EMPTY,
    CROSS,
    ZERO,
    STREAK, // can be used to mark a final streak on the game board
} Cell;

/// Represent a board.
typedef struct
{
    Cell cellArray[TOTAL_CELLS];
} Board;

/// Allocate a new board and set all cells to EMPTY.
/// @param errorCode out error parameter; ERROR_MEMORY if allocation failed, NO_ERROR otherwise.
/// @return pointer to an allocated empty board or nullptr in case of allocation failure.
Board* createEmptyBoard(ErrorCode* errorCode);

/// Check if provided indices are valid in terms of board sizes.
/// @param rowIndex row index to check.
/// @param columnIndex column index to check.
/// @return true if provided indices are valid; false otherwise.
bool areValidCellIndices(const int rowIndex, const int columnIndex);

/// Get cell from the specified board using provided row/cell indices.
/// @param board board to get cell from.
/// @param rowIndex row index of a target cell.
/// @param columnIndex column index of a target cell.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case board was nullptr,
/// ERROR_ARGUMENT_OUT_OF_RANGE in case provided row and cell indices were invalid (out of range),
/// NO_ERROR otherwise.
/// @return cell at specified location. Check the errorCode before using the return value.
Cell getCellAt(const Board* board, const int rowIndex, const int columnIndex, ErrorCode* errorCode);

/// Set cell in a specified board using provided row/cell indices and a cell.
/// @param board board to set cell in.
/// @param rowIndex row index of the target set location.
/// @param columnIndex column index of the target set location.
/// @param cell cell to set.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case board was nullptr,
/// ERROR_ARGUMENT_OUT_OF_RANGE in case provided row and cell indices were invalid (out of range),
/// NO_ERROR otherwise.
void setCellAt(Board* board, const int rowIndex, const int columnIndex, const Cell cell, ErrorCode* errorCode);

/// Display a specified board. Display nothing in case board is nullptr.
/// @param board board to display.
void displayBoard(const Board* board);