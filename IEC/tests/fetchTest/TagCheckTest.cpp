//-----------------------------------------------------------------------------
// <copyright file="TagCheckTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/12 22:44:04</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "TagExtractor.h"
#include "FetchContext.h"
#include "MMSTags.h"

using namespace MMS::Extractors;
using namespace MMS::Extractors::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class TagCheckTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    TagCheckTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(TagCheckTest, TestPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = 0x83;
    bool b = false;
    ASSERT_TRUE(checkTag(ctx, b));
}

/************************************//**
 * \brief First negative test case
 ****************************************/
TEST_F(TagCheckTest, TestNegative)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = 0x81;
    bool b = false;
    ASSERT_FALSE(checkTag(ctx, b));
}

/************************************//**
 * \brief Second negative test case
 ****************************************/
TEST_F(TagCheckTest, TestNegativeEndOfContext)
{
    std::array<unsigned char, 1> shortArray;
    auto ctx = createFetchContext(shortArray);
    shortArray[0] = 0x83;
    bool b = false;
    EXPECT_TRUE(checkTag(ctx, b));
    ASSERT_FALSE(checkTag(ctx, b));
}

/************************************//**
 * \brief Positive test case for no tag array
 ****************************************/
TEST_F(TagCheckTest, TestPositiveNoTagArray)
{
    auto ctx = createNoTagFetchContext(testArray);
    testArray[0] = 0x83;
    bool b = false;
    EXPECT_TRUE(checkTag(ctx, b));
    unsigned char extracted = 0;
    EXPECT_TRUE(fetchOctet(ctx, extracted));
    EXPECT_EQ(0x83, extracted);
    EXPECT_TRUE(fetchOctet(ctx, extracted));
    EXPECT_EQ(0, extracted);
    ASSERT_TRUE(checkTag(ctx, b));
}