//-----------------------------------------------------------------------------
// <copyright file="EmitOctetTest.h" company="Six Carrots Software">
//      Copyright (c) 2014 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2014/12/27 19:34:10</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "EmitOctet.h"
#include "EmitContext.h"

using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Emit octet test fixture
 ****************************************/
class EmitOctetTest: public testing::Test
{
protected:
    unsigned char testArea[128];
public:
    EmitOctetTest()
    {
        memset(testArea, 0, sizeof(testArea));
    }

};

TEST_F(EmitOctetTest, TestConstructEmitContext)
{
    ExplicitEmitContextMMS CUT(testArea, sizeof(testArea));
}

TEST_F(EmitOctetTest, TestEmitOctetDirectly)
{
    ExplicitEmitContextMMS CUT(testArea, sizeof(testArea));
    ASSERT_EQ((unsigned char)0, testArea[127]);
    ASSERT_TRUE(CUT.emitOctet(123));
    ASSERT_EQ((unsigned char)123, testArea[127]);
}

TEST_F(EmitOctetTest, TestEmitOctetUsingWraper)
{
    ExplicitEmitContextMMS CUT(testArea, sizeof(testArea));
    ASSERT_EQ((unsigned char)0, testArea[127]);
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ((unsigned char)23, testArea[127]);
}

TEST_F(EmitOctetTest, TestEmitOctetUsingWraperTwice)
{
    ExplicitEmitContextMMS CUT(testArea, sizeof(testArea));
    ASSERT_EQ((unsigned char)0, testArea[127]);
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ((unsigned char)23, testArea[127]);
    ASSERT_EQ((unsigned char)0, testArea[126]);
    CUT = emitOctet(CUT, 213);
    ASSERT_EQ((unsigned char)213, testArea[126]);
}

TEST_F(EmitOctetTest, TestUsingHelperFunctionPodArray)
{
    auto CUT = createMMSExplicitContext(testArea);
    ASSERT_EQ((unsigned char)0, testArea[127]);
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ((unsigned char)23, testArea[127]);
    ASSERT_EQ((unsigned char)0, testArea[126]);
    CUT = emitOctet(CUT, 213);
    ASSERT_EQ((unsigned char)213, testArea[126]);
}

TEST_F(EmitOctetTest, TestUsingHelperFunctionVector)
{
    std::vector<unsigned char> testVec(128);
    auto CUT = createMMSExplicitContext(testVec);
    ASSERT_EQ((unsigned char)0, testVec[127]);
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ((unsigned char)23, testVec[127]);
}

TEST_F(EmitOctetTest, TestUsingHelperFunctionStdArray)
{
    std::array<unsigned char, 128> testArray;
    testArray.fill(0);
    auto CUT = createMMSExplicitContext(testArray);
    ASSERT_EQ((unsigned char)0, testArray[127]);
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ((unsigned char)23, testArray[127]);
}

TEST_F(EmitOctetTest, TestNegativeEmptyVector)
{
    std::vector<unsigned char> testVec;
    auto CUT = createMMSExplicitContext(testVec);
    ASSERT_EQ(0, CUT.GetMissingOctetsCount());
    CUT = emitOctet(CUT, 23);
    ASSERT_EQ(1, CUT.GetMissingOctetsCount());
}