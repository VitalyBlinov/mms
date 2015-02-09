//-----------------------------------------------------------------------------
// <copyright file="ObjectNameTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/18 07:46:06</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "ObjectName.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "serialization.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class ObjectNameTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    ObjectNameTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief Emit positive test case
 ****************************************/
TEST_F(ObjectNameTest, TestEmitDomainSpecific)
{
	MMS::PDU::Elements::Details::Domain_specific<std::string> CUT;
    CUT.domainId = "domain";
    CUT.itemId = "item";

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(16, offset);
    EXPECT_EQ(0x20, testArray[testArray.size() - offset--]) << "Size";
    EXPECT_EQ(offset-1, testArray[testArray.size() - offset--]) << "Correct ASN1 visible string tag expected";
    EXPECT_EQ(0x1a, testArray[testArray.size() - offset--]) << "Correct string tag expected";
    EXPECT_EQ(6, testArray[testArray.size() - offset--]) << "length";
    EXPECT_EQ('d', testArray[testArray.size() - offset--]);
    EXPECT_EQ('o', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('a', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('i', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('n', testArray[testArray.size() - offset--]); 
    EXPECT_EQ(0x1A, testArray[testArray.size() - offset--]) << "Correct ASN1 visible string tag expected";
    EXPECT_EQ(4, testArray[testArray.size() - offset--]) << "length";
    EXPECT_EQ('i', testArray[testArray.size() - offset--]);
    EXPECT_EQ('t', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('e', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 

}

/************************************//**
 * \brief Fetch positive test case
 ****************************************/
TEST_F(ObjectNameTest, TestEmitAndFetchDomainSpecific)
{
	MMS::PDU::Elements::Details::Domain_specific<std::string> CUT;
    CUT.domainId = "domain";
    CUT.itemId = "item";

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, CUT);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(16, offset);

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Elements::Details::Domain_specific<std::string> Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(CUT.domainId, Fetched.domainId);
    ASSERT_EQ(CUT.itemId, Fetched.itemId);
}


/************************************//**
 * \brief Fetch positive test case
 ****************************************/
TEST_F(ObjectNameTest, TestEmitObjectNameVMD)
{
	MMS::PDU::Elements::ObjectName<std::string> CUT;
    CUT.choice = MMS::PDU::Elements::ObjectName<std::string>::id_vmd_specific;
    CUT.vmd_specific = "some vmd specific stuff";


    auto original = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(original);
    auto ctx(emit(original, CUT));

    auto newSize = ctx.GetContextSize();

    auto offset = oldSize - newSize;

    EXPECT_EQ(25, offset);
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Incorrect tagg!!!";
    EXPECT_EQ(CUT.vmd_specific.length(), testArray[testArray.size() - offset--]) << "Length of the data: length of the string+tag (1 byte)";
    //EXPECT_EQ(CUT.vmd_specific.length(), testArray[testArray.size() - offset--]);
    EXPECT_EQ('s', testArray[testArray.size() - offset--]);
    EXPECT_EQ('o', testArray[testArray.size() - offset--]);
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('e', testArray[testArray.size() - offset--]); 
    EXPECT_EQ(' ', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('v', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Elements::ObjectName<std::array<char, 128>> Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(CUT.choice, Fetched.choice);
    ASSERT_EQ(CUT.vmd_specific, Fetched.vmd_specific);

    ctx = emit(ctx, (int)100);
}

/************************************//**
 * \brief Fetch positive test case
 ****************************************/
TEST_F(ObjectNameTest, TestEmitObjectNameAASpecific)
{
	MMS::PDU::Elements::ObjectName<std::string> CUT;
    CUT.aa_specific = "some vmd specific stuff";
    CUT.choice = MMS::PDU::Elements::ObjectName<std::string>::id_aa_specific;

    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ctx = std::move(emit(ctx, CUT));
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    EXPECT_EQ(25, offset);
    EXPECT_EQ(0x82, testArray[testArray.size() - offset--]) << "Incorrect tagg!!!";
    EXPECT_EQ(CUT.aa_specific.length(), testArray[testArray.size() - offset--]) << "Length of the data: length of the string+tag (1 byte)";
    //EXPECT_EQ(CUT.vmd_specific.length(), testArray[testArray.size() - offset--]);
    EXPECT_EQ('s', testArray[testArray.size() - offset--]);
    EXPECT_EQ('o', testArray[testArray.size() - offset--]);
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('e', testArray[testArray.size() - offset--]); 
    EXPECT_EQ(' ', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('v', testArray[testArray.size() - offset--]); 
    EXPECT_EQ('m', testArray[testArray.size() - offset--]); 

    auto fetchContext = ExplicitFetchContextASN(createNoTagFetchContext(testArray.begin()+newSize, testArray.end()));

    MMS::PDU::Elements::ObjectName<std::array<char, 128>> Fetched;
    ASSERT_TRUE(fetch(fetchContext, Fetched));
    ASSERT_EQ(0, getContextSize(fetchContext));
    ASSERT_EQ(CUT.choice, Fetched.choice);
    ASSERT_EQ(CUT.aa_specific, Fetched.aa_specific);
}