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

/// Allocate and populate with basic data a game context for a new game.
/// Player names will be filled by user.
/// @param errorCode out error parameter; ERROR_MEMORY if GameContext or board allocation failed, NO_ERROR otherwise.
/// @return heap allocated empty GameContext. Use the freeGameContext() function to free it.
GameContext* createNewGameContext(ErrorCode* errorCode);

/// Free memory of the provided GameContext.
/// @param gameContext pointer to the heap allocated GameContext to be freed.
void freeGameContext(GameContext* gameContext);
