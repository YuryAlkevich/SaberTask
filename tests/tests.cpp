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