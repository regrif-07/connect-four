#pragma once

#include <error_codes.h>
#include <game_context.h>
#include <game_state.h>

/// Start the main game loop using provided GameContext.
/// @param gameContext GameContext used to start the game and track its state.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case gameContext or gameContext->board are nullptr,
/// NO_ERROR otherwise.
void startGame(GameContext* gameContext, ErrorCode* errorCode);

/// Display the initial information about the game (game header, players, board state).
/// @param gameContext current GameContext.
void displayGameHeader(const GameContext* gameContext);