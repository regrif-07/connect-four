#pragma once

#include <board.h>
#include <error_codes.h>
#include <game_state.h>

/// Represent a player with a name and cell with which he plays.
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
/// @return pointer to a new heap allocated GameContext. Use the freeGameContext() function to free it.
GameContext* createNewGameContext(ErrorCode* errorCode);

/// Free memory of provided GameContext.
/// @param gameContext pointer to a GameContext to be freed.
void freeGameContext(GameContext* gameContext);

/// Start the main game loop using provided GameContext.
/// @param gameContext GameContext used to start the game and track its state.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case gameContext or gameContext->board are nullptr,
/// NO_ERROR otherwise.
void startGame(GameContext* gameContext, ErrorCode* errorCode);
