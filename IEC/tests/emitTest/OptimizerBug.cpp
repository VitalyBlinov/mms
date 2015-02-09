//-----------------------------------------------------------------------------
// <copyright file="OptimizerBug.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/23 17:17:38</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <string>
#include "EmitContext.h"
#include "FetchContext.h"
#include "ContextMisc.h"
#include "MMSTags.h"
#include "VisibleString.h"
#include "VisibleStringEmitter.h"
#include "serialization.h"


using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using namespace serialization;


typedef MMS::DataTypes::VisibleString<std::string> MyTestString;
struct TestStruc
{
    MyTestString blah;
};

PDU_EXPLICIT_FIELD(TestStruc, 0, TestStruc::blah);


std::size_t IamTheTest()
{
    std::array<unsigned char, 128> testArray;
    TestStruc Req;
    Req.blah = "testing...";

    auto ctx = createContext<ImplicitEmitContextASN>(testArray); //ImplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, Req);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    auto result = offset == 15;


    return offset;
// 
//     EXPECT_TRUE(result);
//     ASSERT_EQ(15, offset);
// 
//     auto fetchContext = ImplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));
// 
//     TestStruc Fetched;
//     EXPECT_TRUE(fetch(fetchContext, Fetched));
//     ASSERT_EQ(0, getContextSize(fetchContext));
// 
//     ASSERT_EQ(Req.blah, Fetched.blah);
}

/************************************//**
 * \brief Test fixture class
 ****************************************/
class OptimizerBug: public testing::Test
{
protected:
    //std::array<unsigned char, 128> testArray;
public:
    OptimizerBug()
    {
        //testArray.fill(0);
    }

};


/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(OptimizerBug, TestFirst)
{
    ASSERT_EQ(15, IamTheTest());
}
