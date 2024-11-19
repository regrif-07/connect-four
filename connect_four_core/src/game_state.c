#include <assert.h>
#include <game_state.h>

#include <board.h>
#include <error_codes.h>

constexpr int WINNING_STREAK_LENGTH = 4;

/// Check if the board is in a draw state.
/// @param board board to be checked.
/// @return true if it's a draw; false otherwise.
bool isDraw(const Board* board);

/// Check for a winning cell streak with respect to the last move.
/// Direction of the check is specified by rowOffset and columnOffset.
/// @param board board in which streak should be checked.
/// @param lastMoveRowIndex row index of the last move.
/// @param lastMoveColumnIndex column index of the last move.
/// @param lastMoveCell cell that was placed with the last move.
/// @param rowOffset row offset that specifies the direction of the streak to check.
/// @param columnOffset row offset that specifies the direction of the streak to check.
/// @return true if streak was found and marked; false otherwise.
/// @note For example:
/// - check streak on the left of the last move - rowOffset = 0, columnOffset = -1,
/// - check streak diagonally up-right from the last move - rowOffset = -1, columnOffset = 1
bool checkAndMarkCellStreakByOffsets(
    Board* board,
    const int lastMoveRowIndex,
    const int lastMoveColumnIndex,
    const Cell lastMoveCell,
    const int rowOffset,
    const int columnOffset);

/// Mark the winning streak on the board by setting winning cells to STREAK.
/// @param board board in which streak should be marked.
/// @param streakCellRowIndices row indices of winning streak cells.
/// @param streakCellColumnIndices column indices of winning streak cells.
void markWinningStreak(
    Board* board,
    int streakCellRowIndices[WINNING_STREAK_LENGTH],
    int streakCellColumnIndices[WINNING_STREAK_LENGTH]);

GameState checkGameStateAndMarkWinningStreak(Board* board, const int lastMoveRowIndex, const int lastMoveColumnIndex, ErrorCode* errorCode)
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

    // iterate over all possible direction offsets
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int columnOffset = -1; columnOffset <= 1; ++columnOffset)
        {
            if (rowOffset == 0 && columnOffset == 0) // this is the only invalid "direction"
            {
                continue;
            }

            if (checkAndMarkCellStreakByOffsets(board, lastMoveRowIndex, lastMoveColumnIndex, lastMoveCell, rowOffset, columnOffset))
            {
                if (errorCode) *errorCode = NO_ERROR;
                // winning streak was found, use information about last move to identify the winner
                return (lastMoveCell == CROSS) ? CROSS_WIN : ZERO_WIN;
            }
        }
    }

    if (errorCode) *errorCode = NO_ERROR;
    return IN_PROCESS;
}

bool isDraw(const Board* board)
{
    for (int rowIndex = 0; rowIndex < BOARD_HEIGHT; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < BOARD_WIDTH; ++columnIndex)
        {
            // if there are any empty cells, it's not a draw
            if (getCellAt(board, rowIndex, columnIndex, nullptr) == EMPTY)
            {
                return false;
            }
        }
    }

    return true;
}

bool checkAndMarkCellStreakByOffsets(
    Board* board,
    const int lastMoveRowIndex,
    const int lastMoveColumnIndex,
    const Cell lastMoveCell,
    const int rowOffset,
    const int columnOffset)
{
    assert(!(rowOffset == 0 && columnOffset == 0) && "Invalid offsets");

    // in case it's a winning streak, we will store information about checked cells
    int streakCellRowIndices[WINNING_STREAK_LENGTH];
    int streakCellColumnIndices[WINNING_STREAK_LENGTH];

    int cellStreakCounter = 0;
    for (int rowIndex = lastMoveRowIndex, columnIndex = lastMoveColumnIndex;
         areValidCellIndices(rowIndex, columnIndex);
         rowIndex += rowOffset, columnIndex += columnOffset)
    {
        if (getCellAt(board, rowIndex, columnIndex, nullptr) == lastMoveCell)
        {
            streakCellRowIndices[cellStreakCounter] = rowIndex;
            streakCellColumnIndices[cellStreakCounter] = columnIndex;

            ++cellStreakCounter;
            if (cellStreakCounter >= WINNING_STREAK_LENGTH)
            {
                markWinningStreak(board, streakCellRowIndices, streakCellColumnIndices);
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

void markWinningStreak(
    Board* board,
    int streakCellRowIndices[WINNING_STREAK_LENGTH],
    int streakCellColumnIndices[WINNING_STREAK_LENGTH])
{
    for (int i = 0; i < WINNING_STREAK_LENGTH; ++i)
    {
        setCellAt(board, streakCellRowIndices[i], streakCellColumnIndices[i], STREAK, nullptr);
    }
}