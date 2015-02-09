//-----------------------------------------------------------------------------
// <copyright file="VisibleStringExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 13:33:50</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "VisibleString.h"
#include "VisibleStringExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "MMSTags.h"

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class VisibleStringExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    VisibleStringExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VisibleStringExtractorTest, ShortString)
{
    std::string value("My name is not Earl.");
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::VISIBLE_STRING;
    testArray[1] = value.length();
    std::copy(value.begin(), value.end(), testArray.begin() + 2);
    
    VisibleString<std::array<char, 128>> CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    ASSERT_EQ(value, (std::string)CUT);
}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VisibleStringExtractorTest, StringIsTooLongButWeStillStand)
{
    std::string value("My name is not Earl.");
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::VISIBLE_STRING;
    testArray[1] = value.length();
    std::copy(value.begin(), value.end(), testArray.begin() + 2);
    
    VisibleString<std::array<char, 8>> CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    ASSERT_EQ("My name", (std::string)CUT);
}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VisibleStringExtractorTest, ExtractToString)
{
    std::string value("My name is not Earl.");
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::VISIBLE_STRING;
    testArray[1] = value.length();
    std::copy(value.begin(), value.end(), testArray.begin() + 2);
    
    VisibleString<std::string> CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    ASSERT_EQ(value, (std::string)CUT);
}