//-----------------------------------------------------------------------------
// <copyright file="ErrorClassTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/15 21:21:40</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include "ErrorClass.h"
#include "EmitContext.h"
#include "FetchContext.h"
#include "MMSTags.h"

using namespace MMS;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;
using namespace MMS::Extractors;
using MMS::PDU::Elements::ErrorClass;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class ErrorClassTest: public testing::Test
{

protected:
    std::array<unsigned char, 128> testArray;
public:
    ErrorClassTest()
    {
        testArray.fill(0);
    }

};

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(ErrorClassTest, TestFetchVmdState)
{
    auto ctx = createFetchContext(testArray);
    auto oldSize = getContextSize(ctx);
    ErrorClass Value;
    testArray[0] = 0x80;
    testArray[1] = 1;
    testArray[2] = (unsigned char)ErrorClass::class_vmd_state::vmd_operational_problem;

    ASSERT_TRUE(fetch(ctx, Value));
    EXPECT_EQ(0, Value.choice);
    EXPECT_EQ(ErrorClass::class_vmd_state::vmd_operational_problem, Value.vmd_state);

}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(ErrorClassTest, TestFetchApplicationReference)
{
    auto ctx = createFetchContext(testArray);
    auto oldSize = getContextSize(ctx);
    ErrorClass Value;
    testArray[0] = 0x81;
    testArray[1] = 1;
    testArray[2] = (unsigned char)ErrorClass::class_application_reference::connection_lost;

    ASSERT_TRUE(fetch(ctx, Value));
    EXPECT_EQ(1, Value.choice);
    EXPECT_EQ(ErrorClass::class_application_reference::connection_lost, Value.application_reference);
}

/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(ErrorClassTest, TestFetchDefinition)
{
    auto ctx = ExplicitFetchContextASN(createFetchContext(testArray));
    auto oldSize = getContextSize(ctx);
    ErrorClass Value;
    testArray[0] = 0x82;
    testArray[1] = 1;
    testArray[2] = (unsigned char)ErrorClass::class_definition::object_exists;

    ASSERT_TRUE(fetch(ctx, Value));
    EXPECT_EQ(2, Value.choice);
    EXPECT_EQ(ErrorClass::class_definition::object_exists, Value.definition);
}


/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(ErrorClassTest, TestEmit)
{
    auto ctx = ExplicitEmitContextASN(createMMSImplicitContext(testArray));
    auto oldSize = getContextSize(ctx);
    ErrorClass Value;
    Value.choice = ErrorClass::id_vmd_state;
    Value.vmd_state = ErrorClass::class_vmd_state::state_machine_id_invalid;
    ctx = emit(ctx, Value);
    auto newSize = getContextSize(ctx);
    auto offset = oldSize - newSize;

    ASSERT_EQ(3, offset);
    EXPECT_EQ(0x80, testArray[testArray.size() - offset--]) << "Le Tag";
    EXPECT_EQ(1, testArray[testArray.size() - offset--]) << "Length please";
    EXPECT_EQ((unsigned char)ErrorClass::class_vmd_state::state_machine_id_invalid, testArray[testArray.size() - offset--]) << "Value?";
}