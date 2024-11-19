#pragma once

#include <board.h>
#include <error_codes.h>

/// Represent current state/result of a game.
typedef enum
{
    IN_PROCESS,
    CROSS_WIN,
    ZERO_WIN,
    DRAW,
} GameState;

/// Check the board for current game state (is game in process/finished(victory)/finished(draw)).
/// In case winning streak was found, it will be marked.
/// @param board board to be checked and marked.
/// @param lastMoveRowIndex row index of the last move.
/// @param lastMoveColumnIndex column index of the last move.
/// @param errorCode out error parameter; ERROR_ARGUMENT_OUT_OF_RANGE if provided indices of the last move were invalid,
/// ERROR_INVALID_ARGUMENT in case provided indices of the last move are pointing to an EMPTY cell,
/// NO_ERROR otherwise.
/// @return current game state.
GameState checkGameStateAndMarkWinningStreak(Board* board, const int lastMoveRowIndex, const int lastMoveColumnIndex, ErrorCode* errorCode);