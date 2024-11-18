#include <board.h>

#include <error_codes.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/// Check if provided indices are valid in terms of board sizes.
/// @param rowIndex a row index to check.
/// @param columnIndex a column index to check.
/// @return true if provided indices are valid; false otherwise.
bool areValidCellIndices(const int rowIndex, const int columnIndex);

/// Get a corresponding char representation of a cell.
/// @param cell a cell, char representation of which to receive.
/// @return char representation of cell.
/// @note assertion will fail in case some kind of cell is unhandled (doesn't have corresponding char).
char getCellChar(Cell cell);

Board* allocateEmptyBoard(ErrorCode* errorCode)
{
    Board* board = malloc(sizeof(Board));
    if (!board)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        board->cellArray[cellIndex] = EMPTY;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return board;
}

Cell getCellAt(const Board* board, const int rowIndex, const int columnIndex, ErrorCode* errorCode)
{
    if (!board)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return EMPTY;
    }

    if (!areValidCellIndices(rowIndex, columnIndex))
    {
        if (errorCode) *errorCode = ERROR_ARGUMENT_OUT_OF_RANGE;
        return EMPTY;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return board->cellArray[rowIndex * BOARD_WIDTH + columnIndex];
}

void setCellAt(Board* board, const int rowIndex, const int columnIndex, const Cell cell, ErrorCode* errorCode)
{
    if (!board)
    {
        if (errorCode) *errorCode = ERROR_NULLPTR_ARGUMENT;
        return;
    }

    if (!areValidCellIndices(rowIndex, columnIndex))
    {
        if (errorCode) *errorCode = ERROR_ARGUMENT_OUT_OF_RANGE;
        return;
    }

    if (errorCode) *errorCode = NO_ERROR;
    board->cellArray[rowIndex * BOARD_WIDTH + columnIndex] = cell;
}

void displayBoard(const Board* board)
{
    if (!board)
    {
        return;
    }

    for (int rowIndex = 0; rowIndex < BOARD_HEIGHT; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < BOARD_WIDTH; ++columnIndex)
        {
            printf("%c", getCellChar(getCellAt(board, rowIndex, columnIndex, nullptr)));
        }
        printf("\n");
    }

    for (int columnNumber = 1; columnNumber <= BOARD_WIDTH; ++columnNumber)
    {
        printf("%d", columnNumber);
    }
}

bool areValidCellIndices(const int rowIndex, const int columnIndex)
{
    return rowIndex >= 0 && rowIndex < BOARD_HEIGHT && columnIndex >= 0 && columnIndex < BOARD_WIDTH;
}

char getCellChar(const Cell cell)
{
    switch (cell)
    {
    case EMPTY: return ' ';
    case CROSS: return 'X';
    case ZERO:  return 'O';
    default:
        assert(0 && "Unhandled cell type");
    }
}
