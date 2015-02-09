//-----------------------------------------------------------------------------
// <copyright file="EmitLengthTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/28 01:52:35</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "EmitContext.h"
#include "LengthEmitter.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class EmitLengthTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    EmitLengthTest()
    {
        testArray.fill(0);
    }

};
/************************************//**
 * \brief Short form test case
 ****************************************/
TEST_F(EmitLengthTest, TestShortLength)
{
	auto context = createMMSExplicitContext(testArray);
    emitLength(context, 6);
    ASSERT_EQ(6, testArray[127]);
}

/************************************//**
 * \brief Long form test case
 ****************************************/
TEST_F(EmitLengthTest, TestLongLengthOneByte)
{
	auto context = createMMSExplicitContext(testArray);
    emitLength(context, 250);
    ASSERT_EQ(250, testArray[127]);
    ASSERT_EQ(0x81, testArray[126]);
}

/************************************//**
 * \brief Long form test case 2
 ****************************************/
TEST_F(EmitLengthTest, TestLongLengthTwoBytes)
{
	auto context = createMMSExplicitContext(testArray);
    emitLength(context, 0xf101);
    ASSERT_EQ(0x1, testArray[127]);
    ASSERT_EQ(0xf1, testArray[126]);
    ASSERT_EQ(0x82, testArray[125]);
}

/************************************//**
 * \brief Long form test case 3
 ****************************************/
TEST_F(EmitLengthTest, TestLongLengthThreeBytes)
{
	auto context = createMMSExplicitContext(testArray);
    emitLength(context, 0x1af101);
    ASSERT_EQ(0x1, testArray[127]);
    ASSERT_EQ(0xf1, testArray[126]);
    ASSERT_EQ(0x1a, testArray[125]);
    ASSERT_EQ(0x83, testArray[124]);
}

/************************************//**
 * \brief Long form test case 4
 ****************************************/
TEST_F(EmitLengthTest, TestLongLengthFourBytes)
{
	auto context = createMMSExplicitContext(testArray);
    emitLength(context, 0x21af101);
    ASSERT_EQ(0x1, testArray[127]);
    ASSERT_EQ(0xf1, testArray[126]);
    ASSERT_EQ(0x1a, testArray[125]);
    ASSERT_EQ(0x2, testArray[124]);
    ASSERT_EQ(0x84, testArray[123]);
}

