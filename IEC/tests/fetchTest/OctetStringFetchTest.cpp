//-----------------------------------------------------------------------------
// <copyright file="OctetStringFetchTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/14 00:50:11</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <cmath>
#include "OctetStringExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "FixedSizeBitString.h"
#include "MMSTags.h"

using namespace MMS::Extractors;
using namespace MMS::DataTypes;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class OctetStringFetchTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
    ExplicitFetchContextMMS Ctx;
public:
    OctetStringFetchTest()
    {
        testArray.fill(0);
        char counter = 0;
        auto it = testArray.begin();
        *it++ = MMS::Tags::OCTET_STRING;
        *it++ = 32;
        for (; it != testArray.begin() + 34; ++it, ++counter)
        {
            *it = counter;
        }
        Ctx = createFetchContext(testArray);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(OctetStringFetchTest, VectorExtract)
{
	std::vector<unsigned char> Extracted;
    ASSERT_TRUE(fetch(Ctx, Extracted));
    EXPECT_EQ(32, Extracted.size());
    EXPECT_EQ(0, Extracted[0]);
    EXPECT_EQ(1, Extracted[1]);
    EXPECT_EQ(31, Extracted[31]);
}

TEST_F(OctetStringFetchTest, ArrayExtract)  // Fails
{
    FAIL() << "fix me or remove me, extracting octet strings as arrays may be redundant";
//     std::array<unsigned char, 32> Extracted;
//     ASSERT_TRUE(fetch(Ctx, Extracted));
//     EXPECT_EQ(0, Extracted[0]);
//     EXPECT_EQ(1, Extracted[1]);
//     EXPECT_EQ(31, Extracted[31]);
}

TEST_F(OctetStringFetchTest, ListExtract)
{
    std::list<unsigned char> Extracted;
    ASSERT_TRUE(fetch(Ctx, Extracted));
    EXPECT_EQ(32, Extracted.size());
    auto it = Extracted.begin();
    EXPECT_EQ(0, *it++);
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(2, *it++);
}

TEST_F(OctetStringFetchTest, OctetStringBuffer)
{
    OctetStringBuffer Extracted;
    ASSERT_TRUE(fetch(Ctx, Extracted));
    EXPECT_EQ(32, Extracted.length);
    auto it = Extracted.pPtr;
    EXPECT_EQ(0, *it++);
    EXPECT_EQ(1, *it++);
    EXPECT_EQ(2, *it++);
}