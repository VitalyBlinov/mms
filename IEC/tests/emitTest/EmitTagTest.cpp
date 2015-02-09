//-----------------------------------------------------------------------------
// <copyright file="EmitTagTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 02:26:58</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <memory>
#include "TagEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class EmitTagTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    EmitTagTest()
    {
        testArray.fill(0);
    }

};
/************************************//**
 * \brief Positive test case
 ****************************************/
TEST_F(EmitTagTest, TestPositive)
{
	auto ctx = createMMSExplicitContext(testArray);
    int a = 0;
    emitTag(ctx, a);
    ASSERT_EQ(MMS::Tags::INTEGER, testArray[127]);
}

/************************************//**
 * \brief Negative test case
 ****************************************/
TEST_F(EmitTagTest, TestNegative)
{
	auto ctx = createMMSImplicitContext(testArray);
    ASSERT_EQ(0, testArray[127]);
    int a = 0;
    emitTag(ctx, a);
    ASSERT_EQ(0, testArray[127]);
    ctx = emitOctet(ctx, 12);
    ASSERT_EQ(12, testArray[127]);
    ctx = emitOctet(ctx, 13);
    ASSERT_EQ(12, testArray[127]);
    ASSERT_EQ(13, testArray[126]);
}

/************************************//**
 * \brief Negative test case, dynamic
 ****************************************/
TEST_F(EmitTagTest, TestNegativeDynamic)
{
//     auto ctx = createMMSExplicitContext(testArray);
// 	std::unique_ptr<EmitContextBase> dyn(new MMS::Emitters::ImplicitEmitContextMMS(ctx));
//     ASSERT_EQ(0, testArray[127]);
//     int a = 0;
//     emitTag(*dyn, a);
//     EXPECT_EQ(0, testArray[127]);
//     ctx = emitOctet(ctx, 12);
//     EXPECT_EQ(12, testArray[127]);
//     ctx = emitOctet(ctx, 13);
//     EXPECT_EQ(12, testArray[127]);
//     EXPECT_EQ(13, testArray[126]);
}