//-----------------------------------------------------------------------------
// <copyright file="BoolExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/13 00:18:22</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "BoolExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "MMSTags.h"

using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class BoolExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    BoolExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(BoolExtractorTest, TestPositiveTrue)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BOOLEAN;
    testArray[1] = 1;
    testArray[2] = 1;
    bool val = false;
    EXPECT_TRUE(fetch(ctx, val));
    ASSERT_TRUE(val);
}

/************************************//**
 * \brief Encoded value is "false"
 ****************************************/
TEST_F(BoolExtractorTest, TestPositiveFalse)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BOOLEAN;
    testArray[1] = 1;
    testArray[2] = 0;
    bool val = true;
    EXPECT_TRUE(fetch(ctx, val));
    ASSERT_FALSE(val);
}

/************************************//**
 * \brief Encoded value is "false", context with no tags
 ****************************************/
TEST_F(BoolExtractorTest, TestPositiveFalseNoTags)
{
    auto ctx = createNoTagFetchContext(testArray);
    testArray[0] = 1;
    testArray[1] = 0;
    bool val = true;
    EXPECT_TRUE(fetch(ctx, val));
    ASSERT_FALSE(val);
}

/************************************//**
 * \brief Negative test case - wrong tag
 ****************************************/
TEST_F(BoolExtractorTest, TestNegativeWrongTag)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::INTEGER;
    testArray[1] = 1;
    testArray[2] = 1;
    bool val = false;
    EXPECT_FALSE(fetch(ctx, val));
    ASSERT_FALSE(val);
}

/************************************//**
 * \brief Negative test case - wrong length
 ****************************************/
TEST_F(BoolExtractorTest, TestNegativeWrongLength)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BOOLEAN;
    testArray[1] = 2;
    testArray[2] = 1;
    bool val = false;
    EXPECT_FALSE(fetch(ctx, val));
    ASSERT_FALSE(val);
}

/************************************//**
 * \brief Negative test case - wrong length
 ****************************************/
TEST_F(BoolExtractorTest, TestCheckContextRollback)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BOOLEAN;
    testArray[1] = 2;
    testArray[2] = 1;
    bool val = false;
    EXPECT_FALSE(fetch(ctx, val));
    ASSERT_FALSE(val);
    ASSERT_TRUE(checkTag(ctx, val));
}

/************************************//**
 * \brief Negative test case - wrong length
 ****************************************/
TEST_F(BoolExtractorTest, TestNegativeEmptyContext)
{
    std::array<unsigned char, 2> data;
    auto ctx = createFetchContext(data);
    data[0] = MMS::Tags::BOOLEAN;
    data[1] = 1;
    bool val = false;
    EXPECT_FALSE(fetch(ctx, val));
    ASSERT_FALSE(val);
}