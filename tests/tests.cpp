#include <gtest/gtest.h>

#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

TEST(Task1_Test, TestUseCases)
{
    uint64_t bigUint = 123123123123ull;
    std::string bigUintStr = "0000000000000000000000000001110010101010101101011100001110110011";

    int16_t negativeInt = -3210;
    std::string negativeIntStr = "1111001101110110";

    ASSERT_EQ(bigUintStr, SaberTask::ToBinaryString(bigUint));
    ASSERT_EQ(negativeIntStr, SaberTask::ToBinaryString(negativeInt));
}

TEST(Task2_Tests, TestUseCases)
{
    char testStr[] = "AAAAA_BB_CCCCC_LOL_LOOOOLLLLL";
    std::string expectedResult = "A_B_C_LOL_LOL";

    SaberTask::RemoveDubs(testStr);
    ASSERT_EQ(expectedResult, std::string(testStr));
}

TEST(Task3_Tests, SizeIsPreservedAfterDeserialize)
{
    SaberTask::List list;
    list.pushBack("ONE");
    list.pushBack("TWO");
    list.pushFront("PREONE");

    auto* file = std::fopen("test.bin", "wb");
    list.serialize(file);
    std::fclose(file);

    SaberTask::List newList;
    file = std::fopen("test.bin", "rb");
    newList.deserialize(file);
    std::fclose(file);

    ASSERT_EQ(newList.size(), 3);
}

TEST(Task3_Tests, OrderIsPreservedAfterDeserialize)
{
    SaberTask::List list;
    list.pushBack("ONE");
    list.pushBack("TWO");
    list.pushFront("PREONE");

    auto* file = std::fopen("test.bin", "wb");
    list.serialize(file);
    std::fclose(file);

    SaberTask::List newList;
    file = std::fopen("test.bin", "rb");
    newList.deserialize(file);
    std::fclose(file);

    auto expected = {"PREONE", "ONE", "TWO"};
    auto predicate = [&](const std::string& one, const SaberTask::ListNode& two)
    {
        return two.data == one;
    };
    ASSERT_TRUE(std::equal(expected.begin(), expected.end(), newList.begin(), predicate));
}

TEST(Task3_Tests, RandElementsArePreservedAfterDeserialize)
{
    SaberTask::List list;
    auto& one = list.pushBack("ONE");
    auto& two = list.pushBack("TWO");
    auto& preone = list.pushFront("PREONE");
    auto& prepreone = list.pushFront("PREPREONE");

    one.rand = &prepreone;
    two.rand = &prepreone;
    preone.rand = &one;
    prepreone.rand = &two;

    auto* file = std::fopen("test.bin", "wb");
    list.serialize(file);
    std::fclose(file);

    SaberTask::List newList;
    file = std::fopen("test.bin", "rb");
    newList.deserialize(file);
    std::fclose(file);

    ASSERT_EQ(newList.find("ONE").rand, &newList.find("PREPREONE"));
    ASSERT_EQ(newList.find("TWO").rand, &newList.find("PREPREONE"));
    ASSERT_EQ(newList.find("PREONE").rand, &newList.find("ONE"));
    ASSERT_EQ(newList.find("PREPREONE").rand, &newList.find("TWO"));
}