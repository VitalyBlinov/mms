//-----------------------------------------------------------------------------
// <copyright file="LengthExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 00:03:37</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "LengthExtractor.h"
#include "FetchContext.h"
#include "MMSTags.h"

using namespace MMS::Extractors;
using namespace MMS::Extractors::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class LengthExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    LengthExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief Short form positive test case
 ****************************************/
TEST_F(LengthExtractorTest, TestShortFormPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = 32;
    unsigned int len = 0;
    EXPECT_TRUE(fetchLength(ctx, len));
    ASSERT_EQ(32, len);
}
/************************************//**
 * \brief Simple long form positive test case
 ****************************************/
TEST_F(LengthExtractorTest, TestLongFormPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = 0x81;
    testArray[1] = 128;
    unsigned int len = 0;
    EXPECT_TRUE(fetchLength(ctx, len));
    ASSERT_EQ(128, len);
}
/************************************//**
 * \brief Long form positive test case
 ****************************************/
TEST_F(LengthExtractorTest, TestLongerFormPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = 0x82;
    testArray[1] = 0xAB;
    testArray[2] = 0xCD;
    unsigned int len = 0;
    EXPECT_TRUE(fetchLength(ctx, len));
    ASSERT_EQ(0xABCD, len);
}
/************************************//**
 * \brief Negative test case : context is empty
 ****************************************/
TEST_F(LengthExtractorTest, TestEmtpyContextNeg)
{
    std::vector<bool> data;
    auto ctx = createFetchContext(data);
    unsigned int len = 0;
    ASSERT_FALSE(fetchLength(ctx, len));
}
/************************************//**
 * \brief Negative test case : incomplete long form
 ****************************************/
TEST_F(LengthExtractorTest, TestLongFormFailure)
{
    std::array<unsigned char, 3> data;
    auto ctx = createFetchContext(data);
    data[0] = 0x84;
    unsigned int len = 0;
    ASSERT_FALSE(fetchLength(ctx, len));
}