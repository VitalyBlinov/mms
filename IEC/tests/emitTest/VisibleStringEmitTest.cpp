//-----------------------------------------------------------------------------
// <copyright file="VisibleStringEmitTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/16 04:04:44</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <string>
#include "VisibleString.h"
#include "EmitContext.h"
#include "ContextMisc.h"
#include "MMSTags.h"
#include "VisibleStringEmitter.h"

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class VisibleStringEmitTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    VisibleStringEmitTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VisibleStringEmitTest, TestVisibleStringStandard)
{
	VisibleString<std::string> CUT(std::string("check this out!"));

    ASSERT_EQ(std::string("check this out!"), (std::string)CUT);
}


TEST_F(VisibleStringEmitTest, TestVisibleStringArray)
{
    std::string value("this is the test, this is the day!");

    std::array<char, 128> arr;
    std::copy(value.begin(), value.end(), arr.begin());

    VisibleString<std::array<char,128>> CUT(value.c_str(), value.length());

    EXPECT_EQ(std::string("this is the test, this is the day!"), (std::string)CUT);
}

TEST_F(VisibleStringEmitTest, TestVisibleStringArrayLength)
{
    std::string value("this is the test, this is the day!");

    std::array<char, 128> arr;
    std::copy(value.begin(), value.end(), arr.begin());

    VisibleString<std::array<char,128>> CUT(value.c_str(), value.length());

    EXPECT_EQ(std::string("this is the test, this is the day!"), (std::string)CUT);
    ASSERT_EQ(value.length(), CUT.length());
}

TEST_F(VisibleStringEmitTest, TestCheckCapacity)
{
    std::string value("this is the test, this is the day!");

    VisibleString<std::array<char,128>> CUT(value.c_str(), value.length());

    ASSERT_TRUE(CUT.checkCapacity(127));
    ASSERT_FALSE(CUT.checkCapacity(128));

    VisibleString<std::string> CUT2(value);

    ASSERT_TRUE(CUT2.checkCapacity(127));
    ASSERT_TRUE(CUT2.checkCapacity(128));
}

TEST_F(VisibleStringEmitTest, EmitFromArray)
{
    std::string value("testing...");

    VisibleString<std::array<char,128>> CUT(value.c_str(), value.length());

    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(12, oldSize - newSize);
    EXPECT_NE(0, testArray[127]);
    EXPECT_EQ(value, std::string(testArray.end() - value.length(), testArray.end()));
    EXPECT_EQ(value.length(), testArray[testArray.size() - value.length()-1]);
    ASSERT_EQ(MMS::Tags::VISIBLE_STRING, testArray[testArray.size() - value.length()-2]);
}

TEST_F(VisibleStringEmitTest, EmitWithASN1)
{
    std::string value("testing...");

    VisibleString<std::array<char,128>> CUT(value.c_str(), value.length());

    auto ctx = createContext<ExplicitEmitContextASN>(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(12, oldSize - newSize);
    EXPECT_NE(0, testArray[127]);
    EXPECT_EQ(value, std::string(testArray.end() - value.length(), testArray.end()));
    EXPECT_EQ(value.length(), testArray[testArray.size() - value.length()-1]);
    ASSERT_EQ(ASN1::Tags::VISIBLE_STR, testArray[testArray.size() - value.length()-2]);
}

TEST_F(VisibleStringEmitTest, EmitFromString)
{
    std::string value("testing...");

    VisibleString<std::string> CUT(value.c_str(), value.length());

    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(12, oldSize - newSize);
    EXPECT_NE(0, testArray[127]);
    EXPECT_EQ(value, std::string(testArray.end() - value.length(), testArray.end()));
    EXPECT_EQ(value.length(), testArray[testArray.size() - value.length()-1]);
    ASSERT_EQ(MMS::Tags::VISIBLE_STRING, testArray[testArray.size() - value.length()-2]);
}
