//-----------------------------------------------------------------------------
// <copyright file="VarSizeBitStringEmitTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 08:09:02</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "BitStringEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::DataTypes;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class VarSizeBitStringEmitTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    VarSizeBitStringEmitTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(VarSizeBitStringEmitTest, Test0xFF)
{
    VarSizeBitString CUT(8);
    ASSERT_EQ(8, CUT.size());
    CUT.GetBitSet().set();
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(4, oldSize - newSize);
    EXPECT_EQ(0xff, testArray[127]);
    EXPECT_EQ(0, testArray[126]);
    EXPECT_EQ(2, testArray[125]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[124]);
}

/************************************//**
 * \brief Fourth test case
 ****************************************/
TEST_F(VarSizeBitStringEmitTest, Test0x108)
{
	VarSizeBitString CUT(9);
    CUT[3] = true;
    CUT[8] = true;
    ASSERT_EQ(9, CUT.size());
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(5, oldSize - newSize);
    EXPECT_EQ(0x80, testArray[127]);
    EXPECT_EQ(0x10, testArray[126]);
    EXPECT_EQ(7, testArray[125]);
    EXPECT_EQ(3, testArray[124]);
    ASSERT_EQ(MMS::Tags::BITSTRING, testArray[123]);
}
