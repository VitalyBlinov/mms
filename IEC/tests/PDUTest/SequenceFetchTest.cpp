//-----------------------------------------------------------------------------
// <copyright file="SequenceFetchTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/03 02:46:00</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Test for sequence fetch mechanism utilizing SequenceOf thingy
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <string>
#include "VisibleString.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "ContextMisc.h"
#include "MMSTags.h"
#include "VisibleStringEmitter.h"
#include "evaluator.h"
#include "SequenceOfEmitter.h"
#include "ExtractedSequenceOf.h"

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class SequenceFetchTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    SequenceFetchTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(SequenceFetchTest, TestFetchPositiveExplicit)
{
    std::vector<VisibleString<std::string>> testVector;
    testVector.push_back("First string");
    testVector.push_back("Second string");
    testVector.push_back("Third string");

    auto ctx = ExplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitSequence(ctx, testVector.begin(), testVector.end());
    EXPECT_EQ(testVector.end(), result.second);
    EXPECT_EQ(43, oldSize - getContextSize(result.first));

    // Okay, we have emitted sequence.

    auto newSize = getContextSize(result.first);

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    SequenceOf<decltype(fetchContext), VisibleStringBuffer> CUT(fetchContext);

    std::vector<VisibleString<std::string>> extractedVector;

    for (auto itr = CUT.begin(); itr != CUT.end(); ++itr)
    {
        extractedVector.push_back(*itr);
    }

    EXPECT_EQ(testVector.size(), extractedVector.size());
    EXPECT_TRUE(testVector == extractedVector);

    for (unsigned int idx = 0; idx != testVector.size(); ++idx)
    {
        EXPECT_EQ(testVector[idx], extractedVector[idx]);
    }
}

TEST_F(SequenceFetchTest, TestFetchPositiveSkipWrongItems)
{
    std::vector<VisibleString<std::string>> testVector;
    testVector.push_back("First string");
    testVector.push_back("Second string");
    testVector.push_back("Third string");

    auto ctx = ExplicitEmitContextASN(createMMSExplicitContext(testArray));

    ctx = emit(ctx, (int)223);



    auto result = emitSequence(ctx, testVector.begin(), testVector.end());
    EXPECT_EQ(testVector.end(), result.second);

    ctx = emit(result.first, (unsigned)65234);


    // Okay, we have emitted sequence.

    auto newSize = getContextSize(ctx);

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    SequenceOf<decltype(fetchContext), VisibleStringBuffer> CUT(fetchContext);

    std::vector<VisibleString<std::string>> extractedVector;

    for (auto itr = CUT.begin(); itr != CUT.end(); ++itr)
    {
        extractedVector.push_back(*itr);
    }

    EXPECT_EQ(testVector.size(), extractedVector.size());
    EXPECT_TRUE(testVector == extractedVector);
}


TEST_F(SequenceFetchTest, TestFetchEmpty_NEG)
{
    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin(), testArray.begin()));

    SequenceOf<decltype(fetchContext), VisibleStringBuffer> CUT(fetchContext);

    std::vector<VisibleString<std::string>> extractedVector;

    for (auto itr = CUT.begin(); itr != CUT.end(); ++itr)
    {
        extractedVector.push_back(*itr);
    }

    ASSERT_EQ(0, extractedVector.size());
}

TEST_F(SequenceFetchTest, TestFetchWrongTags_NEG)
{
    std::vector<VisibleString<std::string>> testVector;
    testVector.push_back("First string");
    testVector.push_back("Second string");
    testVector.push_back("Third string");

    auto ctx = ExplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitSequence(ctx, testVector.begin(), testVector.end());
    EXPECT_EQ(testVector.end(), result.second);
    EXPECT_EQ(43, oldSize - getContextSize(result.first));

    // Okay, we have emitted sequence.

    auto newSize = getContextSize(result.first);

    auto fetchContext = ExplicitFetchContextMMS(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    SequenceOf<decltype(fetchContext), VisibleStringBuffer> CUT(fetchContext);

    std::vector<VisibleString<std::string>> extractedVector;

    for (auto itr = CUT.begin(); itr != CUT.end(); ++itr)
    {
        extractedVector.push_back(*itr);
    }

    EXPECT_EQ(0, extractedVector.size());
}