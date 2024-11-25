#pragma once

#include <game_context.h>

#include <error_codes.h>

/// Serialize the provided game context into the string format.
/// @param gameContext game context to serialize.
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case gameContext was nullptr, ERROR_MEMORY in case
/// game context string or board string allocation failed, NO_ERROR otherwise.
/// @return heap allocated serialized game context (string).
/// ("[cross player name]" "[zero player name]" [current player (X or O)] [serialized board] [game state (number)])
char* serializeGameContext(const GameContext* gameContext, ErrorCode* errorCode);

/// Deserialize the provided game context string back into GameContext structure.
/// @param serializedGameContext game context serialized in the string format.
/// ("[cross player name]" "[zero player name]" [current player (X or O)] [serialized board] [game state (number)])
/// @param errorCode out error parameter; ERROR_NULLPTR_ARGUMENT in case serializedGameContext is nullptr,
/// ERROR_INVALID_ARGUMENT in case serializedGameContext has invalid format, ERROR_MEMORY in case GameContext or Board
/// allocation failed, NO_ERROR otherwise.
/// @return heap allocated deserialized GameContext (GameContext structure).
GameContext* deserializeGameContext(const char* serializedGameContext, ErrorCode* errorCode);
