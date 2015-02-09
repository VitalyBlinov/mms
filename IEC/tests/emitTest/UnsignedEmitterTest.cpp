//-----------------------------------------------------------------------------
// <copyright file="UnsignedEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/29 18:24:25</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "UnsignedEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class UnsignedEmitterTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    UnsignedEmitterTest()
    {
        testArray.fill(0);
    }
};

TEST_F(UnsignedEmitterTest, TestSmallPositiveNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (unsigned char)23);
    ASSERT_EQ(23, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::UNSIGNED, testArray[125]);
}

TEST_F(UnsignedEmitterTest, TestItdoesNotMatterHowBigIsTheDataType)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (unsigned long)23);
    ASSERT_EQ(23, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::UNSIGNED, testArray[125]);
}

TEST_F(UnsignedEmitterTest, TestOneBytePositiveNoSpecialRules)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (unsigned short)0x80);
    ASSERT_EQ(0x80, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::UNSIGNED, testArray[125]);
}

TEST_F(UnsignedEmitterTest, TestNotSoSmallPositiveNumber)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (unsigned int)0x432567);
    ASSERT_EQ(0x67, testArray[127]);
    ASSERT_EQ(0x25, testArray[126]);
    ASSERT_EQ(0x43, testArray[125]);
    ASSERT_EQ(0x3, testArray[124]);
    ASSERT_EQ(MMS::Tags::UNSIGNED, testArray[123]);
}
