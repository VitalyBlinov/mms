//-----------------------------------------------------------------------------
// <copyright file="InitiateRequestPDUTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/11 11:10:28</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "serialization.h"
#include "InitiateRequestPDU.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "MMSTags.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class InitiateRequestPDUTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    InitiateRequestPDUTest()
    {
        testArray.fill(0);
    }

};


/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(InitiateRequestPDUTest, TestDefaultEmit)
{
    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(31, offset);
    EXPECT_EQ(offset-1, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Optional field is expected to be skipped";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter";
    EXPECT_EQ(0x82, testArray[testArray.size() - offset--]) << "Optional field 0x82";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter";
}

TEST_F(InitiateRequestPDUTest, TestExplicitEmit)
{
    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(32, offset);
    EXPECT_EQ(0x20, testArray[testArray.size() - offset--]) << "Constructed tag expected";
    EXPECT_EQ(offset-1, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Optional field is expected to be skipped";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter";
    EXPECT_EQ(0x82, testArray[testArray.size() - offset--]) << "Optional field 0x82";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Proposed parameter";
}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(InitiateRequestPDUTest, TestNotSoDefaultEmit)
{
    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    Req.localDetailCalling = 65000;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(36, offset);
    EXPECT_EQ(offset, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Optional field is expected to be present";
    EXPECT_EQ(3, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xfd, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xe8, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Next field must start here";
    EXPECT_EQ(0x1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x82, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x1, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xA4, testArray[testArray.size() - offset--]) << "Tag must represent constructed type!";

}

/************************************//**
 * \brief Emit and fetch test case!
 ****************************************/
TEST_F(InitiateRequestPDUTest, EmitAndFetch)
{
    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    Req.localDetailCalling = 65000;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(36, offset);
    EXPECT_EQ(offset, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Optional field is expected to be present";
    EXPECT_EQ(3, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xfd, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xe8, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Next field must start here";

    auto fetchCtx = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));
    PDU::InitiateRequest Extracted;
    EXPECT_TRUE(fetch(fetchCtx, Extracted));
    EXPECT_EQ(Req.localDetailCalling, Extracted.localDetailCalling);
    EXPECT_EQ(Req.proposedDataStructureNestingLevel, Extracted.proposedDataStructureNestingLevel);
    EXPECT_EQ(Req.proposedMaxServicesOutstandingCalled, Extracted.proposedMaxServicesOutstandingCalled);
    EXPECT_EQ(Req.proposedMaxServicesOutstandingCalling, Extracted.proposedMaxServicesOutstandingCalling);
    EXPECT_EQ(Req.initiateRequestDetails.proposedParametersCBB, Extracted.initiateRequestDetails.proposedParametersCBB);
    
}


/************************************//**
 * \brief Negative fetch test case - fetch context is truncated
 ****************************************/
TEST_F(InitiateRequestPDUTest, EmitAndFetch_NEG)
{
    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    Req.localDetailCalling = 65000;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(36, offset);
    EXPECT_EQ(offset, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Optional field is expected to be present";
    EXPECT_EQ(3, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xfd, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xe8, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Next field must start here";

    auto fetchCtx = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.begin()+newSize+3));
    oldSize = getContextSize(fetchCtx);
    PDU::InitiateRequest Extracted;
    ASSERT_FALSE(fetch(fetchCtx, Extracted));
    ASSERT_EQ(oldSize, getContextSize(fetchCtx));
}

/************************************//**
 * \brief Negative fetch test case - wrong tag value
 ****************************************/
TEST_F(InitiateRequestPDUTest, EmitAndFetch_NEG_wrongTag)
{
    auto ctx = ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    PDU::InitiateRequest Req;
    Req.localDetailCalling = 65000;
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(36, offset);
    EXPECT_EQ(offset, testArray[testArray.size() - offset--]) << "Size! Size! Size?!";
    testArray[testArray.size() - offset-1] = 0x12;              // Modify  the tag
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Optional field is expected to be present";
    EXPECT_EQ(3, testArray[testArray.size() - offset--]) << "Proposed parameter length!";
    EXPECT_EQ(0, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xfd, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0xe8, testArray[testArray.size() - offset--]);
    EXPECT_EQ(0x81, testArray[testArray.size() - offset--]) << "Next field must start here";

    auto fetchCtx = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));
    oldSize = getContextSize(fetchCtx);
    PDU::InitiateRequest Extracted;
    ASSERT_FALSE(fetch(fetchCtx, Extracted));
    ASSERT_EQ(oldSize, getContextSize(fetchCtx));
}