//-----------------------------------------------------------------------------
// <copyright file="octetStringEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/02/14 00:10:57</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <vector>
#include "ASN1Tag.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "ContextMisc.h"
#include "OctetStringExt.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::DataTypes;
using namespace MMS::Extractors;
using namespace ASN1;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class octetStringEmitterTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    octetStringEmitterTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(octetStringEmitterTest, TestEmitVector)
{
    auto ctx = createMMSExplicitContext(testArray);

    std::vector<unsigned char> CUT(32);
    unsigned char counter = 0;
    for (auto it = CUT.begin(); it != CUT.end(); ++it, ++counter)
    {
        *it = counter;
    }

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(34, offset);
    EXPECT_EQ(MMS::Tags::OCTET_STRING, testArray[testArray.size() - offset--]);
    EXPECT_EQ(32, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(2, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
    EXPECT_EQ(4, testArray[testArray.size() - offset--]);
    EXPECT_EQ(5, testArray[testArray.size() - offset--]);
    EXPECT_EQ(6, testArray[testArray.size() - offset--]);
    EXPECT_EQ(7, testArray[testArray.size() - offset--]);
}

TEST_F(octetStringEmitterTest, TestEmitArray)
{
    auto ctx = createMMSExplicitContext(testArray);

    std::array<unsigned char, 32> CUT;
    unsigned char counter = 0;
    for (auto it = CUT.begin(); it != CUT.end(); ++it, ++counter)
    {
        *it = counter;
    }

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(34, offset);
    EXPECT_EQ(MMS::Tags::OCTET_STRING, testArray[testArray.size() - offset--]);
    EXPECT_EQ(32, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(2, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
    EXPECT_EQ(4, testArray[testArray.size() - offset--]);
    EXPECT_EQ(5, testArray[testArray.size() - offset--]);
    EXPECT_EQ(6, testArray[testArray.size() - offset--]);
    EXPECT_EQ(7, testArray[testArray.size() - offset--]);
}

TEST_F(octetStringEmitterTest, TestEmitLost)
{
    auto ctx = createMMSExplicitContext(testArray);

    std::list<unsigned char> CUT(32);
    unsigned char counter = 0;
    for (auto it = CUT.begin(); it != CUT.end(); ++it, ++counter)
    {
        *it = counter;
    }

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(34, offset);
    EXPECT_EQ(MMS::Tags::OCTET_STRING, testArray[testArray.size() - offset--]);
    EXPECT_EQ(32, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(2, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
    EXPECT_EQ(4, testArray[testArray.size() - offset--]);
    EXPECT_EQ(5, testArray[testArray.size() - offset--]);
    EXPECT_EQ(6, testArray[testArray.size() - offset--]);
    EXPECT_EQ(7, testArray[testArray.size() - offset--]);
}

TEST_F(octetStringEmitterTest, TestEmitOctetStringExtracted)
{
    auto ctx = createMMSExplicitContext(testArray);

    std::array<unsigned char, 32> buffer;
    unsigned char counter = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it, ++counter)
    {
        *it = counter;
    }

    OctetStringBuffer CUT = {buffer.data(), buffer.size()};

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(34, offset);
    EXPECT_EQ(MMS::Tags::OCTET_STRING, testArray[testArray.size() - offset--]);
    EXPECT_EQ(32, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(2, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
    EXPECT_EQ(4, testArray[testArray.size() - offset--]);
    EXPECT_EQ(5, testArray[testArray.size() - offset--]);
    EXPECT_EQ(6, testArray[testArray.size() - offset--]);
    EXPECT_EQ(7, testArray[testArray.size() - offset--]);
}
