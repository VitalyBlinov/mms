//-----------------------------------------------------------------------------
// <copyright file="GetNameListResponseTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/13 00:45:50</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>

#include "GetNameListResponse.h"
#include "serialization.h"
#include "InitiateRequestPDU.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "MMSTags.h"
#include "VisibleString.h"

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class GetNameListResponseTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    GetNameListResponseTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(GetNameListResponseTest, EmitTest)
{
    std::vector<std::string> NameList;
    NameList.push_back("First string");
    NameList.push_back("Second string");
    NameList.push_back("Third string");

    auto ctx = ImplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitNameList(ctx, NameList.begin(), NameList.end());
    EXPECT_EQ(NameList.end(), result.second);
    auto newSize = getContextSize(result.first);
    auto offset = oldSize - newSize;

    
    ASSERT_EQ(49, offset);
    EXPECT_EQ(48, testArray[testArray.size() - offset--]) << "Size!";
    EXPECT_EQ(0xa0, testArray[testArray.size() - offset--]) << "Incorrect tag";
    EXPECT_EQ(43, testArray[testArray.size() - offset--]) << "Incorrect size";
    EXPECT_EQ(0x1a, testArray[testArray.size() - offset--]) << "Expected string tag";


    EXPECT_EQ(0x81, testArray[testArray.size() - 3]) << "Expected boolean tag";
    EXPECT_EQ(0x1, testArray[testArray.size() - 2]) << "Expected boolean tag of one byte";
    EXPECT_EQ(0x0, testArray[testArray.size() - 1]) << "Expected boolean tag of one byte and set to false";
}

TEST_F(GetNameListResponseTest, FetchTest)
{
    std::vector<std::string> NameList;
    NameList.push_back("First string");
    NameList.push_back("Second string");
    NameList.push_back("Third string");

    auto ctx = ImplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitNameList(ctx, NameList.begin(), NameList.end());
    EXPECT_EQ(NameList.end(), result.second);
    auto newSize = getContextSize(result.first);
    auto offset = oldSize - newSize;


    ASSERT_EQ(49, offset);

    auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Confirmed::GetNameListExtracted<decltype(fetchContext)> CUT;

    ASSERT_TRUE(fetch(fetchContext, CUT));

    std::vector<std::string> extractedNames;

    for (auto itr = CUT.extractedSequence.begin(); itr != CUT.extractedSequence.end(); ++itr)
    {
        extractedNames.push_back(*itr);
    }

    EXPECT_EQ(NameList.size(), extractedNames.size());
    EXPECT_TRUE(NameList == extractedNames);
    EXPECT_FALSE(CUT.moreFollows);
}

TEST_F(GetNameListResponseTest, EmitAndFetchAlot)
{
    std::vector<std::string> NameList(1024);

    int idx = 0;
    for (auto itr = NameList.begin(); itr != NameList.end(); ++itr, ++idx)
    {
        std::stringstream sStream;
        sStream << "String number " << idx;
        *itr = sStream.str();
    }

    auto ctx = ImplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitNameList(ctx, NameList.begin(), NameList.end());
    EXPECT_NE(NameList.end(), result.second);
    auto emitEnd = result.second;
    auto newSize = getContextSize(result.first);
    auto offset = oldSize - newSize;



    auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Confirmed::GetNameListExtracted<decltype(fetchContext)> CUT;

    ASSERT_TRUE(fetch(fetchContext, CUT));

    std::vector<std::string> extractedNames;

    for (auto itr = CUT.extractedSequence.begin(); itr != CUT.extractedSequence.end(); ++itr)
    {
        extractedNames.push_back(*itr);
    }
    
    EXPECT_EQ(emitEnd - NameList.begin(), extractedNames.size());
    EXPECT_TRUE(std::vector<std::string>(NameList.begin(), emitEnd) == extractedNames);
    EXPECT_TRUE(CUT.moreFollows);
}