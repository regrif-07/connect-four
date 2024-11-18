//
// Created by regrif07 on 11/15/24.
//

#pragma once

#include <error_codes.h>

constexpr int BOARD_HEIGHT = 6;
constexpr int BOARD_WIDTH = 7;
constexpr int TOTAL_CELLS = BOARD_HEIGHT * BOARD_WIDTH;

typedef enum
{
    EMPTY,
    CROSS,
    ZERO
} CellType;

typedef struct
{
    CellType cellArray[TOTAL_CELLS];
} Board;

Board* allocateEmptyBoard(ErrorCode* errorCode);
CellType getCellAt(const Board* board, const int rowIndex, const int columnIndex, ErrorCode* errorCode);
void setCellAt(Board* board, const int rowIndex, const int columnIndex, const CellType cell, ErrorCode* errorCode);
void displayBoard(const Board* board);