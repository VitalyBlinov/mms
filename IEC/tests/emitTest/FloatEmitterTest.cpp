//-----------------------------------------------------------------------------
// <copyright file="FloatEmitterTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/10 01:01:50</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "FloatEmitter.h"
#include "EmitContext.h"
#include "MMSTags.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class FloatEmitterTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    FloatEmitterTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(FloatEmitterTest, TestEmitEmpty)
{
    auto ctx = createMMSExplicitContext(testArray);
    emit(ctx, (float)0);
    ASSERT_EQ(0, testArray[127]);
    ASSERT_EQ(0, testArray[126]);
    ASSERT_EQ(0, testArray[125]);
    ASSERT_EQ(0, testArray[124]);
    ASSERT_EQ(0x80, testArray[123]);
    ASSERT_EQ(5, testArray[122]);
    ASSERT_EQ(MMS::Tags::FLOAT, testArray[121]);
}
