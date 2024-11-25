#include <board_serializer.h>

#include <board.h>

#include <error_codes.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

char cellToChar(const Cell cell)
{
    switch (cell)
    {
    case EMPTY:  return '.';
    case CROSS:  return 'X';
    case ZERO:   return 'O';
    case STREAK: return 'Y';
    default:
        assert(false && "Unhandled cell type");
    }
}

Cell charToCell(const char cellChar, ErrorCode* errorCode)
{
    if (errorCode) *errorCode = NO_ERROR;

    switch (cellChar)
    {
        case '.': return EMPTY;
        case 'X': return CROSS;
        case 'O': return ZERO;
        case 'Y': return STREAK;
    default:
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return EMPTY;
    }
}

char* serializeBoard(const Board* board, ErrorCode* errorCode)
{
    char* serializedBoard = calloc(sizeof(char), TOTAL_CELLS + 1);
    if (!serializedBoard)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        serializedBoard[cellIndex] = cellToChar(board->cellArray[cellIndex]);
    }
    serializedBoard[TOTAL_CELLS] = '\0';

    if (errorCode) *errorCode = NO_ERROR;
    return serializedBoard;
}

Board* deserializeBoard(const char* serializedBoard, ErrorCode* errorCode)
{
    if (strlen(serializedBoard) != TOTAL_CELLS)
    {
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return nullptr;
    }

    Board* deserializedBoard = malloc(sizeof(Board));
    if (!deserializedBoard)
    {
        if (errorCode) *errorCode = ERROR_MEMORY;
        return nullptr;
    }

    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        deserializedBoard->cellArray[cellIndex] = charToCell(serializedBoard[cellIndex], errorCode);
        if (errorCode && *errorCode != NO_ERROR)
        {
            free(deserializedBoard);
            return nullptr;
        }
    }

    return deserializedBoard;
}