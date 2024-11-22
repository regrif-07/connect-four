#include <unity.h>

#include <game_context.h>
#include <game_context_serializer.h>

#include <string.h>
#include <stdlib.h>

void setUp()
{
}

void tearDown()
{
}

// helper function to create a test game context
GameContext* createTestGameContext()
{
    GameContext* gameContext = malloc(sizeof(GameContext));
    TEST_ASSERT_NOT_NULL(gameContext);

    gameContext->id = 42;

    gameContext->crossPlayer.name = strdup("Alice");
    gameContext->crossPlayer.cell = CROSS;

    gameContext->zeroPlayer.name = strdup("Bob");
    gameContext->zeroPlayer.cell = ZERO;

    gameContext->currentPlayer = &gameContext->crossPlayer;

    gameContext->board = createEmptyBoard(nullptr);
    TEST_ASSERT_NOT_NULL(gameContext->board);

    gameContext->board->cellArray[TOTAL_CELLS - 2] = CROSS;
    gameContext->board->cellArray[TOTAL_CELLS - 1] = ZERO;

    gameContext->gameState = IN_PROCESS;

    return gameContext;
}

void testSerializeGameContextValid()
{
    GameContext* gameContext = createTestGameContext();

    ErrorCode errorCode;
    char* serializedContext = serializeGameContext(gameContext, &errorCode);

    TEST_ASSERT_NOT_NULL(serializedContext);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);

    // basic checks on serialized string
    TEST_ASSERT_TRUE(strstr(serializedContext, "42") != nullptr);
    TEST_ASSERT_TRUE(strstr(serializedContext, "\"Alice\"") != nullptr);
    TEST_ASSERT_TRUE(strstr(serializedContext, "\"Bob\"") != nullptr);
    TEST_ASSERT_TRUE(strstr(serializedContext, "X") != nullptr);
    TEST_ASSERT_TRUE(strstr(serializedContext, "\"........................................XO\"") != nullptr);
    TEST_ASSERT_TRUE(strstr(serializedContext, "0") != nullptr);

    free(serializedContext);
    freeGameContext(gameContext);
}

void testDeserializeGameContextValid()
{
    const char* testSerializedContext = "42 \"Alice\" \"Bob\" X \"....................................XO.XO.\" 0";

    ErrorCode errorCode = NO_ERROR;
    GameContext* deserializedContext = deserializeGameContext(testSerializedContext, &errorCode);

    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(deserializedContext);

    // verify deserialized context details
    TEST_ASSERT_EQUAL_INT(42, deserializedContext->id);
    TEST_ASSERT_EQUAL_STRING("Alice", deserializedContext->crossPlayer.name);
    TEST_ASSERT_EQUAL_STRING("Bob", deserializedContext->zeroPlayer.name);
    TEST_ASSERT_EQUAL_INT(CROSS, deserializedContext->currentPlayer->cell);
    TEST_ASSERT_EQUAL_INT(IN_PROCESS, deserializedContext->gameState);

    freeGameContext(deserializedContext);
}

void testSerializeGameContextNullptr()
{
    ErrorCode errorCode;
    const char* serializedContext = serializeGameContext(nullptr, &errorCode);

    TEST_ASSERT_EQUAL_INT(ERROR_NULLPTR_ARGUMENT, errorCode);
    TEST_ASSERT_NULL(serializedContext);
}

void testDeserializeGameContextInvalidFormat()
{
    const char* invalidSerializedContext = "Invalid Format";

    ErrorCode errorCode;
    const GameContext* deserializedContext = deserializeGameContext(invalidSerializedContext, &errorCode);

    TEST_ASSERT_EQUAL_INT(ERROR_INVALID_ARGUMENT, errorCode);
    TEST_ASSERT_NULL(deserializedContext);
}

void testDeserializeGameContextInvalidBoardFormat()
{
    const char* invalidSerializedContext = "42 \"Alice\" \"Bob\" X \"..............`............`........XO.XO.\" 0";

    ErrorCode errorCode;
    const GameContext* deserializedContext = deserializeGameContext(invalidSerializedContext, &errorCode);

    TEST_ASSERT_EQUAL_INT(ERROR_INVALID_ARGUMENT, errorCode);
    TEST_ASSERT_NULL(deserializedContext);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(testSerializeGameContextValid);
    RUN_TEST(testDeserializeGameContextValid);
    RUN_TEST(testSerializeGameContextNullptr);
    RUN_TEST(testDeserializeGameContextInvalidFormat);
    RUN_TEST(testDeserializeGameContextInvalidBoardFormat);

    return UNITY_END();
}
