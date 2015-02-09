//-----------------------------------------------------------------------------
// <copyright file="ContextTraitsTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/17 05:11:43</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "MMSTags.h"
#include "ContextTraits.h"
#include "VisibleString.h"
#include "FixedSizeBitString.h"
#include "EmitContext.h"
using namespace MMS::Tags;
using namespace MMS;
using namespace MMS::Emitters;
/************************************//**
 * \brief Test fixture class
 ****************************************/
class ContextTraitsTest: public testing::Test
{

public:
    typedef ContextTraits<false> ExplicitContext;
    typedef ContextTraits<true> ImplicitContext;

    ContextTraitsTest()
    {
        
    }

};

TEST_F(ContextTraitsTest, TestExplicit)
{
	ASSERT_EQ(false, ExplicitContext::tImplicit::value);
}

TEST_F(ContextTraitsTest, TestResolveIntTag)
{
    int _int;
    char _char;
    long _long;
    long long _long_long;
    short _short;
    auto tag = ExplicitContext().getTag(_int);
    ASSERT_EQ(MMS_TAGS::INTEGER, tag);
    ASSERT_EQ(MMS_TAGS::INTEGER, ExplicitContext().getTag(_char));
    ASSERT_EQ(MMS_TAGS::INTEGER, ExplicitContext().getTag(_long));
    ASSERT_EQ(MMS_TAGS::INTEGER, ExplicitContext().getTag(_long_long));
    ASSERT_EQ(MMS_TAGS::INTEGER, ExplicitContext().getTag(_short));
}

TEST_F(ContextTraitsTest, TestResolveUnsignedTag)
{
    unsigned int _int;
    unsigned char _char;
    unsigned long _long;
    unsigned long long _long_long;
    unsigned short _short;
    auto tag = ExplicitContext().getTag(_int);
    ASSERT_EQ(MMS_TAGS::UNSIGNED, tag);
    ASSERT_EQ(MMS_TAGS::UNSIGNED, ExplicitContext().getTag(_char));
    ASSERT_EQ(MMS_TAGS::UNSIGNED, ExplicitContext().getTag(_long));
    ASSERT_EQ(MMS_TAGS::UNSIGNED, ExplicitContext().getTag(_long_long));
    ASSERT_EQ(MMS_TAGS::UNSIGNED, ExplicitContext().getTag(_short));
}

TEST_F(ContextTraitsTest, TestResolveVisibleString)
{
    DataTypes::VisibleString<std::string> a;
    auto tag = ExplicitContext().getTag(a);
    ASSERT_EQ(MMS_TAGS::VISIBLE_STRING, tag);
}

TEST_F(ContextTraitsTest, TestResolveBitString)
{
    DataTypes::FixedSizeBitString<10> FixedSize;
    std::vector<bool> varsize;
    ASSERT_EQ(MMS_TAGS::BITSTRING, ImplicitContext().getTag(FixedSize));
    ASSERT_EQ(MMS_TAGS::BITSTRING, ImplicitContext().getTag(varsize));
}

TEST_F(ContextTraitsTest, TestFloat)
{
    float _float;
    ASSERT_EQ(MMS_TAGS::FLOAT, ImplicitContext().getTag(_float));
    // Should stop compilation with static assert
//     double _real;
//     ASSERT_EQ(MMS_TAGS::FLOAT, ImplicitContext().getTag(_real));
}

TEST_F(ContextTraitsTest, TestImplicit)
{
    ASSERT_EQ(true, ImplicitContext::tImplicit::value);
}

TEST_F(ContextTraitsTest, TextContextGetters)
{
    std::array<unsigned char, 128> arr;
    auto ctx = createContext<ExplicitEmitContextASN>(arr);
}
