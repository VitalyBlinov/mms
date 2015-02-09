//-----------------------------------------------------------------------------
// <copyright file="UnsignedExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 06:42:33</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "UnsignedExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "MMSTags.h"

using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class UnsignedExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    UnsignedExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(UnsignedExtractorTest, TestUnsignedCharPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::UNSIGNED;
    testArray[1] = 1;
    testArray[2] = 123;
    unsigned char _charval = 0;
    EXPECT_TRUE(fetch(ctx, _charval));
    ASSERT_EQ(123, _charval);
}

TEST_F(UnsignedExtractorTest, TestUnsignedCharPositive2)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::UNSIGNED;
    testArray[1] = 1;
    testArray[2] = 0x80;
    unsigned char _charval = 0;
    EXPECT_TRUE(fetch(ctx, _charval));
    ASSERT_EQ(0x80, _charval);
}

TEST_F(UnsignedExtractorTest, TestLongValue)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::UNSIGNED;
    testArray[1] = 4;
    testArray[2] = 0x22;
    testArray[3] = 0x33;
    testArray[4] = 0x44;
    testArray[5] = 0x55;
    unsigned long _longVal = 0;
    EXPECT_TRUE(fetch(ctx, _longVal));
    ASSERT_EQ(0x22334455, _longVal);
}
