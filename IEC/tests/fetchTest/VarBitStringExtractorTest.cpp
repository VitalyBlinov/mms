//-----------------------------------------------------------------------------
// <copyright file="VarBitStringExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 08:20:47</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <cmath>
#include "BitStringExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "VarSizeBitString.h"
#include "MMSTags.h"

using namespace MMS::Extractors;
using namespace MMS::DataTypes;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class VarBitStringExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    VarBitStringExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VarBitStringExtractorTest, TestExtractSevenBits)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 2;
    testArray[2] = 1;
    testArray[3] = 0xFE;
    VarSizeBitString CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    EXPECT_EQ(7, CUT.size());
    EXPECT_EQ(true, CUT[0]);
    EXPECT_EQ(true, CUT[1]);
    EXPECT_EQ(true, CUT[2]);
    EXPECT_EQ(true, CUT[3]);
    EXPECT_EQ(true, CUT[4]);
    EXPECT_EQ(true, CUT[5]);
    EXPECT_EQ(true, CUT[6]);
}

/************************************//**
 * \brief Another test case
 ****************************************/
TEST_F(VarBitStringExtractorTest, TestExtract13Bits)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 3;
    testArray[2] = 3;
    testArray[3] = 0x81;
    testArray[4] = 0x48;
    VarSizeBitString CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    EXPECT_EQ(13, CUT.size());
    EXPECT_EQ(true, CUT[0]);
    EXPECT_EQ(false, CUT[1]);
    EXPECT_EQ(false, CUT[2]);
    EXPECT_EQ(true, CUT[7]);
    EXPECT_EQ(true, CUT[9]);
    EXPECT_EQ(true, CUT[12]);
}

/************************************//**
 * \brief Another test case
 ****************************************/
TEST_F(VarBitStringExtractorTest, ComparisonTestCase)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 3;
    testArray[2] = 3;
    testArray[3] = 0x81;
    testArray[4] = 0x48;
    VarSizeBitString CUT;
    EXPECT_TRUE(fetch(ctx, CUT));
    EXPECT_EQ(13, CUT.size());
    FixedSizeBitString<13> CUT2;
    ctx = createFetchContext(testArray);
    EXPECT_TRUE(fetch(ctx, CUT2));

    ASSERT_EQ(CUT, CUT2);
}
