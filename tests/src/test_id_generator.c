#include <unity.h>

#include <id_generator.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* TEST_ID_COUNTER_FILEPATH = "test_id_counter.txt";

void setUp(void)
{
    remove(TEST_ID_COUNTER_FILEPATH);
}

void tearDown(void)
{
    remove(TEST_ID_COUNTER_FILEPATH);
}

void writeToTestFile(const char* content)
{
    FILE* file = fopen(TEST_ID_COUNTER_FILEPATH, "w");
    if (file)
    {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

void verifyTestFileId(const long long expectedId)
{
    FILE* file = fopen(TEST_ID_COUNTER_FILEPATH, "r");

    TEST_ASSERT_NOT_NULL(file);

    long long savedId;
    fscanf(file, "%lld", &savedId);
    fclose(file);

    TEST_ASSERT_EQUAL_INT64(expectedId, savedId);
}

void testGenerateNextIdFileDoesNotExist(void)
{
    ErrorCode errorCode;
    const long long id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);

    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT64(1, id);
    verifyTestFileId(1);
}

void testGenerateNextIdFileExistsValidData(void)
{
    writeToTestFile("42");

    ErrorCode errorCode;
    const long long id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);

    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT64(43, id);
    verifyTestFileId(43);
}

void testGenerateNextIdFileExistsInvalidData(void)
{
    writeToTestFile("invalid");

    ErrorCode errorCode;
    const long long id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);

    TEST_ASSERT_EQUAL(ERROR_FILE_STATE, errorCode);
}

void testGenerateNextIdMultipleGenerations()
{
    ErrorCode errorCode;

    long long id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT64(1, id);
    verifyTestFileId(1);

    id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT64(2, id);
    verifyTestFileId(2);

    id = generateNextId(TEST_ID_COUNTER_FILEPATH, &errorCode);
    TEST_ASSERT_EQUAL(NO_ERROR, errorCode);
    TEST_ASSERT_EQUAL_INT64(3, id);
    verifyTestFileId(3);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(testGenerateNextIdFileDoesNotExist);
    RUN_TEST(testGenerateNextIdFileExistsValidData);
    RUN_TEST(testGenerateNextIdFileExistsInvalidData);
    RUN_TEST(testGenerateNextIdMultipleGenerations);

    return UNITY_END();
}
