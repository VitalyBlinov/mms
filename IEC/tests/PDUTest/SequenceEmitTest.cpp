//-----------------------------------------------------------------------------
// <copyright file="SequenceEmitTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/31 03:51:16</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Sequence emitter unit test
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

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class SequenceEmitTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    SequenceEmitTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(SequenceEmitTest, TestEmitAndFetchAFewStrings)
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

    auto newSize = getContextSize(result.first);

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    VisibleString<std::string> Fetched;
    EXPECT_TRUE(fetch(fetchContext, Fetched));
    EXPECT_EQ(std::string("First string"), static_cast<std::string>(Fetched));
    EXPECT_TRUE(fetch(fetchContext, Fetched));
    EXPECT_EQ(std::string("Second string"), static_cast<std::string>(Fetched));
    EXPECT_TRUE(fetch(fetchContext, Fetched));
    EXPECT_EQ(std::string("Third string"), static_cast<std::string>(Fetched));
    ASSERT_FALSE(fetch(fetchContext, Fetched));
}

TEST_F(SequenceEmitTest, TestEmitABitTooMany)
{
    std::vector<VisibleString<std::string>> testVector;
    for (int idx =0; idx != 100; ++idx)
    {
        testVector.push_back("this is a test string");
    }

    auto ctx = ExplicitEmitContextASN(createMMSExplicitContext(testArray));

    auto oldSize = getContextSize(ctx);

    auto result = emitSequence(ctx, testVector.begin(), testVector.end());
    EXPECT_TRUE(testVector.end() != result.second);
    EXPECT_NE(0, oldSize - getContextSize(result.first));
}
