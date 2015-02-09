//-----------------------------------------------------------------------------
// <copyright file="EvaluatorTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/30 04:04:20</created>
// <author>Vital</author>
// <summary>IEC project</summary>
/// \file Unit test for various length evaluators
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include <array>
#include <string>
#include "VisibleString.h"
#include "EmitContext.h"
#include "ContextMisc.h"
#include "MMSTags.h"
#include "VisibleStringEmitter.h"
#include "evaluator.h"

using namespace MMS;
using namespace MMS::DataTypes;
using namespace MMS::Emitters;
using namespace MMS::Emitters::Details;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class EvaluatorTest: public testing::Test
{
protected:
    std::array<unsigned char, 1024> testArray;
public:
    EvaluatorTest()
    {
        testArray.fill(0);
    }

};


/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(EvaluatorTest, TestnegativeIntExplicit)
{
    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, (long)~0x432567);
    ASSERT_EQ(5, oldSize - getContextSize(ctx));
    ASSERT_EQ(5, evaluate(ctx, (long)~0x432567));
}

TEST_F(EvaluatorTest, TestnegativeIntImplicit)
{
    auto ctx = createMMSImplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    ctx = emit(ctx, (long)~0x432567);
    ASSERT_EQ(4, oldSize - getContextSize(ctx));
    ASSERT_EQ(4, evaluate(ctx, (long)~0x432567));
}

/************************************//**
 * \brief Visible string test case
 ****************************************/
TEST_F(EvaluatorTest, TestVisibleStringExplicit)
{
    std::string value("testing...");

    VisibleString<std::string> CUT(value.c_str(), value.length());

    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(12, oldSize - newSize);
    ASSERT_EQ(oldSize - newSize, evaluate(ctx, CUT));
}

/************************************//**
 * \brief Visible string test case, implicit context
 ****************************************/
TEST_F(EvaluatorTest, TestVisibleStringImplicit)
{
    std::string value("testing...");

    VisibleString<std::string> CUT(value.c_str(), value.length());

    auto ctx = createMMSImplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(11, oldSize - newSize);
    ASSERT_EQ(oldSize - newSize, evaluate(ctx, CUT));
}

/************************************//**
 * \brief Visible string test case, long string
 ****************************************/
TEST_F(EvaluatorTest, TestVisibleStringLong)
{
    std::string value(300, 'a');

    VisibleString<std::string> CUT(value.c_str(), value.length());

    auto ctx = createMMSExplicitContext(testArray);
    auto oldSize = getContextSize(ctx);
    auto newSize = getContextSize(emit(ctx, CUT));
    EXPECT_EQ(304, oldSize - newSize);
    ASSERT_EQ(oldSize - newSize, evaluate(ctx, CUT));
}
