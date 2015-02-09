//-----------------------------------------------------------------------------
// <copyright file="IntegerExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 05:57:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "IntegerExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "MMSTags.h"

using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class IntegerExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    IntegerExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief Small integer test case 1
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallPositiveNumber1)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 1;
    testArray[2] = 123;
    char _charval = 0;
    EXPECT_TRUE(fetch(ctx, _charval));
    EXPECT_EQ(123, _charval);
}

/************************************//**
 * \brief Small integer test case 2
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallPositiveNumber2)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 1;
    testArray[2] = 123;
    int _intval = 0;
    EXPECT_TRUE(fetch(ctx, _intval));
    EXPECT_EQ(123, _intval);
}

/************************************//**
 * \brief Small integer test case 3
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallNegativeNumber1)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 1;
    testArray[2] = -23;
    char _charval = 0;
    EXPECT_TRUE(fetch(ctx, _charval));
    EXPECT_EQ(-23, _charval);
}

/************************************//**
 * \brief Small integer test case 4
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallPositiveNumberWithHighBitSet1)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 2;
    testArray[2] = 0;
    testArray[3] = 0x80;
    char _charval = 0;
    EXPECT_FALSE(fetch(ctx, _charval))  << "This positive number cannot be represented in signed character";
    EXPECT_EQ(0, _charval);
}

/************************************//**
 * \brief Small negative test case
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallNegative2)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 1;
    testArray[2] = 0x80;
    char _charval = 0;
    EXPECT_TRUE(fetch(ctx, _charval));
    EXPECT_EQ(-128, _charval);
}

/************************************//**
 * \brief Small integer test case 5
 ****************************************/
TEST_F(IntegerExtractorTest, TestSmallPositiveNumberWithHighBitSet2)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 2;
    testArray[2] = 0;
    testArray[3] = 0x80;
    short _shortVal = 0;
    EXPECT_TRUE(fetch(ctx, _shortVal));
    EXPECT_EQ(0x80, _shortVal);
}

TEST_F(IntegerExtractorTest, TestNotSoSmallPositiveNumber)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 3;
    testArray[2] = 0x43;
    testArray[3] = 0x25;
    testArray[4] = 0x67;
    int _intVal = 0;
    EXPECT_TRUE(fetch(ctx, _intVal));
    EXPECT_EQ(0x432567, _intVal);
}

TEST_F(IntegerExtractorTest, TestNotSoSmallNegativeNumber)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 3;
    testArray[2] = 0xBC;
    testArray[3] = 0xDA;
    testArray[4] = 0x98;
    long _longVal = 0;
    EXPECT_TRUE(fetch(ctx, _longVal));
    EXPECT_EQ((long)~0x432567, _longVal);
}