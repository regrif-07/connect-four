#include <game_state.h>

#include <board.h>
#include <error_codes.h>

constexpr int WINNING_STREAK_LENGTH = 4;

bool isDraw(const Board* board);

bool checkCellStreakByOffsets(
    const Board* board,
    const int lastMoveRowIndex,
    const int lastMoveColumnIndex,
    const Cell lastMoveCell,
    const int rowOffset,
    const int columnOffset);

GameState analyzeGameState(const Board* board, const int lastMoveRowIndex, const int lastMoveColumnIndex, ErrorCode* errorCode)
{
    if (isDraw(board))
    {
        return DRAW;
    }

    const Cell lastMoveCell = getCellAt(board, lastMoveRowIndex, lastMoveColumnIndex, errorCode);
    if (errorCode && *errorCode != NO_ERROR)
    {
        return IN_PROCESS;
    }
    if (lastMoveCell == EMPTY)
    {
        if (errorCode) *errorCode = ERROR_INVALID_ARGUMENT;
        return IN_PROCESS;
    }

    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int columnOffset = -1; columnOffset <= 1; ++columnOffset)
        {
            if (rowOffset == 0 && columnOffset == 0) // this is the only invalid "direction"
            {
                continue;
            }

            if (checkCellStreakByOffsets(board, lastMoveRowIndex, lastMoveColumnIndex, lastMoveCell, rowOffset, columnOffset))
            {
                return (lastMoveCell == CROSS) ? CROSS_WIN : ZERO_WIN;
            }
        }
    }

    return IN_PROCESS;
}

bool isDraw(const Board* board)
{
    for (int rowIndex = 0; rowIndex < BOARD_HEIGHT; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < BOARD_WIDTH; ++columnIndex)
        {
            if (getCellAt(board, rowIndex, columnIndex, nullptr) == EMPTY)
            {
                return false;
            }
        }
    }

    return true;
}

bool checkCellStreakByOffsets(
    const Board* board,
    const int lastMoveRowIndex,
    const int lastMoveColumnIndex,
    const Cell lastMoveCell,
    const int rowOffset,
    const int columnOffset)
{
    int cellStreakCounter = 0;
    for (int rowIndex = lastMoveRowIndex, columnIndex = lastMoveColumnIndex;
         areValidCellIndices(rowIndex, columnIndex);
         rowIndex += rowOffset, columnIndex += columnOffset)
    {
        if (getCellAt(board, rowIndex, columnIndex, nullptr) == lastMoveCell)
        {
            if (++cellStreakCounter >= WINNING_STREAK_LENGTH)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    return false;
}