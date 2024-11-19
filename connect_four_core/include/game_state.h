#pragma once

#include <board.h>
#include <error_codes.h>

typedef enum
{
    IN_PROCESS,
    CROSS_WIN,
    ZERO_WIN,
    DRAW,
} GameState;

GameState checkGameStateAndMarkWinningStreak(Board* board, const int lastMoveRowIndex, const int lastMoveColumnIndex, ErrorCode* errorCode);