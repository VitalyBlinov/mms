//-----------------------------------------------------------------------------
// <copyright file="ConcludePDUTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 06:18:58</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "ConcludePDU.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "serialization.h"
using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using namespace MMS::PDU;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class ConcludePDUTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    ConcludePDUTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief Emitter test case
 ****************************************/
TEST_F(ConcludePDUTest, TestEmitRequest)
{
    MMS::PDU::ConcludeRequest Req;

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
}

TEST_F(ConcludePDUTest, TestEmitResponse)
{
    MMS::PDU::ConcludeResponse Req;

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
}

/************************************//**
 * \brief Emitter test case
 ****************************************/
TEST_F(ConcludePDUTest, TestEmitFetchRequest)
{
    MMS::PDU::ConcludeRequest Req;

    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(1, offset);

    auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    EXPECT_TRUE(fetch(fetchContext, Req));
    ASSERT_EQ(0, getContextSize(fetchContext));
}

/************************************//**
 * \brief Emitter test case
 ****************************************/
TEST_F(ConcludePDUTest, TestEmitFetchRequestExplicit)
{
    MMS::PDU::ConcludeRequest Req;

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(2, offset);
    ASSERT_EQ(ASN1::Tags::_NULL, testArray[testArray.size() - offset--]);

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    EXPECT_TRUE(fetch(fetchContext, Req));
    ASSERT_EQ(0, getContextSize(fetchContext));
}