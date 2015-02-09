//-----------------------------------------------------------------------------
// <copyright file="IntEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/29 03:14:18</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "IntegerEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class IntEmitterTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    IntEmitterTest()
    {
        testArray.fill(0);
    }
};

TEST_F(IntEmitterTest, TestSmallPositiveNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (char)23);
    ASSERT_EQ(23, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[125]);
}

TEST_F(IntEmitterTest, TestItdoesNotMatterHowBigIsTheDataType)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (long)23);
    ASSERT_EQ(23, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[125]);
}

TEST_F(IntEmitterTest, TestSmallNegativeNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (char)-23);
    ASSERT_EQ(-23, static_cast<char>(testArray[127]));
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[125]);
}

TEST_F(IntEmitterTest, TestOneBytePositiveThatDoesNotQuiteFit)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (short)0x80);
    ASSERT_EQ(0x80, testArray[127]);
    ASSERT_EQ(0, testArray[126]);
    ASSERT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[124]);
}

TEST_F(IntEmitterTest, TestOneByteNegativeThatDoesNotQuiteFit)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (short)-129);
    ASSERT_EQ(0x7F, testArray[127]);
    ASSERT_EQ(0xFF, testArray[126]);
    ASSERT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[124]);
}

TEST_F(IntEmitterTest, TestNotSoSmallPositiveNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, 0x432567);
    ASSERT_EQ(0x67, testArray[127]);
    ASSERT_EQ(0x25, testArray[126]);
    ASSERT_EQ(0x43, testArray[125]);
    ASSERT_EQ(0x3, testArray[124]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[123]);
}

TEST_F(IntEmitterTest, TestNotSoSmallNegativeNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (long)~0x432567);
    ASSERT_EQ(0x98, testArray[127]);
    ASSERT_EQ(0xDA, testArray[126]);
    ASSERT_EQ(0xBC, testArray[125]);
    ASSERT_EQ(0x3, testArray[124]);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[123]);
}