//-----------------------------------------------------------------------------
// <copyright file="BitStringEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/09 03:34:13</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "BitStringEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class BitStringEmitterTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    BitStringEmitterTest()
    {
        testArray.fill(0);
    }

};
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(BitStringEmitterTest, Test0xFF)
{
	std::vector<bool> testVector(8, 1);
    ASSERT_EQ(8, testVector.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, testVector));
    EXPECT_EQ(4, oldSize - newSize);
    EXPECT_EQ(0xff, testArray[127]);
    EXPECT_EQ(0, testArray[126]);
    EXPECT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[124]);
}

/************************************//**
 * \brief Second test case
 ****************************************/
TEST_F(BitStringEmitterTest, Test0xF0)
{
	std::vector<bool> testVector(4, 1);
    ASSERT_EQ(4, testVector.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, testVector));
    EXPECT_EQ(4, oldSize - newSize);
    EXPECT_EQ(0xf0, testArray[127]);
    EXPECT_EQ(4, testArray[126]);
    EXPECT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[124]);
}

/************************************//**
 * \brief Third test case
 ****************************************/
TEST_F(BitStringEmitterTest, Test0x10)
{
	std::vector<bool> testVector(4, 0);
    testVector[3] = true;
    ASSERT_EQ(4, testVector.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, testVector));
    EXPECT_EQ(4, oldSize - newSize);
    EXPECT_EQ(0x10, testArray[127]);
    EXPECT_EQ(4, testArray[126]);
    EXPECT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[124]);
}

/************************************//**
 * \brief Fourth test case
 ****************************************/
TEST_F(BitStringEmitterTest, Test0x108)
{
	std::vector<bool> testVector(9, 0);
    testVector[3] = true;
    testVector[8] = true;
    ASSERT_EQ(9, testVector.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, testVector));
    EXPECT_EQ(5, oldSize - newSize);
    EXPECT_EQ(0x80, testArray[127]);
    EXPECT_EQ(0x10, testArray[126]);
    EXPECT_EQ(7, testArray[125]);
    EXPECT_EQ(3, testArray[124]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[123]);
}

/************************************//**
 * \brief Fourth test case
 ****************************************/
TEST_F(BitStringEmitterTest, Test0x12A)
{
	std::vector<bool> testVector(11, 0);
    testVector[3] = true;
    testVector[6] = true;
    testVector[8] = true;
    testVector[10] = true;
    ASSERT_EQ(11, testVector.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, testVector));
    EXPECT_EQ(5, oldSize - newSize);
    EXPECT_EQ(0xA0, testArray[127]);
    EXPECT_EQ(0x12, testArray[126]);
    EXPECT_EQ(5, testArray[125]);
    EXPECT_EQ(3, testArray[124]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[123]);
}
