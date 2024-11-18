#pragma once

#include <board.h>
#include <error_codes.h>
#include <game_state.h>

typedef struct
{
    char* name;
    Cell cell;
} Player;

typedef struct
{
    Player crossPlayer;
    Player zeroPlayer;
    Player* currentPlayer;
    Board* board;
    GameState gameState;
} GameContext;

GameContext* createNewGameContext(ErrorCode* errorCode);
void freeGameContext(GameContext* gameContext);
void startGame(GameContext* gameContext, ErrorCode* errorCode);
