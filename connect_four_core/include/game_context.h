#pragma once

#include <board.h>
#include <game_context.h>
#include <game_state.h>

/// Represent a player with a name and cell type
typedef struct
{
    char* name;
    Cell cell;
} Player;

/// Represent current state/context of a game.
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
