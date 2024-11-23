#include <unity.h>

#include <board.h>
#include <board_serializer.h>
#include <error_codes.h>

#include <stdlib.h>
#include <string.h>

static const Board* g_testBoard = nullptr;
static const char* g_serializedTestBoard = nullptr;

void setUp() {}
void tearDown() {}

void initializeGlobalContext()
{
    ErrorCode errorCode;
    Board* board = createEmptyBoard(&errorCode);
    if (errorCode != NO_ERROR)
    {
        TEST_FAIL_MESSAGE("Test board allocation failure");
    }

    setCellAt(board, 2, 0, STREAK, nullptr);
    setCellAt(board, 2, 4, CROSS, nullptr);

    setCellAt(board, 3, 0, STREAK, nullptr);
    setCellAt(board, 3, 1, CROSS, nullptr);
    setCellAt(board, 3, 3, ZERO, nullptr);
    setCellAt(board, 3, 4, ZERO, nullptr);

    setCellAt(board, 4, 0, STREAK, nullptr);
    setCellAt(board, 4, 1, CROSS, nullptr);
    setCellAt(board, 4, 2, ZERO, nullptr);
    setCellAt(board, 4, 4, CROSS, nullptr);
    setCellAt(board, 4, 5, CROSS, nullptr);
    setCellAt(board, 4, 6, ZERO, nullptr);

    setCellAt(board, 5, 0, STREAK, nullptr);
    setCellAt(board, 5, 1, ZERO, nullptr);
    setCellAt(board, 5, 2, CROSS, nullptr);
    setCellAt(board, 5, 3, ZERO, nullptr);
    setCellAt(board, 5, 4, CROSS, nullptr);
    setCellAt(board, 5, 5, ZERO, nullptr);
    setCellAt(board, 5, 6, CROSS, nullptr);

    g_testBoard = board;
    g_serializedTestBoard = "......."
                            "......."
                            "Y...X.."
                            "YX.OO.."
                            "YXO.XXO"
                            "YOXOXOX";
}

void testAssertEqualBoards(const Board* firstBoard, const Board* secondBoard)
{
    for (int cellIndex = 0; cellIndex < TOTAL_CELLS; ++cellIndex)
    {
        TEST_ASSERT_EQUAL_INT(firstBoard->cellArray[cellIndex], secondBoard->cellArray[cellIndex]);
    }
}

void testCellToChar()
{
    TEST_ASSERT_EQUAL_CHAR('.', cellToChar(EMPTY));
    TEST_ASSERT_EQUAL_CHAR('X', cellToChar(CROSS));
    TEST_ASSERT_EQUAL_CHAR('O', cellToChar(ZERO));
    TEST_ASSERT_EQUAL_CHAR('Y', cellToChar(STREAK));
}

void testCharToCellValid()
{
    ErrorCode errorCode;

    TEST_ASSERT_EQUAL_INT(EMPTY, charToCell('.', &errorCode));
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);

    TEST_ASSERT_EQUAL_INT(CROSS, charToCell('X', &errorCode));
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);

    TEST_ASSERT_EQUAL_INT(ZERO, charToCell('O', &errorCode));
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);

    TEST_ASSERT_EQUAL_INT(STREAK, charToCell('Y', &errorCode));
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
}

void testCharToCellInvalid()
{
    ErrorCode errorCode;

    charToCell('\0', &errorCode);
    TEST_ASSERT_EQUAL_INT(ERROR_INVALID_ARGUMENT, errorCode);
}

void testSerializeBoard()
{
    ErrorCode errorCode;
    char* serializedBoard = serializeBoard(g_testBoard, &errorCode);

    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(serializedBoard);
    TEST_ASSERT_EQUAL_STRING(serializedBoard, g_serializedTestBoard);

    free(serializedBoard);
}

void testDeserializeBoardValid()
{
    ErrorCode errorCode;
    Board* deserializedBoard = deserializeBoard(g_serializedTestBoard, &errorCode);

    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(deserializedBoard);

    testAssertEqualBoards(deserializedBoard, g_testBoard);

    free(deserializedBoard);
}

void testDeserializeBoardInvalidLength()
{
    ErrorCode errorCode;
    const char* invalidSerializedBoard = "X.O";
    const Board* board = deserializeBoard(invalidSerializedBoard, &errorCode);

    TEST_ASSERT_EQUAL_INT(ERROR_INVALID_ARGUMENT, errorCode);
    TEST_ASSERT_NULL(board);
}

void testDeserializeBoardInvalidCharacter()
{
    ErrorCode errorCode;
    const char* invalidSerializedBoard = ".......X.....X.....O.......`.....O..X.....";
    const Board* board = deserializeBoard(invalidSerializedBoard, &errorCode);

    TEST_ASSERT_EQUAL_INT(ERROR_INVALID_ARGUMENT, errorCode);
    TEST_ASSERT_NULL(board);
}

void testSerializeDeserializeCycle()
{
    ErrorCode errorCode;
    char* serializedBoard = serializeBoard(g_testBoard, &errorCode);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(serializedBoard);

    Board* deserializedBoard = deserializeBoard(serializedBoard, &errorCode);
    TEST_ASSERT_EQUAL_INT(NO_ERROR, errorCode);
    TEST_ASSERT_NOT_NULL(deserializedBoard);

    testAssertEqualBoards(deserializedBoard, g_testBoard);

    free(serializedBoard);
    free(deserializedBoard);
}

int main()
{
    UNITY_BEGIN();

    initializeGlobalContext();

    // tests for cellToChar()
    RUN_TEST(testCellToChar);

    // tests for charToCell()
    RUN_TEST(testCharToCellValid);
    RUN_TEST(testCharToCellInvalid);

    // tests for serializeBoard()
    RUN_TEST(testSerializeBoard);

    // tests for deserializeBoard()
    RUN_TEST(testDeserializeBoardValid);
    RUN_TEST(testDeserializeBoardInvalidLength);
    RUN_TEST(testDeserializeBoardInvalidCharacter);

    // complex tests
    RUN_TEST(testSerializeDeserializeCycle);

    return UNITY_END();
}
