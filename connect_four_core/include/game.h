#pragma once

#include <board.h>

#include <error_codes.h>

typedef struct
{
    char* name;
    Cell cell;
} Player;

typedef struct
{
    Player firstPlayer;
    Player secondPlayer;
    Player* currentPlayer;
    Board* board;
} GameContext;

GameContext* createNewGameContext(ErrorCode* errorCode);
void freeGameContext(GameContext* gameContext);
void startGame(GameContext* gameContext, ErrorCode* errorCode);
