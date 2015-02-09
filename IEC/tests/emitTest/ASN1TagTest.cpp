//-----------------------------------------------------------------------------
// <copyright file="ASN1TagTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/24 00:50:30</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "ASN1Tag.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "ContextMisc.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using namespace ASN1;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class ASN1TagTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    ASN1TagTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(ASN1TagTest, TestEmitShortForm)
{
    auto ctx = createMMSExplicitContext(testArray);

    TagValue CUT(12, TagValue::CONSTRUCTED | TagValue::CONTEXT);

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    
    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    ASSERT_EQ(0xAC,testArray[testArray.size() - offset]);
}

TEST_F(ASN1TagTest, TestEmit30)
{
    auto ctx = createMMSExplicitContext(testArray);

    TagValue CUT(30, TagValue::CONSTRUCTED | TagValue::CONTEXT);

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    ASSERT_EQ(0xBE,testArray[testArray.size() - offset]);
}

TEST_F(ASN1TagTest, TestEmit31)
{
    auto ctx = createMMSExplicitContext(testArray);

    TagValue CUT(31, TagValue::CONSTRUCTED | TagValue::CONTEXT);

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(2, offset);
    ASSERT_EQ(0xBF,testArray[testArray.size() - offset--]);
    ASSERT_EQ(0x1F,testArray[testArray.size() - offset--]);
}

TEST_F(ASN1TagTest, TestEmit1024)
{
    auto ctx = createMMSExplicitContext(testArray);

    TagValue CUT(1024, TagValue::CONSTRUCTED | TagValue::CONTEXT);

    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(3, offset);
    ASSERT_EQ(0xBF,testArray[testArray.size() - offset--]);
    ASSERT_EQ(0x88,testArray[testArray.size() - offset--]);
    ASSERT_EQ(0x0,testArray[testArray.size() - offset--]);
}

TEST_F(ASN1TagTest, TestCheckShortForm)
{
    auto ctx = createContext<ImplicitFetchContextASN>(testArray);

    TagValue CUT;

    testArray[0] = 0xAC;

    auto oldSize = getContextSize(ctx);
    ASSERT_TRUE(extract(ctx, CUT));
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    ASSERT_EQ(TagValue(12, TagValue::CONSTRUCTED | TagValue::CONTEXT), CUT);
}

TEST_F(ASN1TagTest, TestFetch30)
{
    auto ctx = createContext<ImplicitFetchContextASN>(testArray);

    TagValue CUT;

    testArray[0] = 0xBE;

    auto oldSize = getContextSize(ctx);
    ASSERT_TRUE(extract(ctx, CUT));
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    ASSERT_EQ(TagValue(30, TagValue::CONSTRUCTED | TagValue::CONTEXT), CUT);
}

TEST_F(ASN1TagTest, TestFetch31)
{
    auto ctx = createContext<ImplicitFetchContextASN>(testArray);

    TagValue CUT;

    testArray[0] = 0xBF;
    testArray[1] = 0x1F;

    auto oldSize = getContextSize(ctx);
    ASSERT_TRUE(extract(ctx, CUT));
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(2, offset);
    EXPECT_EQ(31, CUT.getValue());
    EXPECT_EQ(TagValue::CONSTRUCTED | TagValue::CONTEXT, CUT.getFlags());
    ASSERT_TRUE(TagValue(31, TagValue::CONSTRUCTED | TagValue::CONTEXT) ==  CUT);
}

TEST_F(ASN1TagTest, TestFetch1024)
{
    auto ctx = createContext<ImplicitFetchContextASN>(testArray);

    TagValue CUT;

    testArray[0] = 0xBF;
    testArray[1] = 0x88;
    testArray[2] = 0x0;

    auto oldSize = getContextSize(ctx);
    ASSERT_TRUE(extract(ctx, CUT));
    auto newSize = getContextSize(ctx);

    auto offset = oldSize - newSize;

    ASSERT_EQ(3, offset);
    EXPECT_EQ(1024, CUT.getValue());
    EXPECT_EQ(TagValue::CONSTRUCTED | TagValue::CONTEXT, CUT.getFlags());
    ASSERT_TRUE(TagValue(1024, TagValue::CONSTRUCTED | TagValue::CONTEXT) ==  CUT);

}