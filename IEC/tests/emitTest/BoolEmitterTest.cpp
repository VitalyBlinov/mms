//-----------------------------------------------------------------------------
// <copyright file="BoolEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 02:06:19</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "BoolEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class BoolEmitterTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    BoolEmitterTest()
    {
        testArray.fill(0);
    }

};
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(BoolEmitterTest, TestWithTagTrue)
{
	auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, true);
    ASSERT_EQ(1, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::BOOLEAN, testArray[125]);
}

/************************************//**
 * \brief False value test case
 ****************************************/
TEST_F(BoolEmitterTest, TestWithTagFalse)
{
	auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, false);
    ASSERT_EQ(0, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(MMS::Tags::BOOLEAN, testArray[125]);
}

/************************************//**
 * \brief Another test case - no tag
 ****************************************/
TEST_F(BoolEmitterTest, TestWithTag)
{
	auto ctx = createMMSImplicitContext(testArray);
    emit(ctx, true);
    ASSERT_EQ(1, testArray[127]);
    ASSERT_EQ(1, testArray[126]);
    ASSERT_EQ(0, testArray[125]);
}