//-----------------------------------------------------------------------------
// <copyright file="FloatExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 09:09:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <cmath>
#include "FloatExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "MMSTags.h"

using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class FloatExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    FloatExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(FloatExtractorTest, TestPositiveEmpty)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::FLOAT;
    testArray[1] = 5;
    testArray[2] = 0x80;
    testArray[3] = 0;
    testArray[4] = 0;
    testArray[5] = 0;
    testArray[6] = 0;
    float _floatVal = 0;
    EXPECT_TRUE(fetch(ctx, _floatVal));
    ASSERT_TRUE(_floatVal - _floatVal == 0);
}

/************************************//**
 * \brief Second test case
 ****************************************/
TEST_F(FloatExtractorTest, TestNAN)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::FLOAT;
    testArray[1] = 1;
    testArray[2] = 0x40;
    float _floatVal = 0;
    EXPECT_TRUE(fetch(ctx, _floatVal));
    ASSERT_FALSE(_floatVal == _floatVal);
}

/************************************//**
 * \brief Third test case
 ****************************************/
TEST_F(FloatExtractorTest, TestPositiveNotEmpty)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::FLOAT;
    testArray[1] = 5;
    testArray[2] = 0x80;
    testArray[3] = 1;
    testArray[4] = 2;
    testArray[5] = 3;
    testArray[6] = 4;
    float _floatVal = 0;
    EXPECT_TRUE(fetch(ctx, _floatVal));
    EXPECT_TRUE(_floatVal == _floatVal);
    auto ptr = reinterpret_cast<const unsigned char*>(&_floatVal);
    EXPECT_EQ(1, ptr[0]);
    EXPECT_EQ(2, ptr[1]);
    EXPECT_EQ(3, ptr[2]);
    ASSERT_EQ(4, ptr[3]);
}