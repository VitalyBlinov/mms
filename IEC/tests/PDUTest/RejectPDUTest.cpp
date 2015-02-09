//-----------------------------------------------------------------------------
// <copyright file="RejectPDUTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 07:14:13</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "RejectPDU.h"
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
class RejectPDUTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    RejectPDUTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(RejectPDUTest, TestEmit)
{
    MMS::PDU::Reject Req;
    Req.originalInvokeID = 1024;
    Req.Reason.choice = MMS::PDU::Reject::rejectReason::id_confirmed_errorPDU;
    Req.Reason.confirmed_errorPDU = MMS::PDU::Reject::rejectReason::class_confirmed_errorPDU::invalid_serviceError;

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(9, offset);
    EXPECT_EQ(0x20, testArray[testArray.size() - offset--]);
    EXPECT_EQ(7, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]);
    EXPECT_EQ(2, testArray[testArray.size() - offset--]);
    EXPECT_EQ(4, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x83, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
}

TEST_F(RejectPDUTest, TestEmitReason)
{
    MMS::PDU::Reject::rejectReason Res;
    Res.choice = MMS::PDU::Reject::rejectReason::id_confirmed_errorPDU;
    Res.confirmed_errorPDU = MMS::PDU::Reject::rejectReason::class_confirmed_errorPDU::invalid_serviceError;

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Res);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(3, offset);
    EXPECT_EQ(0x83, testArray[testArray.size() - offset--]);
    EXPECT_EQ(1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(3, testArray[testArray.size() - offset--]);
}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(RejectPDUTest, TestEmitAndFetch)
{
    MMS::PDU::Reject Req;
    Req.originalInvokeID = 1024;
    Req.Reason.choice = MMS::PDU::Reject::rejectReason::id_confirmed_errorPDU;
    Req.Reason.confirmed_errorPDU = MMS::PDU::Reject::rejectReason::class_confirmed_errorPDU::invalid_serviceError;

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Reject Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(Req.originalInvokeID, Fetched.originalInvokeID);
    ASSERT_EQ(Req.Reason.choice, Req.Reason.choice);
    ASSERT_EQ(Req.Reason._value, Req.Reason._value);
}