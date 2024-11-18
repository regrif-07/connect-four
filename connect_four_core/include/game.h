#pragma once

#include <board.h>

#include <error_codes.h>

typedef struct
{
    char* crossPlayerName;
    char* zeroPlayerName;
    Board* board;
} GameContext;

GameContext* allocateNewGameContext(ErrorCode* errorCode);
void startGame(GameContext* gameContext, ErrorCode* errorCode);
