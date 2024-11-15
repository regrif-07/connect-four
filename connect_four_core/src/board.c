//
// Created by regrif07 on 11/15/24.
//

#include <assert.h>
#include <board.h>
#include <stdio.h>
#include <stdlib.h>

bool areValidCellIndices(const int rowIndex, const int columnIndex);
char getCellChar(CellType cellType);

Board* allocateEmptyBoard()
{
    Board* board = malloc(sizeof(Board));
    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        board->cellArray[cellIndex] = EMPTY;
    }

    return board;
}

CellType getCellAt(const Board* board, const int rowIndex, const int columnIndex)
{
    if (!areValidCellIndices(rowIndex, columnIndex))
    {
        assert(0 && "Should be replaced with error-handling system"); // TODO
    }

    return board->cellArray[rowIndex * BOARD_HEIGHT + columnIndex];
}

void setCellAt(Board* board, const int rowIndex, const int columnIndex, const CellType cell)
{
    if (!areValidCellIndices(rowIndex, columnIndex))
    {
        assert(0 && "Should be replaced with error-handling system"); // TODO
    }

    board->cellArray[rowIndex * BOARD_HEIGHT + columnIndex] = cell;
}

void displayBoard(const Board* board)
{
    for (int rowIndex = 0; rowIndex < BOARD_HEIGHT; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < BOARD_WIDTH; ++columnIndex)
        {
            printf("%c", getCellChar(getCellAt(board, rowIndex, columnIndex)));
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
