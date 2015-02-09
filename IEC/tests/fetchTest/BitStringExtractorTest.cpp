//-----------------------------------------------------------------------------
// <copyright file="BitStringExtractorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/14 02:19:05</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <cmath>
#include "BitStringExtractor.h"
#include "FetchContext.h"
#include "TagExtractor.h"
#include "FixedSizeBitString.h"
#include "MMSTags.h"

using namespace MMS::Extractors;
using namespace MMS::DataTypes;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class BitStringExtractorTest: public testing::Test
{
protected:
    std::array<unsigned char, 128> testArray;
public:
    BitStringExtractorTest()
    {
        testArray.fill(0);
    }
};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(BitStringExtractorTest, TestWithVector)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 2;
    testArray[2] = 1;
    testArray[3] = 0xFE;
    std::vector<bool> _vect;
    EXPECT_TRUE(fetch(ctx, _vect));
    EXPECT_EQ(7, _vect.size());
    EXPECT_EQ(true, _vect[0]);
    EXPECT_EQ(true, _vect[1]);
    EXPECT_EQ(true, _vect[2]);
    EXPECT_EQ(true, _vect[3]);
    EXPECT_EQ(true, _vect[4]);
    EXPECT_EQ(true, _vect[5]);
    EXPECT_EQ(true, _vect[6]);
}

/************************************//**
 * \brief Test with FixedSizeBitString
 ****************************************/
TEST_F(BitStringExtractorTest, TestWithFixedSizeBitStringPositive)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 3;
    testArray[2] = 3;
    testArray[3] = 0x81;
    testArray[4] = 0x48;
    FixedSizeBitString<13> _vect;
    EXPECT_TRUE(fetch(ctx, _vect));
    EXPECT_EQ(true, _vect.GetBitSet()[0]);
    EXPECT_EQ(false, _vect.GetBitSet()[1]);
    EXPECT_EQ(false, _vect.GetBitSet()[2]);
    EXPECT_EQ(false, _vect.GetBitSet()[3]);
    EXPECT_EQ(false, _vect.GetBitSet()[4]);
    EXPECT_EQ(false, _vect.GetBitSet()[5]);
    EXPECT_EQ(false, _vect.GetBitSet()[6]);
    EXPECT_EQ(true, _vect.GetBitSet()[7]);
    EXPECT_EQ(false, _vect.GetBitSet()[8]);
    EXPECT_EQ(true, _vect.GetBitSet()[9]);
    EXPECT_EQ(false, _vect.GetBitSet()[10]);
    EXPECT_EQ(false, _vect.GetBitSet()[11]);
    EXPECT_EQ(true, _vect.GetBitSet()[12]);
}
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(BitStringExtractorTest, TestWithFixedSizeBitStringPositive2)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 3;
    testArray[2] = 3;
    testArray[3] = 0x81;
    testArray[4] = 0x48;
    FixedSizeBitString<14> _vect;
    EXPECT_TRUE(fetch(ctx, _vect));
    EXPECT_EQ(true, _vect.GetBitSet()[0]);
    EXPECT_EQ(false, _vect.GetBitSet()[1]);
    EXPECT_EQ(false, _vect.GetBitSet()[2]);
    EXPECT_EQ(false, _vect.GetBitSet()[3]);
    EXPECT_EQ(false, _vect.GetBitSet()[4]);
    EXPECT_EQ(false, _vect.GetBitSet()[5]);
    EXPECT_EQ(false, _vect.GetBitSet()[6]);
    EXPECT_EQ(true, _vect.GetBitSet()[7]);
    EXPECT_EQ(false, _vect.GetBitSet()[8]);
    EXPECT_EQ(true, _vect.GetBitSet()[9]);
    EXPECT_EQ(false, _vect.GetBitSet()[10]);
    EXPECT_EQ(false, _vect.GetBitSet()[11]);
    EXPECT_EQ(true, _vect.GetBitSet()[12]);
}

/************************************//**
 * \brief Negative test case - FixedSizeBitString is too small
 ****************************************/
TEST_F(BitStringExtractorTest, TestWithFixedSizeBitString_NEG)
{
    auto ctx = createFetchContext(testArray);
    testArray[0] = MMS::Tags::BITSTRING;
    testArray[1] = 3;
    testArray[2] = 3;
    testArray[3] = 0x81;
    testArray[4] = 0x48;
    FixedSizeBitString<12> _vect;
    ASSERT_FALSE(fetch(ctx, _vect));
}