//
// Created by regrif07 on 11/15/24.
//

#include <board.h>

#include <error_codes.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool areValidCellIndices(const int rowIndex, const int columnIndex);
char getCellChar(CellType cellType);

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

CellType getCellAt(const Board* board, const int rowIndex, const int columnIndex, ErrorCode* errorCode)
{
    if (!areValidCellIndices(rowIndex, columnIndex))
    {
        if (errorCode) *errorCode = ERROR_ARGUMENT_OUT_OF_RANGE;
        return EMPTY;
    }

    if (errorCode) *errorCode = NO_ERROR;
    return board->cellArray[rowIndex * BOARD_WIDTH + columnIndex];
}

void setCellAt(Board* board, const int rowIndex, const int columnIndex, const CellType cell, ErrorCode* errorCode)
{
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

char getCellChar(const CellType cellType)
{
    switch (cellType)
    {
    case EMPTY: return ' ';
    case CROSS: return 'X';
    case ZERO:  return 'O';
    default:
        assert(0 && "Unhandled cell type");
    }
}
