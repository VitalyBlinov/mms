//-----------------------------------------------------------------------------
// <copyright file="TagDefTest.h" company="Six Carrots Software">
//      Copyright (c) 2015 Six Carrots Software.
//      All rights reserved.
// </copyright>
// <created>2015/01/20 04:08:36</created>
// <author>Vital</author>
// <summary>IEC project</summary>
//-----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "UniversalClass.h"

using namespace ASN1::Tags;

/************************************//**
 * \brief Test fixture class
 ****************************************/
class TagDefTest: public testing::Test
{

public:
    TagDefTest()
    {
        
    }

};
/************************************//**
 * \brief First test case
 ****************************************/
TEST_F(TagDefTest, TestIntDefined)
{
	ASSERT_FALSE(ASN1::Tags::TagDef<int>::TAG == -1);
}

TEST_F(TagDefTest, TestVectorNotDefined)
{
    ASSERT_TRUE(ASN1::Tags::TagDef<std::vector<int>>::TAG == -1);
}
